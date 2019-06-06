// import junit.framework.TestCase;

// public class UnitTest extends TestCase {
public class UnitTest {
	public static void main(String[ ] args) {
		String[] schemes = {"http", "https"};
		UrlValidator v = new UrlValidator(schemes, UrlValidator.NO_FRAGMENTS);
		// assertTrue(v.isValid("http://www.google.com"));
		if (v.isValid("http://www.google.com")) {
			System.out.println("Valid!");
		} 
		else {
			System.out.println("Not valid!");
		}
	}
}