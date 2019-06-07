// import junit.framework.TestCase;
import java.io.*;

// public class UnitTest extends TestCase {
public class UnitTest {
	// public static final String RESET = "\u001B[0m";
	// public static final String RED = "\u001B[31m";
	// public static final String GREEN = "\u001B[32m";
	
	private static void myAssert(boolean b) {
		// Use first block if on terminal which supports ANSI color codes
		/*
		if (b) {
			System.out.println(GREEN + "Valid!" + RESET);
		}
		else {
			System.out.println(RED + "Invalid!" + RESET);
		}
		*/
		
		if (b) {
			System.out.println("Valid!");
		}
		else {
			System.out.println("Invalid!");
		}
	}
	
	private static void uTest(UrlValidator v, String s) {
		System.out.printf("%s  --- ", s);
		myAssert(v.isValid(s));
	}
	
	public static void main(String[ ] args) {
		String[] schemes = {"http", "https", "ftp"};
		String[] emptyschemes = { };
		
		// Validator Constructor tests. Uncomment desired form to test
		// String[] schemes = {};
		// UrlValidator v = new UrlValidator(schemes, UrlValidator.NO_FRAGMENTS);
		// UrlValidator v = new UrlValidator(emptyschemes, UrlValidator.NO_FRAGMENTS);
		// UrlValidator v = new UrlValidator(null);
		UrlValidator v = new UrlValidator(emptyschemes, UrlValidator.ALLOW_ALL_SCHEMES);
		
		// Basic positive tests
		System.out.println("Basic Positive tests:");
		uTest(v, "http://www.google.com");
		uTest(v, "http://www.google.com/");
		uTest(v, "https://www.facebook.com/home.php");
		uTest(v, "http://msdn.microsoft.com/en-us/library/aa752574(VS.85).aspx");
		uTest(v, "http://test.com:10000");
		uTest(v, "http://президент.рф");
		uTest(v, "ftp://ftp.funet.fi/pub/standards/RFC/rfc959.txt");
		
		System.out.println("\nLarge list of arbitrary positive tests...");
		try (BufferedReader in = new BufferedReader(new FileReader("test/unittesturls.txt"))) {
			String url;
			while ((url = in.readLine()) != null) {
				uTest(v, url);
			}
		} catch (Exception e) {
			System.out.println("No file for reading Unit Test URLs");
		}
		
		// Basic negative tests
		System.out.println("\nBasic Negative tests:");
		uTest(v, ".......");
		uTest(v, "http://www.\\uFFFD.ch");
		uTest(v, "http://localhost");
		uTest(v, "http://hostname");
		uTest(v, "http://test.this-test/test.index");
		uTest(v, "http://test.com:99999");
		
		System.out.println("\nNow making a new Regex to make some of the Negative tests positive tests...");
		RegexValidator r = new RegexValidator(new String[] {"localhost", ".*\\.this-test"});
		UrlValidator v2 = new UrlValidator(r, 0);
		uTest(v2, "http://localhost");
		uTest(v2, "http://test.this-test/test.index");
		
		
		
	}
}