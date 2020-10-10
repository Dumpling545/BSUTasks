package tp11;


public class EnemyCar extends Car {
	private PlayerCar playerCar;
	private PoliceCar policeCar;
	public EnemyCar(RoadInfo roadInfo, int lane, int distance, int width, int height, PlayerCar playerCar, PoliceCar policeCar) {
		super(roadInfo, lane, distance, width, height);
		this.playerCar = playerCar;
		this.policeCar = policeCar;
	}

	@Override
	public boolean update() {
		return !intersects(playerCar) && !intersects(policeCar);
	}

}
