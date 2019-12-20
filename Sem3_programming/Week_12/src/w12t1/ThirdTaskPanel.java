package w12t1;

import java.awt.GridLayout;

import javax.swing.ButtonGroup;
import javax.swing.ImageIcon;
import javax.swing.JPanel;
import javax.swing.JRadioButton;

public class ThirdTaskPanel extends JPanel {
	ButtonGroup thirdTaskButtonGroup;
	private String thirdTaskIconFileName = "D:/смхбеп/Sem3_programming/Week_12/src/icon.png";
	private String thirdTaskSelectedIconFileName = "D:/смхбеп/Sem3_programming/Week_12/src/selectedIcon.png";
	private String thirdTaskRolloverIconFileName = "D:/смхбеп/Sem3_programming/Week_12/src/rolloverIcon.png";
	private String thirdTaskPressedIconFileName = "D:/смхбеп/Sem3_programming/Week_12/src/pressedIcon.png";
	private int thirdTaskButtonGroupSize = 5;
	private JRadioButton[] thirdTaskRadioButtons;
	private JPanel[] thirdTaskRadioButtonPanels;
	public ThirdTaskPanel() {
		setLayout(new GridLayout(thirdTaskButtonGroupSize, 1));
		thirdTaskButtonGroup = new ButtonGroup();
		thirdTaskRadioButtons = new JRadioButton[thirdTaskButtonGroupSize];
		thirdTaskRadioButtonPanels = new JPanel[thirdTaskButtonGroupSize];
		ImageIcon icon = new ImageIcon(thirdTaskIconFileName);
		ImageIcon pressedIcon = new ImageIcon(thirdTaskPressedIconFileName);
		ImageIcon rolloverIcon = new ImageIcon(thirdTaskRolloverIconFileName);
		ImageIcon selectedIcon = new ImageIcon(thirdTaskSelectedIconFileName);
		for(int i = 0; i < thirdTaskButtonGroupSize; i++) {
			thirdTaskRadioButtonPanels[i] = new JPanel();
			thirdTaskRadioButtons[i] = new JRadioButton(Integer.toString(i));
			thirdTaskButtonGroup.add(thirdTaskRadioButtons[i]);
			thirdTaskRadioButtonPanels[i].add(thirdTaskRadioButtons[i]);
			thirdTaskRadioButtons[i].setIcon(icon);
			thirdTaskRadioButtons[i].setPressedIcon(pressedIcon);
			thirdTaskRadioButtons[i].setRolloverIcon(rolloverIcon);
			thirdTaskRadioButtons[i].setSelectedIcon(selectedIcon);
			add(thirdTaskRadioButtonPanels[i]);
		}
	}

}
