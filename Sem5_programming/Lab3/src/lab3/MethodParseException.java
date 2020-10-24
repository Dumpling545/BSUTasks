package lab3;

public class MethodParseException extends RuntimeException {

    public MethodParseException(String fragment) {
        super("Cannot parse following fragment:\n" + fragment);
    }  
}
