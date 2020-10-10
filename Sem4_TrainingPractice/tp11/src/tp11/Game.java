package tp11;

import java.awt.Graphics;
import java.awt.Rectangle;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;
import java.util.Queue;

import javax.swing.JPanel;
import javax.swing.Timer;

public abstract class Game extends JPanel implements ActionListener{
	protected Camera camera;
	protected List<GameObject> gameObjects;
	protected List<GameObject> objectsToRemove;
	protected List<GameObject> objectsToAdd;
	protected int fps;
	protected int time;
	//protected int reservedPostionsInEnd = 0;
	protected boolean started = false;
	public Game() {
		gameObjects = new ArrayList<GameObject>();
		objectsToRemove = new ArrayList<GameObject>();
		objectsToAdd = new ArrayList<GameObject>();
	}
	public Game(Camera camera, List<GameObject> gameObjects, int fps) {
		this.camera = camera;
		this.gameObjects = gameObjects;
		this.fps = fps;
	}
	protected void start() {
		started = true;
		Timer timer = new Timer(1000/fps, this);
		timer.start();
	}
	protected void addGameObject(GameObject obj) {
		objectsToAdd.add(obj);
	}
	protected void removeGameObject(GameObject obj) {
		objectsToRemove.add(obj);
	}
	protected void updateGameObjects() {
		camera.update();
		for(GameObject obj : gameObjects) {
			boolean status = obj.update();
			onUpdateObject(status, obj);
		}
		gameObjects.removeAll(objectsToRemove);
		gameObjects.addAll(objectsToAdd);
	}
	@Override
	protected void paintComponent(Graphics g) {
		super.paintComponent(g);
		Rectangle r = camera.getPhysicalBody().getBounds();
		g.translate(r.x, -r.y);
		if(started) {
			for(int i = 0; i < gameObjects.size(); i++) {
				if(gameObjects.get(i) instanceof DrawableGameObject) {
					DrawableGameObject drawable = (DrawableGameObject) gameObjects.get(i);
					if(drawable.intersects(camera)) {
						drawable.draw(g);
					}
				}
			}
		}
	}
	public abstract void onUpdateObject(boolean updateStatus, GameObject object);
	public abstract void beforeIteration();
	@Override
	public void actionPerformed(ActionEvent e) {
		beforeIteration();
		updateGameObjects();
		repaint();
		time += 1000/fps;
	}
}
