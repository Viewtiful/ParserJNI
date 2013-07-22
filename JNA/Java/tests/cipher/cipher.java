import java.io.IOException;
import java.io.FileInputStream;
import java.io.InputStream;
import java.io.FileOutputStream;
import java.io.OutputStream;

public class cipher {
	public static void main(String[] args) {
		ArcanaJNI aJNI = new ArcanaJNI();
		cipher c = new cipher();

		byte[] password = new byte[] { (byte) 1, (byte) 14, (byte) 3 };
		ArcanaJNI.AddressWrapper ctx = new ArcanaJNI.AddressWrapper();

		if (aJNI.ktb_init() == ArcanaJNI.ktb_errno.KTB_ERR_NO_ERROR) {
			System.out.println("ktb init ok");
		}

		if (aJNI.ktb_cipher_init(ctx,
				ArcanaJNI.ktb_cipher_algo_t.KTB_CIPHER_ALGO_AES256,
				ArcanaJNI.ktb_cipher_mode_t.KTB_CIPHER_MODE_CBC, true) == ArcanaJNI.ktb_errno.KTB_ERR_NO_ERROR) {

			System.out.println("ktb_cipher_init ok");
		}

		long key_size = aJNI.ktb_cipher_get_key_len(ctx.getAddress());
		System.out.println("key size : " + key_size);

		byte[] key = c.generate_key(aJNI, password, key_size);

		StringBuilder sb = new StringBuilder();
		for (byte b : key)
			sb.append(String.format("%02X ", b));
		System.out.println(sb.toString());

		if (aJNI.ktb_cipher_set_key(ctx.getAddress(), key) == ArcanaJNI.ktb_errno.KTB_ERR_NO_ERROR) {
			System.out.println("ktb_cipher_set_key ok");
		}

		long iv_size = aJNI.ktb_cipher_get_iv_len(ctx.getAddress());

		System.out.println("iv_size : " + iv_size);

		byte[] iv = c.random(aJNI, iv_size);

		if (aJNI.ktb_cipher_set_iv(ctx.getAddress(), iv) == ArcanaJNI.ktb_errno.KTB_ERR_NO_ERROR) {
			System.out.println("ktb_cipher_set_iv ok");
		}

		try {
			InputStream ios = new FileInputStream("data.txt");
			OutputStream oos = new FileOutputStream("data_cipher.txt");

			oos.write(iv);
			// Useless, just trying if it's working
			System.out.println("ktb_cipher_get_prefix_size : "
					+ aJNI.ktb_cipher_get_prefix_size(ctx.getAddress()));

			boolean pad_output_size = true;
			long block_size = aJNI.ktb_cipher_get_block_len(ctx.getAddress());
			System.out.println("block_size : " + block_size);
			long buffer_size = (4096 / block_size) * block_size;
			byte[] data = new byte[(int) (long) buffer_size];
			int read = 0;

			do {

				read = ios.read(data);
				if (read > 0) {
					long blockrounded_read_count;

					if (pad_output_size) {
						blockrounded_read_count = (read / block_size)
								* block_size;

						if (read % block_size != 0) {
							blockrounded_read_count += block_size;
						}
					} else {
						blockrounded_read_count = read;
					}

					byte[] buffer_in = new byte[read];
					System.arraycopy(data, 0, buffer_in, 0, buffer_in.length);

					byte[] buffer_out = new byte[(int) (long) blockrounded_read_count];
					System.arraycopy(data, 0, buffer_out, 0, buffer_out.length);

					if (aJNI.ktb_cipher_encrypt_block(ctx.getAddress(),
							buffer_in, buffer_out) == ArcanaJNI.ktb_errno.KTB_ERR_NO_ERROR) {
						System.out.println("ktb_cipher_encrypt_block ok");
					}

					oos.write(buffer_out);
				}
			} while (read == buffer_size);

			aJNI.ktb_cipher_finalise(ctx.getAddress());

			long suffix_size = aJNI
					.ktb_cipher_get_suffix_size(ctx.getAddress());
			System.out.println("suffix_size : " + suffix_size);

			if (suffix_size > 0) {
				byte[] suffix = new byte[(int) (long) suffix_size];

				aJNI.ktb_cipher_get_suffix(ctx.getAddress(), suffix);
				oos.write(suffix);
			}

			aJNI.ktb_cipher_clear(ctx.getAddress());

			if (aJNI.ktb_cipher_init(ctx,
					ArcanaJNI.ktb_cipher_algo_t.KTB_CIPHER_ALGO_AES256,
					ArcanaJNI.ktb_cipher_mode_t.KTB_CIPHER_MODE_CBC, false) == ArcanaJNI.ktb_errno.KTB_ERR_NO_ERROR) {

				System.out.println("ktb_cipher_init ok");
			}
			key_size = aJNI.ktb_cipher_get_key_len(ctx.getAddress());
			System.out.println("key size : " + key_size);

			key = c.generate_key(aJNI, password, key_size);

			if (aJNI.ktb_cipher_set_key(ctx.getAddress(), key) == ArcanaJNI.ktb_errno.KTB_ERR_NO_ERROR) {
				System.out.println("ktb_cipher_set_key ok");
			}

			ios.close();
			oos.close();

			OutputStream oos2 = new FileOutputStream("decipher.txt");
			InputStream ios2 = new FileInputStream("data_cipher.txt");

			iv_size = aJNI.ktb_cipher_get_iv_len(ctx.getAddress());
			System.out.println("iv_size : " + iv_size);
			iv = new byte[(int) (long) iv_size];

			ios2.read(iv);

			if (aJNI.ktb_cipher_set_iv(ctx.getAddress(), iv) == ArcanaJNI.ktb_errno.KTB_ERR_NO_ERROR) {
				System.out.println("ktb_cipher_set_iv ok");
			}

			buffer_size = (4096 / block_size) * block_size;
			byte[] data2 = new byte[(int) (long) buffer_size];
			System.out.println("buffer_size : " + buffer_size);
			long prefix_size = aJNI
					.ktb_cipher_get_prefix_size(ctx.getAddress());
			System.out.println("prefix_size : " + prefix_size);
			do {
				read = ios2.read(data2);

				if (read > 0) {
					byte[] buffer_out = new byte[read];
					System.arraycopy(data2, 0, buffer_out, 0, buffer_out.length);

					if (aJNI.ktb_cipher_decrypt_block(ctx.getAddress(),
							buffer_out, buffer_out) == ArcanaJNI.ktb_errno.KTB_ERR_NO_ERROR) {
						System.out.println("ktb_cipher_decrypt_block ok");
					} else {
						System.out.println("ktb_cipher_decrypt_block probleme");
					}

					oos2.write(buffer_out);
				}
			} while (read == buffer_size);

			aJNI.ktb_cipher_finalise(ctx.getAddress());

			long output_size = aJNI.ktb_cipher_get_data_size(ctx.getAddress());
			System.out.println("output_size : " + output_size);

			aJNI.ktb_cipher_clear(ctx.getAddress());
			oos2.close();
			ios2.close();
		} catch (IOException e) {
		}

		aJNI.ktb_clear();
	}

	byte[] random(ArcanaJNI aJNI, long iv_size) {
		byte[] result = new byte[(int) (long) iv_size];

		if (aJNI.ktb_prng_fill_buffer(0, result) == ArcanaJNI.ktb_errno.KTB_ERR_NO_ERROR) {
			System.out.println("ktb_prn_fill_buffer ok");
		}

		return result;
	}

	byte[] generate_key(ArcanaJNI aJNI, byte[] password, long key_size) {
		byte[] result = new byte[(int) (long) key_size];

		if (aJNI.ktb_kdf(ArcanaJNI.ktb_hash_algo_t.KTB_HASH_ALGO_SKEIN512,
				password, result) == ArcanaJNI.ktb_errno.KTB_ERR_NO_ERROR) {
			System.out.println("ktb_kdf ok");
		}

		return result;
	}

}
