package tp6_1;

import java.awt.image.BufferedImage;

public class PuzzleNode extends ImagePanel{
	private int index; 
	public PuzzleNode(int index) {
		super();
		this.index = index;
	}
	public int getIndex() {
		return index;
	}
	public void swap(PuzzleNode node) {
		BufferedImage img = getImage();
		setImage(node.getImage());
		node.setImage(img);
		int temp = index;
		index = node.index;
		node.index = temp;
		
	}

}
