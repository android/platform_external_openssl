/* Copyright (C) 1995-1998 Eric Young (eay@cryptsoft.com)
 * All rights reserved.
 *
 * This package is an SSL implementation written
 * by Eric Young (eay@cryptsoft.com).
 * The implementation was written so as to conform with Netscapes SSL.
 *
 * This library is free for commercial and non-commercial use as long as
 * the following conditions are aheared to.  The following conditions
 * apply to all code found in this distribution, be it the RC4, RSA,
 * lhash, DES, etc., code; not just the SSL code.  The SSL documentation
 * included with this distribution is covered by the same copyright terms
 * except that the holder is Tim Hudson (tjh@cryptsoft.com).
 *
 * Copyright remains Eric Young's, and as such any Copyright notices in
 * the code are not to be removed.
 * If this package is used in a product, Eric Young should be given attribution
 * as the author of the parts of the library used.
 * This can be in the form of a textual message at program startup or
 * in documentation (online or textual) provided with the package.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *    "This product includes cryptographic software written by
 *     Eric Young (eay@cryptsoft.com)"
 *    The word 'cryptographic' can be left out if the rouines from the library
 *    being used are not cryptographic related :-).
 * 4. If you include any Windows specific code (or a derivative thereof) from
 *    the apps directory (application code) you must include an acknowledgement:
 *    "This product includes software written by Tim Hudson (tjh@cryptsoft.com)"
 *
 * THIS SOFTWARE IS PROVIDED BY ERIC YOUNG ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 * The licence and distribution terms for any publically available version or
 * derivative of this code cannot be changed.  i.e. this code cannot simply be
 * copied and put under another distribution licence
 * [including the GNU Public Licence.] */

#ifndef OPENSSL_HEADER_CIPHER_INTERNAL_H
#define OPENSSL_HEADER_CIPHER_INTERNAL_H

#include <openssl/base.h>

#include <openssl/asn1t.h>

#if defined(__cplusplus)
extern "C" {
#endif


struct evp_cipher_st {
  /* type contains a NID identifing the cipher. (For example, NID_rc4.) */
  int nid;

  /* block_size contains the block size, in bytes, of the cipher, or 1 for a
   * stream cipher. */
  unsigned block_size;

  /* key_len contains the key size, in bytes, for the cipher. If the cipher
   * takes a variable key size then this contains the default size. */
  unsigned key_len;

  /* iv_len contains the IV size, in bytes, or zero if inapplicable. */
  unsigned iv_len;

  /* ctx_size contains the size, in bytes, of the per-key context for this
   * cipher. */
  unsigned ctx_size;

  /* flags contains the OR of a number of flags. See |EVP_CIPH_*|. */
  uint32_t flags;

  /* app_data is a pointer to opaque, user data. */
  void *app_data;

  int (*init)(EVP_CIPHER_CTX *ctx, const uint8_t *key, const uint8_t *iv,
              int enc);

  int (*cipher)(EVP_CIPHER_CTX *ctx, uint8_t *out, const uint8_t *in,
                size_t inl);

  int (*cleanup)(EVP_CIPHER_CTX *);

  int (*ctrl)(EVP_CIPHER_CTX *, int type, int arg, void *ptr);
};

/* EVP_CIPH_MODE_MASK contains the bits of |flags| that represent the mode. */
#define EVP_CIPH_MODE_MASK 0x3f


struct evp_aead_ctx_st;

/* EVP_AEAD represents a specific AEAD algorithm. */
struct evp_aead_st {
  uint8_t key_len;
  uint8_t nonce_len;
  uint8_t overhead;
  uint8_t max_tag_len;

  int (*init)(struct evp_aead_ctx_st *, const uint8_t *key,
              size_t key_len, size_t tag_len);
  void (*cleanup)(struct evp_aead_ctx_st *);

  int (*seal)(const struct evp_aead_ctx_st *ctx, uint8_t *out,
              size_t *out_len, size_t max_out_len, const uint8_t *nonce,
              size_t nonce_len, const uint8_t *in, size_t in_len,
              const uint8_t *ad, size_t ad_len);

  int (*open)(const struct evp_aead_ctx_st *ctx, uint8_t *out,
              size_t *out_len, size_t max_out_len, const uint8_t *nonce,
              size_t nonce_len, const uint8_t *in, size_t in_len,
              const uint8_t *ad, size_t ad_len);
};

#if defined(__cplusplus)
} /* extern C */
#endif

#endif /* OPENSSL_HEADER_CIPHER_INTERNAL_H */
