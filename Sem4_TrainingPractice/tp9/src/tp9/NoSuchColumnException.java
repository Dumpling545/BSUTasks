package tp9;

public class NoSuchColumnException extends RuntimeException {
	public NoSuchColumnException(String column) {
		super("Column  " + column +"  doesn't exist");
	}
}
