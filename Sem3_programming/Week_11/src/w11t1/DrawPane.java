package w11t1;

import java.awt.BasicStroke;
import java.awt.Color;
import java.awt.Dimension;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.Image;
import java.awt.LayoutManager;
import java.awt.Point;
import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import java.awt.event.MouseMotionListener;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;
import java.util.Random;

import javax.imageio.ImageIO;
import javax.swing.JPanel;

public class DrawPane extends JPanel implements MouseMotionListener, MouseListener, KeyListener{
	private BufferedImage image;
	private Point point;
	private Color drawColor = Color.red;
	
	public void setDrawColor(Color drawColor) {
		this.drawColor = drawColor;
	}
	public void loadImage(File file) throws IOException{
		BufferedImage img = ImageIO.read(file);
		if(img == null) {
			throw new IOException("File is not image!");
		}
		setPreferredSize(new Dimension(img.getWidth(), img.getHeight()));
		this.image = img;
		repaint();
	}
	public void saveImage(File file) throws IOException {
		String extension = "png";
		int index = file.getPath().lastIndexOf('.');
		if(index > 0) {
			extension = file.getPath().substring(index + 1);
		} else {
			file = new File(file.getPath() + "." + extension);
		}
		ImageIO.write(image, extension, file);
	}

	public DrawPane(Dimension dimension) {
		super();
		setLayout(null);
		setBackground(Color.white);
		image = new BufferedImage(dimension.width, 
								  dimension.height, 
								  BufferedImage.TYPE_INT_RGB);
		Graphics2D g2d = image.createGraphics();
        g2d.setPaint(Color.white);
        g2d.fillRect(0, 0, dimension.width, dimension.height);
		point = new Point(Integer.MAX_VALUE, Integer.MAX_VALUE);
		addMouseMotionListener(this);
		addMouseListener(this);
		addKeyListener(this);
		setPreferredSize(dimension);
		setFocusable(true);
	}
	
	
	@Override
	protected void paintComponent(Graphics g) {
		super.paintComponent(g);
		g.drawImage(image, 0, 0, this);

	}
	@Override
	public void mouseDragged(MouseEvent e) {
		if(point.x != Integer.MAX_VALUE) {
			Graphics2D g2d = image.createGraphics();
	        g2d.setPaint(drawColor);
	        g2d.drawLine(point.x, point.y, e.getX(), e.getY());
	        g2d = (Graphics2D) getGraphics();
	        g2d.setPaint(drawColor);
	        g2d.drawLine(point.x, point.y, e.getX(), e.getY());
		}
		point.move(e.getX(), e.getY());
	}
	@Override
	public void mouseMoved(MouseEvent e) {}

	@Override
	public void mouseClicked(MouseEvent e) {
	}

	@Override
	public void mousePressed(MouseEvent e) {}

	@Override
	public void mouseReleased(MouseEvent e) {
		point.move(Integer.MAX_VALUE, Integer.MAX_VALUE);
	}

	@Override
	public void mouseEntered(MouseEvent e) {}

	@Override
	public void mouseExited(MouseEvent e) {}
	@Override
	public void keyTyped(KeyEvent e) {}
	@Override
	public void keyPressed(KeyEvent e) {
		if(e.getKeyCode() == KeyEvent.VK_B) {
			Random rand = new Random();
			Graphics2D g2d = image.createGraphics();
			g2d.setColor(new Color(rand.nextFloat(), rand.nextFloat(), rand.nextFloat()));
			g2d.fillRect(0, 0, image.getWidth(), image.getHeight());
	        repaint();
		}
	}
	@Override
	public void keyReleased(KeyEvent e) {}
}
