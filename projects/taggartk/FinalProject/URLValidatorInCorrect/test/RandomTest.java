import java.io.*;
import java.security.SecureRandom;

public class RandomTest {

	static final String inputChars = "%@0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz :./";
	static SecureRandom rnd = new SecureRandom();

	private static int randomNumber( int min, int max ) {
		int randNum = rnd.nextInt((max - min) + 1) + min;
		return randNum;
	}

	private static String randomString( int len ) {

		StringBuilder sb = new StringBuilder( len );

		for( int i = 0; i < len; i++ ) {
      			sb.append( inputChars.charAt( rnd.nextInt(inputChars.length()) ) );
   		}

		return sb.toString();
	}


	private static void myAssert(boolean b) {
		
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
		String[] schemes = {"http://", "https://", "file:///", "ftp://", "gopher:/", "mailto:", ""};
		String[] emptyschemes = { };
		String[] tlds = {"com", "org", "net", "int", "edu", "gov", "mil", "au", "br", "ca", "de", "fr", "in", "it", "jp", "ru", "uk", "us"};

		String rando = randomString(24);
		
		// System.out.printf("%s  --- \n", rando);
		// Validator Constructor tests. Uncomment desired form to test
		// String[] schemes = {};
		// UrlValidator v = new UrlValidator(schemes, UrlValidator.NO_FRAGMENTS);
		// UrlValidator v = new UrlValidator(emptyschemes, UrlValidator.NO_FRAGMENTS);
		// UrlValidator v = new UrlValidator(null);
		UrlValidator v = new UrlValidator(emptyschemes, UrlValidator.ALLOW_ALL_SCHEMES);
		
		// int loops = randomNumber(0,100);
		int loops = 100;
		for (int i = 0; i < loops; i++) {

			String testUrl;

			testUrl = schemes[rnd.nextInt(schemes.length)];
			if (randomNumber(0,3) == 0) {
				testUrl = testUrl + "www.";
			}
			testUrl = testUrl + randomString(randomNumber(1,100));
			if (i % 2 == 0) {
				testUrl = testUrl + "." + tlds[randomNumber(0, tlds.length-1)];
			}
			if (i % 7 == 0) {
				testUrl = testUrl + "/" + randomString(randomNumber(1,100));
			}
			if (i % 5 == 0) {
				testUrl = testUrl + ":" + randomNumber(0,1000000);
			} 
			// System.out.printf("%s\n", testUrl);
		        uTest(v,testUrl);
		} 

	}
}
