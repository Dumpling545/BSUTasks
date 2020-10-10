package tp11;

import java.awt.geom.Area;

public abstract class PhysicalGameObject extends GameObject {
	protected Area physicalBody;
	public boolean intersects(PhysicalGameObject pgo) {
		Area intersection = (Area) physicalBody.clone();
		intersection.intersect(pgo.physicalBody);
		return !intersection.isEmpty();
	}
	public Area getPhysicalBody() {
		return physicalBody;
	}

}
