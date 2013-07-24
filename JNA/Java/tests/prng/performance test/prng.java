public class prng {
	public static void main(String[] args) {
		long startTime = System.currentTimeMillis();
		ArcanaJNI aJNI = new ArcanaJNI();

		if (aJNI.ktb_init() == ArcanaJNI.ktb_errno.KTB_ERR_NO_ERROR)
			System.out.println(Utils.getCurrentTime() + "ktb_init() ok");
		else {
			System.out.println(Utils.getCurrentTime()
					+ "Error while initializating ktb_init()");
			System.exit(1);
		}

		if (!prng.exemple1(aJNI)) {
			aJNI.ktb_clear();
			System.exit(1);
		}

		aJNI.ktb_clear();
		long endTime = System.currentTimeMillis() - startTime;
		System.out.println(endTime + "ms");
	}

	public static boolean exemple1(ArcanaJNI aJNI) {

		int buffer_size = 50;
		byte[] buffer = new byte[buffer_size];
		if (aJNI.ktb_prng_fill_buffer(0, buffer) == ArcanaJNI.ktb_errno.KTB_ERR_NO_ERROR)
			System.out.println(Utils.getCurrentTime() + "ktb_fill_buffer() ok");
		else {
			System.out.println(Utils.getCurrentTime()
					+ "Error while initializating ktb_fill_buffer()");
			Utils.freeBuffer(buffer);
			return false;
		}

		Utils.printBuffer(buffer);

		Utils.freeBuffer(buffer);
		return true;
	}
}
