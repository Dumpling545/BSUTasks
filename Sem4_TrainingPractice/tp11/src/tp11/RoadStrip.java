package tp11;

import java.awt.Color;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.Rectangle;
import java.awt.geom.Area;

public class RoadStrip extends DrawableGameObject {
	public RoadStrip(RoadInfo roadInfo, int x, int y) {
		physicalBody = new Area(new Rectangle(x, y, roadInfo.getDividingStripWidth(), roadInfo.getDividingStripLength()));
	}

	@Override
	public boolean update() {
		return true;
	}

	@Override
	public void draw(Graphics g) {
		Graphics2D g2d = (Graphics2D) g;
		g2d.setColor(Color.WHITE);
		g2d.fill(physicalBody);
	}

}
