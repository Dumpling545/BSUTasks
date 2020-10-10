package tp4_2;

import java.awt.BasicStroke;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;
import java.util.Timer;
import java.util.TimerTask;

import javax.imageio.ImageIO;
import javax.swing.JFileChooser;
import javax.swing.JPanel;

public class MovingImagePanel extends JPanel {
	public final static int CLOCKWISE_DIRECTION = 1;
	public final static int COUNTERCLOCKWISE_DIRECTION = -1;
	
	public final static int CONSTANT_ANGLE = 0;
	public final static int CONSTANT_PIXELS = 1;
	private int velocity = 10;
	private int direction = CLOCKWISE_DIRECTION;
	private final int TIMER_PERIOD = 50;
	private double angle = 0;
	private BufferedImage image;
	private Timer timer;
	private final String DEFAULT_IMAGE_SOURCE = "D:\\”Õ»¬≈–\\Sem4_TrainingPractice\\tp4_2\\src\\tp4_2\\alb.jpg";
	private int velocityType = CONSTANT_ANGLE;
	private double getAngleSpeedPerTimePeriod() {
		double result = 0;
		switch(velocityType) {
			case CONSTANT_ANGLE:
				result = ((double)(direction*velocity)) / 360.0;
				break;
			case CONSTANT_PIXELS:
				double radius = Math.min(getWidth() - image.getWidth(), getHeight() - image.getHeight()) / 2;
				result = direction*velocity / radius;
				break;
		}
		return result;
	}
	public MovingImagePanel() throws IOException {
		JFileChooser fc = new JFileChooser("D:\\”Õ»¬≈–\\Sem4_TrainingPractice\\tp4_2\\src\\tp4_2\\");
		int returnValue = fc.showOpenDialog(null);
		if(returnValue == JFileChooser.APPROVE_OPTION) {
			image = ImageIO.read(fc.getSelectedFile());
		} else {
			image = ImageIO.read(new File(DEFAULT_IMAGE_SOURCE));
		}
		timer = new Timer();
		timer.scheduleAtFixedRate(new TimerTask() {	
			@Override
			public void run() {
				angle += getAngleSpeedPerTimePeriod();
				repaint();
			}
		}, 0, TIMER_PERIOD);
	}
	public int getVelocity() {
		return velocity;
	}
	public void setVelocity(int velocity) {
		this.velocity = velocity;
	}
	public int getDirection() {
		return direction;
	}
	public void setDirection(int direction) {
		this.direction = direction;
	}
	@Override
	protected void paintComponent(Graphics g) {
		super.paintComponent(g);
		int diameter = Math.min(getWidth() - image.getWidth(), getHeight() - image.getHeight());
		int radius = diameter/2;
		Graphics2D g2d = (Graphics2D)g;
		int x = (int) (radius + radius * Math.cos(angle));
		int y = (int) (radius + radius * Math.sin(angle));
		g2d.drawImage(image, x, y, this);
	}
	public void setVelocityType(int velocityType) {
		this.velocityType = velocityType;
	}
}
