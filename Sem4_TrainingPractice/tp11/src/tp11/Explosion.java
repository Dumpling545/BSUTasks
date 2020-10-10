package tp11;

import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.Rectangle;
import java.awt.geom.AffineTransform;
import java.awt.geom.Area;
import java.awt.image.BufferedImage;
import java.util.List;

public class Explosion extends DrawableGameObject {
	private List<BufferedImage> images;
	private double scale;
	private int index = 0;
	
	public Explosion(List<BufferedImage> images, Car explodedCar, double scale) {
		physicalBody = explodedCar.getPhysicalBody();
		this.images = images;
		this.scale = scale;
	}

	@Override
	public void draw(Graphics g) {
		if(index < images.size()) {
			Graphics2D g2d = (Graphics2D) g;
			int cX = (int) physicalBody.getBounds().getCenterX();
			int cY = (int) physicalBody.getBounds().getCenterY();
			AffineTransform transform = new AffineTransform();
			transform.scale(scale, scale);
			Rectangle r = 
					physicalBody.createTransformedArea(transform).getBounds();
			int newCX = (int) r.getCenterX();
			int newCY = (int) r.getCenterY();
			g2d.drawImage(images.get(index), r.x - newCX + cX, r.y - newCY +cY, 
					r.width, r.height, null);
		}
	}

	@Override
	public boolean update() {
		if(index < images.size()) {
			
			index++;
			return true;
		} else {
			return false;
		}
	}

}
