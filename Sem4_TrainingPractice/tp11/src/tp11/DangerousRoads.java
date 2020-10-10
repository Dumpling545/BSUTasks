package tp11;

import java.awt.BorderLayout;
import java.awt.Dimension;
import java.awt.LayoutManager;
import java.awt.Rectangle;
import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

import javax.imageio.ImageIO;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JPanel;

public class DangerousRoads extends Game implements KeyListener{
	//EXPLOSION
	private final int EXPLOSION_SPRITE_AMOUNT_OF_ROWS = 5;
	private final int EXPLOSION_SPRITE_AMOUNT_OF_COLUMNS = 5;
	private final double EXPLOSION_SCALE = 2.5;
	private List<BufferedImage> explosionSprite;
	//GRAPHICS/FRAME PARAMETERS
	private final int WIDTH = 600;
	private final int HEIGHT = 600;
	private final int FPS = 30;
	//ROAD PARAMETERS
	private final int LANES = 6;
	private final int LANE_WIDTH = WIDTH / LANES;
	private final int DISTANCE = 50000;
	private final int DIVIDING_STRIP_LENGTH = 40;
	private final int DIVIDING_STRIP_WIDTH = 5;
	//CAR
	private final int CAR_WIDTH = LANE_WIDTH;
	private final int CAR_HEIGHT = LANE_WIDTH * 2;
	//PLAYER
	private final int START_LANE = 4;
	private final int PLAYER_VERTICAL_SPEED = 20;
	private final int PLAYER_HORIZONTAL_SPEED = PLAYER_VERTICAL_SPEED;
	private final int START_DISTANCE = 0;
	//POLICE
	private final int POLICE_DELTA_DISTANCE = 1000;
	private final int POLICE_SPEED = 10;
	private final String ARRESTED_MESSAGE = "You have just been arrested!";
	//NON-CONSTANT PARAMETERS
	private int spawnCarInterval = 1500;
	private final int MINIMUM_SPAWN_INTERVAL_AFTER = 50;
	private RoadInfo roadInfo;
	private int deltaTime = 0;
	private int passedCars = 0;
	//SPECIAL GAME OBJECTS
	private PlayerCar playerCar;
	private PoliceCar policeCar;
	//JAVA SWING
	private JLabel counter;
	private final String counterName = "Cars Passed: ";
	private boolean gameover = false;
	public DangerousRoads(JPanel parametersPanel) throws IOException {
		super();
		this.fps = FPS;
		setPreferredSize(new Dimension(WIDTH, HEIGHT));
		addKeyListener(this);
		setFocusable(true);
		roadInfo = new RoadInfo(LANES, LANE_WIDTH, DISTANCE, DIVIDING_STRIP_LENGTH, DIVIDING_STRIP_WIDTH);
		Road road = new Road(roadInfo);
		gameObjects.add(road);
		for(int y = 0; y < DISTANCE; y+=2*DIVIDING_STRIP_LENGTH) {
			for(int x = LANE_WIDTH; x < roadInfo.getWidth(); x+=LANE_WIDTH) {
				gameObjects.add(new RoadStrip(roadInfo, x, y));
			}
		}
		playerCar =   new PlayerCar(roadInfo, 
									START_LANE, 
									START_DISTANCE, 
									CAR_WIDTH, 
									CAR_HEIGHT, 
									PLAYER_VERTICAL_SPEED,
									PLAYER_HORIZONTAL_SPEED);
		gameObjects.add(playerCar);
		camera = new Camera(playerCar, WIDTH, HEIGHT);
		explosionSprite = new ArrayList<BufferedImage>();
		File file = new File("images/explosion.png");
		BufferedImage source = ImageIO.read(file);
		int dy = source.getHeight()/EXPLOSION_SPRITE_AMOUNT_OF_ROWS;
		int dx = source.getWidth()/EXPLOSION_SPRITE_AMOUNT_OF_COLUMNS;
		for(int y = 0; y < source.getHeight(); y += dy) {
			for(int x = 0; x < source.getWidth(); x += dx) {
				explosionSprite.add(source.getSubimage(x, y, dx, dy));
			}
		}
		policeCar = new PoliceCar(roadInfo, CAR_WIDTH, CAR_HEIGHT, playerCar, POLICE_DELTA_DISTANCE);
		gameObjects.add(policeCar);
		counter = new JLabel(counterName + passedCars);
		parametersPanel.add(counter);
	}

	@Override
	public void onUpdateObject(boolean updateStatus, GameObject object) {
		if(object instanceof DrawableGameObject) {
			DrawableGameObject drawable = (DrawableGameObject) object;
			if(updateStatus && drawable.getPhysicalBody().getBounds().getMaxY() 
					< camera.getPhysicalBody().getBounds().getMinY()) {
				if(drawable instanceof Car) {
					passedCars++;
					counter.setText(counterName + passedCars);
				}
				removeGameObject(drawable);
			} else if(!updateStatus) {
				if(!gameover && drawable instanceof Car) {
					playerCar.stop();
					policeCar.activate(POLICE_SPEED);
					gameover = true;
					Car car = (Car) drawable;
					removeGameObject(car);
					addGameObject(new Explosion(explosionSprite, car, EXPLOSION_SCALE));
				} else {
					if(drawable instanceof EnemyCar) {
						Car car = (Car) drawable;
						removeGameObject(car);
						addGameObject(new Explosion(explosionSprite, car, EXPLOSION_SCALE));
					} else if(drawable instanceof Explosion) {
						removeGameObject(drawable);
					} else if(drawable instanceof PoliceCar) {
						JOptionPane.showMessageDialog(null, ARRESTED_MESSAGE);
					}
				}
			}
		}
	}

	@Override
	public void keyTyped(KeyEvent e) {}

	@Override
	public void keyPressed(KeyEvent e) {
		if(e.getKeyCode() == KeyEvent.VK_LEFT) {
			playerCar.turn(PlayerCar.LEFT);
		} else if(e.getKeyCode() == KeyEvent.VK_RIGHT) {
			playerCar.turn(PlayerCar.RIGHT);
		}
		
	}

	@Override
	public void keyReleased(KeyEvent e) {}

	@Override
	public void beforeIteration() {
		if(deltaTime >= spawnCarInterval  && !gameover) {
			int minIntervalDistance = 2 * CAR_HEIGHT + CAR_HEIGHT * playerCar.getVerticalSpeed()/playerCar.getHorizontalSpeed()/2;
			int minspawnCarInterval = (minIntervalDistance / playerCar.getVerticalSpeed())*1000/fps;
			spawnCarInterval = Math.max(minspawnCarInterval, spawnCarInterval + passedCars*(minspawnCarInterval - spawnCarInterval)/MINIMUM_SPAWN_INTERVAL_AFTER);
			deltaTime = 0;
			Rectangle r = playerCar.getPhysicalBody().getBounds();
			gameObjects.add(new EnemyCar(roadInfo, 
					 						roadInfo.convertXToLanes(r.x) + 1, 
											r.y + HEIGHT, CAR_WIDTH, CAR_HEIGHT, playerCar, policeCar));
		}
		deltaTime += 1000/fps;
	}

	public int getWidth() {
		return WIDTH;
	}
	public int getHeight() {
		return HEIGHT;
	}

}
