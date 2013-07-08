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

#ifndef KTB_KEP_STS_H
#define KTB_KEP_STS_H

#include <ktb.h>
#include <ktb/cipher.h>
#include <ktb/keys.h>

#ifdef __cplusplus
extern "C" {
#endif

    /** @addtogroup KEP_group
     * @{ */

    /** @name Algorithm-specific data
     * @{ */

    typedef struct {
        /** Cipher algorithm used when authenticating peers. */
        ktb_cipher_algo_t cipher_algo;
        /** The public key of the previous peer on the ring. See
         * @ref KEP_indepth for more informations about the structure of KEP
         * exchanges. */
        const_ktb_public_key_t peer_public_key;
        /** This peer private key, used to sign authentication messages. */
        const_ktb_private_key_t self_private_key;

    } ktb_kep_sts_t;

    /** @} */

    /** @} */

#ifdef __cplusplus
}
#endif

#endif

