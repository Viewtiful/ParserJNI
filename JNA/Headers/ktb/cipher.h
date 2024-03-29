/* ================================ *\
| Arcana-KTB                         |
| (c) Copyright eRISCS 2011          |
| http://eriscs.esil.univmed.fr      |
| Contact: traian.muntean@univmed.fr |
\* ================================ */

/** @file
 *
 * @defgroup CIPHER_group Symmetric encryption module
 * This module provide function used to hide large volume of data using
 * symmetric encryption and secret keys.
 */

#ifndef __KTB_CIPHER_H
#define __KTB_CIPHER_H

#include <ktb.h>
#include <ktb/err.h>
#include <stddef.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

    /** @addtogroup CIPHER_group
     * @{ */

    /** @name Available algorithms
     * List the various cipher algorithms and use mode
     * @{ */

    /** Available block ciphers */
    typedef enum {
        KTB_CIPHER_ALGO_AES128,
        KTB_CIPHER_ALGO_AES192,
        KTB_CIPHER_ALGO_AES256,
        KTB_CIPHER_ALGO_TWOFISH128,
        KTB_CIPHER_ALGO_TWOFISH192,
        KTB_CIPHER_ALGO_TWOFISH256,
    }
    ktb_cipher_algo_t;

    /** Available cipher modes of operation */
    typedef enum {
        KTB_CIPHER_MODE_CTR,
        KTB_CIPHER_MODE_GCM,
        KTB_CIPHER_MODE_CBC,
    } ktb_cipher_mode_t;

    /** @} */

    /** @name Context management
     * Creation and destruction of a ciphering context
     * @{ */

    /** Holds the context for use with a block cipher */
    typedef struct ktb_cipher_ctx* ktb_cipher_ctx_t;

    /** Create a block cipher context.
     *
     * @param[out] ctx The context to initialize
     * @param[in] algo The cipher algorithm to use with this context
     * @param[in] mode The cipher mode to use with this context
     * @param[in] encryption Specify the direction of this cipher. Set to true
     * to create an ciphering context, or false to get a deciphering context.
     *
     * @retval KTB_ERR_UNKNOWN_CIPHER_ALGO An invalid cipher algorithm is
     * specified in @a algo
     * @retval KTB_ERR_UNKNOWN_CIPHER_MODE An invalid cipher mode is specified
     * in @a mode
     * @retval KTB_ERR_OUT_OF_MEM An error occured while allocating memory
     *
     * @return @ref KTB_ERR_NO_ERROR in case of success, or an error code when
     * something wrong happened.
     */
    ktb_errno ktb_cipher_init(ktb_cipher_ctx_t* ctx, ktb_cipher_algo_t algo,
            ktb_cipher_mode_t mode, bool encryption);

    /** Release the memory associated with a block cipher context.
     *
     * @param[in] ctx The initialized context to clear
     *
     * @note This function must be called on every context initialized with
     * ktb_cipher_init(), even if an error occur during operations.
     */
    void ktb_cipher_clear(ktb_cipher_ctx_t ctx);

    /** Reset a cipher context.
     *
     * @param[in] ctx An initialized context
     *
     * A reset cipher context can be reused with the same settings (key, ...)
     * but with a new input.
     *
     * @warning This function is not implemented for every algorithm/mode
     *
     * @note A new IV must be provided after a reset.
     */
    void ktb_cipher_reset(ktb_cipher_ctx_t ctx);

    /** @} */

    /** @name Algorithm setup
     * Functions used to set the parameters of a context
     * @{ */

    /** Set the key for use with the cipher context.
     *
     * @param[in] ctx An initialized context
     * @param[in] key The secret key to use for (de)ciphering
     * @param[in] key_size The size of the data pointed by @a key
     *
     * @return @ref KTB_ERR_NO_ERROR in case of success, or an error code when
     * something wrong happened.
     *
     * @note The key must have a size compatible with the specified algorithm. The
     * needed key size can be retrieved by calling ktb_cipher_get_key_len().
     *
     * @attention A key must be set before the cipher context can be used
     * for encryption or decryption.
     */
    ktb_errno ktb_cipher_set_key(ktb_cipher_ctx_t ctx, const void* key,
            size_t key_size);

    /** Set the IV for this cipher context
     *
     * @param[in] ctx An initialized context
     * @param[in] iv The initialization vector to use
     * @param[in] iv_size The size of the data pointed by @a iv
     *
     * @return @ref KTB_ERR_NO_ERROR in case of success, or an error code when
     * something wrong happened.
     *
     * @note The IV must have a size compatible with the specified mode of
     * operation. This size can be retrieved by calling ktb_cipher_get_iv_len().
     *
     * @attention If the cipher mode need an IV, it must be set before the
     * context can be used.
     */
    ktb_errno ktb_cipher_set_iv(ktb_cipher_ctx_t ctx, const void* iv,
            size_t iv_size);

    /** Puts @a ctx's mode into authentication mode if possible.
     *
     * @param[in] ctx An initialized context
     * @param[in] auth_data The extra authentication data to use
     * @param[in] auth_data_size The size of the data pointed by @a auth_data
     *
     * @retval KTB_ERR_NO_ERROR no error occured
     * @retval KTB_ERR_NON_AUTHENTICATING_MODE the specified mode of operation
     * can't provide authentication
     *
     * @return This function can also return other error codes.
     *
     * If Galois/Counter Mode (GCM) is being used, this function can be used to
     * set the additional authentication data (AAD).  If the AAD is set then
     * the integrity data will be generated; if it is not set then no
     * integrity data will be generated.
     *
     * If GCM is not being used, this function does nothing.
     */
    ktb_errno ktb_cipher_set_auth_data(ktb_cipher_ctx_t ctx, const void* auth_data,
            size_t auth_data_size);

    /** @} */

    /** @name Prefix and suffix functions
     * Some use mode need to append data to the ciphered content; those function
     * are used to get the prefix and suffix needed.
     * @{ */

    /** Return the size of the prefix to add to ciphered data.
     *
     * This function should be called before actual ciphering (before
     * ktb_cipher_encrypt_block) to inquiry the size of the prefix block.
     *
     * @param[in] ctx The initialized context that will be used to (de)cipher.
     *
     * @return The size of the prefix block. It can be 0; in this case, it is
     * not needed to call ktb_cipher_get_prefix() or ktb_cipher_set_prefix().
     * Otherwise, those calls are mandatory.
     */
    size_t ktb_cipher_get_prefix_size(ktb_cipher_ctx_t ctx);

    /** Retrieve the prefix to add to ciphered data.
     *
     * This function should be called before the actual ciphering occur. The
     * prefix data it return must be prefixed to the ciphered data, and is part
     * of the ciphered data.
     *
     * @param[in] ctx The initialized context that will be used to cipher
     * @param[out] prefix A buffer to receive the prefix data
     * @param[in] prefix_size The size of the @a prefix buffer. It must be at
     * least large enough to hold the number of bytes returned by
     * ktb_cipher_get_prefix_size().
     *
     * @return An error code
     * @todo Document error code
     */
    ktb_errno ktb_cipher_get_prefix(ktb_cipher_ctx_t ctx, void* prefix,
            size_t prefix_size);

    /** Feed the prefix to the cipher.
     *
     * This function must be called before deciphering occur, with the prefix
     * part. The prefix real size can be determined by calling
     * ktb_cipher_get_prefix_size().
     *
     * @param[in] ctx The initialized context that will be used to decipher
     * @param[in] prefix The received prefix data
     * @param[in] prefix_size The received prefix size. It must be at least
     * ktb_cipher_get_prefix_size() bytes long, and only that much byte are
     * relevant (meaning you can pass larger buffer if needed).
     *
     * @return An error code
     * @todo Document error code
     */
    ktb_errno ktb_cipher_set_prefix(ktb_cipher_ctx_t ctx, void* prefix,
            size_t prefix_size);

    /** Return the size of the suffix to add to ciphered data.
     *
     * This function should be called after actual ciphering (after the last
     * ktb_cipher_encrypt_block()) to inquiry the size of the suffix block.
     *
     * @param[in] ctx The initialized context that was used to (de)cipher.
     *
     * @return The size of the suffix block. It can be 0; in this case, it is
     * not needed to call ktb_cipher_get_suffix(). Otherwise this call is
     * mandatory.
     */
    size_t ktb_cipher_get_suffix_size(ktb_cipher_ctx_t ctx);

    /** Retrieve the suffix to add to ciphered data.
     *
     * This function should be called after the actual ciphering occured. The
     * suffix data it return must be suffixed to the ciphered data, and is part
     * of the ciphered data.
     *
     * @param[in] ctx The initialized context that was used to cipher
     * @param[out] suffix A buffer to receive the suffix data
     * @param[in] suffix_size The size of the @a suffix buffer. It must be at
     * least large enough to hold the number of bytes returned by
     * ktb_cipher_get_suffix_size().
     *
     * @return An error code
     * @todo Document error code
     */
    ktb_errno ktb_cipher_get_suffix(ktb_cipher_ctx_t ctx, void* suffix,
            size_t suffix_size);

    /** @} */

    /** @name Encryption and decryption
     * Functions used to process blocks of data
     * @{ */

    /** Encrypt a block of bytes.
     *
     * @param[in] ctx An initialized context
     * @param[in] in A pointer to the buffer containing the input data
     * @param[in] in_size The size of the @a in buffer
     * @param[out] out A pointer to a buffer that will receive the ciphered data
     * @param[in] out_size The size of the @a out buffer
     *
     * @return @ref KTB_ERR_NO_ERROR when no error occur, or an error code
     *
     * Works in-place or with two buffers. Can be called multiple times
     * to process large bits of data in pieces, however EVERY PIECE must
     * be a multiple of the block size of the underlying cipher (almost
     * always 16 bytes).  Again: this function may be called multiple times
     * with input whose length is a multiple of the block size, and after
     * that exactly ONE call can be made where the input length is not
     * a multiple of the block size.
     *
     * @note The block size of the underlying cipher/mode can be retrieved by
     * calling ktb_cipher_get_block_len()
     *
     * @note Some mode of operation (namely CBC) need the output size to ALWAYS
     * be a multiple of the block size, greater or equal to the size of the
     * input.
     */
    ktb_errno ktb_cipher_encrypt_block(ktb_cipher_ctx_t ctx, const void* in,
            size_t in_size, void* out, size_t out_size);


    /** Decrypt a block of bytes.
     *
     * @param[in] ctx An initialized context
     * @param[in] in The input data (the ciphered content)
     * @param[in] in_size The size of the @a in buffer
     * @param[out] out A buffer that will receive the deciphered data
     * @param[in] out_size The size of the @a out buffer
     *
     * @return @ref KTB_ERR_NO_ERROR in case of success, or another error code
     *
     * See comment for ktb_cipher_encrypt_block().
     */
    ktb_errno ktb_cipher_decrypt_block(ktb_cipher_ctx_t ctx,
            const void* in, size_t in_size, void* out, size_t out_size);

    /** @} */

    /** @name Authenticity verification
     * These function are used to compute a MAC, used in authenticity and
     * integrity verification
     * @{ */

    /** Finalize the authenticity tag computation.
     *
     * @param[in] ctx An initialized context
     *
     * This function must be called once, at the end of the
     * ciphering/deciphering operation, before the authenticity tag
     * can be retrieved. It is not needed when not using authenticity.
     */
    void ktb_cipher_finalise(ktb_cipher_ctx_t ctx);

    /** Retrieve the authentication tag generated by the Galois/Counter Mode.
     *
     * @param[in] ctx An initialized context
     * @param[out] size The size of the generated MAC
     *
     * @return The generated MAC, or NULL if an error occured (no AAD set, or @a
     * ctx is not ready)
     *
     * If Galois/Counter Mode (GCM) is being used and if additional
     * authentication data (AAD) was set (using ktb_cipher_set_auth_data()),
     * this function returns the authentication tag generated by GCM.  The
     * tag should be sent to the recipient along with the AAD and the
     * ciphertext (from ktb_cipher_encrypt_block()).  The
     * recipient can then verify the authenticity of the data by comparing it's
     * own computed MAC with the received value.
     */
    const void* ktb_cipher_get_mac(ktb_cipher_ctx_t ctx, size_t* size);

    /** @} */

    /** @name Information functions
     * @{ */

    /** Return the size of the treated data.
     *
     * This function can be called at the end of operation (after the finalise
     * part, or if applicable after the ktb_cipher_set_suffix() call).
     *
     * When ciphering, this will return the number of ciphered bytes. When
     * deciphering, it will return the real number of deciphered bytes. It might
     * happen that deciphering return a buffer longer than the actual ciphered
     * data size; this function is then used to retrieve the original input size
     *
     * @param[in] ctx The context
     *
     * @return The real size of the processed data.
     */
    size_t ktb_cipher_get_data_size(ktb_cipher_ctx_t ctx);

    /** Return the human readable name of a cipher algorithm.
     *
     * @param[in] algo The cipher algorithm identifier
     *
     * @return A null-terminated string containing the name of the algorithm.
     */
    const char* ktb_cipher_get_name_from_algo(ktb_cipher_algo_t algo);

    /** Return the human readable name of a cipher mode.
     *
     * @param[in] mode The cipher mode identifier
     *
     * @return A null-terminated string containing the name of the mode.
     */
    const char* ktb_cipher_get_name_from_mode(ktb_cipher_mode_t mode);

    /** Return the length of the key needed by a context.
     *
     * @param[in] ctx An initialized context
     *
     * @return The length of the needed key, in bytes.
     */
    size_t ktb_cipher_get_key_len(ktb_cipher_ctx_t ctx);

    /** Return the length of the cipher block for a context
     *
     * @param[in] ctx An initialized context
     *
     * @return The size of a block
     *
     * See ktb_cipher_encrypt_block() for information on how to use the cipher
     * block size.
     */
    size_t ktb_cipher_get_block_len(ktb_cipher_ctx_t ctx);

    /** Return the length of the IV for a context
     *
     * @param[in] ctx An initialized context
     *
     * @return The size of the IV. If it return a positive value, this mean that
     * the IV size is fixed. When returning 0, it mean that any IV size can be
     * used.
     */
    size_t ktb_cipher_get_iv_len(ktb_cipher_ctx_t ctx);

    /** Return the length of the MAC
     *
     * @param[in] ctx An initialized context
     *
     * @return The length of the MAC, if any.
     */
    size_t ktb_cipher_get_mac_size(ktb_cipher_ctx_t ctx);

    /** Return the length of the IV for a given mode
     *
     * @param[in] mode A ciphering mode
     *
     * @return The size of the IV. If it return a positive value, this mean that
     * the IV size is fixed. When returning 0, it mean that any IV size can be
     * used.
     */
    size_t ktb_cipher_get_iv_len_from_mode(ktb_cipher_mode_t mode);

    /** @} */

#if 0
    /**
     * Convenience functions.
     */
    ktb_errno
    ktb_cipher_encrypt_block(ktb_cipher_algo_t algo,
            const void* key, size_t keylen,
            const void* iv, size_t ivlen,
            const void* in, size_t inlen,
            void* out, size_t outlen);


    ktb_errno
    ktb_cipher_encrypt_block(ktb_cipher_algo_t algo,
            const void* key, size_t keylen,
            const void* iv, size_t ivlen,
            const void* in, size_t inlen,
            void* out, size_t outlen);
#endif

    /** @} */

#ifdef __cplusplus
}
#endif

#endif

