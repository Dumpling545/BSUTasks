package w13t1;

import java.awt.BorderLayout;
import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.File;
import java.io.IOException;
import java.util.Iterator;
import java.util.NoSuchElementException;
import java.util.Scanner;
import java.util.TreeSet;

import javax.swing.DefaultListModel;
import javax.swing.JButton;
import javax.swing.JFileChooser;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JList;
import javax.swing.JMenu;
import javax.swing.JMenuBar;
import javax.swing.JMenuItem;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JSpinner;
import javax.swing.JTabbedPane;
import javax.swing.ListSelectionModel;
import javax.swing.SpinnerNumberModel;
import javax.swing.border.EmptyBorder;
import javax.swing.event.ChangeEvent;
import javax.swing.event.ChangeListener;
import javax.xml.parsers.ParserConfigurationException;

import org.xml.sax.SAXException;

public class StudentListFrame extends JFrame implements ActionListener, ChangeListener {

	private JPanel contentPane;
	private JTabbedPane tabbedPane;
	
	private TreeSet<Student> studentTreeSet;
	private StudentComparator studentComparator;
	
	private JList<String> initialStudentList;
	private JList<String> yearStudentList;
	private DefaultListModel<String> initialStudentListModel;
	private DefaultListModel<String> yearStudentListModel;
	
	private JScrollPane initialStudentListScrollPane;
	private JScrollPane yearStudentListScrollPane;
	
	private JPanel yearStudentListContentPanel;
	
	private JSpinner yearFilterSpinner;
	private SpinnerNumberModel yearFilterSpinnerNumberModel;
	private JPanel yearFilterSpinnerPanel;
	private JLabel yearFilterSpinnerLabel;
	
	private JMenuBar menuBar;
	private JMenu fileMenu;
	private JMenuItem openFileMenuItem;
	private JMenuItem openXmlMenuItem;
	private JMenuItem saveXmlMenuItem;
	
	private JButton addStudentButton;
	
	private XmlManager xmlManager;
	
	private final String CURRENT_DIRECTORY = "D:/”Õ»¬≈–/Sem3_programming/Week_13";
	
	private final int START_YEAR = 1;
	private final int YEAR_STEP = 1;
	
	private final int REFRESH_BOTH_LISTS = 0;
	private final int REFRESH_YEAR_LIST = 0;

	public static void main(String[] args) {
		StudentListFrame frame = new StudentListFrame();
		frame.setVisible(true);
	}

	public StudentListFrame() {
		xmlManager = new XmlManager();
		
		studentComparator = new StudentComparator();
		studentTreeSet = new TreeSet<Student>(studentComparator);
		
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		setBounds(100, 100, 450, 300);
		contentPane = new JPanel();
		contentPane.setBorder(new EmptyBorder(5, 5, 5, 5));
		contentPane.setLayout(new BorderLayout(0, 0));
		
		tabbedPane = new JTabbedPane();
		initialStudentListModel = new DefaultListModel<String>();
		initialStudentList = new JList<String>(initialStudentListModel);
		initialStudentList.setSelectionMode(ListSelectionModel.SINGLE_SELECTION);
		initialStudentList.setLayoutOrientation(JList.VERTICAL);
		initialStudentListScrollPane = new JScrollPane(initialStudentList);
		tabbedPane.add(initialStudentListScrollPane, "Initial data");
		contentPane.add(tabbedPane, BorderLayout.CENTER);
		
		yearStudentListContentPanel = new JPanel();
		yearStudentListContentPanel.setLayout(new BorderLayout(0, 0));
		yearStudentListModel = new DefaultListModel<String>();
		yearStudentList = new JList<String>(yearStudentListModel);
		yearStudentList.setSelectionMode(ListSelectionModel.SINGLE_SELECTION);
		yearStudentList.setLayoutOrientation(JList.VERTICAL);
		yearStudentListScrollPane = new JScrollPane(yearStudentList);
		yearStudentListContentPanel.add(yearStudentListScrollPane, BorderLayout.CENTER);
		tabbedPane.add(yearStudentListContentPanel, "Data by year");
		
		menuBar = new JMenuBar();
		fileMenu = new JMenu("File");
		openFileMenuItem = new JMenuItem("Open...");
		openXmlMenuItem = new JMenuItem("Open XML...");
		saveXmlMenuItem = new JMenuItem("Save as XML...");
		openFileMenuItem.addActionListener(this);
		openXmlMenuItem.addActionListener(this);
		saveXmlMenuItem.addActionListener(this);
		fileMenu.add(openFileMenuItem);
		fileMenu.add(openXmlMenuItem);
		fileMenu.add(saveXmlMenuItem);
		menuBar.add(fileMenu);
		setJMenuBar(menuBar);
		
		yearFilterSpinnerPanel = new JPanel();
		yearFilterSpinnerLabel = new JLabel("Year: ");
		yearFilterSpinnerPanel.setLayout(new GridLayout(1, 2));
		yearFilterSpinnerNumberModel = new SpinnerNumberModel(START_YEAR,
															  Student.MINIMAL_YEAR,
															  Student.MAXIMAL_YEAR,
															  YEAR_STEP);
		yearFilterSpinner = new JSpinner(yearFilterSpinnerNumberModel);
		yearFilterSpinner.setEditor(new JSpinner.DefaultEditor(yearFilterSpinner));
		yearFilterSpinner.addChangeListener(this);
		yearFilterSpinnerPanel.add(yearFilterSpinnerLabel);
		yearFilterSpinnerPanel.add(yearFilterSpinner);
		yearStudentListContentPanel.add(yearFilterSpinnerPanel, BorderLayout.NORTH);
		
		addStudentButton = new JButton("Add Student...");
		addStudentButton.addActionListener(this);
		contentPane.add(addStudentButton, BorderLayout.SOUTH);
		setContentPane(contentPane);
	}

