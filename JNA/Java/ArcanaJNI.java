public class ArcanaJNI{

	static {
		System.loadLibrary("arcanaJNI");
	}

	public static class AddressWrapper {
		private long address;

		public long getAddress() {
			return address;
		}

		public void setAddress(long addr) {
			address = addr;
		}
	}

	public static class BoolWrapper {
		private boolean booleanVal;

		public boolean getValue() {
			return booleanVal;
		}

		public void setValue(boolean val) {
			booleanVal = val;
		}
	}

	public static enum ktb_kep_algo_t {
		KTB_KEP_ALGO_DH (0),
		KTB_KEP_ALGO_DH_PASS (1),
		KTB_KEP_ALGO_STS (2);
		int enumValue;

		ktb_kep_algo_t (int val) {
			enumValue = val;
		}

		int getValue() {
			return enumValue;
		}

		void setValue(int val) {
			enumValue = val;
		}
	}

	public static enum ktb_errno {
		KTB_ERR_NO_ERROR (0),
		KTB_ERR_UNKNOWN (1),
		KTB_ERR_ERRNO (2),
		KTB_ERR_INVALID_OFFSET (3),
		KTB_ERR_INVALID_WHENCE (4),
		KTB_ERR_UNKNOWN_FREAD_ERROR (5),
		KTB_ERR_UNKNOWN_FWRITE_ERROR (6),
		KTB_ERR_OUT_OF_MEM (7),
		KTB_ERR_MEM_WRITE_FAILURE (8),
		KTB_ERR_INVALID_PARAMS (9),
		KTB_ERR_PRNG_SEED_FAILURE (10),
		KTB_ERR_UNSUPPORTED_OPERATION (11),
		KTB_ERR_SET_KEY_NOT_SUPPORTED (12),
		KTB_ERR_UNKNOWN_HASH_ALGO (13),
		KTB_ERR_DEST_BUFFER_TOO_SMALL (14),
		KTB_ERR_HMAC_NO_KEY_SUPPLIED (15),
		KTB_ERR_INVALID_ITER_COUNT (16),
		KTB_ERR_DERIVED_KEY_TOO_LONG (17),
		KTB_ERR_INVALID_KEY_SIZE (18),
		KTB_ERR_INVALID_GCM_STATE (19),
		KTB_ERR_BUFFER_SIZE_MISMATCH (20),
		KTB_ERR_UNKNOWN_CIPHER_ALGO (21),
		KTB_ERR_UNKNOWN_CIPHER_MODE (22),
		KTB_ERR_NON_AUTHENTICATING_MODE (23),
		KTB_ERR_INVALID_IV_LEN (24),
		KTB_ERR_NO_KEY_SPECIFIED (25),
		KTB_ERR_NO_IV_SPECIFIED (26),
		KTB_ERR_PROCESS_AFTER_FINISH (27),
		KTB_ERR_UNKNOWN_CURVE_ID (28),
		KTB_ERR_INTERNAL_DB_ERROR (29),
		KTB_ERR_INCOMPATIBLE_POINT_REPR (30),
		KTB_ERR_POINTS_ON_DIFFERENT_CURVES (31),
		KTB_ERR_INVALID_POINT (32),
		KTB_ERR_INVALID_SIGNATURE (33),
		KTB_ERR_UNKNOWN_KEP_ALGO (34),
		KTB_ERR_HANDSHAKE (35),
		KTB_ERR_KEP_TOO_MANY_PEERS (36),
		KTB_ERR_KEP_STARVED (37),
		KTB_ERR_KEP_NOT_STARVED (38),
		KTB_ERR_KEP_COMPLETED (39),
		KTB_ERR_KEP_INCOMPLETE (40),
		KTB_ERR_KEM_ERROR (41),
		KTB_ERR_SIGN_CORRUPT (42),
		KTB_ERR_SIGN_NOT_READY (43),
		KTB_ERR_DATA_INVALID (44),
		KTB_ERRNO_MAX (45);
		int enumValue;

		ktb_errno (int val) {
			enumValue = val;
		}

		int getValue() {
			return enumValue;
		}

		void setValue(int val) {
			enumValue = val;
		}
	}

	public static enum ktb_cipher_algo_t {
		KTB_CIPHER_ALGO_AES128 (0),
		KTB_CIPHER_ALGO_AES192 (1),
		KTB_CIPHER_ALGO_AES256 (2),
		KTB_CIPHER_ALGO_TWOFISH128 (3),
		KTB_CIPHER_ALGO_TWOFISH192 (4),
		KTB_CIPHER_ALGO_TWOFISH256 (5);
		int enumValue;

		ktb_cipher_algo_t (int val) {
			enumValue = val;
		}

		int getValue() {
			return enumValue;
		}

		void setValue(int val) {
			enumValue = val;
		}
	}

	public static enum ktb_cipher_mode_t {
		KTB_CIPHER_MODE_CTR (0),
		KTB_CIPHER_MODE_GCM (1),
		KTB_CIPHER_MODE_CBC (2);
		int enumValue;

		ktb_cipher_mode_t (int val) {
			enumValue = val;
		}

		int getValue() {
			return enumValue;
		}

		void setValue(int val) {
			enumValue = val;
		}
	}

	public static enum ktb_hash_algo_t {
		KTB_HASH_ALGO_SHA1 (0),
		KTB_HASH_ALGO_SHA224 (1),
		KTB_HASH_ALGO_SHA256 (2),
		KTB_HASH_ALGO_SHA384 (3),
		KTB_HASH_ALGO_SHA512 (4),
		KTB_HASH_ALGO_CRC24 (5),
		KTB_HASH_ALGO_SKEIN256 (6),
		KTB_HASH_ALGO_SKEIN512 (7),
		KTB_HASH_ALGO_SKEIN1024 (8),
		KTB_HASH_ALGO_SHABAL192 (9),
		KTB_HASH_ALGO_SHABAL224 (10),
		KTB_HASH_ALGO_SHABAL256 (11),
		KTB_HASH_ALGO_SHABAL384 (12),
		KTB_HASH_ALGO_SHABAL512 (13);
		int enumValue;

		ktb_hash_algo_t (int val) {
			enumValue = val;
		}

		int getValue() {
			return enumValue;
		}

		void setValue(int val) {
			enumValue = val;
		}
	}

	public native long gen_jni_ktb_kep_dh_t_get_struct_size();
	public class ktb_kep_dh_t {
		public int dummy;

		long struct_size;
		private AddressWrapper mInternal;

		public ktb_kep_dh_t() {
			mInternal = new AddressWrapper();
			mInternal.setAddress(gen_jni_ktb_kep_dh_t_create());
		}

		@Override
		public void finalize() {
			gen_jni_ktb_kep_dh_t_free(mInternal.getAddress());
			mInternal = null;
		}

		AddressWrapper getMInternal() {
			return mInternal;
		}

		public void write() {
			gen_jni_ktb_kep_dh_t_set_dummy(mInternal.getAddress(), dummy);
		}

		public void read() {
			 dummy = gen_jni_ktb_kep_dh_t_get_dummy(mInternal.getAddress());
			struct_size = gen_jni_ktb_kep_dh_t_get_struct_size();
		}

	}

	public native long gen_jni_ktb_kep_dh_t_create();
	public native void gen_jni_ktb_kep_dh_t_free(long mInternal);
	public native int gen_jni_ktb_kep_dh_t_get_dummy(long mInternal);

	public native void gen_jni_ktb_kep_dh_t_set_dummy(long mInternal,int dummy);

	public native long gen_jni_ktb_kep_dh_pass_t_get_struct_size();
	public class ktb_kep_dh_pass_t {
		public ktb_cipher_algo_t cipher_algo;
		public byte[] discuss_key;
		public long discuss_key_size;

		long struct_size;
		private AddressWrapper mInternal;

		public ktb_kep_dh_pass_t() {
			mInternal = new AddressWrapper();
			mInternal.setAddress(gen_jni_ktb_kep_dh_pass_t_create());
		}

		@Override
		public void finalize() {
			gen_jni_ktb_kep_dh_pass_t_free(mInternal.getAddress());
			mInternal = null;
		}

		AddressWrapper getMInternal() {
			return mInternal;
		}

		public void write() {
			gen_jni_ktb_kep_dh_pass_t_set_cipher_algo(mInternal.getAddress(), cipher_algo);
			gen_jni_ktb_kep_dh_pass_t_set_discuss_key(mInternal.getAddress(), discuss_key);
			gen_jni_ktb_kep_dh_pass_t_set_discuss_key_size(mInternal.getAddress(), discuss_key_size);
		}

		public void read() {
			 cipher_algo = gen_jni_ktb_kep_dh_pass_t_get_cipher_algo(mInternal.getAddress());
			 discuss_key = gen_jni_ktb_kep_dh_pass_t_get_discuss_key(mInternal.getAddress());
			 discuss_key_size = gen_jni_ktb_kep_dh_pass_t_get_discuss_key_size(mInternal.getAddress());
			struct_size = gen_jni_ktb_kep_dh_pass_t_get_struct_size();
		}

	}

	public native long gen_jni_ktb_kep_dh_pass_t_create();
	public native void gen_jni_ktb_kep_dh_pass_t_free(long mInternal);
	public native ktb_cipher_algo_t gen_jni_ktb_kep_dh_pass_t_get_cipher_algo(long mInternal);

	public native byte[] gen_jni_ktb_kep_dh_pass_t_get_discuss_key(long mInternal);

	public native long gen_jni_ktb_kep_dh_pass_t_get_discuss_key_size(long mInternal);

	public native void gen_jni_ktb_kep_dh_pass_t_set_cipher_algo(long mInternal,ktb_cipher_algo_t cipher_algo);

	public native void gen_jni_ktb_kep_dh_pass_t_set_discuss_key(long mInternal,byte[] discuss_key);

	public native void gen_jni_ktb_kep_dh_pass_t_set_discuss_key_size(long mInternal,long discuss_key_size);

	public native long gen_jni_ktb_kep_sts_t_get_struct_size();
	public class ktb_kep_sts_t {
		public ktb_cipher_algo_t cipher_algo;
		public long peer_public_key;
		public long self_private_key;

		long struct_size;
		private AddressWrapper mInternal;

		public ktb_kep_sts_t() {
			mInternal = new AddressWrapper();
			mInternal.setAddress(gen_jni_ktb_kep_sts_t_create());
		}

		@Override
		public void finalize() {
			gen_jni_ktb_kep_sts_t_free(mInternal.getAddress());
			mInternal = null;
		}

		AddressWrapper getMInternal() {
			return mInternal;
		}

		public void write() {
			gen_jni_ktb_kep_sts_t_set_cipher_algo(mInternal.getAddress(), cipher_algo);
			gen_jni_ktb_kep_sts_t_set_peer_public_key(mInternal.getAddress(), peer_public_key);
			gen_jni_ktb_kep_sts_t_set_self_private_key(mInternal.getAddress(), self_private_key);
		}

		public void read() {
			 cipher_algo = gen_jni_ktb_kep_sts_t_get_cipher_algo(mInternal.getAddress());
			 peer_public_key = gen_jni_ktb_kep_sts_t_get_peer_public_key(mInternal.getAddress());
			 self_private_key = gen_jni_ktb_kep_sts_t_get_self_private_key(mInternal.getAddress());
			struct_size = gen_jni_ktb_kep_sts_t_get_struct_size();
		}

	}

	public native long gen_jni_ktb_kep_sts_t_create();
	public native void gen_jni_ktb_kep_sts_t_free(long mInternal);
	public native ktb_cipher_algo_t gen_jni_ktb_kep_sts_t_get_cipher_algo(long mInternal);

	public native long gen_jni_ktb_kep_sts_t_get_peer_public_key(long mInternal);

	public native long gen_jni_ktb_kep_sts_t_get_self_private_key(long mInternal);

	public native void gen_jni_ktb_kep_sts_t_set_cipher_algo(long mInternal,ktb_cipher_algo_t cipher_algo);

	public native void gen_jni_ktb_kep_sts_t_set_peer_public_key(long mInternal,long peer_public_key);

	public native void gen_jni_ktb_kep_sts_t_set_self_private_key(long mInternal,long self_private_key);

/** Initialize a KEP context.
 *
 * Allocate a new context needed to perform a key exchange, and initialise
 * the protocol.
 *
 * The structure pointed by <i> algo</i>_data depends on the algorithm selected
 * with <i> algo</i>. See the @see KEP_indepth page to know which structure must
 * be used with which algorithm.
 *
 * @param [out] ctx The context to initialize.
 * @param [in] prng The PRNG to use to generate the secret key
 * @param [in] algo Algorithm to use for the key exchange
 * @param [in] algo_data Algorithm specific parameters, see @see KEP_indepth
 *  @a algo_data
 * @param [in] curve_id The database id of the curve to use in the key
 *                     exchange
 * @param [in] hash_algo The hash algorithm used to generate the secret key
 *  @param[in] peer_count The number of peer in this exchange
 *
 * <br /><u>Possible return Value</u> : <br /><ul>
	*<li> KTB_ERR_NO_ERROR  The context was successfuly initialized
</li> * <li> KTB_ERR_INVALID_PARAMS An invalid parameters, such as a NULL
</li> *                                pointer, was passed to the function
 * <li> KTB_ERR_UNKNOWN_KEP_ALGO Invalid algorithm specified
</li> * <li> KTB_ERR_KEP_TOO_MANY_PEERS The number of peers specified is not
</li> *                                    supported by the given algorithm
 * <li> KTB_ERR_OUT_OF_MEM An error occured when allocating memory
</li> *
 * @return  Additionnaly, initialisation error from the underlying algorithm
 * might be returned.
 *
 * <br /><b><i>Note :</i></b> When an error occur, the context is not allocated, and <i> ctx</i> is
 * set to NULL.
 */
	public native ktb_errno ktb_kep_init(AddressWrapper ctx,long prng,ktb_kep_algo_t algo,long algo_data,long algo_data_size,String curve_id,ktb_hash_algo_t hash_algo,long secret_key_size,int peer_count);
/** Clear a kep context.
 *
 * This function clean and release all of the memory associated with a kep
 * context. It must be called on all context successfuly initialized with
 * ktb_kep_init(), even when an error occur during the exchange.
 *
 * @param [in] ctx The context created in ktb_kep_init().
 *
 * <br /><b><i>Note :</i></b> It is possible to call this function on a NULL context without
 * raising an error.
 */
	public native void ktb_kep_clear(long ctx);
/** Return the data to transmit to the next peer.
 *
 * This function is one of the two principal functions used in KEP. Every
 * peer will call it once, transmit the data to the next peer, and wait for
 * input. This process must run in a loop that break when ktb_kep_put_data()
 * return KTB_ERR_KEP_COMPLETED, which mean that this peer don't need to
 * transmit anymore data.
 *
 * @param [in] ctx An initialized context
 * @param [out] size The size of the returned buffer. It can't be NULL, since
 *                  there is no other way to know the size of the returned
 *                  buffer.
 * 
 * @return A pointer to the buffer that need to be transmitted. The size of
 * this buffer is put in <i> size</i>. This point to an internal buffer that is
 * handled by the library, so it should not be freed by the application.
 *
 * <br /><b><i>Note :</i></b>
 * The returned buffer is valid until the next call to ktb_kep_put_data().
 * You must either transmit it's content before the next call to
 * ktb_kep_put_data(), or copy it somewhere else.
 *
 * <br /><b><i>Note :</i></b> You should call this function only once per "loop"; trying to call
 * it again without calling ktb_kep_put_data() in between will return NULL.
 */
	public native byte[] ktb_kep_get_data(long ctx);
/** Feed data received from the previous peer in the exchange.
 *
 * After having sent the data got from ktb_kep_get_data(), each peer will
 * receive a byte buffer that must be passed to ktb_kep_put_data(). When
 * no errors occurs, there will be exactly the same number of successful
 * calls to ktb_kep_get_data() and ktb_kep_put_data() on each peer.
 *
 * @param [in] ctx An initialized context
 * @param [in] peer_data The data received from the preceding peer
 *  @a peer_data
 * @param [out] continue_exchange This variable will be set to true if the
 * exchange need to perform another loop of calls to ktb_kep_get_data() and
 * ktb_kep_put_data(). On the last loop iteration, it will be set to false,
 * indicating that the exchange loop can be exited.
 *
 * <br /><u>Possible return Value</u> : <br /><ul>
	*<li> KTB_ERR_NO_ERROR The input was successfuly consumed
</li> * <li> KTB_ERR_KEP_COMPLETED The exchange is already complete, and
</li> *                               didn't expect anymore data.
 * <li> KTB_ERR_INVALID_PARAMS Either <i> ctx</i> or <i> peer</i>_data or
</li> *                                <i> continue</i>_exchange is NULL
 * <li> KTB_ERR_KEP_NOT_STARVED You tried to call ktb_kep_put_data() but
</li> *                                 the algorithm expected a call to
 *                                 ktb_kep_get_data() instead
 *
 * @return This function can also return error code from the underlying
 * algorithm (such as @see KTB_ERR_DATA_INVALID if the content of
 * <i> peer</i>_data is invalid)
 *
 * If an error occured, the exchange protocol failed and must be stopped.
 *
 * <br /><b><i>Note :</i></b> When <i> continue</i>_exchange is set to false, it does not mean that
 * the exchange was successful; it is important to check that the return
 * code is also set to @see KTB_ERR_NO_ERROR .
 */
	public native ktb_errno ktb_kep_put_data(long ctx,byte[] peer_data,BoolWrapper continue_exchange);
/** Complete the exchange.
 *
 * This function will compute the shared secret key.
 *
 * It can be called only once, after the exchange successfuly completed
 * (when ktb_kep_put_data() set it's <i> continue</i>_exchange parameter to false
 * and return @see KTB_ERR_NO_ERROR ).
 *
 * @param [in] ctx An initialized context
 * @param [out] secret_key The place to put the secret key bytes. It must be
 * already allocated and large enough to hold the key length specified
 * in ktb_kep_init().
 *  @a secret_key.
 * It must be large enough to hold the generated secret key.
 * 
 * <br /><u>Possible return Value</u> : <br /><ul>
	*<li> KTB_ERR_NO_ERROR The shared secret key was generated successfuly
</li> * <li> KTB_ERR_INVALID_PARAMS <i> ctx</i> is NULL
</li> * <li> KTB_ERR_KEP_INCOMPLETE There is still some exchange to do with
</li> * ktb_kep_get_data() and ktb_kep_put_data()
 *
 * @return This function can also return error codes from the underlying
 * algorithm.
 */
	public native ktb_errno ktb_kep_finalise(long ctx,byte[] secret_key);
/**
 * Get the user readable name for an algorithm.
 *
 * @param [in] algo The algorithm identifier
 *
 * @return A null-terminated string representing the algorithm name. This is
 * an internal pointer and must not be freed by the application. If the
 * algorithm doesn't exist, NULL is returned.
 */
	public native String ktb_kep_get_algo_name(ktb_kep_algo_t algo);
/** Perform the necessary initialisation.
     *
     * This function allocate ressources for the correct operation of the
     * library. It must be called before anything else.
     *
     * @attention
     * Must be called before any other call to the KTB library.
     */
	public native ktb_errno ktb_init();
/** Perform any remaining chores needed to ensure a clean exit from the
     * program.
     *
     * @attention
     * Must be called after the last call to the KTB library has been
     * completed.
     */
	public native void ktb_clear();
/** Create a signature context.
     *
     * After the context is created, you must call either
     * ktb_sign_set_public_key() or ktb_sign_set_private_key() to prepare the
     * context for verification/signature respectively.
     *
     * @param [out] ctx The context to initialize
     * @param [in] algo The hash algorithm to use for this signature. The hash must
     * be the same in both signature and verification.
     *
     * <br /><u>Possible return Value</u> : <br /><ul>
	*<li> KTB_ERR_NO_ERROR no error occurred
</li>     * <li> KTB_ERR_INVALID_PARAMS <i> ctx</i> is NULL
</li>     * <li> KTB_ERR_OUT_OF_MEM An error occured while allocating memory
</li>     *
     * <br /><b><i>Note :</i></b> When an error occured, <i> *ctx</i> (if valid) is set to NULL.
     */
	public native ktb_errno ktb_sign_init(AddressWrapper ctx,ktb_hash_algo_t algo);
/** Cleanup a signature context
     *
     * @param [in] ctx The context to clear. If <i> ctx</i> == NULL, nothing happen.
     *
     * <br /><b><i>Note :</i></b> After ktb_sign_clear() have been called on a context, it can't be
     * used again.
     */
	public native void ktb_sign_clear(long ctx);
/** Reset a signature context.
     *
     * Remove all input and computed signature from the context, but retain the
     * context key. After this call, the context can be reused to sign or verify
     * another message.
     *
     * @param [in] ctx The signature context
     *
     * <br /><u>Possible return Value</u> : <br /><ul>
	*<li> KTB_ERR_NO_ERROR No error occurred; the context is ready to be used
</li>     *                          again
     * <li> KTB_ERR_INVALID_PARAMS <i> ctx</i> is NULL
</li>     *
     * @return This function can also return an error code from
     * ktb_sign_set_private_key() or ktb_sign_set_public_key()
     *
     * <br /><b><i>Note :</i></b> If an error occured here, the context can't be used to perform any
     * operation before it is initialised again with either
     * ktb_sign_set_public_key() or ktb_sign_set_private_key().
     */
	public native ktb_errno ktb_sign_reset(long ctx);
/** Append data to the signature context.
     *
     * In both sign and verify mode, you must use this function to feed the
     * message to the signature context.
     * This function can be called repeatedly to process a big source of data,
     * or a stream.
     *
     * @param [in] ctx The signature context
     * @param [in] data A pointer to the data to sign
     *  @retval KTB_ERR_NO_ERROR No error occured
     * <br /><u>Possible return Value</u> : <br /><ul>
	*<li> KTB_ERR_INVALID_PARAMS One of the parameters is NULL or the context is
</li>     *                                not setup for either signing or verifying (used
     *                                without a previous call to
     *                                ktb_sign_set_public_key() or
     *                                ktb_sign_set_private_key()).
     * <li> KTB_ERR_PROCESS_AFTER_FINISH ktb_sign_finalise() was already called on
</li>     *                                      this context.
     *
     * <br /><b><i>Note :</i></b> If an error occur in this function, the context is cleared, meaning
     * you'll need to set it up before using it again (using
     * ktb_sign_set_public_key() or ktb_sign_set_private_key()).
     */
	public native ktb_errno ktb_sign_process(long ctx,byte[] data);
/** Finalise the data input of a signature context.
     *
     * When the whole message to sign/to verify was given to the context using
     * ktb_sign_process(), you must call this function to close the input.
     * In the case of a signing context, this will also trigger the computation
     * of the signature. If it is a signature verification context, you can then
     * call ktb_sign_verify() to check a signature against the message.
     *
     * @param [in] ctx The signature context
     *
     * <br /><u>Possible return Value</u> : <br /><ul>
	*<li> KTB_ERR_NO_ERROR No error occured
</li>     * <li> KTB_ERR_INVALID_PARAMS <i> ctx</i> is NULL
</li>     * <li> KTB_ERR_PROCESS_AFTER_FINISH This function was already called on this
</li>     *                                      context
     * <li> KTB_ERR_OUT_OF_MEM Not enough memory available to perform this
</li>     *                            operation
     *
     * @return This function can also return an error code from
     * ktb_prng_fill_buffer()
     *
     * <br /><b><i>Note :</i></b> If an error occur, using the context without setting it up again is
     * undefined.
     */
	public native ktb_errno ktb_sign_finalise(long ctx);
/** Set the public key, and prepare the context for signature verification.
     *
     * When this function is called, the given context is setup to verify
     * signature. If the context was previously set to another key, or to sign
     * data, it is reset.
     *
     * @param [in] ctx The context to setup
     * @param [in] public_key The public key used to check signatures
     *
     * <br /><u>Possible return Value</u> : <br /><ul>
	*<li> KTB_ERR_NO_ERROR No error occured
</li>     * <li> KTB_ERR_INVALID_PARAMS A mandatory parameter was omitted
</li>     *
     * @return This function can also return an error code from ktb_hash_init()
     *
     * <br /><b><i>Note :</i></b> If an error occured in this function, the context is left uninitialized.
     *
     * <br /><b><i>Note :</i></b> For now, the key is not copied, so it must not be destroyed while
     * the signature context use it.
     */
	public native ktb_errno ktb_sign_set_public_key(long ctx,long public_key);
/** Check whether a signature corresponds to the given signed data.
     *
     * @param [in] ctx The signature context
     * @param [in] signature The signature to verify
     *  @param[out] is_valid Set to true if the signature is valid and no error
     *                      occurred in the computation, false otherwise.
     *
     * <br /><u>Possible return Value</u> : <br /><ul>
	*<li> KTB_ERR_NO_ERROR No error occurred during computation.
</li>     * <li> KTB_ERR_SIGN_CORRUPT The data at \a signature isn't a signature
</li>     * <li> KTB_ERR_OUT_OF_MEM Not enough memory to perform the verification
</li>     * <li> KTB_ERR_INVALID_PARAMS One of the parameters was NULL, or the context
</li>     *                                is a signing context
     * <li> KTB_ERR_BUFFER_SIZE_MISMATCH The given signature size is too small
</li>     *
     * <br /><b><i>Note :</i></b> The context is left unaffected if an error occur here.
     */
	public native ktb_errno ktb_sign_verify(long ctx,byte[] signature,BoolWrapper is_valid);
/** All-in-one function used to verify a signature
     *
     * This function can be used when the signed data is relatively small, and
     * can be held in a single buffer.
     *
     * @param [in] algo The hash algorithm used before signing.
     * @param [in] public_key The public key used to verify the signature
     * @param [in] data The buffer containing the data to be signed
     *  @a data
     * @param [in] signature The signature to verify
     *  @a signature buffer
     * @param [out] is_valid A boolean variable used to determine if the signature
     * is valid.
     *
     * @return This function can return any error code from the individual
     * functions used in the verification process.
     */
	public native ktb_errno ktb_sign_verify_block(ktb_hash_algo_t algo,long public_key,byte[] data,byte[] signature,BoolWrapper is_valid);
/** Set the private key, and prepare the context to sign data.
     *
     * When this function is called, the given context is setup to sign data. If
     * the context was previously set to another key, or to verify signatures,
     * it is reset.
     *
     * @param [in] ctx The context to setup
     * @param [in] private_key The private key used to check signatures
     * @param [in] prng The PRNG used for signature
     *
     * <br /><u>Possible return Value</u> : <br /><ul>
	*<li> KTB_ERR_NO_ERROR No error occured
</li>     * <li> KTB_ERR_INVALID_PARAMS A mandatory parameter was omitted
</li>     * <li> KTB_ERR_OUT_OF_MEM An error occured while allocating memory
</li>     *
     * @return This function can also return an error code from ktb_hash_init()
     *
     * <br /><b><i>Note :</i></b> If an error occured in this function, the context is left uninitialized.
     *
     * <br /><b><i>Note :</i></b> For now, the key is not copied, so it must not be destroyed while
     * the signature context use it.
     */
	public native ktb_errno ktb_sign_set_private_key(long ctx,long private_key,long prng);
/** Return the size of a signature memory block.
     *
     * This function allow the caller to get the size of the signature before
     * calling ktb_sign_get_sign().
     *
     * @param [in] ctx The signature context
     *
     * @return The size needed to hold a signature from this context. If the context
     * is invalid, 0 is returned.
     */
	public native long ktb_sign_get_sign_size(long ctx);
/** Retrieve the signature computed for a given context.
     *
     * You can call this function on a signing context after ktb_sign_finalise()
     * to retrieve the computed signature.
     *
     * @param [in] ctx The signature context
     * @param [out] size The size of the returned buffer. This can be NULL if the size
     *                  is already known.
     *
     * @return A pointer to the signature block, whose size can be known by calling
     * ktb_sign_get_sign_size(), or NULL if the context is not a signing
     * context, or if the signature is not ready (before a call to
     * ktb_sign_finalise().
     * The pointer returned is valid until the context is reset or destroyed.
     *
     * <br /><b><i>Note :</i></b> The returned pointer must NOT be freed by the caller, as it is stored
     * in the signature context.
     */
	public native byte[] ktb_sign_get_sign(long ctx);
/** Return the size of a signature memory block.
     *
     * This function can be used without a signature context, in case of
     * complicated memory allocation issue that need the signature size to be
     * known even before initialising a signature context.
     *
     * @param [in] private_key The private key that will be used to sign.
     *
     * @return The size needed to hold a signature from this context. If the key is
     * invalid, 0 is returned.
     */
	public native long ktb_sign_get_sign_size_from_key(long private_key);
/** All-in-one function used to sign a block of data.
     *
     * This function can be used when the data to sign is relatively small, and
     * can be held in a single buffer.
     *
     * @param [in] algo The hash algorithm used before signing.
     * @param [in] prng The PRNG to use when signing
     * @param [in] private_key The private key used to compute the signature
     * @param [in] data The buffer containing the data to be signed
     *  @a data
     * @param [out] signature A buffer large enough to hold the signature
     *  @a signature buffer
     *
     * @return This function can return any error code from the individual
     * functions used in the signature process.
     *
     * <br /><b><i>Note :</i></b> data and signature can overlap; in this case data will be replaced by
     * signature (only if there is enough space, otherwise an error is returned)
     */
	public native ktb_errno ktb_sign_sign_block(ktb_hash_algo_t algo,long prng,long private_key,byte[] data,byte[] signature);
/** Key derivation function (aka mask generation function).
 *
 * @param [in] algo The hash algorithm to use.
 * @param [in] seed The seed from which to derive a new key.
 *  @a seed.
 * @param [out] derived_key Point to memory where the derived key should be put.
 *  @a derived_key.
 *
 * This function implements the KDF2 key derivation function, details
 * of which can be found in ISO-18033-2
 * (http://www.shoup.net/iso/std6.pdf).  Given a block of memory as the
 * <i> seed</i>, the function will fill the memory block at <i> derived</i>_key
 * with a value based on hashing <i> seed</i> with a counter.  The length
 * <i> derived</i>_key_size determines the length of the generated derived key.
 *
 * This function should only be used on "high-entropy"
 * (i.e. essentially random) shared secrets.  For shared secrets
 * coming from user supplied passwords (for example), use ktb_pbkdf()
 * instead.
 *
 * @see The site http://www.di-mgt.com.au/cryptoKDFs.html has an excellent
 * overview of the various key derivation functions available.
 */
	public native ktb_errno ktb_kdf(ktb_hash_algo_t algo,byte[] seed,byte[] derived_key);
/** Password-based key generation function.
 *
 * @param [in] algo The hash algorithm to use.  It must support HMAC mode.
 * @param [in] passwd The seed password from which to derive a new key.
 *  @a passwd.
 * @param [in] salt The salt to apply to the computation.
 *  @a salt.
 * @param [in] iteration_count The number of iterations to perform.
 * @param [out] derived_key A block of memory where the derived key should be put.
 *  @a derived_key.
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
 * Add advice on the choice of <i> salt</i> and <i> iteration</i>_count.  See
 * section 4 of PKCS #5 v2.1.
 */
	public native ktb_errno ktb_pbkdf(ktb_hash_algo_t algo,byte[] passwd,byte[] salt,long iteration_count,byte[] derived_key);
/** Return the maximum derived key size for a specific hash algorithm.
 *
 * @param [in] algo The algorithm used in the KDF.
 *
 * @return The maximum size of the derived key. Calling ktb_kdf() or
 * ktb_pbkdf() and asking for a derived key longer than this value will
 * return a @see KTB_ERR_DERIVED_KEY_TOO_LONG error.
 */
	public native long ktb_kdf_max_size(ktb_hash_algo_t algo);
/** Print a human-friendly version of <i> err</i> into <i> buf</i>.
 *
 * This function is thread-safe, unlike the standard C library's
 * strerror().  It is based rather on the strerror_r() function
 * available on some platforms.
 *
 * If insufficient storage is provided in <i> buf</i> (as specified in
 * <i> buf</i>_size) to contain the error string, ktb_strerror() returns ERANGE 
 * and <i> buf</i> will contain an error message that has been truncated and 
 * NUL terminated to fit the length specified by <i> buf</i>_size.
 *
 * If <i> err</i> does not correspond to a known error message, the string
 * "Unknown error: " followed by a numerical representation of <i> err</i> is 
 * placed in <i> buf</i>.
 */
	public native int ktb_strerror(ktb_errno err,byte[] buf);
/** Return the size needed to hold an encapsulated key.
 *
 * @param [in] peer_public_key The public key used to encapsulate the secret
 * key.
 *
 * @return The size of the buffer needed by ktb_kem_psec_encrypt_size(),
 * or 0 if the key is invalid.
 *
 * <br /><b><i>Note :</i></b> You must use this function to find out the size of the buffer that must
 * be passed to ktb_kem_psec_encrypt().
 */
	public native long ktb_kem_psec_encrypt_size(long peer_public_key);
/** Generate and encrypt a shared secret key.
 *
 * @param [in] algo The hash algorithm to use internally
 * @param [in] prng The PRNG to use to generate the secret key
 * @param [in] peer_public_key The public key of the other peer.
 * @param [out] secret_key The generated secret key. This space must have already
 * been allocated, and must be <i> secret</i>_key_size bytes long.
 *  @param[out] ciphertext The encapsulated secret key, to be sent to the other
 * peer. This buffer must have been previously allocated by the application to at
 * least ktb_kem_psec_encrypt_size() bytes.
 *  @a ciphertext.
 *
 * <br /><u>Possible return Value</u> : <br /><ul>
	*<li> KTB_ERR_NO_ERROR No error occurred.
</li> * <li> KTB_ERR_INVALID_PARAMS One of the parameters given was NULL
</li> * <li> KTB_ERR_DERIVED_KEY_TOO_LONG <i> secret</i>_key_size is too big
</li> * <li> KTB_ERR_DEST_BUFFER_TOO_SMALL The buffer allocated for <i> ciphertext</i>
</li> * is too small
 *
 * @return This function can also return an error code from ktb_kdf()
 */
	public native ktb_errno ktb_kem_psec_encrypt(ktb_hash_algo_t algo,long prng,long peer_public_key,byte[] secret_key,byte[] ciphertext);
/** Decrypt a key that was encapsulated with ktb_kem_psec_encrypt().
 *
 * @param [in] algo The hash algorithm used to derivate the key
 * @param [in] self_private_key The private key
 * @param [in] input_ciphertext The buffer received (this is the value put in 
 * <i> ciphertext</i> by ktb_kem_psec_encrypt()).
 *  @param[out] secret_key The place to put the decrypted shared secret key.
 *  @retval KTB_ERR_NO_ERROR The key was successfuly retrieved
 * <br /><u>Possible return Value</u> : <br /><ul>
	*<li> KTB_ERR_BUFFER_SIZE_MISMATCH <i> input</i>_ciphertext is not large enough
</li> * to get data from it
 * <li> KTB_ERR_DERIVED_KEY_TOO_LONG <i> secret</i>_key_size is too big. Note that
</li> * this is triggered by the same limitation that is in ktb_kem_psec_encrypt()
 * <li> KTB_ERR_KEM_ERROR The retrieved key was invalid
</li> *
 * @return This function can also return an error code from ktb_kdf()
 *
 * <br /><b><i>Note :</i></b> Parameters must have the same size as described in ktb_kem_psec_encrypt().
 */
	public native ktb_errno ktb_kem_psec_decrypt(ktb_hash_algo_t algo,long self_private_key,byte[] input_ciphertext,byte[] secret_key);
/** Clear the memory used by the pseudo-random number generator.
 *
 * @param [in] prng The PRNG to deallocate. It must have been initialized by a
 * call to ktb_prng_init_custom() before.
 */
	public native void ktb_prng_clear(long prng);
/** Reseed the PRNG with user specified values.
 *
 * This function add a new seed to the PRNG. It does not replace the current
 * seed.
 *
 * @param [in] prng The PRNG to reseed. Can be NULL to use the internal PRNG.
 *
 * @param [in] buffer The seed to add to the PRNG
 *
 *  @a buffer
 *
 * @return This function can return KTB_ERR_NO_ERROR on success,
 * or any other value to indicate an error.
 *
 * <br /><b><i>Note :</i></b> If this function is called with a NULL value for <i> buffer</i>, 
 * it have the same effect as calling ktb_prng_reseed().
 */
	public native ktb_errno ktb_prng_reseed_with(long prng,byte[] buffer);
/** Reseed the PRNG with an internal entropy source.
 *
 * This function add a new seed to the PRNG. This new seed is taken from an
 * internal source.
 *
 * For the KTB PRNG, this source is:
 *  - on Posix systems: /dev/random or /dev/urandom
 *  - on Windows systems: The CryptoAPI random generator
 *
 * @param [in] prng The PRNG to reseed. Can be NULL to use the internal PRNG.
 *
 * @return This function can return KTB_ERR_NO_ERROR on success,
 * or any other value to indicate an error.
 *
 * <br /><b><i>Note :</i></b> Some entropy source might block the application if not enough 
 * entropy is available when the function is called.
 */
	public native ktb_errno ktb_prng_reseed(long prng);
/** Fill a buffer with random values.
 *
 * @param [in] prng The PRNG object. Can be NULL to use the internal PRNG.
 *
 * @param [out] buffer The buffer to fill with random data. 
 * It must already have been allocated.
 *
 *  @a buffer
 *
 * @return KTB_ERR_NO_ERROR on success, or an error value.
 */
	public native ktb_errno ktb_prng_fill_buffer(long prng,byte[] buffer);
/** Safely free the memory associated with the public key <i> key</i>.
 *
 * @param [in] key A pointer to the public key to cleanup. 
 * It is possible to pass a NULL pointer without raising an error.
 *
 * <br /><b><i>Note :</i></b> The <i> key</i> pointer should not be used after this call.
 */
	public native void ktb_keys_public_key_clear(long key);
/** Safely free the memory associated with the private key <i> key</i>.
 *
 * @param [in] key A pointer to the public key to cleanup.
 * It is possible to pass a NULL pointer without raising an error.
 *
 * <br /><b><i>Note :</i></b> The <i> key</i> pointer should not be used after this call.
 */
	public native void ktb_keys_private_key_clear(long key);
/** Return the size needed to hold an exported public key.
 *
 * @param [in] public_key The public key to convert to a byte buffer
 *
 * @return The size of the needed buffer, in bytes, or 0 if <i> public</i>_key is
 * NULL.
 */
	public native long ktb_keys_public_key_export_size(long public_key);
/** Export a public key to an opaque byte buffer.
 *
 * @param [in] public_key The public key to export
 * @param [out] result A buffer to hold the key bytes
 *  @a result buffer. This buffer
 * should have already been allocated by the application, and must have a
 * size of at least the return value from ktb_keys_public_key_export_size().
 *
 * <br /><u>Possible return Value</u> : <br /><ul>
	*<li> KTB_ERR_NO_ERROR on success
</li> * <li> KTB_ERR_INVALID_PARAMS if a mandatory parameter is missing
</li> * <li> KTB_ERR_DEST_BUFFER_TOO_SMALL if <i> result</i>_size is not large enough
</li> *
 * <br /><b><i>Note :</i></b> In case of error, <i> result</i> content is unspecified.
 */
	public native ktb_errno ktb_keys_public_key_export(long public_key,byte[] result);
/** Import back an opaque byte buffer as a public key.
 *
 * @param [in] public_key_bytes The source buffer
 *  @param [out] public_key The resulting public key
 *
 * <br /><u>Possible return Value</u> : <br /><ul>
	*<li> KTB_ERR_NO_ERROR no error occured
</li> * <li> KTB_ERR_INVALID_PARAMS one of the parameter is NULL
</li> * <li> KTB_ERR_OUT_OF_MEM an error occured while allocating memory
</li> * <li> KTB_ERR_DATA_INVALID <i> public</i>_key_bytes contain invalid data
</li> *
 * <br /><b><i>Note :</i></b> If an error occured, there is no public key created, and <i> public</i>_key
 * is set to NULL.
 */
	public native ktb_errno ktb_keys_public_key_import(byte[] public_key_bytes,AddressWrapper public_key);
/** Determine the size needed to hold a private key in a byte buffer.
 *
 * @param [in] key The private key to convert
 *
 * @return The size of the needed buffer, or 0 if <i> key</i> is invalid
 */
	public native long ktb_keys_private_key_export_size(long key);
/** Export a private key to an opaque byte buffer.
 *
 * @param [in] key The key to convert
 * @param [out] buffer The buffer that will receive the key
 *  @retval KTB_ERR_NO_ERROR no error occured
 * <br /><u>Possible return Value</u> : <br /><ul>
	*<li> KTB_ERR_INVALID_PARAMS if <i> key</i> of <i> buffer</i> is NULL
</li> * <li> KTB_ERR_DEST_BUFFER_TOO_SMALL <i> buffer</i> is too small to hold the
</li> * exported key
 *
 * <br /><b><i>Note :</i></b> When an error occur, <i> buffer</i> content is unspecified.
 */
	public native ktb_errno ktb_keys_private_key_export(long key,byte[] buffer);
/** Import back a byte buffer as a private key
 *
 * @param [in] private_key_bytes The bytes to convert back to a private key
 *  @param[out] private_key The resulting private key
 *
 * <br /><u>Possible return Value</u> : <br /><ul>
	*<li> KTB_ERR_NO_ERROR the private key was retrieved successfully
</li> * <li> KTB_ERR_INVALID_PARAMS if <i> private</i>_key or <i> private</i>_key_bytes
</li> *                                is NULL
 * <li> KTB_ERR_DATA_INVALID <i> private</i>_key_bytes contain invalid data
</li> * <li> KTB_ERR_OUT_OF_MEM an error occured while allocating memory
</li> *
 * <br /><b><i>Note :</i></b> If an error occured, there is no private key created.
 */
	public native ktb_errno ktb_keys_private_key_import(byte[] private_key_bytes,AddressWrapper private_key);
/**
 * Generate a pair of public/private keys.
 *
 * @todo
 * Add a paragraph describing the recommended key sizes for
 * different levels of security, in particular mentioning the
 * size one should pick assuming the use of a block cipher of
 * a particular "strength".
 *
 * @param [in] prng The PRNG to use to generate a random key
 * @param [in] curve_id The Arcana-ECDB identifier of the curve used to generate
 * this keypair.
 * @param [out] public_key The place to put the generated public key
 * @param [out] private_key The place to put the generated private key
 *
 * <br /><u>Possible return Value</u> : <br /><ul>
	*<li> KTB_ERR_NO_ERROR the keys were generated successfuly
</li> * <li> KTB_ERR_INVALID_PARAMS one of the parameter was NULL,
</li> * or <i> keysize</i> is invalid
 * <li> KTB_ERR_OUT_OF_MEM an error occured while allocating memory
</li> *
 * @return This function can also return an error value from
 * ktb_prng_fill_buffer()
 *
 * <br /><b><i>Note :</i></b> If an error happen, no keys are created, and <i> public</i>_key and <i>
*private</i>_key are set to NULL.
 */
	public native ktb_errno ktb_keys_generate_keypair(long prng,String curve_id,AddressWrapper public_key,AddressWrapper private_key);
/** Return the size needed to encode a buffer in radix64
 *
 *  @return
 * The full size needed to hold the encoded result, without the terminating
 * NULL character.
 */
	public native long ktb_radix64_encode_size(long input_size);
/** Convert a byte sequence to a radix64 encoded string
 *
 * @param [in] input
 * The input buffer
 *
 *  @a input buffer
 *
 * @param [out] result
 * A place to put the encoded string
 *
 *  @a result buffer. The needed size can be retrieved with
 * ktb_radix64_encode_size()
 *
 * <br /><u>Possible return Value</u> : <br /><ul>
	*<li> KTB_ERR_NO_ERROR
</li> * success
 *
 * <li> KTB_ERR_DEST_BUFFER_TOO_SMALL
</li> * The <i> result</i> buffer is too small to hold the encoded result
 *
 * @return
 * This function can return any error code from ktb_hash_block().
 *
 * <br /><b><i>Note :</i></b>
 * If an error occur, the content of <i> result</i> is undefined.
 *
 * <br /><b><i>Note :</i></b>
 * The function does not add the terminal NULL character; it is the
 * responsibility of the caller to do so if needed.
 */
	public native ktb_errno ktb_radix64_encode(byte[] input,byte[] result);
/** Return the size needed to decode a radix64 encoded string
 *
 * @param [in] input
 * The input buffer
 *
 *  @a input buffer
 *
 * @return
 * 0 if the input buffer is invalid, or the size needed to hold the decoded
 * content of <i> input</i> with ktb_radix64_decode
 */
	public native long ktb_radix64_decode_size(byte[] input);
/** Convert a radix64 string into a byte sequence
 *
 * @param [in] input
 * The source radix64 encoded string
 *
 *  @a input
 *
 * @param [out] result
 * A place to hold the decoded buffer
 *
 *  @a result buffer
 *
 * @return
 * This function can return the same error code as ktb_base64_decode
 */
	public native ktb_errno ktb_radix64_decode(byte[] input,byte[] result);
/** Check the CRC24 of a radix64 string
 *
 * @param [in] input
 * The input buffer
 *
 *  @param[out] verified
 * This boolean will be set to @c true if the CRC is valid, @c false
 * otherwise.
 *
 * <br /><u>Possible return Value</u> : <br /><ul>
	*<li> KTB_ERR_NO_ERROR
</li> * No error occured during the verification. This is not indicating that the
 * CRC is verified; see <i> verified</i> for that.
 *
 * <li> KTB_ERR_INVALID_PARAMS
</li> * <i> verified</i> is NULL or another parameter is invalid.
 *
 * <li> KTB_ERR_DATA_INVALID
</li> * The input data is not a valid radix64 input.
 *
 * @return
 * This function can also return error codes from ktb_radix64_decode(),
 * ktb_hash_block() or ktb_base64_encode()
 */
	public native ktb_errno ktb_radix64_verify(byte[] input,BoolWrapper verified);
/** Create a block cipher context.
     *
     * @param [out] ctx The context to initialize
     * @param [in] algo The cipher algorithm to use with this context
     * @param [in] mode The cipher mode to use with this context
     * @param [in] encryption Specify the direction of this cipher. Set to true
     * to create an ciphering context, or false to get a deciphering context.
     *
     * <br /><u>Possible return Value</u> : <br /><ul>
	*<li> KTB_ERR_UNKNOWN_CIPHER_ALGO An invalid cipher algorithm is
</li>     * specified in <i> algo</i>
     * <li> KTB_ERR_UNKNOWN_CIPHER_MODE An invalid cipher mode is specified
</li>     * in <i> mode</i>
     * <li> KTB_ERR_OUT_OF_MEM An error occured while allocating memory
</li>     *
     * @return @see KTB_ERR_NO_ERROR in case of success, or an error code when
     * something wrong happened.
     */
	public native ktb_errno ktb_cipher_init(AddressWrapper ctx,ktb_cipher_algo_t algo,ktb_cipher_mode_t mode,boolean encryption);
/** Release the memory associated with a block cipher context.
     *
     * @param [in] ctx The initialized context to clear
     *
     * <br /><b><i>Note :</i></b> This function must be called on every context initialized with
     * ktb_cipher_init(), even if an error occur during operations.
     */
	public native void ktb_cipher_clear(long ctx);
/** Reset a cipher context.
     *
     * @param [in] ctx An initialized context
     *
     * A reset cipher context can be reused with the same settings (key, ...)
     * but with a new input.
     *
     * @warning This function is not implemented for every algorithm/mode
     *
     * <br /><b><i>Note :</i></b> A new IV must be provided after a reset.
     */
	public native void ktb_cipher_reset(long ctx);
/** Set the key for use with the cipher context.
     *
     * @param [in] ctx An initialized context
     * @param [in] key The secret key to use for (de)ciphering
     *  @a key
     *
     * @return @see KTB_ERR_NO_ERROR in case of success, or an error code when
     * something wrong happened.
     *
     * <br /><b><i>Note :</i></b> The key must have a size compatible with the specified algorithm. The
     * needed key size can be retrieved by calling ktb_cipher_get_key_len().
     *
     * @attention A key must be set before the cipher context can be used
     * for encryption or decryption.
     */
	public native ktb_errno ktb_cipher_set_key(long ctx,byte[] key);
/** Set the IV for this cipher context
     *
     * @param [in] ctx An initialized context
     * @param [in] iv The initialization vector to use
     *  @a iv
     *
     * @return @see KTB_ERR_NO_ERROR in case of success, or an error code when
     * something wrong happened.
     *
     * <br /><b><i>Note :</i></b> The IV must have a size compatible with the specified mode of
     * operation. This size can be retrieved by calling ktb_cipher_get_iv_len().
     *
     * @attention If the cipher mode need an IV, it must be set before the
     * context can be used.
     */
	public native ktb_errno ktb_cipher_set_iv(long ctx,byte[] iv);
/** Puts <i> ctx</i>'s mode into authentication mode if possible.
     *
     * @param [in] ctx An initialized context
     * @param [in] auth_data The extra authentication data to use
     *  @a auth_data
     *
     * <br /><u>Possible return Value</u> : <br /><ul>
	*<li> KTB_ERR_NO_ERROR no error occured
</li>     * <li> KTB_ERR_NON_AUTHENTICATING_MODE the specified mode of operation
</li>     * can't provide authentication
     *
     * @return This function can also return other error codes.
     *
     * If Galois/Counter Mode (GCM) is being used, this function can be used to
     * set the additional authentication data (AAD).  If the AAD is set then
     * the integrity data will be generated; if it is not set then no
     * integrity data will be generated.
     *
     * If GCM is not being used, this function does nothing.
     */
	public native ktb_errno ktb_cipher_set_auth_data(long ctx,byte[] auth_data);
/** Return the size of the prefix to add to ciphered data.
     *
     * This function should be called before actual ciphering (before
     * ktb_cipher_encrypt_block) to inquiry the size of the prefix block.
     *
     * @param [in] ctx The initialized context that will be used to (de)cipher.
     *
     * @return The size of the prefix block. It can be 0; in this case, it is
     * not needed to call ktb_cipher_get_prefix() or ktb_cipher_set_prefix().
     * Otherwise, those calls are mandatory.
     */
	public native long ktb_cipher_get_prefix_size(long ctx);
/** Retrieve the prefix to add to ciphered data.
     *
     * This function should be called before the actual ciphering occur. The
     * prefix data it return must be prefixed to the ciphered data, and is part
     * of the ciphered data.
     *
     * @param [in] ctx The initialized context that will be used to cipher
     * @param [out] prefix A buffer to receive the prefix data
     *  @a prefix buffer. It must be at
     * least large enough to hold the number of bytes returned by
     * ktb_cipher_get_prefix_size().
     *
     * @return An error code
     * @todo Document error code
     */
	public native ktb_errno ktb_cipher_get_prefix(long ctx,byte[] prefix);
/** Feed the prefix to the cipher.
     *
     * This function must be called before deciphering occur, with the prefix
     * part. The prefix real size can be determined by calling
     * ktb_cipher_get_prefix_size().
     *
     * @param [in] ctx The initialized context that will be used to decipher
     * @param [in] prefix The received prefix data
     *  @return An error code
     * @todo Document error code
     */
	public native ktb_errno ktb_cipher_set_prefix(long ctx,byte[] prefix);
/** Return the size of the suffix to add to ciphered data.
     *
     * This function should be called after actual ciphering (after the last
     * ktb_cipher_encrypt_block()) to inquiry the size of the suffix block.
     *
     * @param [in] ctx The initialized context that was used to (de)cipher.
     *
     * @return The size of the suffix block. It can be 0; in this case, it is
     * not needed to call ktb_cipher_get_suffix(). Otherwise this call is
     * mandatory.
     */
	public native long ktb_cipher_get_suffix_size(long ctx);
/** Retrieve the suffix to add to ciphered data.
     *
     * This function should be called after the actual ciphering occured. The
     * suffix data it return must be suffixed to the ciphered data, and is part
     * of the ciphered data.
     *
     * @param [in] ctx The initialized context that was used to cipher
     * @param [out] suffix A buffer to receive the suffix data
     *  @a suffix buffer. It must be at
     * least large enough to hold the number of bytes returned by
     * ktb_cipher_get_suffix_size().
     *
     * @return An error code
     * @todo Document error code
     */
	public native ktb_errno ktb_cipher_get_suffix(long ctx,byte[] suffix);
/** Encrypt a block of bytes.
     *
     * @param [in] ctx An initialized context
     * @param [in] in A pointer to the buffer containing the input data
     *  @a in buffer
     * @param [out] out A pointer to a buffer that will receive the ciphered data
     *  @a out buffer
     *
     * @return @see KTB_ERR_NO_ERROR when no error occur, or an error code
     *
     * Works in-place or with two buffers. Can be called multiple times
     * to process large bits of data in pieces, however EVERY PIECE must
     * be a multiple of the block size of the underlying cipher (almost
     * always 16 bytes).  Again: this function may be called multiple times
     * with input whose length is a multiple of the block size, and after
     * that exactly ONE call can be made where the input length is not
     * a multiple of the block size.
     *
     * <br /><b><i>Note :</i></b> The block size of the underlying cipher/mode can be retrieved by
     * calling ktb_cipher_get_block_len()
     *
     * <br /><b><i>Note :</i></b> Some mode of operation (namely CBC) need the output size to ALWAYS
     * be a multiple of the block size, greater or equal to the size of the
     * input.
     */
	public native ktb_errno ktb_cipher_encrypt_block(long ctx,byte[] in,byte[] out);
/** Decrypt a block of bytes.
     *
     * @param [in] ctx An initialized context
     * @param [in] in The input data (the ciphered content)
     *  @a in buffer
     * @param [out] out A buffer that will receive the deciphered data
     *  @a out buffer
     *
     * @return @see KTB_ERR_NO_ERROR in case of success, or another error code
     *
     * See comment for ktb_cipher_encrypt_block().
     */
	public native ktb_errno ktb_cipher_decrypt_block(long ctx,byte[] in,byte[] out);
/** Finalize the authenticity tag computation.
     *
     * @param [in] ctx An initialized context
     *
     * This function must be called once, at the end of the
     * ciphering/deciphering operation, before the authenticity tag
     * can be retrieved. It is not needed when not using authenticity.
     */
	public native void ktb_cipher_finalise(long ctx);
/** Retrieve the authentication tag generated by the Galois/Counter Mode.
     *
     * @param [in] ctx An initialized context
     * @param [out] size The size of the generated MAC
     *
     * @return The generated MAC, or NULL if an error occured (no AAD set, or <i>
  *ctx</i> is not ready)
     *
     * If Galois/Counter Mode (GCM) is being used and if additional
     * authentication data (AAD) was set (using ktb_cipher_set_auth_data()),
     * this function returns the authentication tag generated by GCM.  The
     * tag should be sent to the recipient along with the AAD and the
     * ciphertext (from ktb_cipher_encrypt_block()).  The
     * recipient can then verify the authenticity of the data by comparing it's
     * own computed MAC with the received value.
     */
	public native byte[] ktb_cipher_get_mac(long ctx);
/** Return the size of the treated data.
     *
     * This function can be called at the end of operation (after the finalise
     * part, or if applicable after the ktb_cipher_set_suffix() call).
     *
     * When ciphering, this will return the number of ciphered bytes. When
     * deciphering, it will return the real number of deciphered bytes. It might
     * happen that deciphering return a buffer longer than the actual ciphered
     * data size; this function is then used to retrieve the original input size
     *
     * @param [in] ctx The context
     *
     * @return The real size of the processed data.
     */
	public native long ktb_cipher_get_data_size(long ctx);
/** Return the human readable name of a cipher algorithm.
     *
     * @param [in] algo The cipher algorithm identifier
     *
     * @return A null-terminated string containing the name of the algorithm.
     */
	public native String ktb_cipher_get_name_from_algo(ktb_cipher_algo_t algo);
/** Return the human readable name of a cipher mode.
     *
     * @param [in] mode The cipher mode identifier
     *
     * @return A null-terminated string containing the name of the mode.
     */
	public native String ktb_cipher_get_name_from_mode(ktb_cipher_mode_t mode);
/** Return the length of the key needed by a context.
     *
     * @param [in] ctx An initialized context
     *
     * @return The length of the needed key, in bytes.
     */
	public native long ktb_cipher_get_key_len(long ctx);
/** Return the length of the cipher block for a context
     *
     * @param [in] ctx An initialized context
     *
     * @return The size of a block
     *
     * See ktb_cipher_encrypt_block() for information on how to use the cipher
     * block size.
     */
	public native long ktb_cipher_get_block_len(long ctx);
/** Return the length of the IV for a context
     *
     * @param [in] ctx An initialized context
     *
     * @return The size of the IV. If it return a positive value, this mean that
     * the IV size is fixed. When returning 0, it mean that any IV size can be
     * used.
     */
	public native long ktb_cipher_get_iv_len(long ctx);
/** Return the length of the MAC
     *
     * @param [in] ctx An initialized context
     *
     * @return The length of the MAC, if any.
     */
	public native long ktb_cipher_get_mac_size(long ctx);
/** Return the length of the IV for a given mode
     *
     * @param [in] mode A ciphering mode
     *
     * @return The size of the IV. If it return a positive value, this mean that
     * the IV size is fixed. When returning 0, it mean that any IV size can be
     * used.
     */
	public native long ktb_cipher_get_iv_len_from_mode(ktb_cipher_mode_t mode);
/** Initialise a hash context.
 *
 * @param [out] ctx The context to initialise.
 * @param [in] algo The hash algorithm to use.
 *
 * <br /><u>Possible return Value</u> : <br /><ul>
	*<li> KTB_ERR_NO_ERROR No error occured
</li> * <li> KTB_ERR_UNKNOWN_HASH_ALGO The <i> algo</i> value is invalid
</li> * <li> KTB_ERR_OUT_OF_MEM An error occured when trying to allocate memory
</li> */
	public native ktb_errno ktb_hash_init(AddressWrapper ctx,ktb_hash_algo_t algo);
/** Initialise an HMAC context.
 *
 * @param [out] ctx The context to initialise.
 * @param [in] algo The hash algorithm to use.
 * @param [in] key The key for the MAC.
 *  @a key.
 *
 * <br /><u>Possible return Value</u> : <br /><ul>
	*<li> KTB_ERR_NO_ERROR No error occured
</li> * <li> KTB_ERR_UNKNOWN_HASH_ALGO The <i> algo</i> value is invalid
</li> * <li> KTB_ERR_OUT_OF_MEM An error occured when trying to allocate memory
</li> */
	public native ktb_errno ktb_hash_init_hmac(AddressWrapper ctx,ktb_hash_algo_t algo,byte[] key);
/** Clear all resources associated with a hash context.
 *
 * @param [in] ctx An initialized context
 */
	public native void ktb_hash_clear(long ctx);
/** Reset a hash context.
 *
 * @param [in] ctx The hash context to reset.
 *
 * After calling ktb_hash_reset(), <i> ctx</i> will be in the state it was
 * immediately after ktb_hash_init() or ktb_hash_init_hmac() was called.
 * Calling ktb_hash_reset() is faster than clearing and then reinitialising
 * <i> ctx</i>.
 */
	public native void ktb_hash_reset(long ctx);
/** Process a block of data.
 *
 * Append the contents of <i> buf</i> to the stream of data being hashed.
 *
 * @param [in] ctx An initialized context
 * @param [in] buf Pointer to the block of memory to be hashed.
 *  @a buf.
 */
	public native void ktb_hash_process(long ctx,byte[] buf);
/** Finalise the hash computation.
 *
 * @param [in] ctx An initialized context
 *
 * This function should be called only once, after all the data has
 * been processed with ktb_hash_process() and before the actual hash
 * value has been retrieved with ktb_hash_retrieve().
 */
	public native void ktb_hash_finalise(long ctx);
/** Retrieve the computed hash.
 *
 * @param [in] ctx An initialized context
 * @param [out] size The size of the returned buffer. This can be NULL if the size
 * is already known.
 *
 * @return A pointer to the computed hash value.  The pointer will point to a
 * block of memory of length ktb_hash_get_len() bytes.
 * 
 * @warning This function can only be called after calling ktb_hash_finalise().
 */
	public native byte[] ktb_hash_retrieve(long ctx);
/** Return a human-readable name of the hash algorithm associated
 * with a given context.
 *
 * @param [in] ctx An initialized context
 *
 * @return A string containing the name of the hash algorithm.
 *
 * @warning The returned string should not be freed or modified in any way.
 * If the string must be modified, make a copy of it and modify the copy.
 */
	public native String ktb_hash_get_name(long ctx);
/** Return a human-readable name of the hash algorithm.
 *
 * @param [in] algo The hash algorithm
 *
 * @return A string containing the name of the hash algorithm.
 *
 * @warning The returned string should not fe free()ed or modified in any way.
 */
	public native String ktb_hash_get_name_from_algo(ktb_hash_algo_t algo);
/** Return the length in bytes of the hash value that the given context
 * will produce.
 *
 * @param [in] ctx The context the length of whose hash value we are interested in
 *
 * @return The length in bytes of the hash value produced by <i> ctx</i>.
 */
	public native long ktb_hash_get_len(long ctx);
/** Return he length in bytes of the hash value that the given
 * algorithm will produce.
 *
 * @param [in] algo An algorithm identifier
 *
 * @return The length in bytes of the hash value produced by a context
 * initialised with <i> algo</i>.
 */
	public native long ktb_hash_get_len_from_algo(ktb_hash_algo_t algo);
/** Return the length in bytes of the block size of the given context.
 *
 * @param [in] ctx The context whose block size we want.
 *
 * @return The length in bytes of the block size of the hash algorithm associated
 * with <i> ctx</i>.
 * 
 * <br /><b><i>Note :</i></b> Most people will have no use for this function, but we expose it
 * anyway. It's used only in the HMAC code.
 */
	public native long ktb_hash_get_block_size(long ctx);
/** Hash a block of memory.
 *
 * @param [in] algo The hash algorithm to use.
 * @param [in] block The block of data to hash.
 *  @a block.
 * @param [out] result The location where the computed hash should be put.
 *  @a result.
 *
 * @return An error if any step in the hash computation failed, or if 
 * <i> result</i>_size is too small to contain the computed hash.
 * 
 * <br /><b><i>Note :</i></b>
 * <i> result</i> must already refer to an available block of memory of
 * at least <i> result</i>_size bytes.  Moreover, <i> result</i>_size must be at
 * least ktb_hash_get_len_from_algo() bytes long.
 *
 * This function is (roughly) equivalent to the following code:
 * @code
 *     ktb_hash_ctx_t ctx;
 *     ktb_hash_init(&ctx, algo);
 *     ktb_hash_process(ctx, block, blocklen);
 *     ktb_hash_finalise(ctx);
 *     memcpy(result, ktb_hash_retrieve(ctx), result_size);
 *     ktb_hash_clear(ctx);
 * @endcode
 */
	public native ktb_errno ktb_hash_block(ktb_hash_algo_t algo,byte[] block,byte[] result);
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
	public native int ktb_curves_count();
/** Return a curve identifier, to be used throughout the KTB.
 *
 * All available curves are identified with a unique null-terminated string.
 * This function make it possible to retrieve those identifiers at run-time,
 * effectively avoiding the need to hardcode them.
 *
 * @param [in] index The curve index. This value must be greater or equal to 0 and
 * less than the value returned bt ktb_curves_count().
 *
 * @return The corresponding curve identifier. The returned value must not be
 * freed, since it is managed by the library.
 */
	public native String ktb_curves_id(int index);
/** Determine the size of a string needed to hold a base64 encoded buffer.
 *
 *  @return
 * The size needed to hold the base64 encoded buffer, without the terminal
 * NULL character.
 */
	public native long ktb_base64_encode_size(long input_size);
/** Convert a byte sequence to a base64-printable string.
 *
 * @param [in] input
 * The input buffer
 *
 *  @a input buffer
 *
 * @param [out] result
 * A buffer to hold the converted string. It must be large enough to hold
 * the converted string without the terminating NULL character.
 *
 *  @a result buffer. The size needed to hold the encoded
 * string can be retrieved with ktb_base64_encode_size().
 *
 * <br /><u>Possible return Value</u> : <br /><ul>
	*<li> KTB_ERR_NO_ERROR
</li> * no error occured
 *
 * <li> KTB_ERR_DEST_BUFFER_TOO_SMALL 
</li> * The <i> result</i> buffer is too small to hold the converted result
 *
 * <li> KTB_ERR_INVALID_PARAMS 
</li> * Parameters <i> input</i> or <i> result</i> is NULL.
 *
 * <br /><b><i>Note :</i></b>
 * If an error occur, the content of <i> result</i> is undefined.
 *
 * <br /><b><i>Note :</i></b>
 * This function will not set the final NULL character in <i> result</i>; it is
 * the responsibility of the caller to do so if needed.
 */
	public native ktb_errno ktb_base64_encode(byte[] input,byte[] result);
/** Return the size of the buffer needed for ktb_base64_decode()
 *
 * @param [in] input
 * The base64 encoded string
 *
 *  @a input
 *
 * @return
 * The size of the buffer needed to hold the decoded string, or 0 if input
 * is NULL.
 */
	public native long ktb_base64_decode_size(byte[] input);
/** Convert a base64 encoded string into a byte sequence.
 *
 * @param [in] input
 * The source base64 string
 *
 *  @a input
 *
 * @param [out] result
 * The place to put the decoded sequence. It must be large enough.
 *
 *  @a result buffer. The size needed to hold the decoded
 * buffer can be retrieved with ktb_base64_decode_size().
 *
 * <br /><u>Possible return Value</u> : <br /><ul>
	*<li> KTB_ERR_NO_ERROR
</li> * success
 *
 * <li> KTB_ERR_DEST_BUFFER_TOO_SMALL 
</li> * The <i> result</i> buffer is too small to hold the result
 *
 * <li> KTB_ERR_INVALID_PARAMS
</li> * Parameters <i> input</i> or <i> result</i> is NULL
 *
 * <li> KTB_ERR_DATA_INVALID 
</li> * Parameter <i> input</i> contain invalid data
 *
 * <br /><b><i>Note :</i></b>
 * If an error occur, the content of <i> result</i> is undefined.
 */
	public native ktb_errno ktb_base64_decode(byte[] input,byte[] result);
}
