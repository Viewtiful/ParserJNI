public class kep_dh_t {
	public static void main(String[] args) {
		ArcanaJNI aJNI = new ArcanaJNI();

		//Initialization of the ktb.
		if(aJNI.ktb_init() == ArcanaJNI.ktb_errno.KTB_ERR_NO_ERROR) {
			System.out.println("ktb_init() ok");
		}

		//We create a Java class which call the JNI function which create the
		//C structure.
		ArcanaJNI.ktb_kep_dh_t kep_dh = aJNI.new ktb_kep_dh_t();

		//We assign a value to dummy and try to print it.
		kep_dh.dummy = 10;
		System.out.println("Valeur de kep_dh.dummy : " + kep_dh.dummy);

		//We call the JNI function in order to assign to the C structure the
		//value of dummy from the Java class.
		kep_dh.write();

		//We put a random value in dummy, in order to see if by calling read()
		//we get the correct value, which is 10 in this example.
		kep_dh.dummy = 15151;
		System.out.println("Valeur de kep_dh.dummy : " + kep_dh.dummy);
	
		kep_dh.read();
		System.out.println("Valeur de kep_dh.dummy : " + kep_dh.dummy);

		//We "delete" the object, in order for the garbage collector to see 
		//that the object is not used anymore. We do that in order to see if
		//finalize() correctly call the JNI function which destroy the C
		//structure.
		kep_dh = null;

		//We create a new object.
		kep_dh = aJNI.new ktb_kep_dh_t();

		//We try to read the value, of course it's a random value.
		kep_dh.read();

		System.out.println("Valeur de kep_dh.dummy : " + kep_dh.dummy);
		
		aJNI.ktb_clear();
	}
}
