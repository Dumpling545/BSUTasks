package tp4_1;

import java.awt.BasicStroke;
import java.awt.Color;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.util.Timer;
import java.util.TimerTask;

import javax.swing.JPanel;

public class StopWatchPanel extends JPanel {
	private final double ANGULAR_VELOCITY= Math.PI / 30;
	private double angle = - Math.PI / 2.0;
	private Timer timer;
	
	private final int BORDER_THICKNESS = 10;
	private final Color BORDER_COLOR = Color.CYAN;
	
	private final int HAND_THICKNESS = 5;
	private final Color HAND_COLOR = Color.RED;
	private final double HAND_RELATIVE_LENGTH = 0.8;
	
	public StopWatchPanel() {
		timer = new Timer();
		timer.scheduleAtFixedRate(new TimerTask() {	
			@Override
			public void run() {
				angle += ANGULAR_VELOCITY;
				repaint();
			}
		}, 0, 1000);
	}
	@Override
	protected void paintComponent(Graphics g) {
		super.paintComponent(g);
		int externalDiameter = Math.min(getWidth(), getHeight());
		int externalRadius = externalDiameter / 2;
		int handLength = (int) (HAND_RELATIVE_LENGTH*(externalRadius - BORDER_THICKNESS));
		int margin = BORDER_THICKNESS/2;
		Graphics2D g2d = (Graphics2D)g;
		g2d.setStroke(new BasicStroke(BORDER_THICKNESS));
		g2d.setColor(BORDER_COLOR);
		g2d.drawOval(margin, margin, externalDiameter - BORDER_THICKNESS, externalDiameter - BORDER_THICKNESS);
		g2d.setStroke(new BasicStroke(HAND_THICKNESS));
		g2d.setColor(HAND_COLOR);
		int x2 = (int) (externalRadius + handLength * Math.cos(angle));
		int y2 = (int) (externalRadius + handLength * Math.sin(angle));
		g2d.drawLine(externalRadius, externalRadius, x2,  y2);
	}
}
