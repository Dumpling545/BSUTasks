package task1;

public class NonPositivePrecisionException extends RuntimeException {

	public NonPositivePrecisionException() {
		super("Precision must be positive");
	}

}
