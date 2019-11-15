package w10t2;

import java.awt.BorderLayout;
import java.awt.EventQueue;
import java.awt.FocusTraversalPolicy;
import java.awt.Point;
import java.awt.Rectangle;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import java.awt.event.MouseMotionListener;

import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.border.Border;
import javax.swing.border.EmptyBorder;
import javax.swing.JLabel;
import javax.swing.JButton;

public class QuestionFrame extends JFrame {

	private Rectangle bounds = new Rectangle(100, 100, 284, 158);
	private JPanel contentPane;
	private JLabel question;
	private Rectangle questionBounds = new Rectangle(0, 0, 200, 20);
	private JButton yesButton;
	private int yesButtonX = 0;
	private int buttonY = 59;
	private int margin = 20;
	private int buttonWidth = 60;
	private int buttonHeight = 30;
	private Rectangle yesButtonBounds = new Rectangle(yesButtonX, 
													  buttonY, 
													  buttonWidth, 
													  buttonHeight);
	private JPanel noButtonSurroundings;
	private int noButtonSurroundingsX = 120;
	private Rectangle noButtonSurroundingsBounds = new Rectangle(noButtonSurroundingsX, 
																 buttonY - margin, 
																 buttonWidth + 2*margin, 
																 buttonHeight + 2*margin);
	private JButton noButton;
	private Rectangle noButtonBounds = new Rectangle(margin, 
													 margin, 
													 buttonWidth, 
													 buttonHeight);
	private Point entryPoint = new Point(0, 0);
	public static void main(String[] args) {
		EventQueue.invokeLater(new Runnable() {
			public void run() {
				try {
					QuestionFrame frame = new QuestionFrame();
					frame.setVisible(true);
				} catch (Exception e) {
					e.printStackTrace();
				}
			}
		});
	}

	public QuestionFrame() {
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		setBounds(bounds);
		contentPane = new JPanel();
		setContentPane(contentPane);
		contentPane.setLayout(null);
		MouseListener ml =  new MouseListener() {
			@Override
			public void mouseClicked(MouseEvent e) {}
			@Override
			public void mousePressed(MouseEvent e) {}
			@Override
			public void mouseReleased(MouseEvent e) {}
			@Override
			public void mouseEntered(MouseEvent e) {
				entryPoint.move(e.getX(), e.getY());
			}

			@Override
			public void mouseExited(MouseEvent e) {}
			
		};		
		question = new JLabel("Радует ли вас размер стипендии?");
		question.setBounds(questionBounds);
		contentPane.add(question);
		
		yesButton = new JButton("Да");
		yesButton.setBounds(yesButtonBounds);
		contentPane.add(yesButton);
		yesButton.addActionListener(new ActionListener() {
			
			@Override
			public void actionPerformed(ActionEvent e) {
				yesButton.setVisible(false);
				noButton.setVisible(false);
				question.setText("Отлично!");
			}
		});
		
		
		noButtonSurroundings = new JPanel();
		noButtonSurroundings.setBounds(noButtonSurroundingsBounds);
		contentPane.add(noButtonSurroundings);
		noButtonSurroundings.setLayout(null);
		noButtonSurroundings.addMouseListener(ml);
		noButtonSurroundings.addMouseMotionListener(new MouseMotionListener() {
			@Override
			public void mouseDragged(MouseEvent e) {}
			@Override
			public void mouseMoved(MouseEvent e) {
				onMouseMovedIntoNoButtonSurroundings(e.getX(), e.getY());
			}	
		});
		
		noButton = new JButton("Нет");
		noButton.setBounds(noButtonBounds);
		noButtonSurroundings.add(noButton);
		noButton.setFocusable(false);
		noButton.addMouseMotionListener(new MouseMotionListener() {
			@Override
			public void mouseDragged(MouseEvent e) {}
			@Override
			public void mouseMoved(MouseEvent e) {
				onMouseMovedIntoNoButtonSurroundings(noButton.getX() + e.getX(), 
													 noButton.getY() + e.getY());
			}	
		});
	}
	private void onMouseMovedIntoNoButtonSurroundings(int x, int y) {
		Rectangle newBounds = noButtonSurroundings.getBounds();
		int dx= x - entryPoint.x;
		int dy= y - entryPoint.y;
		dx *= 2;
		dy *= 2;
		newBounds.x += dx;
		newBounds.y += dy;
		noButtonSurroundings.setBounds(newBounds);
	}
}
