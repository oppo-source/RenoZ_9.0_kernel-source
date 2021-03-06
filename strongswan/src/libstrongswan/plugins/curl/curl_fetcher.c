/*
 * Copyright (C) 2008 Martin Willi
 * Copyright (C) 2007 Andreas Steffen
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

#include <curl/curl.h>

#include <library.h>
#include <utils/debug.h>

#include "curl_fetcher.h"
#ifdef STRONGSWAN_UNIT_TEST
#include "ut_epdg_utils.h"
#endif


#define CONNECT_TIMEOUT 10

typedef struct private_curl_fetcher_t private_curl_fetcher_t;

/**
 * private data of a curl_fetcher_t object.
 */
struct private_curl_fetcher_t {
	/**
	 * Public data
	 */
	curl_fetcher_t public;

	/**
	 * CURL handle
	 */
	CURL* curl;

	/**
	 * Optional HTTP headers
	 */
	struct curl_slist *headers;

	/**
	 * Callback function
	 */
	fetcher_callback_t cb;

	/**
	 * Timeout for a transfer
	 */
	long timeout;
};

/**
 * Data to pass to curl callback
 */
typedef struct {
	fetcher_callback_t cb;
	void *user;
} cb_data_t;

/**
 * Curl callback function, invokes fetcher_callback_t function
 */
static size_t curl_cb(void *ptr, size_t size, size_t nmemb, cb_data_t *data)
{
	size_t realsize = size * nmemb;

	if (data->cb(data->user, chunk_create(ptr, realsize)))
	{
		return realsize;
	}
	return 0;
}

METHOD(fetcher_t, fetch, status_t,
	private_curl_fetcher_t *this, char *uri, void *userdata)
{
	char error[CURL_ERROR_SIZE], *enc_uri;
	status_t status;
	cb_data_t data = {
		.cb = this->cb,
		.user = userdata,
	};

	if (this->cb == fetcher_default_callback)
	{
		*(chunk_t*)userdata = chunk_empty;
	}

	/* the URI has to be URL-encoded, we only replace spaces as replacing other
	 * characters (e.g. '/' or ':') would render the URI invalid */
	enc_uri = strreplace(uri, " ", "%20");

	if (curl_easy_setopt(this->curl, CURLOPT_URL, enc_uri) != CURLE_OK)
	{	/* URL type not supported by curl */
		status = NOT_SUPPORTED;
		goto out;
	}
	curl_easy_setopt(this->curl, CURLOPT_ERRORBUFFER, error);
	curl_easy_setopt(this->curl, CURLOPT_FAILONERROR, TRUE);
	curl_easy_setopt(this->curl, CURLOPT_NOSIGNAL, TRUE);
	if (this->timeout)
	{
		curl_easy_setopt(this->curl, CURLOPT_TIMEOUT, this->timeout);
	}
	curl_easy_setopt(this->curl, CURLOPT_CONNECTTIMEOUT, CONNECT_TIMEOUT);
	curl_easy_setopt(this->curl, CURLOPT_WRITEFUNCTION, (void*)curl_cb);
	curl_easy_setopt(this->curl, CURLOPT_WRITEDATA, &data);
	if (this->headers)
	{
		curl_easy_setopt(this->curl, CURLOPT_HTTPHEADER, this->headers);
	}

	DBG2(DBG_LIB, "  sending http request to '%s'...", uri);
#ifdef STRONGSWAN_UNIT_TEST
	switch (ut_curl_easy_perform(enc_uri, (void*)curl_cb, &data))
#else
	switch (curl_easy_perform(this->curl))
#endif
	{
		case CURLE_UNSUPPORTED_PROTOCOL:
			status = NOT_SUPPORTED;
			break;
		case CURLE_OK:
			status = SUCCESS;
			break;
		default:
			DBG1(DBG_LIB, "libcurl http request failed: %s", error);
			status = FAILED;
			break;
	}

out:
	if (enc_uri != uri)
	{
		free(enc_uri);
	}
	return status;
}

METHOD(fetcher_t, set_option, bool,
	private_curl_fetcher_t *this, fetcher_option_t option, ...)
{
	bool supported = TRUE;
	va_list args;

	va_start(args, option);
	switch (option)
	{
		case FETCH_REQUEST_DATA:
		{
			chunk_t data = va_arg(args, chunk_t);

			curl_easy_setopt(this->curl, CURLOPT_POSTFIELDS, (char*)data.ptr);
			curl_easy_setopt(this->curl, CURLOPT_POSTFIELDSIZE, data.len);
			break;
		}
		case FETCH_REQUEST_TYPE:
		{
			char header[BUF_LEN];
			char *request_type = va_arg(args, char*);

			snprintf(header, BUF_LEN, "Content-Type: %s", request_type);
			this->headers = curl_slist_append(this->headers, header);
			break;
		}
		case FETCH_REQUEST_HEADER:
		{
			char *header = va_arg(args, char*);

			this->headers = curl_slist_append(this->headers, header);
			break;
		}
		case FETCH_HTTP_VERSION_1_0:
		{
			curl_easy_setopt(this->curl, CURLOPT_HTTP_VERSION,
							 CURL_HTTP_VERSION_1_0);
			break;
		}
		case FETCH_TIMEOUT:
		{
			this->timeout = va_arg(args, u_int);
			break;
		}
		case FETCH_CALLBACK:
		{
			this->cb = va_arg(args, fetcher_callback_t);
			break;
		}
		case FETCH_SOURCEIP:
		{
			char buf[64];

			snprintf(buf, sizeof(buf), "%H", va_arg(args, host_t*));
			supported = curl_easy_setopt(this->curl, CURLOPT_INTERFACE,
										 buf) == CURLE_OK;
			break;
		}
		default:
			supported = FALSE;
			break;
	}
	va_end(args);
	return supported;
}

METHOD(fetcher_t, destroy, void,
	private_curl_fetcher_t *this)
{
	curl_slist_free_all(this->headers);
	curl_easy_cleanup(this->curl);
	free(this);
}

/*
 * Described in header.
 */
curl_fetcher_t *curl_fetcher_create()
{
	private_curl_fetcher_t *this;

	INIT(this,
		.public = {
			.interface = {
				.fetch = _fetch,
				.set_option = _set_option,
				.destroy = _destroy,
			},
		},
		.curl = curl_easy_init(),
		.cb = fetcher_default_callback,
	);

	if (!this->curl)
	{
		free(this);
		return NULL;
	}
	return &this->public;
}
