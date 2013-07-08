/* ================================ *\
| Arcana-KTB                         |
| (c) Copyright eRISCS 2011          |
| http://eriscs.esil.univmed.fr      |
| Contact: traian.muntean@univmed.fr |
\* ================================ */

/** @file
 *
 * base64 encoding functions
 */

#ifndef  __KTB_BASE64_H
#define  __KTB_BASE64_H

#include <ktb.h>
#include <stdbool.h>
#include <ktb/err.h>

#ifdef __cplusplus
extern "C" {
#endif

/** Determine the size of a string needed to hold a base64 encoded buffer.
 *
 * @param[in] input_size
 * The size of the buffer to encode
 *
 * @return
 * The size needed to hold the base64 encoded buffer, without the terminal
 * NULL character.
 */
size_t ktb_base64_encode_size(size_t input_size);

/** Convert a byte sequence to a base64-printable string.
 *
 * @param[in] input
 * The input buffer
 *
 * @param[in] input_size
 * The size of the @a input buffer
 *
 * @param[out] result
 * A buffer to hold the converted string. It must be large enough to hold
 * the converted string without the terminating NULL character.
 *
 * @param[in] result_size
 * The size of the @a result buffer. The size needed to hold the encoded
 * string can be retrieved with ktb_base64_encode_size().
 *
 * @retval KTB_ERR_NO_ERROR
 * no error occured
 *
 * @retval KTB_ERR_DEST_BUFFER_TOO_SMALL 
 * The @a result buffer is too small to hold the converted result
 *
 * @retval KTB_ERR_INVALID_PARAMS 
 * Parameters @a input or @a result is NULL.
 *
 * @note
 * If an error occur, the content of @a result is undefined.
 *
 * @note
 * This function will not set the final NULL character in @a result; it is
 * the responsibility of the caller to do so if needed.
 */
ktb_errno ktb_base64_encode(const void *input, size_t input_size,
                            void *result, size_t result_size);

/** Return the size of the buffer needed for ktb_base64_decode()
 *
 * @param[in] input
 * The base64 encoded string
 *
 * @param[in] input_size
 * The size of @a input
 *
 * @return
 * The size of the buffer needed to hold the decoded string, or 0 if input
 * is NULL.
 */
size_t ktb_base64_decode_size(const void *input, size_t input_size);

/** Convert a base64 encoded string into a byte sequence.
 *
 * @param[in] input
 * The source base64 string
 *
 * @param[in] input_size
 * The size of @a input
 *
 * @param[out] result
 * The place to put the decoded sequence. It must be large enough.
 *
 * @param[in] result_size
 * The size of the @a result buffer. The size needed to hold the decoded
 * buffer can be retrieved with ktb_base64_decode_size().
 *
 * @retval KTB_ERR_NO_ERROR
 * success
 *
 * @retval KTB_ERR_DEST_BUFFER_TOO_SMALL 
 * The @a result buffer is too small to hold the result
 *
 * @retval KTB_ERR_INVALID_PARAMS
 * Parameters @a input or @a result is NULL
 *
 * @retval KTB_ERR_DATA_INVALID 
 * Parameter @a input contain invalid data
 *
 * @note
 * If an error occur, the content of @a result is undefined.
 */
ktb_errno ktb_base64_decode(const void *input, size_t input_size, 
                            void *result, size_t result_size);

#ifdef __cplusplus
}
#endif
    
#endif /*__INCL_KTB_BASE64__*/

