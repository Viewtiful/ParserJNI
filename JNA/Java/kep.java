public class kep
{
   public static void main(String[] args) {
      ArcanaJNI aJNI = new ArcanaJNI();

      if( aJNI.ktb_init() == ArcanaJNI.ktb_errno.KTB_ERR_NO_ERROR) {
         System.out.println("KTB INIT DONE");
      }

      System.out.println("nb curve : " + aJNI.ktb_curves_count());

      for(int i = 0; i < aJNI.ktb_curves_count(); ++i) {
         System.out.println(aJNI.ktb_curves_id(i));
      }

      ArcanaJNI.ktb_kep_dh_t algo_params = aJNI.new ktb_kep_dh_t();
      ArcanaJNI.AddressWrapper ctx = new ArcanaJNI.AddressWrapper(); 
      long shared_key_size = 64;

      if(aJNI.ktb_kep_init(ctx, 0, ArcanaJNI.ktb_kep_algo_t.KTB_KEP_ALGO_DH, algo_params.getMInternal(), 0, "nistP521", ArcanaJNI.ktb_hash_algo_t.KTB_HASH_ALGO_SHA512, shared_key_size, 2) == ArcanaJNI.ktb_errno.KTB_ERR_INVALID_PARAMS) {
         System.out.println("ok");   
         byte[] resultat = new byte[256];
         int retour = aJNI.ktb_strerror(ArcanaJNI.ktb_errno.KTB_ERR_INVALID_PARAMS, resultat, 256);

         StringBuilder sb = new StringBuilder();
         for(byte b : resultat) 
            sb.append(String.format("%c ", b));
         System.out.println(sb.toString());
      }
      else {
         System.out.println("probleme");   
      }

      aJNI.ktb_clear();
   }
}
