/* ================================ *\
| Arcana-KTB                         |
| (c) Copyright eRISCS 2011          |
| http://eriscs.esil.univmed.fr      |
| Contact: traian.muntean@univmed.fr |
\* ================================ */

/** @file
 * 
 * @defgroup KEYS_group Key manipulations module
 * Functions and types in this module are used to create and export public and
 * private keys used in Elliptic Curve Cryptography throughout the Arcana-KTB.
 */

#ifndef __INCL_KEYS_H
#define __INCL_KEYS_H

#include <ktb.h>
#include <ktb/prng.h>
#include <ktb/err.h>

#ifdef __cplusplus
extern "C" {
#endif

/** @addtogroup KEYS_group
 * @{ */

/** @name Key types
 * The key types are opaque pointers used to manipulate public and private
 * keys in the library.
 * @{ */

/** A public key and its associated configuration. */
typedef struct ktb_public_key *ktb_public_key_t;
/** A pointer to a pubic key that can't be modified. Functions taking this as
 * their parameter guarantees that they won't alter the key. */
typedef const struct ktb_public_key *const_ktb_public_key_t;


/** A private key and its associated configuration. */
typedef struct ktb_private_key *ktb_private_key_t;
/** A pointer to a private key that can't be modified. Functions taking this as
 * their parameter guarantees that they won't alter the key. */
typedef const struct ktb_private_key *const_ktb_private_key_t;

/** @} */

/** @name Keys management
 *
 * Functions used to clear a previously allocated key
 * @{ */

/** Safely free the memory associated with the public key @a key.
 *
 * @param[in] key A pointer to the public key to cleanup. 
 * It is possible to pass a NULL pointer without raising an error.
 *
 * @note The @a key pointer should not be used after this call.
 */
void ktb_keys_public_key_clear(ktb_public_key_t key);

/** Safely free the memory associated with the private key @a key.
 *
 * @param[in] key A pointer to the public key to cleanup.
 * It is possible to pass a NULL pointer without raising an error.
 *
 * @note The @a key pointer should not be used after this call.
 */
void ktb_keys_private_key_clear(ktb_private_key_t key);

/** @} */

/** @name Raw key export/import
 * Functions used to export/import public and private keys
 * @{ */

/** Return the size needed to hold an exported public key.
 *
 * @param[in] public_key The public key to convert to a byte buffer
 *
 * @return The size of the needed buffer, in bytes, or 0 if @a public_key is
 * NULL.
 */
size_t ktb_keys_public_key_export_size(const_ktb_public_key_t public_key);

/** Export a public key to an opaque byte buffer.
 *
 * @param[in] public_key The public key to export
 * @param[out] result A buffer to hold the key bytes
 * @param [in] result_size The size of the @a result buffer. This buffer
 * should have already been allocated by the application, and must have a
 * size of at least the return value from ktb_keys_public_key_export_size().
 *
 * @retval KTB_ERR_NO_ERROR on success
 * @retval KTB_ERR_INVALID_PARAMS if a mandatory parameter is missing
 * @retval KTB_ERR_DEST_BUFFER_TOO_SMALL if @a result_size is not large enough
 *
 * @note In case of error, @a result content is unspecified.
 */
ktb_errno ktb_keys_public_key_export(const_ktb_public_key_t public_key,
        void *result, size_t result_size);

/** Import back an opaque byte buffer as a public key.
 *
 * @param [in] public_key_bytes The source buffer
 * @param [in] public_key_bytes_size The size of the source buffer
 * @param [out] public_key The resulting public key
 *
 * @retval KTB_ERR_NO_ERROR no error occured
 * @retval KTB_ERR_INVALID_PARAMS one of the parameter is NULL
 * @retval KTB_ERR_OUT_OF_MEM an error occured while allocating memory
 * @retval KTB_ERR_DATA_INVALID @a public_key_bytes contain invalid data
 *
 * @note If an error occured, there is no public key created, and @a public_key
 * is set to NULL.
 */
ktb_errno ktb_keys_public_key_import(const void *public_key_bytes,
                                     size_t public_key_bytes_size,
                                     ktb_public_key_t *public_key);

/** Determine the size needed to hold a private key in a byte buffer.
 *
 * @param[in] key The private key to convert
 *
 * @return The size of the needed buffer, or 0 if @a key is invalid
 */
size_t ktb_keys_private_key_export_size(const_ktb_private_key_t key);

/** Export a private key to an opaque byte buffer.
 *
 * @param[in] key The key to convert
 * @param[out] buffer The buffer that will receive the key
 * @param[in] buffer_size The size of buffer.
 *
 * @retval KTB_ERR_NO_ERROR no error occured
 * @retval KTB_ERR_INVALID_PARAMS if @a key of @a buffer is NULL
 * @retval KTB_ERR_DEST_BUFFER_TOO_SMALL @a buffer is too small to hold the
 * exported key
 *
 * @note When an error occur, @a buffer content is unspecified.
 */
ktb_errno ktb_keys_private_key_export(const_ktb_private_key_t key,
                                      void *buffer, size_t buffer_size);

/** Import back a byte buffer as a private key
 *
 * @param[in] private_key_bytes The bytes to convert back to a private key
 * @param[in] private_key_bytes_size The size of the private_key_bytes buffer
 * @param[out] private_key The resulting private key
 *
 * @retval KTB_ERR_NO_ERROR the private key was retrieved successfully
 * @retval KTB_ERR_INVALID_PARAMS if @a private_key or @a private_key_bytes
 *                                is NULL
 * @retval KTB_ERR_DATA_INVALID @a private_key_bytes contain invalid data
 * @retval KTB_ERR_OUT_OF_MEM an error occured while allocating memory
 *
 * @note If an error occured, there is no private key created.
 */
ktb_errno ktb_keys_private_key_import(const void *private_key_bytes,
                                      size_t private_key_bytes_size,
                                      ktb_private_key_t *private_key);

/** @} */

/** @name Keys creation
 * Functions used to generate new keypairs
 * @{ */

/**
 * Generate a pair of public/private keys.
 *
 * @todo
 * Add a paragraph describing the recommended key sizes for
 * different levels of security, in particular mentioning the
 * size one should pick assuming the use of a block cipher of
 * a particular "strength".
 *
 * @param[in] prng The PRNG to use to generate a random key
 * @param[in] curve_id The Arcana-ECDB identifier of the curve used to generate
 * this keypair.
 * @param[out] public_key The place to put the generated public key
 * @param[out] private_key The place to put the generated private key
 *
 * @retval KTB_ERR_NO_ERROR the keys were generated successfuly
 * @retval KTB_ERR_INVALID_PARAMS one of the parameter was NULL,
 * or @a keysize is invalid
 * @retval KTB_ERR_OUT_OF_MEM an error occured while allocating memory
 *
 * @return This function can also return an error value from
 * ktb_prng_fill_buffer()
 *
 * @note If an error happen, no keys are created, and @a public_key and @a
 * private_key are set to NULL.
 */
ktb_errno ktb_keys_generate_keypair(ktb_prng_t prng, const char *curve_id,
                                    ktb_public_key_t *public_key,
                                    ktb_private_key_t *private_key);

/** @} */

/** @} */

#ifdef __cplusplus
}
#endif

#endif

