package tp11;

import java.awt.BorderLayout;
import java.io.IOException;

import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.text.AbstractDocument.Content;

public class GameFrame extends JFrame {
	private DangerousRoads game;
	public GameFrame() throws IOException {
		setTitle("Dangerous Roads");
		JPanel contentPane = new JPanel();
		JPanel parametersPanel = new JPanel();
		game = new DangerousRoads(parametersPanel);
		contentPane.setLayout(new BorderLayout());
		contentPane.add(parametersPanel, BorderLayout.NORTH);
		contentPane.add(game, BorderLayout.CENTER);
		setContentPane(contentPane);
		pack();
		game.start();
	}
	public static void main(String[] args) {
		GameFrame frame;
		try {
			frame = new GameFrame();
			frame.setVisible(true);
		} catch (IOException e) {
			System.out.println(e.getMessage());
		}
	}

}
