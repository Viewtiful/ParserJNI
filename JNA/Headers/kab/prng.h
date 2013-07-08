/* ================================ *\
| Arcana-KTB                         |
| (c) Copyright eRISCS 2011          |
| http://eriscs.esil.univmed.fr      |
| Contact: traian.muntean@univmed.fr |
\* ================================ */

/** @file
 *
 * @defgroup PRNG_group Pseudo-Random Number Generator
 * Functions and structure used to define and use a PRNG with other KTB
 * functions.
 */

#ifndef  __KTB_PRNG_H
#define  __KTB_PRNG_H

#include <ktb.h>
#include <ktb/err.h>

#ifdef __cplusplus
extern "C" {
#endif

/** @addtogroup PRNG_group
 * @{ */

/** @name Context management
 * @{ */

/** A Pseudo-Random Number Generator */
typedef struct ktb_prng *ktb_prng_t;

/** Clear the memory used by the pseudo-random number generator.
 *
 * @param[in] prng The PRNG to deallocate. It must have been initialized by a
 * call to ktb_prng_init_custom() before.
 */
void ktb_prng_clear(ktb_prng_t prng);

/** @} */

/** @name Usage
 * @{ */

/** Reseed the PRNG with user specified values.
 *
 * This function add a new seed to the PRNG. It does not replace the current
 * seed.
 *
 * @param[in] prng The PRNG to reseed. Can be NULL to use the internal PRNG.
 *
 * @param[in] buffer The seed to add to the PRNG
 *
 * @param[in] buffer_size The size of @a buffer
 *
 * @return This function can return KTB_ERR_NO_ERROR on success,
 * or any other value to indicate an error.
 *
 * @note If this function is called with a NULL value for @a buffer, 
 * it have the same effect as calling ktb_prng_reseed().
 */
ktb_errno ktb_prng_reseed_with(ktb_prng_t prng,
                               void *buffer, size_t buffer_size);

/** Reseed the PRNG with an internal entropy source.
 *
 * This function add a new seed to the PRNG. This new seed is taken from an
 * internal source.
 *
 * For the KTB PRNG, this source is:
 *  - on Posix systems: /dev/random or /dev/urandom
 *  - on Windows systems: The CryptoAPI random generator
 *
 * @param[in] prng The PRNG to reseed. Can be NULL to use the internal PRNG.
 *
 * @return This function can return KTB_ERR_NO_ERROR on success,
 * or any other value to indicate an error.
 *
 * @note Some entropy source might block the application if not enough 
 * entropy is available when the function is called.
 */
ktb_errno ktb_prng_reseed(ktb_prng_t prng);

/** Fill a buffer with random values.
 *
 * @param[in] prng The PRNG object. Can be NULL to use the internal PRNG.
 *
 * @param[out] buffer The buffer to fill with random data. 
 * It must already have been allocated.
 *
 * @param[in] buffer_size The size of @a buffer
 *
 * @return KTB_ERR_NO_ERROR on success, or an error value.
 */
ktb_errno ktb_prng_fill_buffer(ktb_prng_t prng,
                               void *buffer, size_t buffer_size);

/** @} */

/** @} */

#ifdef __cplusplus
}
#endif

#endif

