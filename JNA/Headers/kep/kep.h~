/* ================================ *\
| Arcana-KTB                         |
| (c) Copyright eRISCS 2011          |
| http://eriscs.esil.univmed.fr      |
| Contact: traian.muntean@univmed.fr |
\* ================================ */

/** @file
 *
 * @defgroup KEP_group Key Exchange Protocol Module
 * Functions used to make many peers agree on a shared secret key securely.
 */

#ifndef __KTB_KEP_H
#define __KTB_KEP_H

#include <ktb.h>
#include <stdbool.h>
#include <ktb/err.h>
#include <ktb/prng.h>
#include <ktb/keys.h>
#include <ktb/hash.h>

#ifdef __cplusplus
extern "C" {
#endif

/** @addtogroup KEP_group
 * @{ */

/** @name Algorithm-specific data
 * @{ */

/** Placeholder type for different KEP algorithm parameters.
 *
 * The @c algo_data parameter of the ktb_kep_init() function is of this
 * type. It can take a pointer to any of the other KEP parameters structure,
 * see @ref KEP_indepth to find out which structure is needed for
 * every algorithms available.
 */
//JNA TYPEDEF "com.sun.jna.Structure"
typedef void *ktb_kep_algo_data_t;

/** @} */

/** @name Context management
 * @{ */

/** Key Exchange algorithms available */
typedef enum ktb_kep_algo {
    KTB_KEP_ALGO_DH,
    KTB_KEP_ALGO_DH_PASS,
    KTB_KEP_ALGO_STS,
} ktb_kep_algo_t;

/** Key Exchange context object.
 *
 * @ref ktb_kep_ctx_t contexts are initialized with ktb_kep_init(),
 * used through ktb_kep_*() functions, and cleared with ktb_kep_clear().
 *
 * To declare a context, it's best to initially set it to NULL to avoid
 * possible mistakes:
 * @code
 * ktb_kep_ctx_t ctx = NULL;
 * @endcode
 */
typedef struct ktb_kep_ctx *ktb_kep_ctx_t;

/** Initialize a KEP context.
 *
 * Allocate a new context needed to perform a key exchange, and initialise
 * the protocol.
 *
 * The structure pointed by @a algo_data depends on the algorithm selected
 * with @a algo. See the @ref KEP_indepth page to know which structure must
 * be used with which algorithm.
 *
 * @param[out] ctx The context to initialize.
 * @param[in] prng The PRNG to use to generate the secret key
 * @param[in] algo Algorithm to use for the key exchange
 * @param[in] algo_data Algorithm specific parameters, see @ref KEP_indepth
 * @param[in] algo_data_size Size of the data pointed by @a algo_data
 * @param[in] curve_id The database id of the curve to use in the key
 *                     exchange
 * @param[in] hash_algo The hash algorithm used to generate the secret key
 * @param[in] secret_key_size The size of the secret key to generate
 * @param[in] peer_count The number of peer in this exchange
 *
 * @retval KTB_ERR_NO_ERROR  The context was successfuly initialized
 * @retval KTB_ERR_INVALID_PARAMS An invalid parameters, such as a NULL
 *                                pointer, was passed to the function
 * @retval KTB_ERR_UNKNOWN_KEP_ALGO Invalid algorithm specified
 * @retval KTB_ERR_KEP_TOO_MANY_PEERS The number of peers specified is not
 *                                    supported by the given algorithm
 * @retval KTB_ERR_OUT_OF_MEM An error occured when allocating memory
 *
 * @return  Additionnaly, initialisation error from the underlying algorithm
 * might be returned.
 *
 * @note When an error occur, the context is not allocated, and @a ctx is
 * set to NULL.
 */
ktb_errno ktb_kep_init(ktb_kep_ctx_t *ctx, ktb_prng_t prng,
        ktb_kep_algo_t algo, ktb_kep_algo_data_t algo_data,
        size_t algo_data_size, const char *curve_id,
        ktb_hash_algo_t hash_algo, size_t secret_key_size,
        int peer_count);

/** Clear a kep context.
 *
 * This function clean and release all of the memory associated with a kep
 * context. It must be called on all context successfuly initialized with
 * ktb_kep_init(), even when an error occur during the exchange.
 *
 * @param[in] ctx The context created in ktb_kep_init().
 *
 * @note It is possible to call this function on a NULL context without
 * raising an error.
 */
void ktb_kep_clear(ktb_kep_ctx_t ctx);

/** @} */

/** @name Data exchange functions
 * @{ */

/** Return the data to transmit to the next peer.
 *
 * This function is one of the two principal functions used in KEP. Every
 * peer will call it once, transmit the data to the next peer, and wait for
 * input. This process must run in a loop that break when ktb_kep_put_data()
 * return KTB_ERR_KEP_COMPLETED, which mean that this peer don't need to
 * transmit anymore data.
 *
 * @param[in] ctx An initialized context
 * @param[out] size The size of the returned buffer. It can't be NULL, since
 *                  there is no other way to know the size of the returned
 *                  buffer.
 * 
 * @return A pointer to the buffer that need to be transmitted. The size of
 * this buffer is put in @a size. This point to an internal buffer that is
 * handled by the library, so it should not be freed by the application.
 *
 * @note
 * The returned buffer is valid until the next call to ktb_kep_put_data().
 * You must either transmit it's content before the next call to
 * ktb_kep_put_data(), or copy it somewhere else.
 *
 * @note You should call this function only once per "loop"; trying to call
 * it again without calling ktb_kep_put_data() in between will return NULL.
 */
const void *ktb_kep_get_data(ktb_kep_ctx_t ctx, size_t *size);

/** Feed data received from the previous peer in the exchange.
 *
 * After having sent the data got from ktb_kep_get_data(), each peer will
 * receive a byte buffer that must be passed to ktb_kep_put_data(). When
 * no errors occurs, there will be exactly the same number of successful
 * calls to ktb_kep_get_data() and ktb_kep_put_data() on each peer.
 *
 * @param[in] ctx An initialized context
 * @param[in] peer_data The data received from the preceding peer
 * @param[in] peer_data_size The size of @a peer_data
 * @param[out] continue_exchange This variable will be set to true if the
 * exchange need to perform another loop of calls to ktb_kep_get_data() and
 * ktb_kep_put_data(). On the last loop iteration, it will be set to false,
 * indicating that the exchange loop can be exited.
 *
 * @retval KTB_ERR_NO_ERROR The input was successfuly consumed
 * @retval KTB_ERR_KEP_COMPLETED The exchange is already complete, and
 *                               didn't expect anymore data.
 * @retval KTB_ERR_INVALID_PARAMS Either @a ctx or @a peer_data or
 *                                @a continue_exchange is NULL
 * @retval KTB_ERR_KEP_NOT_STARVED You tried to call ktb_kep_put_data() but
 *                                 the algorithm expected a call to
 *                                 ktb_kep_get_data() instead
 *
 * @return This function can also return error code from the underlying
 * algorithm (such as @ref KTB_ERR_DATA_INVALID if the content of
 * @a peer_data is invalid)
 *
 * If an error occured, the exchange protocol failed and must be stopped.
 *
 * @note When @a continue_exchange is set to false, it does not mean that
 * the exchange was successful; it is important to check that the return
 * code is also set to @ref KTB_ERR_NO_ERROR .
 */
ktb_errno ktb_kep_put_data(ktb_kep_ctx_t ctx, const void *peer_data,
        size_t peer_data_size, bool *continue_exchange);

/** @} */

/** @name Secret key retrieval
 * @{ */

/** Complete the exchange.
 *
 * This function will compute the shared secret key.
 *
 * It can be called only once, after the exchange successfuly completed
 * (when ktb_kep_put_data() set it's @a continue_exchange parameter to false
 * and return @ref KTB_ERR_NO_ERROR ).
 *
 * @param[in] ctx An initialized context
 * @param[out] secret_key The place to put the secret key bytes. It must be
 * already allocated and large enough to hold the key length specified
 * in ktb_kep_init().
 * @param[in] secret_key_size The size of the buffer pointed by @a secret_key.
 * It must be large enough to hold the generated secret key.
 * 
 * @retval KTB_ERR_NO_ERROR The shared secret key was generated successfuly
 * @retval KTB_ERR_INVALID_PARAMS @a ctx is NULL
 * @retval KTB_ERR_KEP_INCOMPLETE There is still some exchange to do with
 * ktb_kep_get_data() and ktb_kep_put_data()
 *
 * @return This function can also return error codes from the underlying
 * algorithm.
 */
ktb_errno ktb_kep_finalise(ktb_kep_ctx_t ctx, void *secret_key,
        size_t secret_key_size);

/** @} */

/** @name Miscellaneous functions
 * @{ */

/**
 * Get the user readable name for an algorithm.
 *
 * @param[in] algo The algorithm identifier
 *
 * @return A null-terminated string representing the algorithm name. This is
 * an internal pointer and must not be freed by the application. If the
 * algorithm doesn't exist, NULL is returned.
 */
const char *ktb_kep_get_algo_name(ktb_kep_algo_t algo);

/** @} */

/** @} */

#ifdef __cplusplus
}
#endif

#endif

