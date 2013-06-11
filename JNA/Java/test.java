package test;
import com.sun.jna.NativeLibrary;
/** Provide the glue to use the KTB library */
public class test
{
    private static final NativeLibrary sLibrary;
    static { sLibrary = NativeLibrary.getInstance(getLibName());}
    /** Return the shared library file path. */
    private static String getLibName()
    {
        String libName;
        final String envLibName = System.getenv("KTB_LIBRARY");
        if (envLibName != null)
        {
            libName = envLibName;
            System.out.println("Using KTB library path:" + libName);
        }
        else {
    	    libName = "ktb";
            System.out.println("KTB library path not specified \n Looking for KTB in system");
        }
       return libName;
    }
    /** return the KTB NativeLibrary instance */
    public static NativeLibrary getLibrary()
    {
        return sLibrary;
    }
}
