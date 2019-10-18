package w6t1;

public class NotEnoughOperandsException extends RuntimeException {

	public NotEnoughOperandsException(String expression) {
		super("A binary operation with less than two operands. Caused in expression: " + expression);
	}


}
