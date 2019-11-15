/* C code produced by gperf version 3.0.4 */
/* Command-line: /usr/bin/gperf -m 10 -C -G -D -t  */
/* Computed positions: -k'2-3,6,$' */

#if !((' ' == 32) && ('!' == 33) && ('"' == 34) && ('#' == 35) \
      && ('%' == 37) && ('&' == 38) && ('\'' == 39) && ('(' == 40) \
      && (')' == 41) && ('*' == 42) && ('+' == 43) && (',' == 44) \
      && ('-' == 45) && ('.' == 46) && ('/' == 47) && ('0' == 48) \
      && ('1' == 49) && ('2' == 50) && ('3' == 51) && ('4' == 52) \
      && ('5' == 53) && ('6' == 54) && ('7' == 55) && ('8' == 56) \
      && ('9' == 57) && (':' == 58) && (';' == 59) && ('<' == 60) \
      && ('=' == 61) && ('>' == 62) && ('?' == 63) && ('A' == 65) \
      && ('B' == 66) && ('C' == 67) && ('D' == 68) && ('E' == 69) \
      && ('F' == 70) && ('G' == 71) && ('H' == 72) && ('I' == 73) \
      && ('J' == 74) && ('K' == 75) && ('L' == 76) && ('M' == 77) \
      && ('N' == 78) && ('O' == 79) && ('P' == 80) && ('Q' == 81) \
      && ('R' == 82) && ('S' == 83) && ('T' == 84) && ('U' == 85) \
      && ('V' == 86) && ('W' == 87) && ('X' == 88) && ('Y' == 89) \
      && ('Z' == 90) && ('[' == 91) && ('\\' == 92) && (']' == 93) \
      && ('^' == 94) && ('_' == 95) && ('a' == 97) && ('b' == 98) \
      && ('c' == 99) && ('d' == 100) && ('e' == 101) && ('f' == 102) \
      && ('g' == 103) && ('h' == 104) && ('i' == 105) && ('j' == 106) \
      && ('k' == 107) && ('l' == 108) && ('m' == 109) && ('n' == 110) \
      && ('o' == 111) && ('p' == 112) && ('q' == 113) && ('r' == 114) \
      && ('s' == 115) && ('t' == 116) && ('u' == 117) && ('v' == 118) \
      && ('w' == 119) && ('x' == 120) && ('y' == 121) && ('z' == 122) \
      && ('{' == 123) && ('|' == 124) && ('}' == 125) && ('~' == 126))
/* The character set is not based on ISO-646.  */
error "gperf generated tables don't work with this execution character set. Please report a bug to <bug-gnu-gperf@gnu.org>."
#endif


/*
 * Copyright (C) 2005 Andreas Steffen
 * Hochschule fuer Technik Rapperswil, Switzerland
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

#include <string.h>

#include "keywords.h"

struct kw_entry {
    char *name;
    kw_token_t token;
};

#define TOTAL_KEYWORDS 194
#define MIN_WORD_LENGTH 2
#define MAX_WORD_LENGTH 20
#define MIN_HASH_VALUE 9
#define MAX_HASH_VALUE 386
/* maximum key range = 378, duplicates = 0 */

