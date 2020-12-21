package server;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.ObjectOutputStream;
import java.io.PrintWriter;
import java.net.Socket;
import java.util.logging.Logger;
import java.util.regex.Matcher;
import java.util.regex.Pattern;
import tictactoe.Cell;
import tictactoe.TicTacToe;
import tictactoe.TicTacToeSymbol;

public class ClientHandler extends Thread {
    private Socket socket;
    private final String SUCCESS_REGISTRATION_TAG = "success";
    private final String TURN_TAG = "turn";
    private final Pattern MAKE_TURN_PATTERN;
    private TicTacToe ticTacToe;

    public ClientHandler(Socket socket, TicTacToe ticTacToe) {
        this.socket = socket;
        this.ticTacToe = ticTacToe;
        MAKE_TURN_PATTERN = Pattern.compile(TURN_TAG + " (\\d+) (\\d+)");
    }

    @Override
    public void run() {
        Logger.getLogger("").info("start new client handler");
        try (PrintWriter out = new PrintWriter(socket.getOutputStream(), true);
                BufferedReader in =
                        new BufferedReader(new InputStreamReader(socket.getInputStream()))) {
            Logger.getLogger("").info("sleep new client handler");
            synchronized (ticTacToe) {
                while (ticTacToe.isPlayersNeeded() || !ticTacToe.isActivePlayer(socket)) {
                    try {
                        ticTacToe.wait();
                    } catch (InterruptedException e) {
                        Logger.getLogger("").warning("Things are bad");
                        Thread.currentThread().interrupt();
                    }
                }
            }
            Logger.getLogger("").info("wake up new client handler");
            if (ticTacToe.getLastCell() == null) {
                Logger.getLogger("").info("send registration to first player");
                out.println(SUCCESS_REGISTRATION_TAG);
                Logger.getLogger("").info("registration sent");
            } else {
                Logger.getLogger("").info("send first turn to second player");
                out.println(ticTacToe.getLastCell().getX() + " " + ticTacToe.getLastCell().getY()
                        + " n");
            }
            String inputLine;
            while ((inputLine = in.readLine()) != null) {
                Logger.getLogger("").info("REQUEST " + inputLine);
                Matcher matcher = MAKE_TURN_PATTERN.matcher(inputLine);
                if (matcher.find()) {
                    Logger.getLogger("").info("REQUEST identified");
                    int x = Integer.parseInt(matcher.group(1));
                    int y = Integer.parseInt(matcher.group(2));
                    Cell cell = new Cell(x, y);
                    ticTacToe.makeTurn(socket, cell);
                    synchronized (ticTacToe) {
                        ticTacToe.notify();
                    }
                    synchronized (ticTacToe) {
                        while (!ticTacToe.isActivePlayer(socket) && ticTacToe.checkWinner() == null) {
                            try {
                                ticTacToe.wait();
                            } catch (InterruptedException e) {
                                Logger.getLogger("").warning("Things are bad");
                                Thread.currentThread().interrupt();
                            }
                        }
                    }
                    char c = 'n';
                    if (ticTacToe.checkWinner() != null) {
                        synchronized (ticTacToe) {
                            ticTacToe.notifyAll();
                            Logger.getLogger("").info("wake up sleeping opponent");
                        }
                        if (ticTacToe.checkWinner() == socket) {
                            c = 'w';
                            Logger.getLogger("").info("this user won");
                        } else {
                            c = 'l';
                            Logger.getLogger("").info("this user lost");
                        }
                    }
                    Logger.getLogger("").info("woken up SEND RESPONSE " + c);
                    out.println(ticTacToe.getLastCell().getX() + " "
                            + ticTacToe.getLastCell().getY() + " " + c);
                            Logger.getLogger("").info("RESPONSE SENT");

                }

            }
            socket.close();
        } catch (IOException e) {
            Logger.getLogger("").warning("Things are bad");
            Thread.currentThread().interrupt();
        }
    }

}