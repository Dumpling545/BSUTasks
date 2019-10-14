package task1;

public class NotDoubleParametersException extends RuntimeException {

	public NotDoubleParametersException() {
		super("Invalid parameters. Must be doubles");
	}

}