#ifdef __GNUC__
__inline
#else
#ifdef __cplusplus
inline
#endif
#endif
static unsigned int
hash (str, len)
     register const char *str;
     register unsigned int len;
{
  static const unsigned short asso_values[] =
    {
      387, 387, 387, 387, 387, 387, 387, 387, 387, 387,
      387, 387, 387, 387, 387, 387, 387, 387, 387, 387,
      387, 387, 387, 387, 387, 387, 387, 387, 387, 387,
      387, 387, 387, 387, 387, 387, 387, 387, 387, 387,
      387, 387, 387, 387, 387, 387, 387, 387, 387,  13,
      187, 387,  65, 387,  13, 387, 387, 387, 387, 387,
      387, 387, 387, 387, 387, 387, 387, 387, 387, 387,
      387, 387, 387, 387, 387, 387, 387, 387, 387, 387,
      387, 387, 387, 387, 387, 387, 387, 387, 387, 387,
      387, 387, 387, 387, 387,  54, 387,  22,   2, 121,
       51,   4,   9,   0,  93,   0, 387, 157,  73, 196,
       18,  85,  56,   2,  13,   0,  12, 147,  36, 387,
        0,  50,   4, 387, 387, 387, 387, 387, 387, 387,
      387, 387, 387, 387, 387, 387, 387, 387, 387, 387,
      387, 387, 387, 387, 387, 387, 387, 387, 387, 387,
      387, 387, 387, 387, 387, 387, 387, 387, 387, 387,
      387, 387, 387, 387, 387, 387, 387, 387, 387, 387,
      387, 387, 387, 387, 387, 387, 387, 387, 387, 387,
      387, 387, 387, 387, 387, 387, 387, 387, 387, 387,
      387, 387, 387, 387, 387, 387, 387, 387, 387, 387,
      387, 387, 387, 387, 387, 387, 387, 387, 387, 387,
      387, 387, 387, 387, 387, 387, 387, 387, 387, 387,
      387, 387, 387, 387, 387, 387, 387, 387, 387, 387,
      387, 387, 387, 387, 387, 387, 387, 387, 387, 387,
      387, 387, 387, 387, 387, 387, 387, 387, 387, 387,
      387, 387, 387, 387, 387, 387
    };
  register int hval = len;

  switch (hval)
    {
      default:
        hval += asso_values[(unsigned char)str[5]];
      /*FALLTHROUGH*/
      case 5:
      case 4:
      case 3:
        hval += asso_values[(unsigned char)str[2]];
      /*FALLTHROUGH*/
      case 2:
        hval += asso_values[(unsigned char)str[1]];
        break;
    }
  return hval + asso_values[(unsigned char)str[len - 1]];
}

