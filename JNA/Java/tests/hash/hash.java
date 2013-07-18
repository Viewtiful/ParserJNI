public class hash
{
   public static void main(String[] args) {
      ArcanaJNI aJNI = new ArcanaJNI();

      aJNI.ktb_init();

      String hello = "Hello1";
      byte[] helloB = hello.getBytes();

      ArcanaJNI.ktb_hash_algo_t HASH_ALGO = ArcanaJNI.ktb_hash_algo_t.KTB_HASH_ALGO_SHA512;

      long hash_len = aJNI.ktb_hash_get_len_from_algo(HASH_ALGO);
      System.out.println("hash_len : " + hash_len);

      byte[] hash = new byte[(int) (long)hash_len];

      aJNI.ktb_hash_block(HASH_ALGO, helloB, hash);

      StringBuilder sb = new StringBuilder();
      for(byte b : hash) 
         sb.append(String.format("%02X ", b));
      System.out.println(sb.toString());

      aJNI.ktb_clear();
   }
}
