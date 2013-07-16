import java.io.IOException;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.InputStream;

public class hashFile {

	public static void main(String[] args) {

		ArcanaJNI aJNI = new ArcanaJNI();

		if(aJNI.ktb_init() == ArcanaJNI.ktb_errno.KTB_ERR_NO_ERROR) {
			System.out.println("ktb_init ok");
		}

		ArcanaJNI.AddressWrapper ctx = new ArcanaJNI.AddressWrapper();
		ArcanaJNI.ktb_hash_algo_t HASH_ALGO = ArcanaJNI.ktb_hash_algo_t.KTB_HASH_ALGO_SHA512;

		if( aJNI.ktb_hash_init(ctx, HASH_ALGO) == ArcanaJNI.ktb_errno.KTB_ERR_NO_ERROR) {
			System.out.println("ktb_hash_init ok");
		}

		int BUFLEN = 512;
		byte[] data = new byte[BUFLEN];

		try {
			InputStream ios = new FileInputStream("texte.txt");

			int read = 0;

			while((read = ios.read(data)) > 0) {
				aJNI.ktb_hash_process(ctx.getAddress(), data);
			}
			aJNI.ktb_hash_finalise(ctx.getAddress());

			byte[] hash = aJNI.ktb_hash_retrieve(ctx.getAddress());

			StringBuilder sb = new StringBuilder();
			for(byte b : hash) 
				sb.append(String.format("%02X ", b));
			System.out.println(sb.toString());

		} catch( FileNotFoundException e) {


		}catch(IOException e) {

		}
	}
}
