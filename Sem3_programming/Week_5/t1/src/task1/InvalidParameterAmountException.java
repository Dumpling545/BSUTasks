package task1;

public class InvalidParameterAmountException extends RuntimeException {

	public InvalidParameterAmountException() {
		super("Invalid amount of parameters. Must be 2");
	}

}
