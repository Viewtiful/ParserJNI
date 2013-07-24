import java.io.FileOutputStream;
import java.io.OutputStream;

public class kep
{
	public static void main(String[] args) throws Exception{
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

		for(int i = 0; i < nbCurve; ++i) {
			System.out.println(aJNI.ktb_curves_id(i));
		}


		ArcanaJNI.ktb_kep_sts_t algo_params = aJNI.new ktb_kep_sts_t();
		ArcanaJNI.AddressWrapper ctx = new ArcanaJNI.AddressWrapper();
		ArcanaJNI.AddressWrapper public_key = new ArcanaJNI.AddressWrapper();
		ArcanaJNI.AddressWrapper private_key = new ArcanaJNI.AddressWrapper();  
		long shared_key_size = 64;

		if( aJNI.ktb_keys_generate_keypair(0, "nistP521", public_key, private_key) == ArcanaJNI.ktb_errno.KTB_ERR_NO_ERROR) {
			System.out.println("ktb_keys_generate_keypair ok");   
		}

		algo_params.cipher_algo = ArcanaJNI.ktb_cipher_algo_t.KTB_CIPHER_ALGO_AES256;
		algo_params.peer_public_key = public_key.getAddress();
		algo_params.self_private_key = private_key.getAddress();
		algo_params.write();
		algo_params.read();

		if(aJNI.ktb_kep_init(ctx, 0, ArcanaJNI.ktb_kep_algo_t.KTB_KEP_ALGO_STS, algo_params.getMInternal().getAddress(), algo_params.struct_size, "nistP521", ArcanaJNI.ktb_hash_algo_t.KTB_HASH_ALGO_SHA512, shared_key_size, 2) == ArcanaJNI.ktb_errno.KTB_ERR_NO_ERROR) {
			System.out.println("ktb_kep_init ok");   
		}
		else {
			byte[] resultat = new byte[256];
			aJNI.ktb_strerror(ArcanaJNI.ktb_errno.KTB_ERR_INVALID_PARAMS, resultat);

			StringBuilder sb = new StringBuilder();
			for(byte b : resultat) 
				sb.append(String.format("%02X ", b));
			System.out.println(sb.toString());
			System.out.println("probleme");   
		}

		ArcanaJNI.BoolWrapper cont = new ArcanaJNI.BoolWrapper();
		int iter_max_left = 10;

		do {
			byte[] data = aJNI.ktb_kep_get_data(ctx.getAddress());
			if(aJNI.ktb_kep_put_data(ctx.getAddress(), data, cont) == ArcanaJNI.ktb_errno.KTB_ERR_NO_ERROR) {
				System.out.println("ktb_kep_put_data ok");
			}
		} while (cont.getValue() && (--iter_max_left >= 0));

		byte[] secret_key = new byte[(int) (long)shared_key_size];
		if(aJNI.ktb_kep_finalise(ctx.getAddress(), secret_key) == ArcanaJNI.ktb_errno.KTB_ERR_NO_ERROR) {
			System.out.println("ktb_kep_finalise ok");
		}

		System.out.println("Generated key : ");
		StringBuilder sb = new StringBuilder();
		for(byte b : secret_key) 
			sb.append(String.format("%02X ", b));
		System.out.println(sb.toString());

	aJNI.ktb_keys_public_key_clear(public_key.getAddress());
	aJNI.ktb_keys_private_key_clear(private_key.getAddress());
	aJNI.ktb_kep_clear(ctx.getAddress());

	aJNI.ktb_clear();
	long endTime = System.currentTimeMillis() - startTime;
	System.out.println(endTime + "ms");
}
}
