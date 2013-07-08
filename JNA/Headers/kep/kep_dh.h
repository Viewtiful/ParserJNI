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

#ifndef KTB_KEP_DH_H
#define KTB_KEP_DH_H

#include <ktb.h>

#ifdef __cplusplus
extern "C" {
#endif

/** @addtogroup KEP_group
 * @{ */

/** @name Algorithm-specific data
 * @{ */

/** Parameters for the Diffie-Hellman protocol. It is not used, but exist to
 * be consistent with the rest of the library. */
typedef struct
{
    int dummy;

} ktb_kep_dh_t;

/** @} */

/** @} */

#ifdef __cplusplus
}
#endif

#endif

