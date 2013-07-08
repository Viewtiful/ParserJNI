/* ================================ *\
| Arcana-KTB                         |
| (c) Copyright eRISCS 2011          |
| http://eriscs.esil.univmed.fr      |
| Contact: traian.muntean@univmed.fr |
\* ================================ */

/** @file
 *
 * radix64 encoding functions
 */

#ifndef  __KTB_RADIX64_H
#define  __KTB_RADIX64_H

#include <ktb.h>
#include <stdbool.h>
#include <ktb/err.h>

#ifdef __cplusplus
extern "C" {
#endif

/** Return the size needed to encode a buffer in radix64
 *
 * @param[in] input_size
 * The input buffer size
 *
 * @return
 * The full size needed to hold the encoded result, without the terminating
 * NULL character.
 */
size_t ktb_radix64_encode_size(size_t input_size);

/** Convert a byte sequence to a radix64 encoded string
 *
 * @param[in] input
 * The input buffer
 *
 * @param[in] input_size
 * The size of the @a input buffer
 *
 * @param[out] result
 * A place to put the encoded string
 *
 * @param[in] result_size
 * The size of the @a result buffer. The needed size can be retrieved with
 * ktb_radix64_encode_size()
 *
 * @retval KTB_ERR_NO_ERROR
 * success
 *
 * @retval KTB_ERR_DEST_BUFFER_TOO_SMALL
 * The @a result buffer is too small to hold the encoded result
 *
 * @return
 * This function can return any error code from ktb_hash_block().
 *
 * @note
 * If an error occur, the content of @a result is undefined.
 *
 * @note
 * The function does not add the terminal NULL character; it is the
 * responsibility of the caller to do so if needed.
 */
ktb_errno ktb_radix64_encode(const void *input, size_t input_size,
                             void *result, size_t result_size);

/** Return the size needed to decode a radix64 encoded string
 *
 * @param[in] input
 * The input buffer
 *
 * @param[in] input_size
 * The size of the @a input buffer
 *
 * @return
 * 0 if the input buffer is invalid, or the size needed to hold the decoded
 * content of @a input with ktb_radix64_decode
 */
size_t ktb_radix64_decode_size(const void *input, size_t input_size);

/** Convert a radix64 string into a byte sequence
 *
 * @param[in] input
 * The source radix64 encoded string
 *
 * @param[in] input_size
 * The size of @a input
 *
 * @param[out] result
 * A place to hold the decoded buffer
 *
 * @param[in] result_size
 * The size of the @a result buffer
 *
 * @return
 * This function can return the same error code as ktb_base64_decode
 */
ktb_errno ktb_radix64_decode(const void *input, size_t input_size, 
                             void *result, size_t result_size);

/** Check the CRC24 of a radix64 string
 *
 * @param[in] input
 * The input buffer
 *
 * @param[in] input_size
 *
 * @param[out] verified
 * This boolean will be set to @c true if the CRC is valid, @c false
 * otherwise.
 *
 * @retval KTB_ERR_NO_ERROR
 * No error occured during the verification. This is not indicating that the
 * CRC is verified; see @a verified for that.
 *
 * @retval KTB_ERR_INVALID_PARAMS
 * @a verified is NULL or another parameter is invalid.
 *
 * @retval KTB_ERR_DATA_INVALID
 * The input data is not a valid radix64 input.
 *
 * @return
 * This function can also return error codes from ktb_radix64_decode(),
 * ktb_hash_block() or ktb_base64_encode()
 */
ktb_errno ktb_radix64_verify(const void *input, size_t input_size, 
                             bool *verified);

#ifdef __cplusplus
}
#endif

#endif /*__INCL_KTB_RADIX64__*/

