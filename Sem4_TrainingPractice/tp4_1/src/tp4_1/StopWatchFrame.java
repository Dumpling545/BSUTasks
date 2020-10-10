package tp4_1;

import java.util.TreeMap;

import javax.swing.BoxLayout;
import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.JScrollPane;


public class StopWatchFrame extends JFrame {
	private JPanel stopWatchPanel;
	public static void main(String[] args) {
		StopWatchFrame frame;
			try {
				frame = new StopWatchFrame();
				frame.setVisible(true);
			} catch (Exception e) {
				System.out.println(e.getMessage());
			}
			
	}
	public StopWatchFrame() {
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		setSize(640, 480);
		setTitle("Stopwatch");
		stopWatchPanel = new StopWatchPanel();
		setContentPane(stopWatchPanel);
	}
}
