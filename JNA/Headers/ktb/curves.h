/* ================================ *\
| Arcana-KTB                         |
| (c) Copyright eRISCS 2011          |
| http://eriscs.esil.univmed.fr      |
| Contact: traian.muntean@univmed.fr |
\* ================================ */

/** @file
 *
 * @defgroup CURVES_group Elliptic Curves Management Module
 * Functions used to retrieve the list of available elliptic curves at run-time.
 */

#ifndef __KTB_CURVES_H
#define __KTB_CURVES_H

#include <ktb.h>

#ifdef __cplusplus
extern "C" {
#endif

/** @addtogroup CURVES_group
 * @{ */

/** @name Elliptic Curves usage
 *
 * These two functions are used in all applications to query the library about
 * the available elliptic curves at run-time.
 * @{ */

/** Get the number of available elliptic curves at run-time.
 *
 * This function give the application a way to use a dynamic list of elliptic
 * curves instead of hardcoding which curves to use.
 *
 * @return The number of curves available.
 *
 * @see The function ktb_curves_id() is used to retrieve the actual curves
 * identifiers.
 */
int ktb_curves_count(void);

/** Return a curve identifier, to be used throughout the KTB.
 *
 * All available curves are identified with a unique null-terminated string.
 * This function make it possible to retrieve those identifiers at run-time,
 * effectively avoiding the need to hardcode them.
 *
 * @param[in] index The curve index. This value must be greater or equal to 0 and
 * less than the value returned bt ktb_curves_count().
 *
 * @return The corresponding curve identifier. The returned value must not be
 * freed, since it is managed by the library.
 */
const char *ktb_curves_id(int index);

/** @} */

/** @} */

#ifdef __cplusplus
}
#endif

#endif

