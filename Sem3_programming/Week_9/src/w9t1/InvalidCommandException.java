package w9t1;

public class InvalidCommandException extends RuntimeException {

	public InvalidCommandException() {
		super("Command is invalid.");
	}	

}
