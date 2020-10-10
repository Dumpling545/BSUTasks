package tp11;

import java.awt.Color;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.Rectangle;
import java.awt.geom.AffineTransform;


public class PoliceCar extends Car {
	private PlayerCar playerCar;
	private int deltaDistance;
	private int speed = 0;
	public PoliceCar(RoadInfo roadInfo, int width, int height, PlayerCar playerCar, int deltaDistance) {
		super(roadInfo, 1, 
				Integer.MAX_VALUE - height - 1, 
				width, height, Color.black, Color.white, Color.yellow, Color.red);
		this.playerCar = playerCar;
		this.deltaDistance = deltaDistance;
	}

	
	@Override
	public boolean update() {
		if(speed != 0) {
			Rectangle r = physicalBody.getBounds();
			int playerY = (int)playerCar.getPhysicalBody().getBounds().getMaxY();
			if(Math.min(Math.abs(r.y - playerY), Math.abs(r.y  + r.height - playerY))  < speed) {
				speed = 0;
				return false;
			} else if(speed > 0){
				AffineTransform transform = new AffineTransform();
				transform.setToTranslation(0, -speed);
				physicalBody.transform(transform);
			}
		}
		return true;
	}
	
	public void activate(int speed) {
		this.speed = Math.abs(speed);
		AffineTransform transform = new AffineTransform();
		Rectangle r = playerCar.getPhysicalBody().getBounds();
		transform.setToTranslation(r.x - physicalBody.getBounds().x, r.y + deltaDistance - physicalBody.getBounds().y);
		physicalBody.transform(transform);
	}

	@Override
	public void draw(Graphics g) {
		super.draw(g);
		Graphics2D g2d = (Graphics2D) g;
		Rectangle r = physicalBody.getBounds();
		g2d.setColor(Color.red);
		g2d.fillRect(r.x, r.y + r.height*3/8, r.width/2, r.height/8);
		g2d.setColor(Color.blue);
		g2d.fillRect(r.x + r.width/2, r.y + r.height*3/8, r.width/2, r.height/8);
	}

}
