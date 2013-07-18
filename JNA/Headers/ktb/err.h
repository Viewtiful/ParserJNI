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

/** @} */

/** @name Error reporting
 * @{ */

/** The maximum length of an error's string representation (including
 * the terminating nul character).
 *
 * @a KTB_MAX_STRERROR_LEN should be used with buffers given to
 * ktb_strerror() when one needs to guarantee that ERANGE is not returned.
 * For example
 * @code
 *     ktb_errno err = func_returning_an_error();
 *     if (err != 0) {
 *         char errstr[KTB_MAX_STRERROR_LEN];
 *         ktb_strerror(err, errstr, KTB_MAX_STRERROR_LEN);
 *         printf("Error: %s\n", errstr);
 *     }
 * @endcode
 * Note that the above code mimics the functionality of ktb_err().  In
 * general, ktb_strerror() should only be used when ktb_err() or ktb_ferr()
 * cannot be used.
 */
#define KTB_MAX_STRERROR_LEN 256
//JNA CONST int KTB_MAX_STRERROR_LEN 256

/** Print a human-friendly version of @a err into @a buf.
 *
 * This function is thread-safe, unlike the standard C library's
 * strerror().  It is based rather on the strerror_r() function
 * available on some platforms.
 *
 * If insufficient storage is provided in @a buf (as specified in
 * @a buf_size) to contain the error string, ktb_strerror() returns ERANGE 
 * and @a buf will contain an error message that has been truncated and 
 * NUL terminated to fit the length specified by @a buf_size.
 *
 * If @a err does not correspond to a known error message, the string
 * "Unknown error: " followed by a numerical representation of @a err is 
 * placed in @a buf.
 */
int ktb_strerror(ktb_errno err, char *buf, size_t buf_size);

/** Print a human-readable error message to stderr.
 *
 * This function is equivalent to ktb_ferr() with a @a stream
 * parameter equal to @c stderr.
 */
void ktb_err(const char *whoami, ktb_errno err, const char *format, ...);

/** Print a human-readable error message to stderr.
 *
 * This function is equivalent to ktb_ferr_va() with a @a stream
 * parameter equal to @c stderr.
 */
void ktb_err_va(const char *whoami, ktb_errno err, const char *format,
                va_list args);

/** Print a human-readable error message to a stream.
 *
 * This function prints the string @a whoami, followed by a string
 * produced using the printf @a format string and any following arguments,
 * followed by a human-readable description of @a err, and finally a
 * new-line character.  The total length of the expanded format string
 * (i.e. the string resulting from expanding all the arguments in @a format)
 * is limited to 256 bytes.
 * 
 * @param[in,out] stream
 * The stream to which we send the message.
 *
 * @param[in] whoami
 * Name of the programme/module where the error originated.
 *
 * @param[in] err
 * The error to be printed.
 *
 * @param[in] format
 * The @c printf-style format of the error message.  @a format can be NULL
 * to suppress printing any specific message beyond the error message.
 */
void ktb_ferr(FILE *stream, const char *whoami, ktb_errno err,
              const char *format, ...);

/** Print a human-readable error message to a stream.
 *
 * This function follows the same interface as ktb_ferr(), but provides
 * access to the @c va_list, making it easier to use from higher level
 * variadic functions.
 */
void ktb_ferr_va(FILE *stream, const char *whoami, ktb_errno err,
                 const char *format, va_list args);

/** @} */

/** @} */

#ifdef __cplusplus
}
#endif

#endif
