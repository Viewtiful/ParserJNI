public class kep_dh_pass_t {
	public static void main(String[] args) {
		ArcanaJNI aJNI = new ArcanaJNI();

		//Initialization of the ktb.
		if(aJNI.ktb_init() == ArcanaJNI.ktb_errno.KTB_ERR_NO_ERROR) {
			System.out.println("ktb_init() ok");
		}

		//We create a Java class which call the JNI function which create the
		//C structure.
		ArcanaJNI.ktb_kep_dh_pass_t kep_dh_pass = aJNI.new ktb_kep_dh_pass_t();

		//We assign a values and try to print them.
		kep_dh_pass.cipher_algo = 
			ArcanaJNI.ktb_cipher_algo_t.KTB_CIPHER_ALGO_AES128;
		System.out.println("Valeur de kep_dh.cipher_algo : " +
				kep_dh_pass.cipher_algo);

		//We need a key for the discussion between the pair, creating a "fake
		//key" with the function ktb_keys_generate_keypair.
		ArcanaJNI.AddressWrapper public_key = new ArcanaJNI.AddressWrapper();
		ArcanaJNI.AddressWrapper private_key = new ArcanaJNI.AddressWrapper();

		if( aJNI.ktb_keys_generate_keypair(0, "nistP521", public_key,
					private_key) == ArcanaJNI.ktb_errno.KTB_ERR_NO_ERROR) {
			System.out.println("ktb_keys_generate_keypair() ok");
		}

		long discuss_key_size = aJNI.ktb_keys_public_key_export_size(
				public_key.getAddress());
		System.out.println("Taille de discuss_key_size : " + discuss_key_size);

		byte[] discuss_key = new byte[(int) (long) discuss_key_size];

		if(aJNI.ktb_keys_public_key_export(public_key.getAddress(),
					discuss_key) == ArcanaJNI.ktb_errno.KTB_ERR_NO_ERROR) {
			System.out.println("ktb_keys_public_key_export() ok");
		}

		kep_dh_pass.discuss_key = discuss_key;
		kep_dh_pass.discuss_key_size = discuss_key_size;

		//We call the JNI function in order to assign to the C structure the
		//values from the Java class.
		kep_dh_pass.write();

		//We put a random value in each field, in order to see if by calling
		//read() we get the correct values we passed.
		kep_dh_pass.cipher_algo = 
			ArcanaJNI.ktb_cipher_algo_t.KTB_CIPHER_ALGO_AES192;
		System.out.println("Valeur de kep_dh_pass.cipher_algo : " +
				kep_dh_pass.cipher_algo);

		byte[] tab = new byte[] {(byte)1, (byte)2, (byte)3};

		kep_dh_pass.discuss_key = tab;
		StringBuilder sb = new StringBuilder();
		for(byte b : kep_dh_pass.discuss_key) 
			sb.append(String.format("%02X ", b));
		System.out.println(sb.toString());  
		kep_dh_pass.discuss_key_size = 3;
		System.out.println("Valeur de discuss_key_size : " +
				kep_dh_pass.discuss_key_size);

		kep_dh_pass.read();

		System.out.println("Valeur de kep_dh_pass.cipher_algo : " +
				kep_dh_pass.cipher_algo);
		StringBuilder sb2 = new StringBuilder();
		for(byte b : kep_dh_pass.discuss_key) 
			sb2.append(String.format("%02X ", b));
		System.out.println(sb2.toString());  
		System.out.println("Valeur de discuss_key_size : " +
				kep_dh_pass.discuss_key_size);

		
		//We "delete" the object, in order for the garbage collector to see 
		//that the object is not used anymore. We do that in order to see if
		//finalize() correctly call the JNI function which destroy the C
		//structure.
		kep_dh_pass = null;

		//We create a new object.
		kep_dh_pass = aJNI.new ktb_kep_dh_pass_t();

		//We try to read the value, of course it's a random value.
		kep_dh_pass.read();

		System.out.println("Valeur de kep_dh_pass.cipher_algo : " +
				kep_dh_pass.cipher_algo);
		StringBuilder sb3 = new StringBuilder();
		for(byte b : kep_dh_pass.discuss_key) 
			sb3.append(String.format("%02X ", b));
		System.out.println(sb3.toString());  
		System.out.println("Valeur de discuss_key_size : " +
				kep_dh_pass.discuss_key_size);

		aJNI.ktb_clear();
	}
}
