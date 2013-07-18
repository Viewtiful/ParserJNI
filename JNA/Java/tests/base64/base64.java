public class base64 {
	public static void main(String[] args) throws Exception {
		ArcanaJNI aJNI = new ArcanaJNI();
		
		if (aJNI.ktb_init() == ArcanaJNI.ktb_errno.KTB_ERR_NO_ERROR)
			System.out.println(Utils.getCurrentTime() + "ktb_init() ok");
		else {
			System.out.println(Utils.getCurrentTime()
					+ "Error while initializating ktb_init()");
			System.exit(1);
		}
		
		String s = "test";
		byte[] input = s.getBytes();
		
		if (!base64.encode(aJNI, input)) {
			aJNI.ktb_clear();
			System.exit(1);
		}
		
		s = null;
		aJNI.ktb_clear();
	}

	public static boolean encode(ArcanaJNI aJNI, byte[] input) throws Exception {
		
		long result_size = aJNI.ktb_base64_encode_size(input.length);
		byte[] result = new byte[(int) (long) result_size];
		
		if (aJNI.ktb_base64_encode(input, result) == ArcanaJNI.ktb_errno.KTB_ERR_NO_ERROR)
			System.out.println(Utils.getCurrentTime() + "ktb_base64_encode() ok");
		else {
			System.out.println(Utils.getCurrentTime() + "Error while initializating ktb_base64_encode()");
			Utils.freeBuffer(input);
			Utils.freeBuffer(result);
			return false;
		}
		
		Utils.printBuffer(result);
		
		base64.decode(aJNI, result);
		
		return true;
	}
	
	public static boolean decode(ArcanaJNI aJNI, byte[] input)  throws Exception {
		
		long result_size = aJNI.ktb_base64_decode_size(input);
		byte[] result = new byte[(int) (long) result_size];
		
		if (aJNI.ktb_base64_decode(input, result) == ArcanaJNI.ktb_errno.KTB_ERR_NO_ERROR)
			System.out.println(Utils.getCurrentTime() + "ktb_base64_decode() ok");
		else {
			System.out.println(Utils.getCurrentTime() + "Error while initializating ktb_base64_decode()");
			Utils.freeBuffer(input);
			Utils.freeBuffer(result);
			return false;
		}
		
		Utils.printBuffer(result);
		
		String s = new String(result, "UTF-8");
		System.out.println(s);
		
		return true;
	}
}
