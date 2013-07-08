/* ================================ *\
| Arcana-KTB                         |
| (c) Copyright eRISCS 2011          |
| http://eriscs.esil.univmed.fr      |
| Contact: traian.muntean@univmed.fr |
\* ================================ */

/** @file
 *
 * @defgroup ERROR_group Error handling module
 * This module contain the error constants as well as functions to retrieve and
 * display an human readable error string.
 */

#ifndef __KTB_ERR_H
#define __KTB_ERR_H

#include <stdarg.h>
#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

/** @addtogroup ERROR_group
 * @{ */

/** @name List of error codes
 * @{ */

/**
 * The error type.
 *
 * If a variable of type ktb_errno is @c == to zero, then this always
 * means no error has occurred.
 *
 * @internal
 * DO NOT CHANGE THE ORDER OF THESE VALUES!!  The order must match the
 * array of strings in ktb_err.c.
 */
typedef enum {
    KTB_ERR_NO_ERROR = 0,
    KTB_ERR_UNKNOWN,
    KTB_ERR_ERRNO,
    KTB_ERR_INVALID_OFFSET,
    KTB_ERR_INVALID_WHENCE,
    
    KTB_ERR_UNKNOWN_FREAD_ERROR,
    KTB_ERR_UNKNOWN_FWRITE_ERROR,
    KTB_ERR_OUT_OF_MEM,
    KTB_ERR_MEM_WRITE_FAILURE,
    KTB_ERR_INVALID_PARAMS,

    KTB_ERR_PRNG_SEED_FAILURE,
    KTB_ERR_UNSUPPORTED_OPERATION,
    KTB_ERR_SET_KEY_NOT_SUPPORTED,
    KTB_ERR_UNKNOWN_HASH_ALGO,
    KTB_ERR_DEST_BUFFER_TOO_SMALL,

    KTB_ERR_HMAC_NO_KEY_SUPPLIED,
    KTB_ERR_INVALID_ITER_COUNT,
    KTB_ERR_DERIVED_KEY_TOO_LONG,
    KTB_ERR_INVALID_KEY_SIZE,
    KTB_ERR_INVALID_GCM_STATE,

    KTB_ERR_BUFFER_SIZE_MISMATCH,
    KTB_ERR_UNKNOWN_CIPHER_ALGO,
    KTB_ERR_UNKNOWN_CIPHER_MODE,
    KTB_ERR_NON_AUTHENTICATING_MODE,
    KTB_ERR_INVALID_IV_LEN,

    KTB_ERR_NO_KEY_SPECIFIED,
    KTB_ERR_NO_IV_SPECIFIED,
    KTB_ERR_PROCESS_AFTER_FINISH,
    KTB_ERR_UNKNOWN_CURVE_ID,
    KTB_ERR_INTERNAL_DB_ERROR,

    KTB_ERR_INCOMPATIBLE_POINT_REPR,
    KTB_ERR_POINTS_ON_DIFFERENT_CURVES,
    KTB_ERR_INVALID_POINT,
    KTB_ERR_INVALID_SIGNATURE,

    /** The specified algorithm identifier is invalid. */
    KTB_ERR_UNKNOWN_KEP_ALGO,
    /** Hosts of the exchange doesn't use the same parameters. */
    KTB_ERR_HANDSHAKE,
    /** Too many peers for the specified algorithm. */
    KTB_ERR_KEP_TOO_MANY_PEERS,
    /** The exchange is expecting a call to ktb_kep_put_data() instead. */
    KTB_ERR_KEP_STARVED,
    /** The exchange is expecting a call to ktb_kep_get_data() instead. */
    KTB_ERR_KEP_NOT_STARVED,
    /** The exchange is already complete. */
    KTB_ERR_KEP_COMPLETED,
    /** The exchange is not yet complete. */
    KTB_ERR_KEP_INCOMPLETE,
    
    KTB_ERR_KEM_ERROR,

    KTB_ERR_SIGN_CORRUPT,
    KTB_ERR_SIGN_NOT_READY,

    KTB_ERR_DATA_INVALID,

    KTB_ERRNO_MAX
} ktb_errno;

int ktb_strerror(ktb_errno err, char *buf, size_t buf_size);

#ifdef __cplusplus
}
#endif

#endif
