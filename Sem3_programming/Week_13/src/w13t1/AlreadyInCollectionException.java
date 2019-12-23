package w13t1;

public class AlreadyInCollectionException extends RuntimeException {
	public AlreadyInCollectionException() {
		super("Identificators must be unique");
	}
}