static const struct kw_entry wordlist[] =
  {
    {"rightimei",         KW_RIGHTIMEI},
    {"rightgroups",       KW_RIGHTGROUPS},
    {"pfs",               KW_PFS_DEPRECATED},
    {"aggressive",        KW_AGGRESSIVE},
    {"right",             KW_RIGHT},
    {"lifetime",          KW_KEYLIFE},
    {"rightsourceif",     KW_RIGHTSOURCEIF},
    {"rightsubnet",       KW_RIGHTSUBNET},
    {"rightikeport",      KW_RIGHTIKEPORT},
    {"rightsendcert",     KW_RIGHTSENDCERT},
    {"rightintsubnet",    KW_RIGHTINTSUBNET},
    {"rightimeiformat",   KW_RIGHTIMEIFORMAT},
    {"rightikeportnatt",  KW_RIGHTIKEPORTNATT},
    {"left",              KW_LEFT},
    {"rightidr_apn",      KW_RIGHTIDR_APN},
    {"uniqueids",         KW_UNIQUEIDS},
    {"rightsubnetwithin", KW_RIGHTSUBNET},
    {"leftgroups",        KW_LEFTGROUPS},
    {"leftcert",          KW_LEFTCERT},
    {"leftdns",           KW_LEFTDNS},
    {"max_redirects",   KW_MAX_REDIRECTS },
    {"leftsendcert",      KW_LEFTSENDCERT},
    {"lifepackets",       KW_LIFEPACKETS},
    {"keep_alive",        KW_SETUP_DEPRECATED},
    {"certuribase",       KW_CERTURIBASE},
    {"retrans_tries",     KW_RETRANS_TRIES},
    {"interfaces",        KW_SETUP_DEPRECATED},
    {"retrans_base",      KW_RETRANS_BASE},
    {"leftprotoport",     KW_LEFTPROTOPORT},
    {"interface",         KW_INTERFACE},
    {"virtual_private",   KW_SETUP_DEPRECATED},
    {"server_nocert",     KW_SERVER_NOCERT},
    {"leftintsubnet",     KW_LEFTINTSUBNET},
    {"rightid",           KW_RIGHTID},
    {"rightdns",          KW_RIGHTDNS},
    {"mark_in",           KW_MARK_IN},
    {"rightsigkey",       KW_RIGHTSIGKEY},
    {"reqid",             KW_REQID},
    {"leftca",            KW_LEFTCA},
    {"marginbytes",       KW_MARGINBYTES},
    {"keyingtries",       KW_KEYINGTRIES},
    {"marginpackets",     KW_MARGINPACKETS},
    {"margintime",        KW_REKEYMARGIN},
    {"lifebytes",         KW_LIFEBYTES},
    {"rightsourceip",     KW_RIGHTSOURCEIP},
    {"fragmentation",     KW_FRAGMENTATION},
    {"leftsigkey",        KW_LEFTSIGKEY},
    {"keylife",           KW_KEYLIFE},
    {"rightpcscf",        KW_RIGHTPCSCF},
    {"leftrsasigkey",     KW_LEFTSIGKEY},
    {"rightrsasigkey",    KW_RIGHTSIGKEY},
    {"redirect_enable",   KW_REDIRECT_ENABLE },
    {"use_cfg_vip",       KW_USE_CFG_VIP},
    {"leftcertpolicy",    KW_LEFTCERTPOLICY},
    {"rightprotoport",    KW_RIGHTPROTOPORT},
    {"leftnexthop",       KW_LEFT_DEPRECATED},
    {"rightallowany",     KW_RIGHTALLOWANY},
    {"rightnexthop",      KW_RIGHT_DEPRECATED},
    {"rightforcetsi64",   KW_RIGHTFORCETSI64},
    {"redirect_loop_detect",  KW_REDIRECT_LOOP_DETECT},
    {"crluri",            KW_CRLURI},
    {"leftidr_apn",       KW_LEFTIDR_APN},
    {"mediation",         KW_MEDIATION},
    {"rightfirewall",     KW_RIGHTFIREWALL},
    {"leftupdown",        KW_LEFTUPDOWN},
    {"leftfirewall",      KW_LEFTFIREWALL},
    {"rightforcetsifull", KW_RIGHTFORCETSIFULL},
    {"inactivity",        KW_INACTIVITY},
    {"mobike",	           KW_MOBIKE},
    {"strictcrlpolicy",   KW_STRICTCRLPOLICY},
    {"crluri1",           KW_CRLURI},
    {"ldapbase",          KW_CA_DEPRECATED},
    {"righthostaccess",   KW_RIGHTHOSTACCESS},
    {"device_identity",   KW_DEVICE_IDENTITY},
    {"certreq_critical",  KW_CERTREQ_CRITICAL},
    {"lefthostaccess",    KW_LEFTHOSTACCESS},
    {"forceencaps",       KW_FORCEENCAPS},
    {"type",              KW_TYPE},
    {"esp",               KW_ESP},
    {"leftsourceif",      KW_LEFTSOURCEIF},
    {"leftid",            KW_LEFTID},
    {"me_peerid",         KW_ME_PEERID},
    {"hashandurl",        KW_HASHANDURL},
    {"rightauth",         KW_RIGHTAUTH},
    {"mediated_by",       KW_MEDIATED_BY},
    {"retrans_to",        KW_RETRANS_TO},
    {"reauth_mbb",        KW_REAUTH_MBB},
    {"nat_traversal",     KW_SETUP_DEPRECATED},
    {"klipsdebug",        KW_SETUP_DEPRECATED},
    {"detach_timeout",    KW_DETACH_TIMEOUT},
    {"rightcustcpimei",   KW_RIGHTCUSTCPIMEI},
    {"eap",               KW_CONN_DEPRECATED},
    {"fast_reauth",       KW_FAST_REAUTH},
    {"mark_out",          KW_MARK_OUT},
    {"ocspuri",           KW_OCSPURI},
    {"rightcert",         KW_RIGHTCERT},
    {"hidetos",           KW_SETUP_DEPRECATED},
    {"charondebug",       KW_CHARONDEBUG},
    {"keepalivedelay",    KW_KEEPALIVEDELAY},
    {"dpdaction",         KW_DPDACTION},
    {"leftallowany",      KW_LEFTALLOWANY},
    {"rightca",           KW_RIGHTCA},
    {"rightcustcppcscf6", KW_RIGHTCUSTCPPCSCF6},
    {"leftpcscf",         KW_LEFTPCSCF},
    {"installpolicy",     KW_INSTALLPOLICY},
    {"ocspuri1",          KW_OCSPURI},
    {"charonstart",       KW_SETUP_DEPRECATED},
    {"aaa_identity",      KW_AAA_IDENTITY},
    {"pfsgroup",          KW_PFS_DEPRECATED},
    {"no_initct",         KW_NO_INIT_CONTACT},
    {"also",              KW_ALSO},
    {"leftsourceip",      KW_LEFTSOURCEIP},
    {"ike",               KW_IKE},
    {"force_keepalive",   KW_SETUP_DEPRECATED},
    {"rightintnetmask",   KW_RIGHTINTNETMASK},
    {"cacert",            KW_CACERT},
    {"leftcustcpimei",    KW_LEFTCUSTCPIMEI},
    {"rightupdown",       KW_RIGHTUPDOWN},
    {"leftforcetsi64",    KW_LEFTFORCETSI64},
    {"ldaphost",          KW_CA_DEPRECATED},
    {"crlcheckinterval",  KW_SETUP_DEPRECATED},
    {"packetdefault",     KW_SETUP_DEPRECATED},
    {"ocsp",              KW_OCSP},
    {"leftsubnet",        KW_LEFTSUBNET},
    {"rekeyfuzz",         KW_REKEYFUZZ},
    {"ikelifetime",       KW_IKELIFETIME},
    {"rightcertpolicy",   KW_RIGHTCERTPOLICY},
    {"leftforcetsifull",  KW_LEFTFORCETSIFULL},
    {"ah",                KW_AH},
    {"leftcustcppcscf6",  KW_LEFTCUSTCPPCSCF6},
    {"keyexchange",       KW_KEYEXCHANGE},
    {"eap_identity",      KW_EAP_IDENTITY},
    {"pcscf_restore",     KW_PCSCF_RESTORE},
    {"leftikeport",       KW_LEFTIKEPORT},
    {"leftsubnetwithin",  KW_LEFTSUBNET},
    {"rightid2",          KW_RIGHTID2},
    {"mark",              KW_MARK},
    {"leftikeportnatt",   KW_LEFTIKEPORTNATT},
    {"overridemtu",       KW_SETUP_DEPRECATED},
    {"rightgroups2",      KW_RIGHTGROUPS2},
    {"leftintnetmask",    KW_LEFTINTNETMASK},
    {"rightcustcppcscf4", KW_RIGHTCUSTCPPCSCF4},
    {"encrkeydisplay",    KW_ENCRKEYDISPLAY},
    {"closeaction",       KW_CLOSEACTION},
    {"liveness_check",    KW_LIVENESS_CHECK},
    {"leftcert2",         KW_LEFTCERT2},
    {"rekey",             KW_REKEY},
    {"leftimei",          KW_LEFTIMEI},
    {"reauth",            KW_REAUTH},
    {"rightauth2",        KW_RIGHTAUTH2},
    {"fragicmp",          KW_SETUP_DEPRECATED},
    {"emergency_numbers",  KW_EMERGENCY_NUMBERS},
    {"leftgroups2",       KW_LEFTGROUPS2},
    {"leftca2",           KW_LEFTCA2},
    {"modeconfig",        KW_MODECONFIG},
    {"plutostderrlog",    KW_SETUP_DEPRECATED},
    {"leftimeiformat",    KW_LEFTIMEIFORMAT},
    {"dpddelay",          KW_DPDDELAY},
    {"wdrv_keepalive",    KW_WDRV_KEEPALIVE},
    {"leftcustcppcscf4",  KW_LEFTCUSTCPPCSCF4},
    {"plutostart",        KW_SETUP_DEPRECATED},
    {"auto",              KW_AUTO},
    {"postpluto",         KW_SETUP_DEPRECATED},
    {"dpd_noreply",       KW_DPD_NOREPLY},
    {"tfc",               KW_TFC},
    {"no_eaponly",        KW_NO_EAP_ONLY},
    {"prepluto",          KW_SETUP_DEPRECATED},
    {"leftid2",           KW_LEFTID2},
    {"leftauth",          KW_LEFTAUTH},
    {"authby",            KW_AUTHBY},
    {"xauth",             KW_XAUTH},
    {"nocrsend",          KW_SETUP_DEPRECATED},
    {"cachecrls",         KW_CACHECRLS},
    {"skipcheckcert",     KW_SKIPCHECKCERT},
    {"crluri2",           KW_CRLURI2},
    {"plutodebug",        KW_SETUP_DEPRECATED},
    {"xauth_identity",    KW_XAUTH_IDENTITY},
    {"compress",          KW_COMPRESS},
    {"addrchg_reauth",    KW_ADDRCHG_REAUTH},
    {"oostimeout",        KW_OOSTIMEOUT},
    {"pkcs11initargs",    KW_PKCS11_DEPRECATED},
    {"pkcs11module",      KW_PKCS11_DEPRECATED},
    {"pkcs11keepstate",   KW_PKCS11_DEPRECATED},
    {"skipcheckid",       KW_SKIPCHECKID},
    {"rightca2",          KW_RIGHTCA2},
    {"rightcert2",        KW_RIGHTCERT2},
    {"wsharkfiledump",    KW_WSHARKFILEDUMP},
    {"dpdtimeout",        KW_DPDTIMEOUT},
    {"ocspuri2",          KW_OCSPURI2},
    {"ikedscp",           KW_IKEDSCP,},
    {"pkcs11proxy",       KW_PKCS11_DEPRECATED},
    {"leftauth2",         KW_LEFTAUTH2},
    {"dumpdir",           KW_SETUP_DEPRECATED},
    {"rekeymargin",       KW_REKEYMARGIN}
  };

