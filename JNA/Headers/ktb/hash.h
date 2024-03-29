/* ================================ *\
| Arcana-KTB                         |
| (c) Copyright eRISCS 2011          |
| http://eriscs.esil.univmed.fr      |
| Contact: traian.muntean@univmed.fr |
\* ================================ */

/** @file
 *
 * @defgroup HASH_group Hash and HMAC module
 * Set of functions to compute the hash of an arbitrary sized input.
 */

#ifndef __KTB_HASH_H
#define __KTB_HASH_H

#include <ktb.h>
#include <stddef.h>
#include <ktb/err.h>

#ifdef __cplusplus
extern "C" {
#endif

/** @addtogroup HASH_group
 * @{ */

/** @name Available algorithms
 * @{ */

/** Available hash algorithms */
typedef enum ktb_hash_algo {
    KTB_HASH_ALGO_SHA1,
    KTB_HASH_ALGO_SHA224,
    KTB_HASH_ALGO_SHA256,
    KTB_HASH_ALGO_SHA384,
    KTB_HASH_ALGO_SHA512,
    KTB_HASH_ALGO_CRC24,
    KTB_HASH_ALGO_SKEIN256,
    KTB_HASH_ALGO_SKEIN512,
    KTB_HASH_ALGO_SKEIN1024,
    KTB_HASH_ALGO_SHABAL192,
    KTB_HASH_ALGO_SHABAL224,
    KTB_HASH_ALGO_SHABAL256,
    KTB_HASH_ALGO_SHABAL384,
    KTB_HASH_ALGO_SHABAL512,
} ktb_hash_algo_t;

/** @} */

/** @name Context management.
 * @{ */

/** A hash/HMAC context.
 *
 * @note
 * Context should be initialized to NULL to ease ressource management:
 * @code
 * ktb_hash_ctx_t hash_ctx = NULL;
 * @endcode
 */
typedef struct ktb_hash_ctx *ktb_hash_ctx_t;

/** Initialise a hash context.
 *
 * @param[out] ctx The context to initialise.
 * @param[in] algo The hash algorithm to use.
 *
 * @retval KTB_ERR_NO_ERROR No error occured
 * @retval KTB_ERR_UNKNOWN_HASH_ALGO The @a algo value is invalid
 * @retval KTB_ERR_OUT_OF_MEM An error occured when trying to allocate memory
 */
ktb_errno ktb_hash_init(ktb_hash_ctx_t *ctx, ktb_hash_algo_t algo);

/** Initialise an HMAC context.
 *
 * @param[out] ctx The context to initialise.
 * @param[in] algo The hash algorithm to use.
 * @param[in] key The key for the MAC.
 * @param[in] key_size The length of @a key.
 *
 * @retval KTB_ERR_NO_ERROR No error occured
 * @retval KTB_ERR_UNKNOWN_HASH_ALGO The @a algo value is invalid
 * @retval KTB_ERR_OUT_OF_MEM An error occured when trying to allocate memory
 */
ktb_errno ktb_hash_init_hmac(ktb_hash_ctx_t *ctx, ktb_hash_algo_t algo,
                             const void *key, size_t key_size);

/** Clear all resources associated with a hash context.
 *
 * @param[in] ctx An initialized context
 */
void ktb_hash_clear(ktb_hash_ctx_t ctx);

/** Reset a hash context.
 *
 * @param[in] ctx The hash context to reset.
 *
 * After calling ktb_hash_reset(), @a ctx will be in the state it was
 * immediately after ktb_hash_init() or ktb_hash_init_hmac() was called.
 * Calling ktb_hash_reset() is faster than clearing and then reinitialising
 * @a ctx.
 */
void ktb_hash_reset(ktb_hash_ctx_t ctx);

/** @} */

/** @name Computing the hash.
 * @{ */

/** Process a block of data.
 *
 * Append the contents of @a buf to the stream of data being hashed.
 *
 * @param[in] ctx An initialized context
 * @param[in] buf Pointer to the block of memory to be hashed.
 * @param[in] buf_size The length of @a buf.
 */
void ktb_hash_process(ktb_hash_ctx_t ctx, const void *buf, size_t buf_size);

/** Finalise the hash computation.
 *
 * @param[in] ctx An initialized context
 *
 * This function should be called only once, after all the data has
 * been processed with ktb_hash_process() and before the actual hash
 * value has been retrieved with ktb_hash_retrieve().
 */
void ktb_hash_finalise(ktb_hash_ctx_t ctx);

/** @} */

/** @name Retrieving the hash
 * @{ */

/** Retrieve the computed hash.
 *
 * @param[in] ctx An initialized context
 * @param[out] size The size of the returned buffer. This can be NULL if the size
 * is already known.
 *
 * @return A pointer to the computed hash value.  The pointer will point to a
 * block of memory of length ktb_hash_get_len() bytes.
 * 
 * @warning This function can only be called after calling ktb_hash_finalise().
 */
const void *ktb_hash_retrieve(ktb_hash_ctx_t ctx, size_t *size);

/** @} */

/** @name Information functions
 * @{ */

/** Return a human-readable name of the hash algorithm associated
 * with a given context.
 *
 * @param[in] ctx An initialized context
 *
 * @return A string containing the name of the hash algorithm.
 *
 * @warning The returned string should not be freed or modified in any way.
 * If the string must be modified, make a copy of it and modify the copy.
 */
const char *ktb_hash_get_name(ktb_hash_ctx_t ctx);

/** Return a human-readable name of the hash algorithm.
 *
 * @param[in] algo The hash algorithm
 *
 * @return A string containing the name of the hash algorithm.
 *
 * @warning The returned string should not fe free()ed or modified in any way.
 */
const char *ktb_hash_get_name_from_algo(ktb_hash_algo_t algo);

/** Return the length in bytes of the hash value that the given context
 * will produce.
 *
 * @param[in] ctx The context the length of whose hash value we are interested in
 *
 * @return The length in bytes of the hash value produced by @a ctx.
 */
size_t ktb_hash_get_len(ktb_hash_ctx_t ctx);

/** Return he length in bytes of the hash value that the given
 * algorithm will produce.
 *
 * @param[in] algo An algorithm identifier
 *
 * @return The length in bytes of the hash value produced by a context
 * initialised with @a algo.
 */
size_t ktb_hash_get_len_from_algo(ktb_hash_algo_t algo);

/** Return the length in bytes of the block size of the given context.
 *
 * @param[in] ctx The context whose block size we want.
 *
 * @return The length in bytes of the block size of the hash algorithm associated
 * with @a ctx.
 * 
 * @note Most people will have no use for this function, but we expose it
 * anyway. It's used only in the HMAC code.
 */
size_t ktb_hash_get_block_size(ktb_hash_ctx_t ctx);

/** @} */

/** @name Convenience functions
 * @{ */

/** Hash a block of memory.
 *
 * @param[in] algo The hash algorithm to use.
 * @param[in] block The block of data to hash.
 * @param[in] block_size The length of @a block.
 * @param[out] result The location where the computed hash should be put.
 * @param[in] result_size The length of @a result.
 *
 * @return An error if any step in the hash computation failed, or if 
 * @a result_size is too small to contain the computed hash.
 * 
 * @note
 * @a result must already refer to an available block of memory of
 * at least @a result_size bytes.  Moreover, @a result_size must be at
 * least ktb_hash_get_len_from_algo() bytes long.
 *
 * This function is (roughly) equivalent to the following code:
 * @code
 *     ktb_hash_ctx_t ctx;
 *     ktb_hash_init(&ctx, algo);
 *     ktb_hash_process(ctx, block, blocklen);
 *     ktb_hash_finalise(ctx);
 *     memcpy(result, ktb_hash_retrieve(ctx), result_size);
 *     ktb_hash_clear(ctx);
 * @endcode
 */
ktb_errno ktb_hash_block(ktb_hash_algo_t algo, const void *block,
        size_t block_size, void *result, size_t result_size);

/** @} */

/** @} */
               
#ifdef __cplusplus
}
#endif

#endif

