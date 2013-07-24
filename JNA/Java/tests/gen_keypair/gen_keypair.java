import java.io.FileOutputStream;
import java.io.OutputStream;

public class gen_keypair {
	public static void main(String[] args) throws Exception {
		long startTime = System.currentTimeMillis();
		ArcanaJNI aJNI = new ArcanaJNI();

		if (aJNI.ktb_init() == ArcanaJNI.ktb_errno.KTB_ERR_NO_ERROR)
			System.out.println(Utils.getCurrentTime() + "ktb_init() ok");
		else {
			System.out.println(Utils.getCurrentTime()
					+ "Error while initializating ktb_init()");
			System.exit(1);
		}

		int nbCurve = aJNI.ktb_curves_count();
		System.out.println("nb curve : " + nbCurve);

		for (int i = 0; i < nbCurve; ++i) {
			System.out.println(aJNI.ktb_curves_id(i));
		}

		ArcanaJNI.AddressWrapper public_key = new ArcanaJNI.AddressWrapper();
		ArcanaJNI.AddressWrapper private_key = new ArcanaJNI.AddressWrapper();

		if (aJNI.ktb_keys_generate_keypair(0, "nistP521", public_key,
				private_key) == ArcanaJNI.ktb_errno.KTB_ERR_NO_ERROR) {
			System.out.println("ktb_keys_generate_keypair ok");
		}

		long public_buffer_size = aJNI
				.ktb_keys_public_key_export_size(public_key.getAddress());
		System.out.println("Taille public_buffer_size : " + public_buffer_size);
		
		byte[] public_buffer = new byte[(int) (long) public_buffer_size];
		if (aJNI.ktb_keys_public_key_export(public_key.getAddress(),
				public_buffer) == ArcanaJNI.ktb_errno.KTB_ERR_NO_ERROR) {
			System.out.println("ktb_keys_public_key_export ok");

			StringBuilder sb = new StringBuilder();
			for (byte b : public_buffer)
				sb.append(String.format("%02X ", b));
			System.out.println(sb.toString());

			OutputStream oos = new FileOutputStream("public_key.txt");
			oos.write(public_buffer);
			oos.close();
		}
		System.out.println("");

		long private_buffer_size = aJNI
				.ktb_keys_private_key_export_size(private_key.getAddress());
		System.out.println("Taille private_buffer_size : "
				+ private_buffer_size);
		
		byte[] private_buffer = new byte[(int) (long) private_buffer_size];
		if (aJNI.ktb_keys_private_key_export(private_key.getAddress(),
				private_buffer) == ArcanaJNI.ktb_errno.KTB_ERR_NO_ERROR) {
			System.out.println("ktb_keys_private_key_export ok");

			StringBuilder sb = new StringBuilder();
			for (byte b : private_buffer)
				sb.append(String.format("%02X ", b));
			System.out.println(sb.toString());

			OutputStream oos = new FileOutputStream("private_key.txt");
			oos.write(private_buffer);
			oos.close();
		}
		
		aJNI.ktb_clear();
		
		public_key = null;
		private_key = null;
		Utils.freeBuffer(public_buffer); 
		Utils.freeBuffer(private_buffer);
		
		long endTime = System.currentTimeMillis() - startTime;
		System.out.println(endTime + "ms");
	}
}
