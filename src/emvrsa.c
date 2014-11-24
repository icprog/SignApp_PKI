/* RSA.C - RSA routines for RSAREF
 */

/* Copyright (C) RSA Laboratories, a division of RSA Data Security,
     Inc., created 1991. All rights reserved.
 */

#include "emvrsa.h"
#include "emvnn.h"

static int RSAPublicBlock PROTO_LIST
((unsigned char *, unsigned int *, unsigned char *, unsigned int,
  R_RSA_PRIVATE_KEY *));

/* RSA public-key encryption, according to PKCS #1.
 */
int RSAPublicEncrypt(unsigned char *output, unsigned int *outputLen,
                     unsigned char *input, unsigned int inputLen, R_RSA_PRIVATE_KEY * publicKey)
{
	int status;
	unsigned char pkcsBlock[MAX_RSA_MODULUS_LEN];
	unsigned int i, modulusLen;

	modulusLen =(publicKey->mod_bits+7)/8 ;
	if (inputLen + 11 > modulusLen)
		return (RE_LEN);

	pkcsBlock[0] = 0;
	/* block type 2 */
	pkcsBlock[1] = 2;

	for (i = 2; i < modulusLen - inputLen - 1; i++) {
		/*Моід0x80*/
		pkcsBlock[i] = 0x80;
	}
	/* separator */
	pkcsBlock[i++] = 0;

	R_memcpy ((POINTER)&pkcsBlock[i], (POINTER)input, inputLen);

	status = RSAPublicBlock
	         (output, outputLen, pkcsBlock, modulusLen, publicKey);

	/* Zeroize sensitive information.
	 */
	R_memset ((POINTER)pkcsBlock, 0, sizeof (pkcsBlock));

	return (status);
}

/* RSA public-key decryption, according to PKCS #1.
 */
int RSAPublicDecrypt (unsigned char *output, unsigned int *outputLen,
                      unsigned char *input, unsigned int inputLen, R_RSA_PRIVATE_KEY *publicKey)
{
	int status;
	unsigned char pkcsBlock[MAX_RSA_MODULUS_LEN];
	unsigned int  modulusLen, pkcsBlockLen;

	modulusLen = publicKey->mod_bits;
	if (inputLen > modulusLen)
		return (RE_LEN);

	if ((status = RSAPublicBlock
	              (pkcsBlock, &pkcsBlockLen, input, inputLen, publicKey))!=0)
		return (status);

	if (pkcsBlockLen != modulusLen)
		return (RE_LEN);

	*outputLen = modulusLen;

	R_memcpy ((POINTER)output, (POINTER)&pkcsBlock, *outputLen);

	/* Zeroize potentially sensitive information.
	 */
	R_memset ((POINTER)pkcsBlock, 0, sizeof (pkcsBlock));

	return (0);
}


/* Raw RSA public-key operation. Output has same length as modulus.

   Assumes inputLen < length of modulus.
   Requires input < modulus.
 */
static int RSAPublicBlock (unsigned char *output, unsigned int * outputLen,
                           unsigned char * input, unsigned int inputLen,R_RSA_PRIVATE_KEY *publicKey)
{
	NN_DIGIT c[MAX_NN_DIGITS], e[MAX_NN_DIGITS], m[MAX_NN_DIGITS],
	n[MAX_NN_DIGITS];
	unsigned int eDigits, nDigits;

	NN_Decode (m, MAX_NN_DIGITS, input, inputLen);
	NN_Decode (n, MAX_NN_DIGITS, publicKey->modulus, MAX_RSA_MODULUS_LEN);
	NN_Decode (e, MAX_NN_DIGITS, publicKey->exponent, MAX_RSA_MODULUS_LEN);
	nDigits = NN_Digits (n, MAX_NN_DIGITS);
	eDigits = NN_Digits (e, MAX_NN_DIGITS);

	if (NN_Cmp (m, n, nDigits) >= 0)
		return (RE_DATA);

	/* Compute c = m^e mod n.
	 */
	NN_ModExp (c, m, e, eDigits, n, nDigits);

	*outputLen = (publicKey->mod_bits+7)/8;
	NN_Encode (output, *outputLen, c, nDigits);

	/* Zeroize sensitive information.
	 */
	R_memset ((POINTER)c, 0, sizeof (c));
	R_memset ((POINTER)m, 0, sizeof (m));

	return (0);
}
