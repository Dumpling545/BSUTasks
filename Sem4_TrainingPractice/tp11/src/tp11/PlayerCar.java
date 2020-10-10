package tp11;

import java.awt.Color;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.Rectangle;
import java.awt.geom.AffineTransform;

public class PlayerCar extends Car {
	public static final int LEFT = 0;
	public static final int RIGHT = 1;
	private Color signColor;
	private int deltaX  = 0;
	private int horizontalSpeed;
	private int verticalSpeed;
	private RoadInfo roadInfo;
	public PlayerCar(RoadInfo roadInfo, int lane, int distance, int width, int height, int verticalSpeed, int horizontalSpeed) {
		super(roadInfo, lane, distance, width, height);
		int halfDeltaRed = Math.abs(bodyColor.getRed() - roofColor.getRed())/2;
		int signRed;
		int leftDeltaRed = Math.min(bodyColor.getRed(), roofColor.getRed());
		int rightDeltaRed = 255 - Math.max(bodyColor.getRed(), roofColor.getRed());
		if(halfDeltaRed < leftDeltaRed) {
			signRed = 0;
		} else if(halfDeltaRed < rightDeltaRed) {
			signRed = 255;
		} else {
			signRed = leftDeltaRed + halfDeltaRed;
		}
		int halfDeltaGreen = Math.abs(bodyColor.getGreen() - roofColor.getGreen())/2;
		int signGreen;
		int leftDeltaGreen =  Math.min(bodyColor.getGreen(), roofColor.getGreen());
		int rightDeltaGreen =  255 - Math.max(bodyColor.getGreen(), roofColor.getGreen());
		if(halfDeltaGreen < leftDeltaGreen) {
			signGreen = 0;
		} else if(halfDeltaGreen < rightDeltaGreen) {
			signGreen = 255;
		} else {
			signGreen = leftDeltaGreen + halfDeltaGreen;
		}
		int halfDeltaBlue = Math.abs(bodyColor.getBlue() - roofColor.getBlue())/2;
		int signBlue;
		int leftDeltaBlue =  Math.min(bodyColor.getBlue(), roofColor.getBlue());
		int rightDeltaBlue =  255 - Math.max(bodyColor.getBlue(), roofColor.getBlue());
		if(halfDeltaBlue < leftDeltaBlue) {
			signBlue = 0;
		} else if(halfDeltaBlue < rightDeltaBlue) {
			signBlue = 255;
		} else {
			signBlue = leftDeltaBlue + halfDeltaBlue;
		}
		signColor = new Color(signRed, signGreen, signBlue);
		this.verticalSpeed = verticalSpeed;
		this.horizontalSpeed = horizontalSpeed;
		this.roadInfo = roadInfo;
	}

	@Override
	public boolean update() {
		AffineTransform transform = new AffineTransform();
		int absoluteTranslationX = Math.min(horizontalSpeed, Math.abs(deltaX));
		if(deltaX < 0) {
			deltaX += absoluteTranslationX;
			transform.setToTranslation(-absoluteTranslationX, verticalSpeed);
		} else if(deltaX > 0) {
			deltaX -= absoluteTranslationX;
			transform.setToTranslation(absoluteTranslationX, verticalSpeed);
		} else {
			transform.setToTranslation(0, verticalSpeed);
		}
		physicalBody.transform(transform);
		return true;
	}

	@Override
	public void draw(Graphics g) {
		super.draw(g);
		Rectangle r = physicalBody.getBounds();
		Graphics2D g2d = (Graphics2D) g;
		g2d.setColor(signColor);
		int x[] = {r.x + r.width/4, 
				   r.x + r.width*3/4, 
				   r.x + r.width*3/4, 
				   r.x + r.width/2, 
				   r.x + r.width/2, 
				   r.x + r.width/4};
		int y[] = {r.y + r.height/4, 
				   r.y + r.height/4, 
				   r.y + r.height/2, 
				   r.y + r.height/2, 
				   r.y + r.height*3/4, 
				   r.y + r.height*3/4};
		g2d.fillPolygon(x, y, 6);
	}
	public void stop() {
		verticalSpeed = 0;
		horizontalSpeed = 0;
	}
	public int getVerticalSpeed() {
		return verticalSpeed;
	}
	public int getHorizontalSpeed() {
		return horizontalSpeed;
	}
	public void setVerticalSpeed(int speed) {
		this.verticalSpeed = speed;
	}
	public void setHorizontalSpeed(int speed) {
		this.horizontalSpeed = speed;
	}
	public void turn(int side) {
		if(side == LEFT && physicalBody.getBounds().x + deltaX >= roadInfo.getLaneWidth()) {
			deltaX -= roadInfo.getLaneWidth();
		} else if(side == RIGHT && physicalBody.getBounds().getMaxX() + deltaX  + roadInfo.getLaneWidth() <= roadInfo.getWidth()) {
			deltaX += roadInfo.getLaneWidth();
		}
	}
}
