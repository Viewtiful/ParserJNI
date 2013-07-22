import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.InputStream;
import java.io.OutputStream;

public class kem {

	public static void main(String[] args) throws Exception {
		ArcanaJNI aJNI = new ArcanaJNI();

		if (aJNI.ktb_init() == ArcanaJNI.ktb_errno.KTB_ERR_NO_ERROR)
			System.out.println(Utils.getCurrentTime() + "ktb_init() ok");
		else {
			System.out.println(Utils.getCurrentTime()
					+ "Error while initializating ktb_init()");
			System.exit(1);
		}

		if (!kem.generateKey(aJNI)) {
			aJNI.ktb_clear();
			System.exit(1);
		}

		if (!kem.retrieveKey(aJNI)) {
			aJNI.ktb_clear();
			System.exit(1);
		}

		aJNI.ktb_clear();
	}

	public static boolean generateKey(ArcanaJNI aJNI) throws Exception {
		ArcanaJNI.AddressWrapper public_key = new ArcanaJNI.AddressWrapper();

		File file = new File("public_key.txt");
		InputStream ios = new FileInputStream(file);
		int key_buffer_size = (int) file.length();
		byte[] key_buffer = new byte[key_buffer_size];

		System.out.println("key_buffer_size : " + key_buffer_size);

		ios.read(key_buffer);

		if (aJNI.ktb_keys_public_key_import(key_buffer, public_key) == ArcanaJNI.ktb_errno.KTB_ERR_NO_ERROR)
			System.out.println(Utils.getCurrentTime()
					+ "ktb_keys_public_key_import() ok");
		else {
			System.out.println(Utils.getCurrentTime()
					+ "Error at ktb_keys_public_key_import()");
			Utils.freeBuffer(key_buffer);
			public_key = null;
			ios.close();
			return false;
		}

		byte[] secret_key = new byte[128];

		long encapsulated_size = aJNI.ktb_kem_psec_encrypt_size(public_key
				.getAddress());
		System.out.println("encapsulated_size : " + encapsulated_size);

		byte[] encapsulated = new byte[(int) (long) encapsulated_size];

		if (aJNI.ktb_kem_psec_encrypt(
				ArcanaJNI.ktb_hash_algo_t.KTB_HASH_ALGO_SKEIN512, 0,
				public_key.getAddress(), secret_key, encapsulated) == ArcanaJNI.ktb_errno.KTB_ERR_NO_ERROR)
			System.out.println(Utils.getCurrentTime()
					+ "ktb_kem_psec_encrypt() ok");
		else {
			System.out.println(Utils.getCurrentTime()
					+ "Error at ktb_kem_psec_encrypt()");
			Utils.freeBuffer(key_buffer);
			Utils.freeBuffer(encapsulated);
			Utils.freeBuffer(secret_key);
			public_key = null;
			ios.close();
			return false;
		}

		OutputStream oos = new FileOutputStream("secret_key.txt");
		OutputStream oos2 = new FileOutputStream("encapsulated.txt");

		oos.write(secret_key);
		oos2.write(encapsulated);

		oos.close();
		oos2.close();
		Utils.freeBuffer(key_buffer);
		Utils.freeBuffer(encapsulated);
		Utils.freeBuffer(secret_key);
		aJNI.ktb_keys_public_key_clear(public_key.getAddress());
		public_key = null;
		ios.close();

		return true;
	}

	public static boolean retrieveKey(ArcanaJNI aJNI) throws Exception {
		ArcanaJNI.AddressWrapper private_key = new ArcanaJNI.AddressWrapper();

		File file = new File("private_key.txt");
		InputStream ios = new FileInputStream(file);
		int key_buffer_size = (int) file.length();
		byte[] key_buffer = new byte[key_buffer_size];

		System.out.println("key_buffer_size : " + key_buffer_size);

		ios.read(key_buffer);

		if (aJNI.ktb_keys_private_key_import(key_buffer, private_key) == ArcanaJNI.ktb_errno.KTB_ERR_NO_ERROR)
			System.out.println(Utils.getCurrentTime()
					+ "ktb_keys_private_key_import() ok");
		else {
			System.out.println(Utils.getCurrentTime()
					+ "Error at ktb_keys_private_key_import()");
			Utils.freeBuffer(key_buffer);
			private_key = null;
			ios.close();
			return false;
		}

		byte[] secret_key = new byte[128];

		File file2 = new File("encapsulated.txt");
		InputStream ios2 = new FileInputStream(file2);
		long encapsulated_size = (int) file2.length();
		byte[] encapsulated = new byte[(int) (long) encapsulated_size];

		System.out.println("encapsulated_size : " + encapsulated_size);

		ios2.read(encapsulated);

		if (aJNI.ktb_kem_psec_decrypt(
				ArcanaJNI.ktb_hash_algo_t.KTB_HASH_ALGO_SKEIN512,
				private_key.getAddress(), encapsulated, secret_key) == ArcanaJNI.ktb_errno.KTB_ERR_NO_ERROR)
			System.out.println(Utils.getCurrentTime()
					+ "ktb_kem_psec_decrypt() ok");
		else {
			System.out.println(Utils.getCurrentTime()
					+ "Error at ktb_kem_psec_decrypt()");
			Utils.freeBuffer(key_buffer);
			Utils.freeBuffer(encapsulated);
			Utils.freeBuffer(secret_key);
			private_key = null;
			ios.close();
			return false;
		}

		OutputStream oos = new FileOutputStream("secret_key2.txt");

		oos.write(secret_key);

		oos.close();
		
		Utils.freeBuffer(key_buffer);
		Utils.freeBuffer(encapsulated);
		Utils.freeBuffer(secret_key);
		aJNI.ktb_keys_private_key_clear(private_key.getAddress());
		private_key = null;
		ios.close();

		return true;
	}
}
