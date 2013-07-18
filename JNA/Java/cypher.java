public class cypher {

   public static void main(String[] args) {
      ArcanaJNI jni = new ArcanaJNI();

      if( jni.ktb_init() == ArcanaJNI.ktb_errno.KTB_ERR_NO_ERROR) {
         System.out.println("ktb_init successful");
      }

      ArcanaJNI.AddressWrapper ctx = new ArcanaJNI.AddressWrapper(); 

      if( jni.ktb_cipher_init(ctx, ArcanaJNI.ktb_cipher_algo_t.KTB_CIPHER_ALGO_AES128, ArcanaJNI.ktb_cipher_mode_t.KTB_CIPHER_MODE_CBC, true) == ArcanaJNI.ktb_errno.KTB_ERR_NO_ERROR) {
             System.out.println("ktb_cipher_init successful");     
      }

      long key_size = jni.ktb_cipher_get_key_len(ctx.getAddress());

      System.out.println("Key_size : " + key_size);

      String password = "test";
      byte[] password2 = password.getBytes();

      byte[] result = new byte[(int) (long)key_size];

      if( jni.ktb_kdf(ArcanaJNI.ktb_hash_algo_t.KTB_HASH_ALGO_SKEIN512, password2, 4, result, key_size) == ArcanaJNI.ktb_errno.KTB_ERR_NO_ERROR ) {
             System.out.println("ktb_kdf successful");  
      }

      StringBuilder sb = new StringBuilder();
         for(byte b : result) 
            sb.append(String.format("%02X ", b));
      System.out.println(sb.toString());

      if( jni.ktb_cipher_set_key(ctx.getAddress(), result, key_size) == ArcanaJNI.ktb_errno.KTB_ERR_NO_ERROR ) {
             System.out.println("cipher_set_key successful");  
      }

      long iv_size = jni.ktb_cipher_get_iv_len(ctx.getAddress());
      System.out.println("iv_size : " + iv_size);
   }
}
