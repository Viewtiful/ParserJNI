/* ================================ *\
| Arcana-KTB                         |
| (c) Copyright eRISCS 2011          |
| http://eriscs.esil.univmed.fr      |
| Contact: traian.muntean@univmed.fr |
\* ================================ */

/** @file
 *
 * Definition of data structure to use a custom source of random numbers.
 */

#ifndef __KTB_PRNG_CUSTOM_H
#define __KTB_PRNG_CUSTOM_H

#include <ktb.h>
#include <ktb/err.h>
#include <ktb/prng.h>

#ifdef __cplusplus
extern "C" {
#endif

/** @addtogroup PRNG_group
 * @{ */

/** @name Custom Context management
 * @{ */

/** User function to initialize a PRNG.
 *
 * This function is called once, to initialize the PRNG.
 *
 * @param[in] init_data Initialization data passed to the
 * ktb_prng_init_custom() function
 *
 * @param[out] cookie_data The custom PRNG context. This is a buffer
 * created automatically by ktb_prng_init_custom() with the size
 * specified in the ktb_prng_custom_t structure.
 *
 * @return This function must return KTB_ERR_NO_ERROR on success,
 * another value when an error occur. If an error occured, the
 * PRNG object is immediately destroyed.
 */
typedef ktb_errno (*ktb_prng_init_fn)(void *init_data,
                                      void *cookie_data);

/** User function to generate random numbers.
 *
 * This function is called when ktb_prng_fill_buffer() is called on the
 * custom PRNG.
 *
 * @param[in] cookie_data The custom PRNG context
 *
 * @param[out] buffer The buffer to fill with random values
 *
 * @param[in] buffer_size The size of @a buffer
 *
 * @return This function should return KTB_ERR_NO_ERROR on success,
 * another value when an error occur. This return value will be
 * passed as is to the application.
 */
typedef ktb_errno (*ktb_prng_fill_buffer_fn)(void *cookie_data, 
                                             void *buffer,
                                             size_t buffer_size);

/** User function to add a new seed to a PRNG.
 *
 * This function can be called by the user to add something to the current
 * seed. This function should not replace the existing seed, to never reduce
 * the amount of entropy available.
 *
 * @param[in] cookie_data The custom PRNG context
 *
 * @param[in] reseed The buffer used to reseed the PRNG. This can be NULL
 * if we expect the PRNG to reseed itself with an internal entropy source,
 * for example the one used to initialize the PRNG the first time.
 *
 * @param[in] reseed_size The size of @a reseed, or 0 if @a reseed is NULL
 *
 * @return This function must return KTB_ERR_NO_ERROR on success, another
 * value when an error occure. This error value will be passed as is to the
 * application.
 */
typedef ktb_errno (*ktb_prng_reseed_with_fn)(void *cookie_data,
                                             void *reseed,
                                             size_t reseed_size);

/** User function to clean a custom PRNG.
 *
 * This function will be called once, when you call ktb_prng_clear() on a
 * custom PRNG.
 *
 * @param [in] cookie_data The custom PRNG context
 *
 * @note As all of the clear function, this function must not fail.
 */
typedef void (*ktb_prng_clear_fn)(void *cookie_data);

/** A set of functions used to specify a custom PRNG to use. */
typedef struct {
    ktb_prng_init_fn init_fn;
    ktb_prng_fill_buffer_fn fill_buffer_fn;
    /** The reseed function can be NULL if this functionnality is not
     * available. In this case, a call to ktb_prng_reseed() or
     * ktb_prng_reseed_with() will return KTB_ERR_UNSUPPORTED_OPERATION.
     */
    ktb_prng_reseed_with_fn reseed_with_fn;
    ktb_prng_clear_fn clear_fn;
    /** If the custom PRNG need some space allocated for internal use, set
     * this variable to the size of those data. cookie_data will point to an
     * allocated space in all the functions, space that will be deallocated
     * with ktb_prng_clear().
     */
    size_t cookie_size;

} ktb_prng_custom_t;

/** Create a pseudo-random number generator using custom functions.
 *
 * This function create a ktb_prng_t object that will work using user
 * supplied functions.
 *
 * @param[out] prng  The PRNG to initialise
 *
 * @param[in] cookie The user specific functions definition
 *
 * @param[in] init_data User specific data passed to the initialisation function
 *
 * @return A value of KTB_ERR_NO_ERROR indicate success, another value can be
 * returned when an error occur while initializing the PRNG. When an error
 * occur, the PRNG object is not created.
 *
 * @note  If the user supplied init function was called and returned an error,
 * the user supplied clear function will not be called. If an error occured at
 * some point after the call to the user init function, then the user clear
 * function will be called.
 */
ktb_errno ktb_prng_init_custom(ktb_prng_t *prng,
                               ktb_prng_custom_t cookie,
                               void *init_data);

/** @} */

/** @} */

#ifdef __cplusplus
}
#endif

#endif

