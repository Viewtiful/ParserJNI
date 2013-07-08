/* ================================ *\
| Arcana-KTB                         |
| (c) Copyright eRISCS 2011          |
| http://eriscs.esil.univmed.fr      |
| Contact: traian.muntean@univmed.fr |
\* ================================ */

/** @file
 *
 * @defgroup SIGN_group Elliptic Curves Digital Signature Module
 * User interface used to sign and check digital signatures.
 */

#ifndef  KTB_SIGN_H
#define  KTB_SIGN_H

#include <ktb.h>
#include <stdbool.h>
#include <ktb/err.h>
#include <ktb/keys.h>
#include <ktb/prng.h>
#include <ktb/hash.h>

#ifdef __cplusplus
extern "C" {
#endif

    /** @addtogroup SIGN_group
     * @{ */

    /** @name Context management
     * Functions used to initialize and cleanup a signature context
     * @{ */

    /** A signature context */
    typedef struct ktb_sign_ctx* ktb_sign_ctx_t;

    /** Create a signature context.
     *
     * After the context is created, you must call either
     * ktb_sign_set_public_key() or ktb_sign_set_private_key() to prepare the
     * context for verification/signature respectively.
     *
     * @param[out] ctx The context to initialize
     * @param[in] algo The hash algorithm to use for this signature. The hash must
     * be the same in both signature and verification.
     *
     * @retval KTB_ERR_NO_ERROR no error occurred
     * @retval KTB_ERR_INVALID_PARAMS @a ctx is NULL
     * @retval KTB_ERR_OUT_OF_MEM An error occured while allocating memory
     *
     * @note When an error occured, @a *ctx (if valid) is set to NULL.
     */
    ktb_errno ktb_sign_init(ktb_sign_ctx_t* ctx, ktb_hash_algo_t algo);

    /** Cleanup a signature context
     *
     * @param[in] ctx The context to clear. If @a ctx == NULL, nothing happen.
     *
     * @note After ktb_sign_clear() have been called on a context, it can't be
     * used again.
     */
    void ktb_sign_clear(ktb_sign_ctx_t ctx);

    /** Reset a signature context.
     *
     * Remove all input and computed signature from the context, but retain the
     * context key. After this call, the context can be reused to sign or verify
     * another message.
     *
     * @param[in] ctx The signature context
     *
     * @retval KTB_ERR_NO_ERROR No error occurred; the context is ready to be used
     *                          again
     * @retval KTB_ERR_INVALID_PARAMS @a ctx is NULL
     *
     * @return This function can also return an error code from
     * ktb_sign_set_private_key() or ktb_sign_set_public_key()
     *
     * @note If an error occured here, the context can't be used to perform any
     * operation before it is initialised again with either
     * ktb_sign_set_public_key() or ktb_sign_set_private_key().
     */
    ktb_errno ktb_sign_reset(ktb_sign_ctx_t ctx);

    /** @} */

    /** @name Processing input
     * Functions used to provide data to the signature context
     * @{ */

    /** Append data to the signature context.
     *
     * In both sign and verify mode, you must use this function to feed the
     * message to the signature context.
     * This function can be called repeatedly to process a big source of data,
     * or a stream.
     *
     * @param[in] ctx The signature context
     * @param[in] data A pointer to the data to sign
     * @param[in] data_size The size of the buffer pointed by data
     *
     * @retval KTB_ERR_NO_ERROR No error occured
     * @retval KTB_ERR_INVALID_PARAMS One of the parameters is NULL or the context is
     *                                not setup for either signing or verifying (used
     *                                without a previous call to
     *                                ktb_sign_set_public_key() or
     *                                ktb_sign_set_private_key()).
     * @retval KTB_ERR_PROCESS_AFTER_FINISH ktb_sign_finalise() was already called on
     *                                      this context.
     *
     * @note If an error occur in this function, the context is cleared, meaning
     * you'll need to set it up before using it again (using
     * ktb_sign_set_public_key() or ktb_sign_set_private_key()).
     */
    ktb_errno ktb_sign_process(ktb_sign_ctx_t ctx, const void* data,
            size_t data_size);

    /** Finalise the data input of a signature context.
     *
     * When the whole message to sign/to verify was given to the context using
     * ktb_sign_process(), you must call this function to close the input.
     * In the case of a signing context, this will also trigger the computation
     * of the signature. If it is a signature verification context, you can then
     * call ktb_sign_verify() to check a signature against the message.
     *
     * @param[in] ctx The signature context
     *
     * @retval KTB_ERR_NO_ERROR No error occured
     * @retval KTB_ERR_INVALID_PARAMS @a ctx is NULL
     * @retval KTB_ERR_PROCESS_AFTER_FINISH This function was already called on this
     *                                      context
     * @retval KTB_ERR_OUT_OF_MEM Not enough memory available to perform this
     *                            operation
     *
     * @return This function can also return an error code from
     * ktb_prng_fill_buffer()
     *
     * @note If an error occur, using the context without setting it up again is
     * undefined.
     */
    ktb_errno ktb_sign_finalise(ktb_sign_ctx_t ctx);

    /** @} */

    /** @name Verification functions
     * Functions used to determine if a given signature is valid.
     * @{ */

    /** Set the public key, and prepare the context for signature verification.
     *
     * When this function is called, the given context is setup to verify
     * signature. If the context was previously set to another key, or to sign
     * data, it is reset.
     *
     * @param[in] ctx The context to setup
     * @param[in] public_key The public key used to check signatures
     *
     * @retval KTB_ERR_NO_ERROR No error occured
     * @retval KTB_ERR_INVALID_PARAMS A mandatory parameter was omitted
     *
     * @return This function can also return an error code from ktb_hash_init()
     *
     * @note If an error occured in this function, the context is left uninitialized.
     *
     * @note For now, the key is not copied, so it must not be destroyed while
     * the signature context use it.
     */
    ktb_errno ktb_sign_set_public_key(ktb_sign_ctx_t ctx,
            const_ktb_public_key_t public_key);

    /** Check whether a signature corresponds to the given signed data.
     *
     * @param[in] ctx The signature context
     * @param[in] signature The signature to verify
     * @param[in] signature_size The size of signature
     * @param[out] is_valid Set to true if the signature is valid and no error
     *                      occurred in the computation, false otherwise.
     *
     * @retval KTB_ERR_NO_ERROR No error occurred during computation.
     * @retval KTB_ERR_SIGN_CORRUPT The data at \a signature isn't a signature
     * @retval KTB_ERR_OUT_OF_MEM Not enough memory to perform the verification
     * @retval KTB_ERR_INVALID_PARAMS One of the parameters was NULL, or the context
     *                                is a signing context
     * @retval KTB_ERR_BUFFER_SIZE_MISMATCH The given signature size is too small
     *
     * @note The context is left unaffected if an error occur here.
     */
    ktb_errno ktb_sign_verify(ktb_sign_ctx_t ctx, const void* signature,
            size_t signature_size, bool* is_valid);

    /** All-in-one function used to verify a signature
     *
     * This function can be used when the signed data is relatively small, and
     * can be held in a single buffer.
     *
     * @param[in] algo The hash algorithm used before signing.
     * @param[in] public_key The public key used to verify the signature
     * @param[in] data The buffer containing the data to be signed
     * @param[in] data_size The size of @a data
     * @param[in] signature The signature to verify
     * @param[in] signature_size The size of the @a signature buffer
     * @param[out] is_valid A boolean variable used to determine if the signature
     * is valid.
     *
     * @return This function can return any error code from the individual
     * functions used in the verification process.
     */
    ktb_errno ktb_sign_verify_block(ktb_hash_algo_t algo,
            const_ktb_public_key_t public_key, const void* data, size_t data_size,
            const void* signature, size_t signature_size, bool* is_valid);

    /** @} */

    /** @name Signature functions
     * Functions used to create a signature from the input data and a private key.
     * @{ */

    /** Set the private key, and prepare the context to sign data.
     *
     * When this function is called, the given context is setup to sign data. If
     * the context was previously set to another key, or to verify signatures,
     * it is reset.
     *
     * @param[in] ctx The context to setup
     * @param[in] private_key The private key used to check signatures
     * @param[in] prng The PRNG used for signature
     *
     * @retval KTB_ERR_NO_ERROR No error occured
     * @retval KTB_ERR_INVALID_PARAMS A mandatory parameter was omitted
     * @retval KTB_ERR_OUT_OF_MEM An error occured while allocating memory
     *
     * @return This function can also return an error code from ktb_hash_init()
     *
     * @note If an error occured in this function, the context is left uninitialized.
     *
     * @note For now, the key is not copied, so it must not be destroyed while
     * the signature context use it.
     */
    ktb_errno ktb_sign_set_private_key(ktb_sign_ctx_t ctx,
            const_ktb_private_key_t private_key,
            ktb_prng_t prng);

    /** Return the size of a signature memory block.
     *
     * This function allow the caller to get the size of the signature before
     * calling ktb_sign_get_sign().
     *
     * @param[in] ctx The signature context
     *
     * @return The size needed to hold a signature from this context. If the context
     * is invalid, 0 is returned.
     */
    size_t ktb_sign_get_sign_size(ktb_sign_ctx_t ctx);

    /** Retrieve the signature computed for a given context.
     *
     * You can call this function on a signing context after ktb_sign_finalise()
     * to retrieve the computed signature.
     *
     * @param[in] ctx The signature context
     * @param[out] size The size of the returned buffer. This can be NULL if the size
     *                  is already known.
     *
     * @return A pointer to the signature block, whose size can be known by calling
     * ktb_sign_get_sign_size(), or NULL if the context is not a signing
     * context, or if the signature is not ready (before a call to
     * ktb_sign_finalise().
     * The pointer returned is valid until the context is reset or destroyed.
     *
     * @note The returned pointer must NOT be freed by the caller, as it is stored
     * in the signature context.
     */
    const void* ktb_sign_get_sign(ktb_sign_ctx_t ctx, size_t* size);

    /** Return the size of a signature memory block.
     *
     * This function can be used without a signature context, in case of
     * complicated memory allocation issue that need the signature size to be
     * known even before initialising a signature context.
     *
     * @param[in] private_key The private key that will be used to sign.
     *
     * @return The size needed to hold a signature from this context. If the key is
     * invalid, 0 is returned.
     */
    size_t ktb_sign_get_sign_size_from_key(const_ktb_private_key_t private_key);

    /** All-in-one function used to sign a block of data.
     *
     * This function can be used when the data to sign is relatively small, and
     * can be held in a single buffer.
     *
     * @param[in] algo The hash algorithm used before signing.
     * @param[in] prng The PRNG to use when signing
     * @param[in] private_key The private key used to compute the signature
     * @param[in] data The buffer containing the data to be signed
     * @param[in] data_size The size of @a data
     * @param[out] signature A buffer large enough to hold the signature
     * @param[out] signature_size The size of the @a signature buffer
     *
     * @return This function can return any error code from the individual
     * functions used in the signature process.
     *
     * @note data and signature can overlap; in this case data will be replaced by
     * signature (only if there is enough space, otherwise an error is returned)
     */
    ktb_errno ktb_sign_sign_block(ktb_hash_algo_t algo, ktb_prng_t prng,
            const_ktb_private_key_t private_key, const void* data, size_t data_size,
            void* signature, size_t signature_size);

    /** @} */

    /** @} */

#ifdef __cplusplus
}
#endif

#endif
