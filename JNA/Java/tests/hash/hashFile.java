import java.io.IOException;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.InputStream;

public class hashFile {

	public static void main(String[] args) throws Exception {

		ArcanaJNI aJNI = new ArcanaJNI();

		if (aJNI.ktb_init() == ArcanaJNI.ktb_errno.KTB_ERR_NO_ERROR)
			System.out.println(Utils.getCurrentTime() + "ktb_init() ok");
		else {
			System.out.println(Utils.getCurrentTime()
					+ "Error while initializating ktb_init()");
			System.exit(1);
		}

		if (!hashFile.hashToFile(aJNI)) {
			aJNI.ktb_clear();
			System.exit(1);
		}

		aJNI.ktb_clear();
	}

	public static boolean hashToFile(ArcanaJNI aJNI) throws Exception {
		ArcanaJNI.AddressWrapper ctx = new ArcanaJNI.AddressWrapper();
		ArcanaJNI.ktb_hash_algo_t HASH_ALGO = ArcanaJNI.ktb_hash_algo_t.KTB_HASH_ALGO_SHA512;

		if (aJNI.ktb_hash_init(ctx, HASH_ALGO) == ArcanaJNI.ktb_errno.KTB_ERR_NO_ERROR)
			System.out.println(Utils.getCurrentTime() + "ktb_hash_init() ok");
		else {
			System.out.println(Utils.getCurrentTime()
					+ "Error while initializating ktb_hash_init()");
			ctx = null;
			return false;
		}

		int BUFLEN = 512;
		byte[] data = new byte[BUFLEN];

		InputStream ios = new FileInputStream("texte.txt");


		while (ios.read(data) > 0) {
			aJNI.ktb_hash_process(ctx.getAddress(), data);
		}
		aJNI.ktb_hash_finalise(ctx.getAddress());

		byte[] hash = aJNI.ktb_hash_retrieve(ctx.getAddress());

		Utils.printBuffer(hash);
		
		Utils.freeBuffer(hash);
		ios.close();
		return true;

	}
}
