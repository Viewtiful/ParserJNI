/* ================================ *\
| Arcana-KTB                         |
| (c) Copyright eRISCS 2011          |
| http://eriscs.esil.univmed.fr      |
| Contact: traian.muntean@univmed.fr |
\* ================================ */

/** @file
 *
 * @defgroup KTB_group General library functions
 * The functions of this module are used to initialise the library itself.
 */

#ifndef __KTB_H
#define __KTB_H

/* Use GNU extension of libc */

#ifndef __USE_POSIX
#define __USE_POSIX
#endif

/* Allow large file manipulations on 32Bits systems */
#ifndef _LARGEFILE64_SOURCE
#define _LARGEFILE64_SOURCE
#endif
#ifdef _FILE_OFFSET_BITS
#undef _FILE_OFFSET_BITS
#endif
#define _FILE_OFFSET_BITS 64
#ifndef __USE_FILE_OFFSET64
#define __USE_FILE_OFFSET64
#endif
#ifndef __USE_LARGEFILE64
#define __USE_LARGEFILE64
#endif

#include <stddef.h>
#include <ktb/err.h>

#ifdef __cplusplus
extern "C" {
#endif

    /** @addtogroup KTB_group
     * @{ */

    /** Perform the necessary initialisation.
     *
     * This function allocate ressources for the correct operation of the
     * library. It must be called before anything else.
     *
     * @attention
     * Must be called before any other call to the KTB library.
     */
    ktb_errno ktb_init(void);

    /** Perform any remaining chores needed to ensure a clean exit from the
     * program.
     *
     * @attention
     * Must be called after the last call to the KTB library has been
     * completed.
     */
    void ktb_clear(void);

    /** @} */

#ifdef __cplusplus
}
#endif

#endif

