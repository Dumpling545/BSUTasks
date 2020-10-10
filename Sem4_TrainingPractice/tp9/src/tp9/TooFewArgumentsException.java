package tp9;

public class TooFewArgumentsException extends RuntimeException {
	public TooFewArgumentsException() {
		super("Too few arguments for this operation");
	}
}
