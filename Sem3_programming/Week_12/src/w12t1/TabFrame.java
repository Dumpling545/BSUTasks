package w12t1;

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.EventQueue;
import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;

import javax.swing.ButtonGroup;
import javax.swing.DefaultListModel;
import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JList;
import javax.swing.JPanel;
import javax.swing.JRadioButton;
import javax.swing.JScrollPane;
import javax.swing.JTabbedPane;
import javax.swing.ListSelectionModel;

public class TabFrame extends JFrame implements ActionListener, MouseListener {
	private JTabbedPane tabbedPane;
	private JPanel contentPane;
	private String firstTaskTabName = "Task 1",
				   secondTaskTabName = "Task 2",
				   thirdTaskTabName = "Task 3";
	
	private JPanel firstTaskPanel, firstTaskInnerPanel;
	private JButton firstTaskLeftButton, firstTaskRightButton;
	private String firstTaskLeftButtonText = "<<", firstTaskRightButtonText = ">>";
	private JScrollPane firstTaskLeftListScrollPane, firstTaskRightListScrollPane;
	private JList<String> firstTaskLeftList, firstTaskRightList;
	private DefaultListModel<String> firstTaskLeftListModel, firstTaskRightListModel;
	
	private JPanel secondTaskPanel;
	private final int secondTaskGridLayoutRows = 10;
	private final int secondTaskGridLayoutCols = 10;
	private JButton[][]  secondTaskButtons;
	private final Color secondTaskDefaultButtonColor = Color.YELLOW;
	private final String secondTaskDefaultButtonText = "";
	private final Color secondTaskEnteredButtonColor = Color.BLUE;
	private final String secondTaskPressedButtonText = "Clicked!";

	private JPanel thirdTaskPanel;
	ButtonGroup thirdTaskButtonGroup;
	private final String thirdTaskIconFileName = "D:/”Õ»¬≈–/Sem3_programming/Week_12/src/icon.png";
	private final String thirdTaskSelectedIconFileName = "D:/”Õ»¬≈–/Sem3_programming/Week_12/src/selectedIcon.png";
	private final String thirdTaskRolloverIconFileName = "D:/”Õ»¬≈–/Sem3_programming/Week_12/src/rolloverIcon.png";
	private final String thirdTaskPressedIconFileName = "D:/”Õ»¬≈–/Sem3_programming/Week_12/src/pressedIcon.png";
	private final int thirdTaskButtonGroupSize = 5;
	private JRadioButton[] thirdTaskRadioButtons;
	
	public static void main(String[] args) {
		EventQueue.invokeLater(new Runnable() {
			public void run() {
				try {
					TabFrame frame = new TabFrame();
					frame.setVisible(true);
				} catch (Exception e) {
					e.printStackTrace();
				}
			}
		});
	}

	public void initFirstTaskListModels() {
		firstTaskLeftListModel = new DefaultListModel<String>();
		firstTaskRightListModel = new DefaultListModel<String>();
		for(int i = 0; i < 'z' - 'a' + 1; i++) {
			StringBuffer sbleft = new StringBuffer();
			StringBuffer sbright = new StringBuffer();
			for(int j = 0; j < 10; j++) {
				sbleft.append((char)('a' + i));
				sbright.append((char)('A' + i));
			}
			firstTaskLeftListModel.addElement(sbleft.toString());
			firstTaskRightListModel.addElement(sbright.toString());
		}
	}
	public void createFirstTaskPanel() {
		initFirstTaskListModels();
		
		firstTaskPanel = new JPanel();
		firstTaskPanel.setLayout(new BorderLayout(0, 0));
		
		firstTaskInnerPanel = new JPanel();
		firstTaskInnerPanel.setLayout(new BorderLayout(0, 0));
		
		firstTaskRightButton = new JButton(firstTaskRightButtonText);
		firstTaskRightButton.addActionListener(this);
		
		firstTaskLeftButton = new JButton(firstTaskLeftButtonText);
		firstTaskLeftButton.addActionListener(this);
		
		firstTaskInnerPanel.add(firstTaskRightButton, BorderLayout.NORTH);
		firstTaskInnerPanel.add(firstTaskLeftButton, BorderLayout.SOUTH);
		
		firstTaskLeftList = new JList<String>(firstTaskLeftListModel);
		firstTaskLeftList.setSelectionMode(ListSelectionModel.MULTIPLE_INTERVAL_SELECTION);
		firstTaskLeftList.setLayoutOrientation(JList.VERTICAL);
		firstTaskLeftListScrollPane = new JScrollPane(firstTaskLeftList);
		
		firstTaskRightList = new JList<String>(firstTaskRightListModel);
		firstTaskRightList.setSelectionMode(ListSelectionModel.MULTIPLE_INTERVAL_SELECTION);
		firstTaskRightList.setLayoutOrientation(JList.VERTICAL);
		firstTaskRightListScrollPane = new JScrollPane(firstTaskRightList);
		
		firstTaskPanel.add(firstTaskLeftListScrollPane, BorderLayout.WEST);
		firstTaskPanel.add(firstTaskRightListScrollPane, BorderLayout.EAST);
		firstTaskPanel.add(firstTaskInnerPanel, BorderLayout.CENTER);
	}
	
