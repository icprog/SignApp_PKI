#ifndef _RSA_H_
#define _RSA_H_

#include <string.h>
#include "PriKeyDownload.h"

/* Type definitions.
 */
/* POINTER defines a generic pointer type */
typedef unsigned char *POINTER;

/* UINT2 defines a two byte word */
typedef unsigned short int UINT2;

/* UINT4 defines a four byte word */
typedef unsigned long int UINT4;

#if 0
#define R_memset(x, y, z) NL_memset(x, y, z)
#define R_memcpy(x, y, z) NL_memcpy(x, y, z)
#define R_memcmp(x, y, z) NL_memcmp(x, y, z)
#else
#define R_memset(x, y, z) memset(x, y, z)
#define R_memcpy(x, y, z) memcpy(x, y, z)
#define R_memcmp(x, y, z) memcmp(x, y, z)
#endif

#define PROTO_LIST(list) list

#define MIN_RSA_MODULUS_BITS 508
#define MAX_RSA_MODULUS_BITS 2048
#undef  MAX_RSA_MODULUS_LEN 
#define MAX_RSA_MODULUS_LEN ((MAX_RSA_MODULUS_BITS + 7) / 8)
#define MAX_RSA_PRIME_BITS ((MAX_RSA_MODULUS_BITS + 1) / 2)
#undef  MAX_RSA_PRIME_LEN
#define MAX_RSA_PRIME_LEN ((MAX_RSA_PRIME_BITS + 7) / 8)


#define RE_LEN 0x0406
#define RE_MODULUS_LEN 0x0407
#define RE_PRIVATE_KEY 0x0409
#define RE_PUBLIC_KEY 0x040a
#define RE_DATA 0x0401



int RSAPublicEncrypt PROTO_LIST
((unsigned char *, unsigned int *, unsigned char *, unsigned int,
 R_RSA_PRIVATE_KEY *));
int RSAPublicDecrypt PROTO_LIST
((unsigned char *, unsigned int *, unsigned char *, unsigned int,
  R_RSA_PRIVATE_KEY *));

#endif

