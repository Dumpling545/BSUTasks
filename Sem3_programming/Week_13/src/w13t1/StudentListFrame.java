package w13t1;

import java.awt.BorderLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.File;
import java.io.IOException;
import java.util.NoSuchElementException;
import java.util.Scanner;

import javax.swing.JButton;
import javax.swing.JFileChooser;
import javax.swing.JFrame;
import javax.swing.JList;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.ListSelectionModel;
import javax.swing.border.EmptyBorder;

public class StudentListFrame extends JFrame implements ActionListener {

	private JPanel contentPane;
	private JList<String> studentList;
	private StudentListModel studentListModel;
	private JScrollPane studentListScrollPane;
	private JButton openFileButton;
	private JButton addStudentButton;
	private final String CURRENT_DIRECTORY = "D:/”Õ»¬≈–/Sem3_programming/Week_13";

	public static void main(String[] args) {
		StudentListFrame frame = new StudentListFrame();
		frame.setVisible(true);
	}

	public StudentListFrame() {
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		setBounds(100, 100, 450, 300);
		contentPane = new JPanel();
		contentPane.setBorder(new EmptyBorder(5, 5, 5, 5));
		contentPane.setLayout(new BorderLayout(0, 0));
		
		studentListModel = new StudentListModel();
		studentList = new JList<String>(studentListModel);
		studentList.setSelectionMode(ListSelectionModel.SINGLE_SELECTION);
		studentList.setLayoutOrientation(JList.VERTICAL);
		studentListScrollPane = new JScrollPane(studentList);
		contentPane.add(studentListScrollPane, BorderLayout.CENTER);
		
		openFileButton = new JButton("Open File...");
		openFileButton.addActionListener(this);
		contentPane.add(openFileButton, BorderLayout.NORTH);
		
		addStudentButton = new JButton("Add Student...");
		addStudentButton.addActionListener(this);
		contentPane.add(addStudentButton, BorderLayout.SOUTH);
		setContentPane(contentPane);
	}

	@Override
	public void actionPerformed(ActionEvent e) {
		try {
			if(e.getSource() == openFileButton) {
				JFileChooser chooser = new JFileChooser();
				chooser.setCurrentDirectory(new File(CURRENT_DIRECTORY));
				if(chooser.showOpenDialog(null) == JFileChooser.APPROVE_OPTION) {
					File file = chooser.getSelectedFile();
					Scanner sc = new Scanner(file);
					studentListModel.clear();
					while(sc.hasNextLine()) {
						Student s = new Student(sc.nextLine());
						studentListModel.add(s);
					}
					sc.close();
				}
			} else if(e.getSource() == addStudentButton) {
				String src = (String) JOptionPane.showInputDialog(
	                    this,
	                    "Add student using next format:\n"
	                    + "[id] [surname] [year] [group]",
	                    "Add student",
	                    JOptionPane.PLAIN_MESSAGE,
	                    null,
	                    null,
	                    null);
				Student s = new Student(src);
				studentListModel.add(s);
			}
		} catch(IOException ex) {
			JOptionPane.showMessageDialog(null, "File issue: " + ex.getMessage());
		} catch(NoSuchElementException ex) {
			JOptionPane.showMessageDialog(null, "Incomplete data about student");
		} catch(NullPointerException ex) {
			JOptionPane.showMessageDialog(null, "Empty data about student");
		} catch(NumberFormatException ex) {
			JOptionPane.showMessageDialog(null, "Wrong data format");
		}
	}

}
