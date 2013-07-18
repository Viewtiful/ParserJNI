/* ================================ *\
| Arcana-KTB                         |
| (c) Copyright eRISCS 2011          |
| http://eriscs.esil.univmed.fr      |
| Contact: traian.muntean@univmed.fr |
\* ================================ */

/** @file
 *
 * @defgroup KEM_group Key Encapsulation Mechanisms
 * Functions used to generate and cipher a key using a public/private keypair.
 */

#ifndef __KTB_KEM_H
#define __KTB_KEM_H

#include <ktb.h>
#include <ktb/err.h>
#include <ktb/keys.h>
#include <ktb/prng.h>
#include <ktb/hash.h>

#ifdef __cplusplus
extern "C" {
#endif

/** @addtogroup KEM_group
 * @{ */

/** @name Secret Key encapsulation
 * Functions used to encapsulate a key into a ciphered buffer.
 * @{ */

/** Return the size needed to hold an encapsulated key.
 *
 * @param[in] peer_public_key The public key used to encapsulate the secret
 * key.
 *
 * @return The size of the buffer needed by ktb_kem_psec_encrypt_size(),
 * or 0 if the key is invalid.
 *
 * @note You must use this function to find out the size of the buffer that must
 * be passed to ktb_kem_psec_encrypt().
 */
size_t ktb_kem_psec_encrypt_size(const_ktb_public_key_t peer_public_key);

/** Generate and encrypt a shared secret key.
 *
 * @param[in] algo The hash algorithm to use internally
 * @param[in] prng The PRNG to use to generate the secret key
 * @param[in] peer_public_key The public key of the other peer.
 * @param[out] secret_key The generated secret key. This space must have already
 * been allocated, and must be @a secret_key_size bytes long.
 * @param[in] secret_key_size The length of the secret key to generate.
 * This length is limited by the capability of ktb_kdf() and the kind of
 * curve used.
 * @param[out] ciphertext The encapsulated secret key, to be sent to the other
 * peer. This buffer must have been previously allocated by the application to at
 * least ktb_kem_psec_encrypt_size() bytes.
 * @param[in] ciphertext_size The size of the buffer allocated for @a ciphertext.
 *
 * @retval KTB_ERR_NO_ERROR No error occurred.
 * @retval KTB_ERR_INVALID_PARAMS One of the parameters given was NULL
 * @retval KTB_ERR_DERIVED_KEY_TOO_LONG @a secret_key_size is too big
 * @retval KTB_ERR_DEST_BUFFER_TOO_SMALL The buffer allocated for @a ciphertext
 * is too small
 *
 * @return This function can also return an error code from ktb_kdf()
 */
ktb_errno ktb_kem_psec_encrypt(ktb_hash_algo_t algo, ktb_prng_t prng,
                               const_ktb_public_key_t peer_public_key,
                               void *secret_key, size_t secret_key_size,
                               void *ciphertext, size_t ciphertext_size);

/** @} */

/** @name Secret key retrieval
 * Functions used to retrieve a ciphered secret key
 * @{ */

/** Decrypt a key that was encapsulated with ktb_kem_psec_encrypt().
 *
 * @param[in] algo The hash algorithm used to derivate the key
 * @param[in] self_private_key The private key
 * @param[in] input_ciphertext The buffer received (this is the value put in 
 * @a ciphertext by ktb_kem_psec_encrypt()).
 * @param[in] input_ciphertext_size The size of input_ciphertext
 * @param[out] secret_key The place to put the decrypted shared secret key.
 * @param[in] secret_key_size The length of the key
 *
 * @retval KTB_ERR_NO_ERROR The key was successfuly retrieved
 * @retval KTB_ERR_BUFFER_SIZE_MISMATCH @a input_ciphertext is not large enough
 * to get data from it
 * @retval KTB_ERR_DERIVED_KEY_TOO_LONG @a secret_key_size is too big. Note that
 * this is triggered by the same limitation that is in ktb_kem_psec_encrypt()
 * @retval KTB_ERR_KEM_ERROR The retrieved key was invalid
 *
 * @return This function can also return an error code from ktb_kdf()
 *
 * @note Parameters must have the same size as described in ktb_kem_psec_encrypt().
 */
ktb_errno ktb_kem_psec_decrypt(ktb_hash_algo_t algo,
        const_ktb_private_key_t self_private_key, const void *input_ciphertext,
        size_t input_ciphertext_size, void *secret_key, size_t secret_key_size);

/** @} */

/** @} */

#ifdef __cplusplus
}
#endif

#endif