	private void refreshListModels(int refreshPolicy) {
		if(refreshPolicy == REFRESH_BOTH_LISTS) {
			initialStudentListModel.clear();
		}
		yearStudentListModel.clear();
		Iterator<Student> studentIterator = studentTreeSet.iterator();
		while(studentIterator.hasNext()) {
			Student s = studentIterator.next();
			if(refreshPolicy == REFRESH_BOTH_LISTS) {
				initialStudentListModel.addElement(s.toString());
			}
			if((int)yearFilterSpinner.getValue() ==  s.getYear()) {
				yearStudentListModel.addElement(s.toString());
			}
		}
	}
	@Override
	public void actionPerformed(ActionEvent e) {
		try {
			if(e.getSource() == openFileMenuItem) {
				JFileChooser chooser = new JFileChooser();
				chooser.setCurrentDirectory(new File(CURRENT_DIRECTORY));
				if(chooser.showOpenDialog(null) == JFileChooser.APPROVE_OPTION) {
					File file = chooser.getSelectedFile();
					studentTreeSet.clear();
					Scanner sc = new Scanner(file);
					while(sc.hasNextLine()) {
						Student student = new Student(sc.nextLine());
						studentTreeSet.add(student);
					}
					sc.close();
					refreshListModels(REFRESH_BOTH_LISTS);
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
				if(src != null) {
					Student s = new Student(src);
					studentTreeSet.add(s);
					refreshListModels(REFRESH_BOTH_LISTS);
				}
			}else if(e.getSource() == openXmlMenuItem) {
				JFileChooser chooser = new JFileChooser();
				chooser.setCurrentDirectory(new File(CURRENT_DIRECTORY));
				if(chooser.showOpenDialog(null) == JFileChooser.APPROVE_OPTION) {
					File file = chooser.getSelectedFile();
					studentTreeSet = xmlManager.read(file);
					refreshListModels(REFRESH_BOTH_LISTS);
				}
			} else if(e.getSource() == saveXmlMenuItem) {
				JFileChooser chooser = new JFileChooser();
				chooser.setCurrentDirectory(new File(CURRENT_DIRECTORY));
				if(chooser.showSaveDialog(null) == JFileChooser.APPROVE_OPTION) {
					File file = chooser.getSelectedFile();
					xmlManager.write(file, studentTreeSet.iterator());
				}
			}
		} catch(IOException ex) {
			JOptionPane.showMessageDialog(null, "File issue: " + ex.getMessage());
		} catch(NoSuchElementException ex) {
			JOptionPane.showMessageDialog(null, "Empty or incomplete data about student");
		} catch(NullPointerException ex) {
			JOptionPane.showMessageDialog(null, ex.getMessage());
		} catch(NumberFormatException ex) {
			JOptionPane.showMessageDialog(null, "Wrong data format");
		} catch (ParserConfigurationException | SAXException ex) {
			JOptionPane.showMessageDialog(null, "XML File issue: " + ex.getMessage());
		} catch(AlreadyInCollectionException ex) {
			JOptionPane.showMessageDialog(null, ex.getMessage());
		} catch (Exception ex) {
			JOptionPane.showMessageDialog(null, "Unsupported exception: " + ex.getMessage());
		}
	}

	@Override
	public void stateChanged(ChangeEvent e) {
		refreshListModels(REFRESH_YEAR_LIST);
	}

}
