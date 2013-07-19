import java.text.SimpleDateFormat;
import java.util.Calendar;

public class Utils {
	public static String getCurrentTime() {
		Calendar cal = Calendar.getInstance();
		cal.getTime();
		SimpleDateFormat sdf = new SimpleDateFormat("HH:mm:ss");
		return sdf.format(cal.getTime()) + " : ";
	}
	
	public static void freeBuffer(byte[] buffer) {
		for( int i = 0; i < buffer.length; ++i)
			buffer[i] = 0;
		buffer = null;
	}
	
	public static void printBuffer(byte[] buffer) {
		StringBuilder sb = new StringBuilder();
		System.out.println("========================");
		System.out.println("Content of the buffer : ");
		for (byte b : buffer)
			sb.append(String.format("%02X ", b));
		System.out.println(sb.toString());
		System.out.println("========================");
	}
}
