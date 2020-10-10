package tp11;

import java.awt.Color;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.Rectangle;
import java.awt.geom.Area;

public class Road extends DrawableGameObject {
	public Road(RoadInfo roadInfo) {
		physicalBody = new Area(new Rectangle(0, 0, roadInfo.getWidth(), roadInfo.getDistance()));
	}

	@Override
	public boolean update() {
		return true;
	}

	@Override
	public void draw(Graphics g) {
		Graphics2D g2d = (Graphics2D) g;
		g2d.setColor(Color.GRAY);
		g2d.fill(physicalBody);
	}

}
