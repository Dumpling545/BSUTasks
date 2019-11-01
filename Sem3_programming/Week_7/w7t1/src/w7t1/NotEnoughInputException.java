package w7t1;

public class NotEnoughInputException extends RuntimeException {
	public NotEnoughInputException() {
		super("Not enough elements in input!");
	}
}
