package tictactoe;

import java.net.Socket;
import java.util.ArrayDeque;
import java.util.Deque;
import java.util.LinkedList;
import java.util.Queue;
import java.util.logging.Logger;

public class TicTacToe {
    private volatile Deque<Socket> players;
    private volatile TicTacToeSymbol[][] field;
    private volatile int cols = 3;
    private volatile int rows = 3;
    private volatile int lengthToWin = 3;
    private volatile TicTacToeSymbol currentSymbol;
    private volatile Cell lastCell;
    private volatile Socket winner = null;

    public TicTacToe(Socket socket) {
        Logger.getLogger("").info("new game constructor");
        players = new LinkedList<>();
        players.add(socket);
        currentSymbol = TicTacToeSymbol.X;
        field = new TicTacToeSymbol[rows][cols];
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                field[i][j] = TicTacToeSymbol.EMPTY;
            }
        }
        Logger.getLogger("").info("new game constructor: ending");
    }

    public boolean isPlayersNeeded() {
        return players.size() < 2;
    }

    public boolean isActivePlayer(Socket player) {
        return player == players.peek();
    }

    public synchronized void addSecondPlayer(Socket socket) {
        players.add(socket);
    }

    public synchronized void switchSymbol() {
        if (currentSymbol == TicTacToeSymbol.X)
            currentSymbol = TicTacToeSymbol.O;
        else if (currentSymbol == TicTacToeSymbol.O)
            currentSymbol = TicTacToeSymbol.X;
    }

    public Cell getLastCell() {
        return lastCell;
    }

    public synchronized void makeTurn(Socket player, Cell cell)
            throws UnauthorizedPlayerException, IllegalTurnException {
        Logger.getLogger("").info("makeTurn: begin " + ((currentSymbol == TicTacToeSymbol.O) ? "O" : "X"));
        if (player != players.remove()) {
            throw new UnauthorizedPlayerException();
        }
        if (field[cell.getX()][cell.getY()] == TicTacToeSymbol.EMPTY) {
            field[cell.getX()][cell.getY()] = currentSymbol;
            switchSymbol();
            players.add(player);
            lastCell = cell;
        } else {
            throw new IllegalTurnException();
        }
        Logger.getLogger("").info("makeTurn: end");
    }

    public synchronized Socket checkWinner() {
        Logger.getLogger("").info("check winner: begin");
        if(winner == null){
            TicTacToeSymbol winnerSymbol = checkWinnerSymbol();
            if (winnerSymbol == currentSymbol) {
                winner = players.peek();
            } else if (winnerSymbol == TicTacToeSymbol.EMPTY) {
                winner = null;
            } else {
                winner = players.getLast();
            }
        }
        Logger.getLogger("").info("check winner: end");
        return winner;
    }

    private synchronized TicTacToeSymbol checkWinnerSymbol() {
        // check rows
        int counter = 0;
        TicTacToeSymbol symbol = TicTacToeSymbol.EMPTY;
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                if (field[i][j] == symbol && field[i][j] != TicTacToeSymbol.EMPTY) {
                    counter++;
                } else {
                    counter = 1;
                    symbol = field[i][j];
                }
                if (counter == lengthToWin) {
                    Logger.getLogger("").info("WINNING ROW " + i);
                    return symbol;
                }
            }
            counter = 0;
            symbol = TicTacToeSymbol.EMPTY;
        }
        // check columns
        counter = 0;
        symbol = TicTacToeSymbol.EMPTY;
        for (int i = 0; i < cols; i++) {
            for (int j = 0; j < rows; j++) {
                if (field[j][i] == symbol && field[j][i] != TicTacToeSymbol.EMPTY) {
                    counter++;
                } else {
                    counter = 1;
                    symbol = field[j][i];
                }
                if (counter == lengthToWin) {
                    Logger.getLogger("").info("WINNING COLUMN " + i);
                    return symbol;
                }
            }
            counter = 0;
            symbol = TicTacToeSymbol.EMPTY;
        }
        // check left-to-right diagonals
        counter = 0;
        symbol = TicTacToeSymbol.EMPTY;
        for (int r = rows - lengthToWin; r >= 0; r--) {
            for (int c = 0; c < rows - r && c < cols; c++) {
                if (field[r + c][c] == symbol && field[r + c][c] != TicTacToeSymbol.EMPTY) {
                    counter++;
                } else {
                    counter = 1;
                    symbol = field[r + c][c];
                }
                if (counter == lengthToWin) {
                    Logger.getLogger("").info("WINNING LR-DIAGONALE RS=" + r);
                    return symbol;
                }
            }
            counter = 0;
            symbol = TicTacToeSymbol.EMPTY;
        }
        counter = 0;
        symbol = TicTacToeSymbol.EMPTY;
        for (int c = 0; c <= cols - lengthToWin; c++) {
            for (int r = 0; r < cols - c && r < rows; r++) {
                if (field[r][c + r] == symbol && field[r][c + r] != TicTacToeSymbol.EMPTY) {
                    counter++;
                } else {
                    counter = 1;
                    symbol = field[r][c + r]; 
                }
                if (counter == lengthToWin) {
                    Logger.getLogger("").info("WINNING LR-DIAGONALE CS=" + c);
                    return symbol;
                }
            }
            counter = 0;
            symbol = TicTacToeSymbol.EMPTY;
        }
        // check right-to-left diagonals
        counter = 0;
        symbol = TicTacToeSymbol.EMPTY;
        for (int c = lengthToWin - 1; c < cols; c++) {
            for (int r = 0; r <= c && r < rows; r++) {
                if (field[r][c - r] == symbol && field[r][c - r] != TicTacToeSymbol.EMPTY) {
                    counter++;
                } else {
                    counter = 1;
                    symbol = field[r][c - r];
                }
                if (counter == lengthToWin) {
                    Logger.getLogger("").info("WINNING RL-DIAGONALE CS=" + c);
                    return symbol;
                }
            }
            counter = 0;
            symbol = TicTacToeSymbol.EMPTY;
        }
        counter = 0;
        symbol = TicTacToeSymbol.EMPTY;
        for (int r = 0; r <= rows - lengthToWin; r++) {
            for (int c = cols - 1; c >= cols - rows + r && c >= 0; c--) {
                if (field[cols - 1 - c + r][c] == symbol
                        && field[cols - 1 - c + r][c] != TicTacToeSymbol.EMPTY) {
                    counter++;
                } else {
                    counter = 1;
                    symbol = field[cols - 1 - c + r][c];
                }
                if (counter == lengthToWin) {
                    Logger.getLogger("").info("WINNING RL-DIAGONALE RS=" + r);
                    return symbol;
                }
            }
            counter = 0;
            symbol = TicTacToeSymbol.EMPTY;
        }
        return TicTacToeSymbol.EMPTY;
    }

}
