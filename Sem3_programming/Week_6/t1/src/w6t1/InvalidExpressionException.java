package w6t1;

public class InvalidExpressionException extends RuntimeException {

	public InvalidExpressionException(String expression) {
		super("Only whole numbers and signs '-' and '+' are allowed. Caused in expression: " + expression);
	}
}
