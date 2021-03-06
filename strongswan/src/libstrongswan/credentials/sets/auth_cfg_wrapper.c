/*
 * Copyright (C) 2008-2009 Martin Willi
 * Copyright (C) 2008 Tobias Brunner
 * Hochschule fuer Technik Rapperswil
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.  See <http://www.fsf.org/copyleft/gpl.txt>.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 * for more details.
 */

#include <library.h>
#include <utils/debug.h>

#include "auth_cfg_wrapper.h"

typedef struct private_auth_cfg_wrapper_t private_auth_cfg_wrapper_t;

/**
 * private data of auth_cfg_wrapper
 */
struct private_auth_cfg_wrapper_t {

	/**
	 * public functions
	 */
	auth_cfg_wrapper_t public;

	/**
	 * wrapped auth info
	 */
	auth_cfg_t *auth;
};

/**
 * enumerator for auth_cfg_wrapper_t.create_cert_enumerator()
 */
typedef struct {
	/** implements enumerator_t */
	enumerator_t public;
	/** inner enumerator from auth_cfg */
	enumerator_t *inner;
	/** wrapped auth round */
	auth_cfg_t *auth;
	/** enumerated cert type */
	certificate_type_t cert;
	/** enumerated key type */
	key_type_t key;
	/** enumerated id */
	identification_t *id;
} wrapper_enumerator_t;

/**
 * Tries to fetch a certificate that was supplied as "Hash and URL"
 * (replaces rule type and value in place).
 */
static bool fetch_cert(wrapper_enumerator_t *enumerator,
					   auth_rule_t *rule, void **value)
{
	char *url = (char*)*value;
	if (!url)
	{
		/* fetching the certificate previously failed */
		return FALSE;
	}

	chunk_t data;
	certificate_t *cert;

	DBG1(DBG_CFG, "  fetching certificate from '%s' ...", url);
	if (lib->fetcher->fetch(lib->fetcher, url, &data, FETCH_END) != SUCCESS)
	{
		DBG1(DBG_CFG, "  fetching certificate failed");
		/* we set the item to NULL, so we can skip it */
		enumerator->auth->replace(enumerator->auth, enumerator->inner,
								  *rule, NULL);
		return FALSE;
	}

	if (*rule == AUTH_HELPER_BUNDLE_HASH_URL) {
		char *bundle_ptr=data.ptr;
		char *next_ptr = NULL;
		chunk_t im_data; 
		int bundle_len = data.len;
		//	obtain Cert from URL and change the type to Certificate
		//	in order to support multiple certificates in bundle, we chage add more here
		//	use enumerator->auth->add(enumerator->auth, AUTH_HELPER_IM_CERT, cert);
		//		e.g auth->add(auth, AUTH_HELPER_SUBJECT_CERT, cert);

		DBG1(DBG_LIB, "Go parse ... PEM");
		do {
			next_ptr = strstr(bundle_ptr+1, "-----BEGIN CERTIFICATE-----");
			im_data.ptr = bundle_ptr;
			if (next_ptr) {
				im_data.len = (size_t)next_ptr - (size_t)bundle_ptr;
				bundle_len -= im_data.len;
			} else {
				im_data.len = bundle_len;
			}
//			DBG1(DBG_LIB, "Go parse one by one ... : %B", &im_data);
			cert = lib->creds->create(lib->creds, CRED_CERTIFICATE, CERT_X509, BUILD_BLOB_PEM, im_data, BUILD_END);		

			if (!cert) {
				break;
			}

			DBG1(DBG_CFG, "  fetched certificate \"%Y\"", cert->get_subject(cert));
			lib->credmgr->cache_cert(lib->credmgr, cert);

			if (bundle_ptr != (char *)data.ptr) {
				enumerator->auth->add(enumerator->auth, AUTH_HELPER_IM_CERT, cert);
			} else {
				enumerator->auth->replace(enumerator->auth, enumerator->inner, AUTH_HELPER_SUBJECT_CERT, cert->get_ref(cert));
				*value = cert;
			}
			bundle_ptr = next_ptr;
		} while (next_ptr);
		free(data.ptr);
		
		if (!cert)
		{
			DBG1(DBG_CFG, "  parsing fetched certificate failed, only PEM format support");
			/* we set the item to NULL, so we can skip it */
			enumerator->auth->replace(enumerator->auth, enumerator->inner, *rule, NULL);
			return FALSE;
		}

	} else {
		DBG1(DBG_LIB, "Go parse ... DER");
		cert = lib->creds->create(lib->creds, CRED_CERTIFICATE, CERT_X509, BUILD_BLOB_ASN1_DER, data, BUILD_END);
		if (!cert) {
			DBG1(DBG_LIB, "Go parse ... PEM");
			cert = lib->creds->create(lib->creds, CRED_CERTIFICATE, CERT_X509, BUILD_BLOB_PEM, data, BUILD_END);
		}
		free(data.ptr);

		if (!cert)
		{
			DBG1(DBG_CFG, "  parsing fetched certificate failed");
			/* we set the item to NULL, so we can skip it */
			enumerator->auth->replace(enumerator->auth, enumerator->inner, *rule, NULL);
			return FALSE;
		}

		DBG1(DBG_CFG, "  fetched certificate \"%Y\"", cert->get_subject(cert));
		lib->credmgr->cache_cert(lib->credmgr, cert);

		if (*rule == AUTH_HELPER_IM_HASH_URL)
		{
			*rule = AUTH_HELPER_IM_CERT;
		}
		else
		{
			*rule = AUTH_HELPER_SUBJECT_CERT;
		}
		*value = cert;
		enumerator->auth->replace(enumerator->auth, enumerator->inner,
								  *rule, cert->get_ref(cert));
	}

	return TRUE;
}

