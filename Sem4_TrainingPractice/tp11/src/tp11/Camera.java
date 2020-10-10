package tp11;

import java.awt.Rectangle;
import java.awt.geom.AffineTransform;
import java.awt.geom.Area;

public class Camera extends PhysicalGameObject{
	private PhysicalGameObject observable;
	public Camera(PhysicalGameObject observable,  int width, int height) {
		this.observable = observable;
		physicalBody = new Area(new Rectangle(0, 0, width, height));
	}
	@Override
	public boolean update() {
		AffineTransform transform = new AffineTransform();
		int deltaY = observable.getPhysicalBody().getBounds().y  - physicalBody.getBounds().y;
		transform.setToTranslation(0, deltaY);
		physicalBody.transform(transform);
		return true;
	}

}
