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

	public class ktb_kep_dh_t {
		int dummy;	}

	public class ktb_kep_dh_pass_t {
		ktb_cipher_algo_t cipher_algo;		byte discuss_key;		long discuss_key_size;	}

	public class ktb_kep_sts_t {
		ktb_cipher_algo_t cipher_algo;		long peer_public_key;		long self_private_key;	}

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

	public native ktb_errno ktb_sign_init(AddressWrapper ctx,ktb_hash_algo_t algo);
	public native void ktb_sign_clear(long ctx);
	public native ktb_errno ktb_sign_reset(long ctx);
	public native ktb_errno ktb_sign_process(long ctx,byte[] data,long data_size);
	public native ktb_errno ktb_sign_finalise(long ctx);
	public native ktb_errno ktb_sign_set_public_key(long ctx,long public_key);
	public native ktb_errno ktb_sign_verify(long ctx,byte[] signature,long signature_size,BoolWrapper is_valid);
	public native ktb_errno ktb_sign_verify_block(ktb_hash_algo_t algo,long public_key,byte[] data,long data_size,byte[] signature,long signature_size,BoolWrapper is_valid);
	public native ktb_errno ktb_sign_set_private_key(long ctx,long private_key,long prng);
	public native long ktb_sign_get_sign_size(long ctx);
	public native byte[] ktb_sign_get_sign(long ctx);
	public native long ktb_sign_get_sign_size_from_key(long private_key);
	public native ktb_errno ktb_sign_sign_block(ktb_hash_algo_t algo,long prng,long private_key,byte[] data,long data_size,byte[] signature,long signature_size);
	public native ktb_errno ktb_kdf(ktb_hash_algo_t algo,byte[] seed,long seed_size,byte[] derived_key,long derived_key_size);
	public native ktb_errno ktb_pbkdf(ktb_hash_algo_t algo,byte[] passwd,long passwd_size,byte[] salt,long salt_size,long iteration_count,byte[] derived_key,long derived_key_size);
	public native long ktb_kdf_max_size(ktb_hash_algo_t algo);
	public native long ktb_kem_psec_encrypt_size(long peer_public_key);
	public native ktb_errno ktb_kem_psec_encrypt(ktb_hash_algo_t algo,long prng,long peer_public_key,byte[] secret_key,long secret_key_size,byte[] ciphertext,long ciphertext_size);
	public native ktb_errno ktb_kem_psec_decrypt(ktb_hash_algo_t algo,long self_private_key,byte[] input_ciphertext,long input_ciphertext_size,byte[] secret_key,long secret_key_size);
	public native void ktb_prng_clear(long prng);
	public native ktb_errno ktb_prng_reseed_with(long prng,byte[] buffer,long buffer_size);
	public native ktb_errno ktb_prng_reseed(long prng);
	public native ktb_errno ktb_prng_fill_buffer(long prng,byte[] buffer,long buffer_size);
	public native void ktb_keys_public_key_clear(long key);
	public native void ktb_keys_private_key_clear(long key);
	public native long ktb_keys_public_key_export_size(long public_key);
	public native ktb_errno ktb_keys_public_key_export(long public_key,byte[] result,long result_size);
	public native ktb_errno ktb_keys_public_key_import(byte[] public_key_bytes,long public_key_bytes_size,AddressWrapper public_key);
	public native long ktb_keys_private_key_export_size(long key);
	public native ktb_errno ktb_keys_private_key_export(long key,byte[] buffer,long buffer_size);
	public native ktb_errno ktb_keys_private_key_import(byte[] private_key_bytes,long private_key_bytes_size,AddressWrapper private_key);
	public native ktb_errno ktb_keys_generate_keypair(long prng,String curve_id,AddressWrapper public_key,AddressWrapper private_key);
	public native long ktb_radix64_encode_size(long input_size);
	public native ktb_errno ktb_radix64_encode(byte[] input,long input_size,byte[] result,long result_size);
	public native long ktb_radix64_decode_size(byte[] input,long input_size);
	public native ktb_errno ktb_radix64_decode(byte[] input,long input_size,byte[] result,long result_size);
	public native ktb_errno ktb_radix64_verify(byte[] input,long input_size,BoolWrapper verified);
	public native ktb_errno ktb_cipher_init(AddressWrapper ctx,ktb_cipher_algo_t algo,ktb_cipher_mode_t mode,boolean encryption);
	public native void ktb_cipher_clear(long ctx);
	public native void ktb_cipher_reset(long ctx);
	public native ktb_errno ktb_cipher_set_key(long ctx,byte[] key,long key_size);
	public native ktb_errno ktb_cipher_set_iv(long ctx,byte[] iv,long iv_size);
	public native ktb_errno ktb_cipher_set_auth_data(long ctx,byte[] auth_data,long auth_data_size);
	public native long ktb_cipher_get_prefix_size(long ctx);
	public native ktb_errno ktb_cipher_get_prefix(long ctx,byte[] prefix,long prefix_size);
	public native ktb_errno ktb_cipher_set_prefix(long ctx,byte[] prefix,long prefix_size);
	public native long ktb_cipher_get_suffix_size(long ctx);
	public native ktb_errno ktb_cipher_get_suffix(long ctx,byte[] suffix,long suffix_size);
	public native ktb_errno ktb_cipher_encrypt_block(long ctx,byte[] in,long in_size,byte[] out,long out_size);
	public native ktb_errno ktb_cipher_decrypt_block(long ctx,byte[] in,long in_size,byte[] out,long out_size);
	public native void ktb_cipher_finalise(long ctx);
	public native byte[] ktb_cipher_get_mac(long ctx);
	public native long ktb_cipher_get_data_size(long ctx);
	public native String ktb_cipher_get_name_from_algo(ktb_cipher_algo_t algo);
	public native String ktb_cipher_get_name_from_mode(ktb_cipher_mode_t mode);
	public native long ktb_cipher_get_key_len(long ctx);
	public native long ktb_cipher_get_block_len(long ctx);
	public native long ktb_cipher_get_iv_len(long ctx);
	public native long ktb_cipher_get_mac_size(long ctx);
	public native long ktb_cipher_get_iv_len_from_mode(ktb_cipher_mode_t mode);
	public native ktb_errno ktb_hash_init(AddressWrapper ctx,ktb_hash_algo_t algo);
	public native ktb_errno ktb_hash_init_hmac(AddressWrapper ctx,ktb_hash_algo_t algo,byte[] key,long key_size);
	public native void ktb_hash_clear(long ctx);
	public native void ktb_hash_reset(long ctx);
	public native void ktb_hash_process(long ctx,byte[] buf,long buf_size);
	public native void ktb_hash_finalise(long ctx);
	public native byte[] ktb_hash_retrieve(long ctx,long size);
	public native String ktb_hash_get_name(long ctx);
	public native String ktb_hash_get_name_from_algo(ktb_hash_algo_t algo);
	public native long ktb_hash_get_len(long ctx);
	public native long ktb_hash_get_len_from_algo(ktb_hash_algo_t algo);
	public native long ktb_hash_get_block_size(long ctx);
	public native ktb_errno ktb_hash_block(ktb_hash_algo_t algo,byte[] block,long block_size,byte[] result,long result_size);
	public native int ktb_curves_count();
	public native String ktb_curves_id(int index);
	public native long ktb_base64_encode_size(long input_size);
	public native ktb_errno ktb_base64_encode(byte[] input,long input_size,byte[] result,long result_size);
	public native long ktb_base64_decode_size(byte[] input,long input_size);
	public native ktb_errno ktb_base64_decode(byte[] input,long input_size,byte[] result,long result_size);
	public native ktb_errno ktb_kep_init(AddressWrapper ctx,long prng,ktb_kep_algo_t algo,long algo_data,long algo_data_size,String curve_id,ktb_hash_algo_t hash_algo,long secret_key_size,int peer_count);
	public native void ktb_kep_clear(long ctx);
	public native byte[] ktb_kep_get_data(long ctx);
	public native ktb_errno ktb_kep_put_data(long ctx,byte[] peer_data,long peer_data_size,BoolWrapper continue_exchange);
	public native ktb_errno ktb_kep_finalise(long ctx,byte[] secret_key,long secret_key_size);
	public native String ktb_kep_get_algo_name(ktb_kep_algo_t algo);
	public native ktb_errno ktb_init();
	public native void ktb_clear();
}
