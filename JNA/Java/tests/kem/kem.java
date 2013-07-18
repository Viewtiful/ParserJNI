public class kem
{
   public static void main(String[] args) {
      ArcanaJNI aJNI = new ArcanaJNI();

      aJNI.ktb_init();

      long secret_key_length = 128;
      
      aJNI.generate_key(secret_key_length, asym_key_file, secret_key_file, encapsulated_file)

      aJNI.ktb_clear();
   }
}
