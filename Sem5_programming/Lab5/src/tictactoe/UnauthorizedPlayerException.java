package tictactoe;

public class UnauthorizedPlayerException extends RuntimeException{
    public UnauthorizedPlayerException(){
        super("The player is not allowed to perform this action");
    }
}