/**
 * enumerate function for wrapper_enumerator_t
 */
static bool enumerate(wrapper_enumerator_t *this, certificate_t **cert)
{
	auth_rule_t rule;
	certificate_t *current;
	public_key_t *public;

	while (this->inner->enumerate(this->inner, &rule, &current))
	{
		if (rule == AUTH_HELPER_IM_HASH_URL ||
			rule == AUTH_HELPER_SUBJECT_HASH_URL || 
			rule == AUTH_HELPER_BUNDLE_HASH_URL )
		{	/* on-demand fetching of hash and url certificates */
			if (!fetch_cert(this, &rule, (void**)&current))
			{
				continue;
			}
		}
		else if (rule != AUTH_HELPER_SUBJECT_CERT &&
				 rule != AUTH_HELPER_IM_CERT &&
				 rule != AUTH_HELPER_REVOCATION_CERT)
		{	/* handle only HELPER certificates */
			continue;
		}
		if (this->cert != CERT_ANY && this->cert != current->get_type(current))
		{	/* CERT type requested, but does not match */
			continue;
		}
		public = current->get_public_key(current);
		if (this->key != KEY_ANY && !public)
		{	/* key type requested, but no public key */
			DESTROY_IF(public);
			continue;
		}
		if (this->key != KEY_ANY && public && this->key != public->get_type(public))
		{	/* key type requested, but public key has another type */
			DESTROY_IF(public);
			continue;
		}
		DESTROY_IF(public);
		if (this->id && !current->has_subject(current, this->id))
		{	/* subject requested, but does not match */
			continue;
		}
		*cert = current;
		return TRUE;
	}
	return FALSE;
}

/**
 * destroy function for wrapper_enumerator_t
 */
static void wrapper_enumerator_destroy(wrapper_enumerator_t *this)
{
	this->inner->destroy(this->inner);
	free(this);
}

METHOD(credential_set_t, create_enumerator, enumerator_t*,
	private_auth_cfg_wrapper_t *this, certificate_type_t cert, key_type_t key,
	identification_t *id, bool trusted)
{
	wrapper_enumerator_t *enumerator;

	if (trusted)
	{
		return NULL;
	}
	enumerator = malloc_thing(wrapper_enumerator_t);
	enumerator->auth = this->auth;
	enumerator->cert = cert;
	enumerator->key = key;
	enumerator->id = id;
	enumerator->inner = this->auth->create_enumerator(this->auth);
	enumerator->public.enumerate = (void*)enumerate;
	enumerator->public.destroy = (void*)wrapper_enumerator_destroy;
	return &enumerator->public;
}

METHOD(auth_cfg_wrapper_t, destroy, void,
	private_auth_cfg_wrapper_t *this)
{
	free(this);
}

/*
 * see header file
 */
auth_cfg_wrapper_t *auth_cfg_wrapper_create(auth_cfg_t *auth)
{
	private_auth_cfg_wrapper_t *this;

	INIT(this,
		.public = {
			.set = {
				.create_cert_enumerator = _create_enumerator,
				.create_shared_enumerator = (void*)return_null,
				.create_cdp_enumerator = (void*)return_null,
				.cache_cert = (void*)nop,
			},
			.destroy = _destroy,
		},
		.auth = auth,
	);

	return &this->public;
}
