/* ================================ *\
| Arcana-KTB                         |
| (c) Copyright eRISCS 2011          |
| http://eriscs.esil.univmed.fr      |
| Contact: traian.muntean@univmed.fr |
\* ================================ */

/** @file
 *
 * @defgroup KDF_group Key Derivation Functions module
 * Functions used to generate a fixed length key from a variable sized input
 */

#ifndef __KTB_KDF_H
#define __KTB_KDF_H

#include <ktb.h>
#include <ktb/hash.h>
#include <ktb/err.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/** @addtogroup KDF_group
 * @{ */

/** @name Key Derivation functions
 * Functions used to generate a fixed length secret key from an arbitrary seed
 * @{ */

/** Key derivation function (aka mask generation function).
 *
 * @param[in] algo The hash algorithm to use.
 * @param[in] seed The seed from which to derive a new key.
 * @param[in] seed_size The length of @a seed.
 * @param[out] derived_key Point to memory where the derived key should be put.
 * @param[in] derived_key_size The length of the generated @a derived_key.
 *
 * This function implements the KDF2 key derivation function, details
 * of which can be found in ISO-18033-2
 * (http://www.shoup.net/iso/std6.pdf).  Given a block of memory as the
 * @a seed, the function will fill the memory block at @a derived_key
 * with a value based on hashing @a seed with a counter.  The length
 * @a derived_key_size determines the length of the generated derived key.
 *
 * This function should only be used on "high-entropy"
 * (i.e. essentially random) shared secrets.  For shared secrets
 * coming from user supplied passwords (for example), use ktb_pbkdf()
 * instead.
 *
 * @see The site http://www.di-mgt.com.au/cryptoKDFs.html has an excellent
 * overview of the various key derivation functions available.
 */
ktb_errno ktb_kdf(ktb_hash_algo_t algo, const void *seed, size_t seed_size,
                  void *derived_key, size_t derived_key_size);
   
/** Password-based key generation function.
 *
 * @param[in] algo The hash algorithm to use.  It must support HMAC mode.
 * @param[in] passwd The seed password from which to derive a new key.
 * @param[in] passwd_size The length of @a passwd.
 * @param[in] salt The salt to apply to the computation.
 * @param[in] salt_size The length of @a salt.
 * @param[in] iteration_count The number of iterations to perform.
 * @param[out] derived_key A block of memory where the derived key should be put.
 * @param[in] derived_key_size The length of the generated @a derived_key.
 *
 * This function implements the PBKDF2 pasword-based key derivation
 * function, details of which can be found in RSA's document "PKCS #5
 * v2.1" (http://www.rsa.com/rsalabs/node.asp?id=2127)
 * 
 * This function should be prefered over ktb_kdf() when the shared
 * secret is a user supplied password or other "low-entropy"
 * (non-random) source.
 *
 * @todo
 * Add advice on the choice of @a salt and @a iteration_count.  See
 * section 4 of PKCS #5 v2.1.
 */
ktb_errno ktb_pbkdf(ktb_hash_algo_t algo,
                    const void *passwd, size_t passwd_size,
                    const void *salt, size_t salt_size,
                    size_t iteration_count,
                    void *derived_key, size_t derived_key_size);

/** @} */

/** @name Information function
 * @{ */

/** Return the maximum derived key size for a specific hash algorithm.
 *
 * @param[in] algo The algorithm used in the KDF.
 *
 * @return The maximum size of the derived key. Calling ktb_kdf() or
 * ktb_pbkdf() and asking for a derived key longer than this value will
 * return a @ref KTB_ERR_DERIVED_KEY_TOO_LONG error.
 */
size_t ktb_kdf_max_size(ktb_hash_algo_t algo);

/** @} */

/** @} */   
#ifdef __cplusplus
}
#endif

#endif

