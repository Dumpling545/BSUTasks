package w6t1;

public class EmptyInputException extends RuntimeException {
	public EmptyInputException() {
		super("Input is empty");
	}
}
