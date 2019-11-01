package w7t1;

public class TooManyInputException extends RuntimeException {
	public TooManyInputException() {
		super("Too many elements in input!");
	}
}