	public void createSecondTaskPanel() {
		secondTaskPanel = new JPanel();
		secondTaskPanel.setLayout(new GridLayout(secondTaskGridLayoutRows, 
													secondTaskGridLayoutCols));
		secondTaskButtons = new JButton[secondTaskGridLayoutRows][secondTaskGridLayoutCols];
		for(int i = 0; i < secondTaskGridLayoutRows; i++) {
			for(int j = 0; j < secondTaskGridLayoutCols; j++) {
				secondTaskButtons[i][j] = new JButton(secondTaskDefaultButtonText);
				secondTaskButtons[i][j].setBackground(secondTaskDefaultButtonColor);
				secondTaskButtons[i][j].addMouseListener(this);
				secondTaskPanel.add(secondTaskButtons[i][j]);
			}
		}
	}
	
	public void createThirdTaskPanel() {
		thirdTaskPanel = new JPanel();
		thirdTaskPanel.setLayout(new GridLayout(thirdTaskButtonGroupSize, 1));
		thirdTaskButtonGroup = new ButtonGroup();
		thirdTaskRadioButtons = new JRadioButton[thirdTaskButtonGroupSize];
		ImageIcon icon = new ImageIcon(thirdTaskIconFileName);
		ImageIcon pressedIcon = new ImageIcon(thirdTaskPressedIconFileName);
		ImageIcon rolloverIcon = new ImageIcon(thirdTaskRolloverIconFileName);
		ImageIcon selectedIcon = new ImageIcon(thirdTaskSelectedIconFileName);
		for(int i = 0; i < thirdTaskButtonGroupSize; i++) {
			thirdTaskRadioButtons[i] = new JRadioButton(Integer.toString(i));
			thirdTaskButtonGroup.add(thirdTaskRadioButtons[i]);
			thirdTaskRadioButtons[i].setIcon(icon);
			thirdTaskRadioButtons[i].setPressedIcon(pressedIcon);
			thirdTaskRadioButtons[i].setRolloverIcon(rolloverIcon);
			thirdTaskRadioButtons[i].setSelectedIcon(selectedIcon);
			thirdTaskPanel.add(thirdTaskRadioButtons[i]);
		}
	}
	public TabFrame() {
		setExtendedState(JFrame.MAXIMIZED_BOTH);
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		setBounds(100, 100, 450, 300);
		contentPane = new JPanel();
		contentPane.setLayout(new BorderLayout());
		setContentPane(contentPane);
		
		tabbedPane = new JTabbedPane();
		createFirstTaskPanel();
		tabbedPane.addTab(firstTaskTabName, firstTaskPanel);
		createSecondTaskPanel();
		tabbedPane.addTab(secondTaskTabName, secondTaskPanel);
		createThirdTaskPanel();
		tabbedPane.addTab(thirdTaskTabName, thirdTaskPanel);
		contentPane.add(tabbedPane, BorderLayout.CENTER);
	}

	@Override
	public void actionPerformed(ActionEvent e) {
		if(e.getSource() == firstTaskRightButton) {
			firstTaskRightListModel.addAll(firstTaskLeftList.getSelectedValuesList());
			for(String value : firstTaskLeftList.getSelectedValuesList()) {
				firstTaskLeftListModel.removeElement(value);
			}
		} else if(e.getSource() == firstTaskLeftButton){
			firstTaskLeftListModel.addAll(firstTaskRightList.getSelectedValuesList());
			for(String value : firstTaskRightList.getSelectedValuesList()) {
				firstTaskRightListModel.removeElement(value);
			}
		}
		
	}

	@Override
	public void mouseClicked(MouseEvent e) {}

	@Override
	public void mousePressed(MouseEvent e) {
		JButton button = (JButton) e.getSource();
		button.setText(secondTaskPressedButtonText);
	}

	@Override
	public void mouseReleased(MouseEvent e) {
		JButton button = (JButton) e.getSource();
		button.setText(secondTaskDefaultButtonText);
		
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
