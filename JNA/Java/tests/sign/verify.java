import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;

public class verify {
	public static void main(String[] args) throws Exception {
		ArcanaJNI aJNI = new ArcanaJNI();

		if (aJNI.ktb_init() == ArcanaJNI.ktb_errno.KTB_ERR_NO_ERROR) {
			System.out.println("ktb_init() ok");
		}

		ArcanaJNI.AddressWrapper ctx = new ArcanaJNI.AddressWrapper();

		if (aJNI.ktb_sign_init(ctx,
				ArcanaJNI.ktb_hash_algo_t.KTB_HASH_ALGO_SKEIN512) == ArcanaJNI.ktb_errno.KTB_ERR_NO_ERROR) {
			System.out.println("ktb_sign_init() ok");
		}

		ArcanaJNI.AddressWrapper public_key = new ArcanaJNI.AddressWrapper();

		File file = new File("public_key.txt");
		InputStream ios = new FileInputStream(file);
		int key_buffer_size = (int) file.length();
		byte[] key_buffer = new byte[key_buffer_size];
		
		System.out.println("key_buffer_size : " + key_buffer_size);

		ios.read(key_buffer);
		
		if (aJNI.ktb_keys_public_key_import(key_buffer, public_key)
				 == ArcanaJNI.ktb_errno.KTB_ERR_NO_ERROR) {
			System.out.println("ktb_keys_public_key_import ok");
		}
		
		if (aJNI.ktb_sign_set_public_key(ctx.getAddress(), public_key.getAddress())
				 == ArcanaJNI.ktb_errno.KTB_ERR_NO_ERROR) {
			System.out.println("ktb_sign_set_public_key ok");
		}
		
		File input_file = new File("hello.txt");
		InputStream input_file_stream = new FileInputStream(input_file);
		int data_size = (int) input_file.length();
		byte[] data = new byte[data_size];
		input_file_stream.read(data);
		
		if (aJNI.ktb_sign_process(ctx.getAddress(), data)
				 == ArcanaJNI.ktb_errno.KTB_ERR_NO_ERROR) {
			System.out.println("ktb_sign_process ok");
		}
		
		if (aJNI.ktb_sign_finalise(ctx.getAddress())
				 == ArcanaJNI.ktb_errno.KTB_ERR_NO_ERROR) {
			System.out.println("ktb_sign_finalise ok");
		}
		
		File input_file2 = new File("signed.txt");
		InputStream input_file_stream2 = new FileInputStream(input_file2);
		int data_size2 = (int) input_file2.length();
		byte[] data2 = new byte[data_size2];
		input_file_stream2.read(data2);
		
		ArcanaJNI.BoolWrapper is_valid = new ArcanaJNI.BoolWrapper();
		
		if (aJNI.ktb_sign_verify(ctx.getAddress(), data2, is_valid) == ArcanaJNI.ktb_errno.KTB_ERR_NO_ERROR) {
			System.out.println("ktb_sign_get_verify ok");
		}
		
		if(is_valid.getValue())
			System.out.println("File signature is valid");
		else
			System.out.println("File signature is not valid");

		input_file_stream2.close();
		input_file_stream.close();
		ios.close();
		
		aJNI.ktb_sign_clear(ctx.getAddress());
		for(int i = 0; i < data.length; ++i)
			data[i] = 0;
		data = null;
		
		for(int i = 0; i < data2.length; ++i)
			data2[i] = 0;
		data2 = null;
		
		aJNI.ktb_keys_public_key_clear(public_key.getAddress());
		aJNI.ktb_clear();
	}
}
