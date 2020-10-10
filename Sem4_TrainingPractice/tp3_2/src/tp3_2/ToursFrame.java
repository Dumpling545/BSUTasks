package tp3_2;
import java.awt.BorderLayout;
import java.awt.Dimension;
import java.awt.EventQueue;
import java.awt.FlowLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.File;
import java.io.IOException;
import java.util.HashMap;
import java.util.Map;
import java.util.TreeMap;

import javax.swing.BoxLayout;
import javax.swing.JButton;
import javax.swing.JCheckBox;
import javax.swing.JFileChooser;
import javax.swing.JFrame;
import javax.swing.JList;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.border.EmptyBorder;
import javax.swing.event.ListSelectionEvent;
import javax.swing.event.ListSelectionListener;
import javax.xml.parsers.ParserConfigurationException;

import org.xml.sax.SAXException;

public class ToursFrame extends JFrame implements ActionListener {

	private JPanel contentPane;
	private JScrollPane scrollTourTablePane;
	private ToursTable toursTable;
	private JCheckBox editModeCheckBox;
	private JButton addTourButton;
	public static void main(String[] args) {
		ToursFrame frame;
			try {
				frame = new ToursFrame();
				frame.setVisible(true);
			} catch (NumberFormatException | ParserConfigurationException | SAXException | IOException e) {
				System.out.println(e.getMessage());
			}
			
	}

	public ToursFrame() throws NumberFormatException, ParserConfigurationException, SAXException, IOException {
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		setSize(720, 540);
		setTitle("Tours");
		contentPane = new JPanel();
		contentPane.setLayout(new BoxLayout(contentPane, BoxLayout.Y_AXIS));
		toursTable = new ToursTable();
		scrollTourTablePane = new JScrollPane(toursTable);
		contentPane.add(scrollTourTablePane);
		editModeCheckBox = new JCheckBox("Edit mode");
		editModeCheckBox.addActionListener(this);
		contentPane.add(editModeCheckBox);
		addTourButton = new JButton("Add new tour");
		addTourButton.addActionListener(this);
		contentPane.add(addTourButton);
		setContentPane(contentPane);
	}

	@Override
	public void actionPerformed(ActionEvent e) {
		if(e.getSource() == editModeCheckBox) {
			toursTable.setEditMode(editModeCheckBox.isSelected());
		} else {
			JFileChooser fc = new  JFileChooser("D:\\”Õ»¬≈–\\Sem4_TrainingPractice\\tp3_2\\img");
			fc.setDialogTitle("Choose flag image for new tour");
			int status = fc.showOpenDialog(this);
			if(status == JFileChooser.APPROVE_OPTION) {
				String flagSource = fc.getSelectedFile().getPath();
				if(flagSource.substring(flagSource.lastIndexOf('.'), flagSource.length()).equals(".jpg")) {
					String description = JOptionPane.showInputDialog("Enter description of new tour:");
					
					try {
						int price = Integer.parseInt(JOptionPane.showInputDialog("Enter price of new tour:"));
						toursTable.addTour(new Tour(flagSource, description, price));
					} catch(NumberFormatException|NullPointerException ex) {
						JOptionPane.showMessageDialog(this,"Please enter integer!");
					}
					
				} else {
					JOptionPane.showMessageDialog(this,"Please use .jpg images!");
				}
			}
		}
		
	}

}
