public class hash {
	public static void main(String[] args) {
		ArcanaJNI aJNI = new ArcanaJNI();

		if (aJNI.ktb_init() == ArcanaJNI.ktb_errno.KTB_ERR_NO_ERROR)
			System.out.println(Utils.getCurrentTime() + "ktb_init() ok");
		else {
			System.out.println(Utils.getCurrentTime()
					+ "Error while initializating ktb_init()");
			System.exit(1);
		}

		if (!hash.hashString(aJNI)) {
			aJNI.ktb_clear();
			System.exit(1);
		}

		aJNI.ktb_clear();
	}

	public static boolean hashString(ArcanaJNI aJNI) {
		String hello = "Hello1";
		byte[] helloB = hello.getBytes();

		ArcanaJNI.ktb_hash_algo_t HASH_ALGO = ArcanaJNI.ktb_hash_algo_t.KTB_HASH_ALGO_SHA512;

		long hash_len = aJNI.ktb_hash_get_len_from_algo(HASH_ALGO);
		System.out.println("hash_len : " + hash_len);

		byte[] hash = new byte[(int) (long) hash_len];

		if (aJNI.ktb_hash_block(HASH_ALGO, helloB, hash) == ArcanaJNI.ktb_errno.KTB_ERR_NO_ERROR)
			System.out.println(Utils.getCurrentTime() + "ktb_hash_block() ok");
		else {
			System.out.println(Utils.getCurrentTime()
					+ "Error while initializating ktb_hash_block()");
			Utils.freeBuffer(helloB);
			Utils.freeBuffer(hash);
			return false;
		}

		Utils.printBuffer(hash);

		Utils.freeBuffer(helloB);
		Utils.freeBuffer(hash);
		return true;
	}
}
