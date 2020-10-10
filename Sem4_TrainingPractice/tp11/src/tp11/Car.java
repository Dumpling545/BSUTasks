package tp11;

import java.awt.Color;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.Rectangle;
import java.awt.geom.Area;
import java.util.Random;

public abstract class Car extends DrawableGameObject {
	protected Color topLightColor, bodyColor, roofColor, bottomLightColor;
	public Car(RoadInfo roadInfo, int lane, int distance, int width, int height) {
		physicalBody = new Area(new Rectangle(roadInfo.convertLanesToX(lane - 1), distance, width, height));
		Random rand = new Random();
		this.topLightColor = new Color(rand.nextFloat(), rand.nextFloat(), rand.nextFloat());
		this.bodyColor = new Color(rand.nextFloat(), rand.nextFloat(), rand.nextFloat());
		this.roofColor = new Color(rand.nextFloat(), rand.nextFloat(), rand.nextFloat());
		this.bottomLightColor = new Color(rand.nextFloat(), rand.nextFloat(), rand.nextFloat());
	}
	public Car(RoadInfo roadInfo, int lane, int distance, int width, int height, Color bodyColor, Color roofColor, Color topLightColor, Color bottomLightColor) {
		physicalBody = new Area(new Rectangle(roadInfo.convertLanesToX(lane - 1), distance, width, height));
		this.topLightColor = topLightColor;
		this.bodyColor = bodyColor;
		this.roofColor = roofColor;
		this.bottomLightColor = bottomLightColor;
	}
	@Override
	public void draw(Graphics g) {
		Graphics2D g2d = (Graphics2D) g;
		Rectangle r = physicalBody.getBounds();
		g2d.setColor(bodyColor);
		g2d.fill(physicalBody);
		g2d.setColor(topLightColor);
		g2d.fillRect(r.x, r.y, r.width/4, r.height/8);
		g2d.fillRect(r.x + r.width*3/4, r.y, r.width/4, r.height/8);
		g2d.setColor(bottomLightColor);
		g2d.fillRect(r.x, r.y + r.height*7/8, r.width/4, r.height/8);
		g2d.fillRect(r.x + r.width*3/4, r.y + r.height*7/8, r.width/4, r.height/8);
		g2d.setColor(roofColor);
		g2d.fillRect(r.x, r.y + r.height/4, r.width, r.height/2);
	}

}
