package tariffs;

public class InvalidQueryException extends RuntimeException {
	public InvalidQueryException() {
		super("Invalid Query");
	}
}