static const short lookup[] =
  {
     -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,   0,
     -1,   1,   2,  -1,   3,  -1,  -1,   4,  -1,  -1,
     -1,   5,   6,   7,   8,   9,  10,  11,  12,  13,
     14,  15,  -1,  -1,  -1,  16,  17,  18,  19,  20,
     -1,  21,  22,  -1,  23,  24,  -1,  25,  -1,  26,
     27,  28,  29,  -1,  30,  31,  32,  -1,  33,  34,
     35,  36,  37,  38,  39,  40,  41,  42,  43,  44,
     45,  -1,  -1,  46,  47,  48,  49,  50,  51,  -1,
     52,  53,  54,  -1,  55,  56,  57,  -1,  -1,  58,
     -1,  59,  60,  61,  62,  63,  -1,  64,  65,  66,
     67,  68,  69,  -1,  -1,  -1,  70,  71,  72,  73,
     74,  -1,  75,  76,  77,  78,  -1,  -1,  -1,  79,
     -1,  80,  81,  82,  83,  -1,  -1,  -1,  84,  85,
     -1,  86,  -1,  87,  88,  89,  90,  91,  -1,  92,
     93,  94,  95,  96,  97,  98,  99,  -1, 100,  -1,
    101, 102, 103,  -1, 104, 105, 106, 107, 108,  -1,
    109,  -1, 110,  -1,  -1,  -1, 111,  -1, 112,  -1,
     -1, 113, 114, 115, 116,  -1, 117, 118, 119, 120,
    121, 122, 123, 124,  -1, 125, 126, 127, 128, 129,
    130, 131, 132, 133, 134, 135, 136, 137, 138, 139,
     -1,  -1, 140, 141,  -1,  -1,  -1, 142,  -1, 143,
     -1, 144,  -1, 145,  -1,  -1, 146, 147, 148, 149,
    150, 151,  -1,  -1, 152,  -1,  -1,  -1,  -1, 153,
     -1, 154,  -1,  -1, 155, 156,  -1,  -1, 157, 158,
     -1, 159, 160,  -1,  -1,  -1,  -1,  -1, 161,  -1,
     -1,  -1, 162, 163, 164, 165,  -1, 166, 167,  -1,
     -1, 168,  -1,  -1,  -1, 169,  -1, 170,  -1, 171,
     -1,  -1,  -1, 172,  -1, 173,  -1,  -1,  -1,  -1,
    174, 175,  -1,  -1,  -1,  -1,  -1, 176,  -1,  -1,
     -1,  -1,  -1, 177,  -1,  -1,  -1,  -1,  -1,  -1,
     -1,  -1, 178, 179,  -1, 180,  -1, 181,  -1,  -1,
    182,  -1, 183,  -1,  -1,  -1, 184,  -1, 185,  -1,
    186,  -1,  -1,  -1,  -1, 187,  -1,  -1,  -1, 188,
     -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
     -1,  -1,  -1,  -1,  -1, 189,  -1,  -1,  -1,  -1,
     -1,  -1, 190,  -1,  -1,  -1, 191,  -1,  -1,  -1,
     -1,  -1,  -1, 192,  -1,  -1,  -1,  -1,  -1,  -1,
     -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
     -1,  -1,  -1,  -1,  -1,  -1, 193
  };

#ifdef __GNUC__
__inline
#if defined __GNUC_STDC_INLINE__ || defined __GNUC_GNU_INLINE__
__attribute__ ((__gnu_inline__))
#endif
#endif
const struct kw_entry *
in_word_set (str, len)
     register const char *str;
     register unsigned int len;
{
  if (len <= MAX_WORD_LENGTH && len >= MIN_WORD_LENGTH)
    {
      register int key = hash (str, len);

      if (key <= MAX_HASH_VALUE && key >= 0)
        {
          register int index = lookup[key];

          if (index >= 0)
            {
              register const char *s = wordlist[index].name;

              if (*str == *s && !strcmp (str + 1, s + 1))
                return &wordlist[index];
            }
        }
    }
  return 0;
}
