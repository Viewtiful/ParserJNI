/* ================================ *\
| Arcana-KTB                         |
| (c) Copyright eRISCS 2011          |
| http://eriscs.esil.univmed.fr      |
| Contact: traian.muntean@univmed.fr |
\* ================================ */

/** @file
 *
 * This header define some algorithm specific structure used to initialise
 * Key Exchanges. For more information, see ktb_kep_init().
 */

#ifndef KTB_KEP_DHPASS_H
#define KTB_KEP_DHPASS_H

#include <ktb.h>
#include <ktb/cipher.h>

#ifdef __cplusplus
extern "C" {
#endif

/** @addtogroup KEP_group
 * @{ */

/** @name Algorithm-specific data
 * @{ */

/** Parameters for the Diffie-Hellman protocol, protected by a password */
typedef struct
{
    /** Cipher algorithm used to encrypt communications */
    ktb_cipher_algo_t cipher_algo;
    /** Pointer to the discussion key, already shared by everyone.
     * This key must be the same on every peers.
     * You don't need to copy the key in a new pointer here, just pass a
     * pointer to an existing buffer. The key data will be used only during
     * the initialisation of KEP, and can be discarded afterward. */
    const void *discuss_key;
    /** Size of the data pointed by discuss_key */
    size_t discuss_key_size;

} ktb_kep_dh_pass_t;

/** @} */

/** @} */

#ifdef __cplusplus
}
#endif

#endif

