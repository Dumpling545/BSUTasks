package tictactoe;

import java.util.logging.Logger;
import java.net.Socket;
import java.util.Stack;

public class TicTacToeManager {
    private Stack<TicTacToe> games;
    public TicTacToeManager(){
        Logger.getLogger("").info("new manager");
        games = new Stack<TicTacToe>();
    }
    public TicTacToe registerToAvailableGame(Socket socket){
        Logger.getLogger("").info("register new user");
        if(!games.empty() && games.peek().isPlayersNeeded()){
            Logger.getLogger("").info("second user");
            games.peek().addSecondPlayer(socket);
            synchronized(games.peek()){
                games.peek().notifyAll();
                Logger.getLogger("").info("waking up handlers");
            }
        } else {
            Logger.getLogger("").info("first user");
            games.add(new TicTacToe(socket));
        }
        return games.peek();
    }
}
