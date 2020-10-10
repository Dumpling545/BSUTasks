package tp6_1;

import java.awt.Dimension;
import java.awt.Graphics2D;
import java.awt.GraphicsEnvironment;
import java.awt.GridLayout;
import java.awt.Image;
import java.awt.Rectangle;
import java.awt.Toolkit;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import java.awt.image.BufferedImage;
import java.awt.image.MemoryImageSource;
import java.awt.image.PixelGrabber;
import java.io.File;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Collections;

import javax.imageio.ImageIO;
import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JComponent;
import javax.swing.JFileChooser;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JMenu;
import javax.swing.JMenuBar;
import javax.swing.JMenuItem;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JSpinner;
import javax.swing.JTextField;
import javax.swing.SpinnerModel;
import javax.swing.SpinnerNumberModel;

public class PuzzleGameFrame extends JFrame implements ActionListener, MouseListener {
	private int size;
	private int empty;
	private boolean finished = false;
	private final int MINIMAL_SIZE = 2;
	private final int MAXIMAL_SIZE = 10;
	private JPanel puzzlePanel;
	private ImagePanel sourcePanel;
	private JMenuBar menuBar;
	private JMenu gameMenu;
	private JMenuItem startNewMenuItem;
	private BufferedImage chosenImage;
	private JSpinner sizeSpinner;
	private JLabel sizeSpinnerLabel;
	private JButton chooseImageButton;
	private JLabel chosenImageSourceLabel;
	private JComponent[] newGameInputs;
	private double maximumImageHeight;
	private double maximumImageWidth;
	private ArrayList<PuzzleNode> puzzle;
	public PuzzleGameFrame() {
		puzzle = new ArrayList<PuzzleNode>();
		setTitle("Puzzle");
		setResizable(false);
		setSize(new Dimension(640, 480));
		JPanel contentPane = new JPanel();
		contentPane.setLayout(new GridLayout(1, 2));
		setContentPane(contentPane);
		puzzlePanel = new JPanel();
		sourcePanel = new ImagePanel();
		contentPane.add(puzzlePanel);
		contentPane.add(sourcePanel);
		menuBar = new JMenuBar();
		gameMenu = new JMenu("Game");
		startNewMenuItem = new JMenuItem("Start new");
		startNewMenuItem.addActionListener(this);
		gameMenu.add(startNewMenuItem);
		menuBar.add(gameMenu);
		setJMenuBar(menuBar);
		Rectangle bounds = GraphicsEnvironment.getLocalGraphicsEnvironment().getMaximumWindowBounds();
		maximumImageHeight = bounds.height - (getInsets().top +  getInsets().bottom);
		maximumImageWidth = (bounds.width - (getInsets().left +  getInsets().right))/2;
		sizeSpinnerLabel = new JLabel("Size:");
		sizeSpinner = new JSpinner(new SpinnerNumberModel(MINIMAL_SIZE, 
														  MINIMAL_SIZE, 
														  MAXIMAL_SIZE, 
                										  1));
		((JSpinner.DefaultEditor) sizeSpinner.getEditor()).getTextField().setEditable(false);
		chosenImageSourceLabel = new JLabel("<no image chosen>");
		chooseImageButton = new JButton("Choose Image...");
		chooseImageButton.addActionListener(this);
		newGameInputs = new JComponent[] {
				sizeSpinnerLabel,
				sizeSpinner,
				chooseImageButton,
				chosenImageSourceLabel
		};
	}
	public static void main(String[] args) {
        PuzzleGameFrame pgframe = new PuzzleGameFrame();
        pgframe.setVisible(true);
    }
	private void start() {
		finished = false;
		double resizeCoeffficient = Math.min(maximumImageWidth/chosenImage.getWidth(), maximumImageHeight/chosenImage.getHeight());
		if(resizeCoeffficient < 1) {
			int newWidth = (int)(resizeCoeffficient*chosenImage.getWidth());
			int newHeight = (int)(resizeCoeffficient*chosenImage.getHeight());
			Image tmp = chosenImage.getScaledInstance(newWidth, newHeight, Image.SCALE_SMOOTH);
			chosenImage = new BufferedImage(newWidth, newHeight, BufferedImage.TYPE_INT_ARGB);
		    Graphics2D g2d = chosenImage.createGraphics();
		    g2d.drawImage(tmp, 0, 0, null);
		    g2d.dispose();
		}
		puzzle.clear();
		puzzlePanel.removeAll();
		puzzlePanel.revalidate();
		empty = size*size - 1;
		getContentPane().setPreferredSize(new Dimension(2*chosenImage.getWidth(), chosenImage.getHeight()));
		pack();
		sourcePanel.setImage(chosenImage);
		puzzlePanel.setLayout(new GridLayout(size, size));
		puzzlePanel.setPreferredSize(new Dimension(chosenImage.getWidth(), chosenImage.getHeight()));
		int columnWidth = chosenImage.getWidth() / size;
		int rowHeight = chosenImage.getHeight() / size;
		for(int i = 0; i <= empty; i++) {
			PuzzleNode node = new PuzzleNode(i);
			if( i != empty) {
				node.setImage(chosenImage.getSubimage((i % size) * columnWidth, 
													  (i / size) * rowHeight, 
													   columnWidth, 
													   rowHeight));
			}
			node.addMouseListener(this);
			puzzle.add(node);
		}
		while(!isPuzzleValid() || isGameEnded(false)) {
			Collections.shuffle(puzzle);
		}
		for(PuzzleNode node : puzzle) {
			puzzlePanel.add(node);
		}
		getContentPane().repaint();
	}
	private boolean isPuzzleValid() {
		int clutterParameter = 0;
		for (int i = 0; i < puzzle.size(); i++) {
			if (puzzle.get(i).getIndex() == empty && size % 2 == 0) {
				clutterParameter += i/size + 1;
				continue;
			}
			for (int j = i+1; j < puzzle.size(); j++) {
				if (puzzle.get(i).getIndex() > puzzle.get(j).getIndex() && puzzle.get(j).getIndex() != empty) {
					clutterParameter++;
				}
			}
		}
	return clutterParameter % 2 == 0;
	}
	private boolean isGameEnded(boolean messageNeeded) {
		int index = 0;
		for(; index <= empty; index++) {
			if(puzzle.get(index).getIndex() != index) break;
		}
		if(index == empty + 1) {
			if(messageNeeded) JOptionPane.showMessageDialog(null, "You win");
			return true;
		}
		return false;
	}
	@Override
	public void actionPerformed(ActionEvent e) {
		if(e.getSource() == startNewMenuItem) {
			chosenImage = null;
			chosenImageSourceLabel.setText("<no image chosen>");
			int result = JOptionPane.showConfirmDialog(null, 
													   newGameInputs, 
													   "New game", 
													   JOptionPane.PLAIN_MESSAGE);
			if (result == JOptionPane.OK_OPTION) {
				if(chosenImage != null) {
					size = (int) sizeSpinner.getValue();
					start();
				} else {
					JOptionPane.showMessageDialog(null, 
							"Some issues with image (image is not chosen/not-image is choosen)", 
							"Error", 
							JOptionPane.ERROR_MESSAGE);
				}
			}
		} else if(e.getSource() == chooseImageButton) {
			JFileChooser fc = new JFileChooser("D:\\ÓÍÈÂÅÐ\\Sem4_TrainingPractice\\tp6_1");
			int result = fc.showOpenDialog(null);
			if(result == JFileChooser.APPROVE_OPTION) {
				File file = fc.getSelectedFile();
				try {
					chosenImage = ImageIO.read(file);
					chosenImageSourceLabel.setText(file.getName());
				} catch(IllegalArgumentException|IOException ex) {
					JOptionPane.showMessageDialog(null, 
												ex.getMessage(), 
												"Error while reading image", 
												JOptionPane.ERROR_MESSAGE);
				}
			}
		}
	}
	@Override
	public void mouseClicked(MouseEvent e) {}
	@Override
	public void mousePressed(MouseEvent e) {
		if(!finished) {
			PuzzleNode node = (PuzzleNode) e.getSource();
			int index = puzzle.indexOf(node);
			int rowIndex = index / size;
			int columnIndex = index % size;
			if(rowIndex > 0 && puzzle.get(index - size).getIndex() == empty) {
				node.swap(puzzle.get(index - size));
			} else if(rowIndex < size - 1 && puzzle.get(index + size).getIndex() == empty) {
				node.swap(puzzle.get(index + size));
			} else if(columnIndex > 0 && puzzle.get(index - 1).getIndex() == empty) {
				node.swap(puzzle.get(index - 1));
			} else if(columnIndex < size - 1 && puzzle.get(index + 1).getIndex() == empty) {
				node.swap(puzzle.get(index + 1));
			}
			getContentPane().repaint();
			finished = isGameEnded(true);
		}
	}
	@Override
	public void mouseReleased(MouseEvent e) {}
	@Override
	public void mouseEntered(MouseEvent e) {}
	@Override
	public void mouseExited(MouseEvent e) {}
}
