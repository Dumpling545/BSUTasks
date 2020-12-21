package client;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.Socket;
import java.util.logging.Logger;
import java.util.regex.Matcher;
import java.util.regex.Pattern;
import javax.swing.BoxLayout;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JTable;

public class Client extends JFrame implements MouseListener, ActionListener {
    private volatile JLabel infoLabel;
    private volatile JTable ticTacToeField;
    private JButton connectButton;
    private final String HOST_NAME = "127.0.0.1";
    private final String INFO_TEMPLATE = "Game started. You are playing as %1$s. It is %2$s turn.";
    private final String TURN_TEMPLATE = "turn %1$d %2$d";
    private final int PORT = 8000;
    private final String SUCCESS_REGISTRATION_TAG = "success";
    private final Pattern UPDATE_PATTERN;
    private PrintWriter out;
    private BufferedReader in;
    private volatile String symbol;
    private volatile String opponentSymbol;

    public static void main(String[] args) {
        JFrame client = new Client();
        client.setVisible(true);
    }

    public Client() {
        Logger.getLogger("").info("start client constructor");
        UPDATE_PATTERN = Pattern.compile("(\\d+) (\\d+) ([nwl])");
        setSize(640, 480);
        setTitle("Tic-Tac-Toe");
        JPanel pane = new JPanel();
        pane.setLayout(new BoxLayout(pane, BoxLayout.PAGE_AXIS));
        setContentPane(pane);
        infoLabel = new JLabel("Waiting to start a game");
        infoLabel.setVisible(false);
        pane.add(infoLabel);
        connectButton = new JButton("Connect to server");
        connectButton.addActionListener(this);
        pane.add(connectButton);
        ticTacToeField = new JTable(new TicTacToeTabelModel(3, 3));
        ticTacToeField.setEnabled(false);
        ticTacToeField.addMouseListener(this);
        pane.add(ticTacToeField);
        Logger.getLogger("").info("end client constructor");
    }

    @Override
    public void mouseClicked(MouseEvent e) {
        Logger.getLogger("").info("mouse clicked");
        int r = ticTacToeField.getSelectedRow();
        int c = ticTacToeField.getSelectedColumn();
        if (ticTacToeField.isEnabled() && ticTacToeField.getValueAt(r, c) == null) {
            Logger.getLogger("").info("mouse click: enabled and possible to change");
            ticTacToeField.setValueAt(symbol, r, c);
            infoLabel.setText(String.format(INFO_TEMPLATE, symbol, "opponent's"));
            ticTacToeField.setEnabled(false);
            Logger.getLogger("").info("mouse click: before server request");
            Logger.getLogger("").info("mouse click: request: " + String.format(TURN_TEMPLATE, r, c));
            out.println(String.format(TURN_TEMPLATE, r, c));
            Logger.getLogger("").info("mouse click: after server request");
        }
    }

    @Override
    public void actionPerformed(ActionEvent e) {
        try {
            Logger.getLogger("").info("establish connection");
            connectButton.setVisible(false);
            infoLabel.setVisible(true);
            Socket socket = new Socket(HOST_NAME, PORT);
            out = new PrintWriter(socket.getOutputStream(), true);
            in = new BufferedReader(new InputStreamReader(socket.getInputStream()));
            Thread thread = new Thread(new Runnable() {
                @Override
                public void run() {
                    Logger.getLogger("").info("THREAD: start thread");
                    String serverResponse;
                    try {
                        outer: while ((serverResponse = in.readLine()) != null) {
                            Logger.getLogger("").info("THREAD-SERVER RESPONSE: " + serverResponse);
                            if (serverResponse.equals(SUCCESS_REGISTRATION_TAG)) {
                                Logger.getLogger("").info("THREAD-SERVER RESPONSE: identified as registration");
                                symbol = "X";
                                opponentSymbol = "O";
                                infoLabel.setText(String.format(INFO_TEMPLATE, symbol, "your's"));
                                ticTacToeField.setEnabled(true);
                            } else {
                                Matcher matcher = UPDATE_PATTERN.matcher(serverResponse);
                                int r, c;
                                if (matcher.find()) {
                                    Logger.getLogger("").info("THREAD-SERVER RESPONSE: identified as update");
                                    switch (matcher.group(3)) {
                                        case "w":
                                            Logger.getLogger("").info("THREAD-SERVER RESPONSE: game ended: WIN");
                                            infoLabel.setText("You won!");
                                            break outer;
                                        case "l":
                                            r = Integer.parseInt(matcher.group(1));
                                            c = Integer.parseInt(matcher.group(2));
                                            Logger.getLogger("")
                                                    .info("THREAD-SERVER RESPONSE: game ended: LOSE" + r + "" + c);
                                            ticTacToeField.setValueAt(opponentSymbol, r, c);
                                            ticTacToeField.updateUI();
                                            infoLabel.setText("You lost!");
                                            break outer;
                                        case "n":
                                            Logger.getLogger("").info("THREAD-SERVER RESPONSE: game not ended");
                                            if (symbol == null) {
                                                Logger.getLogger("")
                                                        .info("THREAD-SERVER RESPONSE: first turn of O-player");
                                                symbol = "O";
                                                opponentSymbol = "X";
                                            }
                                            r = Integer.parseInt(matcher.group(1));
                                            c = Integer.parseInt(matcher.group(2));
                                            Logger.getLogger("").info(
                                                    "THREAD-SERVER RESPONSE: opponent tick at (" + r + ", " + c + ")");
                                            ticTacToeField.setValueAt(opponentSymbol, r, c);
                                            infoLabel.setText(String.format(INFO_TEMPLATE, symbol, "your's"));
                                            ticTacToeField.setEnabled(true);
                                            break;
                                    }
                                }
                            }
                        }
                        in.close();
                        out.close();
                        socket.close();
                    } catch (IOException e) {
                        Logger.getLogger("").warning("Things are bad");
                        JOptionPane.showMessageDialog(null, "Something wrong:\n" + e.getMessage(), "Network error",
                                JOptionPane.ERROR_MESSAGE);
                    }
                }
            });
            thread.start();
        } catch (IOException e1) {
            Logger.getLogger("").warning("Things are bad");
            JOptionPane.showMessageDialog(null, "Cannot establish connection", "Network error",
                    JOptionPane.ERROR_MESSAGE);
        }
    }

    @Override
    public void mouseEntered(MouseEvent arg0) {
    }

    @Override
    public void mouseExited(MouseEvent arg0) {
    }

    @Override
    public void mousePressed(MouseEvent arg0) {
    }

    @Override
    public void mouseReleased(MouseEvent arg0) {
    }
}
