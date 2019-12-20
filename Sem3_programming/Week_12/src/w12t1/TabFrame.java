package w12t1;

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.EventQueue;
import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.KeyEvent;
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

public class TabFrame extends JFrame {
	private JTabbedPane tabbedPane;
	private JPanel contentPane;
	private String firstTaskTabName = "Task 1",
				   secondTaskTabName = "Task 2",
				   thirdTaskTabName = "Task 3";
	
	private FirstTaskPanel firstTaskPanel;
	private SecondTaskPanel secondTaskPanel;
	private ThirdTaskPanel thirdTaskPanel;
	
	
	public static void main(String[] args) {
		TabFrame frame = new TabFrame();
		frame.setVisible(true);
	}
	
	public TabFrame() {
		setExtendedState(JFrame.MAXIMIZED_BOTH);
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		setBounds(100, 100, 450, 300);
		contentPane = new JPanel();
		contentPane.setLayout(new BorderLayout());
		setContentPane(contentPane);
		
		tabbedPane = new JTabbedPane();
		firstTaskPanel = new FirstTaskPanel();
		tabbedPane.addTab(firstTaskTabName, firstTaskPanel);
		secondTaskPanel = new SecondTaskPanel();
		tabbedPane.addTab(secondTaskTabName, secondTaskPanel);
		thirdTaskPanel = new ThirdTaskPanel();
		tabbedPane.addTab(thirdTaskTabName, thirdTaskPanel);
		contentPane.add(tabbedPane, BorderLayout.CENTER);
	}

}
