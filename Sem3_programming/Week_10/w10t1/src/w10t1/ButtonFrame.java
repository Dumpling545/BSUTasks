package w10t1;

import java.awt.BorderLayout;
import java.awt.EventQueue;
import java.awt.Rectangle;
import java.awt.event.ComponentEvent;
import java.awt.event.ComponentListener;
import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import java.awt.event.MouseMotionListener;

import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.border.EmptyBorder;
import javax.swing.JButton;
import javax.swing.JLabel;

public class ButtonFrame extends JFrame {
	private Rectangle bounds = new Rectangle(100, 100, 450, 300);
	private JPanel contentPane;
	private JButton button;
	private Rectangle buttonBounds = new Rectangle(0, 0, 89, 23);
	private JLabel statusbar;
	private Rectangle statusbarBounds = new Rectangle(0, 247, 200, 14);
	private int button_pressed_inner_x = 0;
	private int button_pressed_inner_y = 0;
	public ButtonFrame() {
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		setBounds(bounds);
		setFocusable(true);
		contentPane = new JPanel();
		setContentPane(contentPane);
		contentPane.setLayout(null);
		
		button = new JButton("Button");
		button.setBounds(buttonBounds);
		contentPane.add(button);
		
		statusbar = new JLabel();
		statusbar.setBounds(statusbarBounds);
		contentPane.add(statusbar);
		KeyListener kl = new KeyListener() {
			@Override
			public void keyTyped(KeyEvent e) {}
			@Override
			public void keyReleased(KeyEvent e) {
				if(e.getKeyCode() == KeyEvent.VK_BACK_SPACE) {
					int length = button.getText().length();
					if(length > 0) {
						button.setText(button.getText().substring(0, length-1));
					}
				} else if(Character.isDefined(e.getKeyChar())) {
					button.setText(button.getText() + e.getKeyChar());
				}
			}
			@Override
			public void keyPressed(KeyEvent e) {}
		};
		addKeyListener(kl);
		contentPane.addComponentListener(new ComponentListener() {
			@Override
			public void componentResized(ComponentEvent e) {
				statusbar.setBounds(0, 
										contentPane.getHeight() - statusbar.getHeight(), 
										statusbar.getWidth(),
										statusbar.getHeight());			
			}
			@Override
			public void componentMoved(ComponentEvent e) {}
			@Override
			public void componentHidden(ComponentEvent e) {}
			@Override
			public void componentShown(ComponentEvent e) {}
		});
		
		contentPane.addMouseListener(new MouseListener() {
			@Override
			public void mouseReleased(MouseEvent e) {}
			@Override
			public void mousePressed(MouseEvent e) {}
			@Override
			public void mouseExited(MouseEvent e) {}
			@Override
			public void mouseEntered(MouseEvent e) {}
			@Override
			public void mouseClicked(MouseEvent e) {
				button.setBounds(e.getX(), e.getY(), button.getWidth(), button.getHeight());
			}
		});
		contentPane.addMouseMotionListener(new MouseMotionListener() {
			
			@Override
			public void mouseMoved(MouseEvent e) {
				onMouseMoved(e.getX(), e.getY());
			}
			
			@Override
			public void mouseDragged(MouseEvent e) {
				onMouseMoved(e.getX(), e.getY());
				
			}
		});
		button.addKeyListener(kl);
		button.addMouseListener(new MouseListener() {
			@Override
			public void mouseReleased(MouseEvent e) {}
			@Override
			public void mousePressed(MouseEvent e) {
				button_pressed_inner_x = e.getXOnScreen() - button.getX();
				button_pressed_inner_y = e.getYOnScreen() - button.getY();
			}
			@Override
			public void mouseExited(MouseEvent e) {}
			@Override
			public void mouseEntered(MouseEvent e) {}
			@Override
			public void mouseClicked(MouseEvent e) {}
		});
		button.addMouseMotionListener(new MouseMotionListener() {
			@Override
			public void mouseMoved(MouseEvent e) {
				onMouseMoved(e.getX() + button.getX(), 
							 e.getY() + button.getY());
			}
			
			@Override
			public void mouseDragged(MouseEvent e) {
				onMouseMoved(e.getX() + button.getX(), 
						 e.getY() + button.getY());
				if(e.isControlDown()) {
					button.setBounds(e.getXOnScreen() - button_pressed_inner_x, 
									 e.getYOnScreen() - button_pressed_inner_y, 
									 button.getWidth(), 
									 button.getHeight());
				}
			}
		});
	}
	private void onMouseMoved(int x, int y) {
		StringBuffer sb = new StringBuffer();
		sb.append("Mouse at(");
		sb.append(x);
		sb.append("; ");
		sb.append(y);
		sb.append(")");
		statusbar.setText(sb.toString());
	}
}
