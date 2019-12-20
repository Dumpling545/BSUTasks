package w12t1;

import java.awt.BorderLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.DefaultListModel;
import javax.swing.JButton;
import javax.swing.JList;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.ListSelectionModel;

public class FirstTaskPanel extends JPanel  implements ActionListener{
	private JPanel firstTaskInnerPanel;
	private JButton firstTaskLeftButton, firstTaskRightButton;
	private String firstTaskLeftButtonText = "<<", firstTaskRightButtonText = ">>";
	private JScrollPane firstTaskLeftListScrollPane, firstTaskRightListScrollPane;
	private JList<String> firstTaskLeftList, firstTaskRightList;
	private DefaultListModel<String> firstTaskLeftListModel, firstTaskRightListModel;
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
	public FirstTaskPanel() {
		super();
		initFirstTaskListModels();	
		setLayout(new BorderLayout(0, 0));
		
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
		
		add(firstTaskLeftListScrollPane, BorderLayout.WEST);
		add(firstTaskRightListScrollPane, BorderLayout.EAST);
		add(firstTaskInnerPanel, BorderLayout.CENTER);
	}
	@Override
	public void actionPerformed(ActionEvent e) {
		if(e.getSource() == firstTaskRightButton) {
			firstTaskRightListModel.addAll(firstTaskLeftList.getSelectedValuesList());
			int [] leftIndices = firstTaskLeftList.getSelectedIndices();
			for(int i = leftIndices.length - 1; i >= 0; i--) {
				firstTaskLeftListModel.removeElementAt(leftIndices[i]);
			}
		} else if(e.getSource() == firstTaskLeftButton){
			firstTaskLeftListModel.addAll(firstTaskRightList.getSelectedValuesList());
			int [] rightIndices = firstTaskRightList.getSelectedIndices();
			for(int i = rightIndices.length - 1; i >= 0; i--) {
				firstTaskRightListModel.removeElementAt(rightIndices[i]);
			}
		}
	}
}
