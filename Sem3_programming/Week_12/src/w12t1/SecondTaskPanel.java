package w12t1;

import java.awt.Color;
import java.awt.GridLayout;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;

import javax.swing.JButton;
import javax.swing.JPanel;

public class SecondTaskPanel extends JPanel implements MouseListener {
	private final int secondTaskGridLayoutRows = 10;
	private final int secondTaskGridLayoutCols = 10;
	private final Color secondTaskDefaultButtonColor = Color.YELLOW;
	private  String currentSecondTaskButtonText = "";
	private final Color secondTaskEnteredButtonColor = Color.BLUE;
	private final String secondTaskPressedButtonText = "Clicked!";
	public SecondTaskPanel() {
		setLayout(new GridLayout(secondTaskGridLayoutRows, 
		secondTaskGridLayoutCols));
		JButton secondTaskButton;
		for(int i = 0; i < secondTaskGridLayoutRows; i++) {
			for(int j = 0; j < secondTaskGridLayoutCols; j++) {
				secondTaskButton = new JButton();
				secondTaskButton.setText(Integer.toString(i*secondTaskGridLayoutRows + j));
				secondTaskButton.setBackground(secondTaskDefaultButtonColor);
				secondTaskButton.addMouseListener(this);
				add(secondTaskButton);
			}
		}
	}
	@Override
	public void mouseClicked(MouseEvent e) {}

	@Override
	public void mousePressed(MouseEvent e) {
		if(e.getButton() == MouseEvent.BUTTON1) {
			JButton button = (JButton) e.getSource();
			currentSecondTaskButtonText = button.getText();
			button.setText(secondTaskPressedButtonText);
		}
	}

	@Override
	public void mouseReleased(MouseEvent e) {
		if(e.getButton() == MouseEvent.BUTTON1) {
			JButton button = (JButton) e.getSource();
			button.setText(currentSecondTaskButtonText);
		}
	}

	@Override
	public void mouseEntered(MouseEvent e) {
		JButton button = (JButton) e.getSource();
		button.setBackground(secondTaskEnteredButtonColor);
		
	}

	@Override
	public void mouseExited(MouseEvent e) {
		JButton button = (JButton) e.getSource();
		button.setBackground(secondTaskDefaultButtonColor);
		
	}
}
