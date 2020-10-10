package tp11;

public class RoadInfo {
	private int lanes;
	private int laneWidth;
	private int distance;
	private int dividingStripLength;
	private int dividingStripWidth;
	public RoadInfo(int lanes, int laneWidth, int distance, int dividingStripLength, int dividingStripWidth) {
		this.lanes = lanes;
		this.laneWidth = laneWidth;
		this.distance = distance;
		this.dividingStripLength = dividingStripLength;
		this.dividingStripWidth = dividingStripWidth;
	}
	public int convertLanesToX(int lane) {
		return laneWidth*lane;
	}
	public int convertXToLanes(int x) {
		return x/laneWidth;
	}
	public int getWidth() {
		return lanes*laneWidth;
	}
	public int getLanes() {
		return lanes;
	}
	public int getLaneWidth() {
		return laneWidth;
	}
	public int getDistance() {
		return distance;
	}
	public int getDividingStripLength() {
		return dividingStripLength;
	}
	public int getDividingStripWidth() {
		return dividingStripWidth;
	}
}
