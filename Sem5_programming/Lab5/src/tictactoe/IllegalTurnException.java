package tictactoe;

public class IllegalTurnException extends RuntimeException{
    public IllegalTurnException(){
        super("This turn cannot be allowed");
    }
    
}
