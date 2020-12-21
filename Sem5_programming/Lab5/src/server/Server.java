package server;

import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.logging.Logger;
import tictactoe.TicTacToeManager;

public class Server {
    private final static int PORT_NUMBER = 8000;

    public static void main(String[] args) {
        TicTacToeManager ticTacToeManager = new TicTacToeManager();
        try (ServerSocket serverSocket = new ServerSocket(PORT_NUMBER);) {
            while (true) {
                Socket clientSocket = serverSocket.accept();
                Logger.getLogger("").info("accept new client");
                new ClientHandler(clientSocket,
                        ticTacToeManager.registerToAvailableGame(clientSocket)).start();
            }
        } catch (IOException e) {
            e.printStackTrace();
        }

    }
}
