package w7t1;

public class NonNumberInputException extends RuntimeException {
	public NonNumberInputException() {
		super("No-number element in input!");
	}
}
