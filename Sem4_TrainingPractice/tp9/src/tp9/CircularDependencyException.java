package tp9;

public class CircularDependencyException extends RuntimeException {
	public CircularDependencyException() {
		super("Circular dependency");
	}
}
