package tp12;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;
import java.io.File;
import java.io.IOException;
import java.util.NoSuchElementException;
import java.util.Scanner;
import java.util.TreeSet;

import javax.swing.DefaultListModel;
import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JComboBox;
import javax.swing.JComponent;
import javax.swing.JFileChooser;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JList;
import javax.swing.JMenu;
import javax.swing.JMenuBar;
import javax.swing.JMenuItem;
import javax.swing.JOptionPane;
import javax.swing.JScrollPane;
import javax.swing.JTextField;
import javax.swing.JTree;
import javax.swing.JWindow;
import javax.swing.SwingConstants;
import javax.swing.tree.DefaultTreeModel;
import javax.swing.tree.TreePath;
import javax.swing.tree.TreeSelectionModel;
import javax.xml.parsers.ParserConfigurationException;
import javax.xml.parsers.SAXParserFactory;

import org.xml.sax.SAXException;

import javax.xml.parsers.SAXParser;



public class EmployeeTreeFrame extends JFrame implements ActionListener{
		
	private JTree employeeTree;
	
	private JScrollPane initialEmployeeTreeScrollPane;
	
	private JMenuBar menuBar;
	private JMenu xmlMenu;
	private JMenuItem checkXmlSchemeMenuItem;
	private JMenuItem xmlInfolMenuItem;
	private JMenuItem openXmlMenuItem;
	private JMenuItem saveXmlMenuItem;	
	private JMenuItem saveAsXmlMenuItem;
	private JMenu binaryMenu;
	private JMenuItem openBinaryMenuItem;
	private JMenuItem saveBinaryMenuItem;	
	private JMenuItem saveAsBinaryMenuItem;
	private JMenu employeeMenu;
	private JMenuItem addSubordinateMenuItem;
	private JMenuItem removeEmployeeMenuItem;	
	private JMenuItem employeeInfoMenuItem;
	private DataIOManager xmlManager, binaryManager;
	private XmlValidator xmlValidator;
	
	private JTextField fullNameTextField;
	private JComboBox<Sex> sexComboBox;
	private JTextField ageTextField;
	private JComboBox<Boolean> unfireableComboBox;
	private JTextField positionTextField;
	private JComboBox<EmploymentForm> employmentFormComboBox;
	private JTextField salaryTextField;
	private JLabel directSupervisorLabel;
	private JComponent[] inputs;
	
	private final String CURRENT_DIRECTORY = "D:\\”Õ»¬≈–\\Sem4_TrainingPractice\\tp12";
	public EmployeeTreeFrame() {
		super("Employee Tree");
		xmlManager = new XmlManager();
		binaryManager = new BinaryManager();
		try {
			xmlValidator = new XmlValidator();
		} catch(SAXException ex) {
			JOptionPane.showMessageDialog(null, "XML Schema issue: " + ex.getMessage());
		}
		setSize(700, 500);
		//starter
		JWindow window = new JWindow();
       window.getContentPane().add(
                new JLabel("", new ImageIcon(getClass().getResource("/images/startImage.jpg")), SwingConstants.CENTER));
        window.setBounds(getBounds());
        window.setVisible(true);
        try {
            Thread.sleep(5000);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
        window.setVisible(false);
        
		menuBar = new JMenuBar();
		xmlMenu = new JMenu("XML");
		checkXmlSchemeMenuItem = new JMenuItem("Check with XML scheme");
		xmlInfolMenuItem = new JMenuItem("XML Info");
		openXmlMenuItem = new JMenuItem("Open XML ...");
		saveXmlMenuItem = new JMenuItem("Save XML");
		saveAsXmlMenuItem = new JMenuItem("Save XML as ...");
		checkXmlSchemeMenuItem.addActionListener(this);
		openXmlMenuItem.addActionListener(this);
		saveXmlMenuItem.addActionListener(this);
		saveAsXmlMenuItem.addActionListener(this);
		xmlInfolMenuItem.addActionListener(this);
		xmlMenu.add(checkXmlSchemeMenuItem);
		xmlMenu.add(xmlInfolMenuItem);
		xmlMenu.add(openXmlMenuItem);
		xmlMenu.add(saveXmlMenuItem);
		xmlMenu.add(saveAsXmlMenuItem);
		menuBar.add(xmlMenu);
		
		binaryMenu = new JMenu("Binary");
		openBinaryMenuItem = new JMenuItem("Open Binary ...");
		saveBinaryMenuItem = new JMenuItem("Save Binary");
		saveAsBinaryMenuItem = new JMenuItem("Save Binary as ...");
		openBinaryMenuItem.addActionListener(this);
		saveBinaryMenuItem.addActionListener(this);
		saveAsBinaryMenuItem.addActionListener(this);
		binaryMenu.add(openBinaryMenuItem);
		binaryMenu.add(saveBinaryMenuItem);
		binaryMenu.add(saveAsBinaryMenuItem);
		menuBar.add(binaryMenu);
		
		employeeMenu = new JMenu("Employee");
		addSubordinateMenuItem = new JMenuItem("Add subordinate");
		removeEmployeeMenuItem = new JMenuItem("Remove employee");
		employeeInfoMenuItem = new JMenuItem("Employee Info");
		addSubordinateMenuItem.addActionListener(this);
		removeEmployeeMenuItem.addActionListener(this);
		employeeInfoMenuItem.addActionListener(this);
		employeeMenu.add(addSubordinateMenuItem);
		employeeMenu.add(removeEmployeeMenuItem);
		employeeMenu.add(employeeInfoMenuItem);
		menuBar.add(employeeMenu);
		setJMenuBar(menuBar);
		
		fullNameTextField = new JTextField();
		sexComboBox = new JComboBox<Sex>(Sex.values());
		ageTextField = new JTextField();
		unfireableComboBox = new JComboBox<Boolean>(new Boolean [] {true, false});
		positionTextField = new JTextField();
		employmentFormComboBox = new JComboBox<EmploymentForm>(EmploymentForm.values());
		salaryTextField = new JTextField();
		directSupervisorLabel = new JLabel();
		inputs = new JComponent[] {
		        new JLabel("Full Name: "),
		        fullNameTextField,
		        new JLabel("Sex: "),
		        sexComboBox,
		        new JLabel("Age: "),
		        ageTextField,
		        new JLabel("Is unfireable: "),
		        unfireableComboBox,
		        new JLabel("Position: "),
		        positionTextField,
		        new JLabel("Employment form: "),
		        employmentFormComboBox,
		        new JLabel("Salary: "),
		        salaryTextField,
		        new JLabel("Direct supervisor: "),
		        directSupervisorLabel
		};
		
		employeeTree = new JTree();
		employeeTree.setModel(null);
		employeeTree.updateUI();
		employeeTree.getSelectionModel().setSelectionMode(TreeSelectionModel.SINGLE_TREE_SELECTION);
		employeeTree.setCellRenderer(new EmployeeTreeCellRenderer());
		employeeTree.setFocusable(true);
		employeeTree.requestFocus();
		initialEmployeeTreeScrollPane = new JScrollPane(employeeTree);		
		setContentPane(initialEmployeeTreeScrollPane);
	}
	public static void main(String[] args) {
		JFrame frame = new EmployeeTreeFrame();
		frame.setVisible(true);
	}
	@Override
	public void actionPerformed(ActionEvent e) {
		try {
			if(e.getSource() == xmlInfolMenuItem) {
				JFileChooser chooser = new JFileChooser();
				chooser.setCurrentDirectory(new File(CURRENT_DIRECTORY));
				if(chooser.showOpenDialog(null) == JFileChooser.APPROVE_OPTION) {
					File file = chooser.getSelectedFile();
					SAXParserFactory factory = SAXParserFactory.newInstance();
                    SAXParser parser = factory.newSAXParser();
                    XmlInfromationExtractor handler = new XmlInfromationExtractor();
                    parser.parse(chooser.getSelectedFile(), handler);
                    StringBuilder sb = new StringBuilder("Minimal salary: " );
                    sb.append(handler.getMinSalary());
                    sb.append("$");
					sb.append('\n');
					sb.append("Maximal salary: ");
					sb.append(handler.getMaxSalary());
					sb.append("$");
					sb.append('\n');
					sb.append("Average salary: ");
					sb.append(handler.getAvgSalary());
					sb.append("$");
					sb.append('\n');
					sb.append("Minimal age: ");
					sb.append(handler.getMinAge());
					sb.append('\n');
					sb.append("Maximal age: ");
					sb.append(handler.getMaxAge());
					sb.append('\n');
					sb.append("Average age: ");
					sb.append(handler.getAvgAge());
					sb.append('\n');
					sb.append("Number of employees: ");
					sb.append(handler.getNumberOfEmployees());
					JOptionPane.showMessageDialog(null, sb.toString(), "Company Info",JOptionPane.INFORMATION_MESSAGE);
				}
			}else if(e.getSource() == checkXmlSchemeMenuItem) {
				JFileChooser chooser = new JFileChooser();
				chooser.setCurrentDirectory(new File(CURRENT_DIRECTORY));
				if(chooser.showOpenDialog(null) == JFileChooser.APPROVE_OPTION) {
					if(xmlValidator != null) {
						String validateMessage = xmlValidator.validate(chooser.getSelectedFile());
						JOptionPane.showMessageDialog(null, validateMessage);
					} else {
						JOptionPane.showMessageDialog(null, "Xml Validator is not initialised!");
					}
				}
			} else if(e.getSource() == openXmlMenuItem) {
				JFileChooser chooser = new JFileChooser();
				chooser.setCurrentDirectory(new File(CURRENT_DIRECTORY));
				if(chooser.showOpenDialog(null) == JFileChooser.APPROVE_OPTION) {
					File file = chooser.getSelectedFile();
					xmlManager.setFile(file);
					binaryManager.setFile(null);
					employeeTree.setModel(new EmployeeTreeModel(xmlManager));
					employeeTree.updateUI();
				}
			}  else if(e.getSource() == openBinaryMenuItem) {
				JFileChooser chooser = new JFileChooser();
				chooser.setCurrentDirectory(new File(CURRENT_DIRECTORY));
				if(chooser.showOpenDialog(null) == JFileChooser.APPROVE_OPTION) {
					File file = chooser.getSelectedFile();
					binaryManager.setFile(file);
					xmlManager.setFile(null);
					employeeTree.setModel(new EmployeeTreeModel(binaryManager));
					employeeTree.updateUI();
				}
			} else if(e.getSource() == saveAsXmlMenuItem) {
				if(employeeTree.getModel() != null) {
					JFileChooser chooser = new JFileChooser();
					chooser.setCurrentDirectory(new File(CURRENT_DIRECTORY));
					if(chooser.showSaveDialog(null) == JFileChooser.APPROVE_OPTION) {
						File file = chooser.getSelectedFile();
						xmlManager.setFile(file);
						binaryManager.setFile(null);
						xmlManager.save((Employee)employeeTree.getModel().getRoot());
					}
				} else {
					JOptionPane.showMessageDialog(null, "Action is not allowed if no file opened");
				}
			} else if(e.getSource() == saveAsBinaryMenuItem) {
				if(employeeTree.getModel() != null) {
					JFileChooser chooser = new JFileChooser();
					chooser.setCurrentDirectory(new File(CURRENT_DIRECTORY));
					if(chooser.showSaveDialog(null) == JFileChooser.APPROVE_OPTION) {
						File file = chooser.getSelectedFile();
						binaryManager.setFile(file);
						xmlManager.setFile(null);
						binaryManager.save((Employee)employeeTree.getModel().getRoot());
					}
				} else {
					JOptionPane.showMessageDialog(null, "Action is not allowed if no file opened");
				}
			} else if(e.getSource() == saveXmlMenuItem) {
				if(xmlManager.getFile() != null) xmlManager.save((Employee)employeeTree.getModel().getRoot());
				else JOptionPane.showMessageDialog(null, "Opened file is not XML");
			} else if(e.getSource() == saveBinaryMenuItem) {
				if(binaryManager.getFile() != null) xmlManager.save((Employee)employeeTree.getModel().getRoot());
				else JOptionPane.showMessageDialog(null, "Opened file is not Binary");
			}  else if(employeeTree.getModel() != null) {
				if(employeeTree.getSelectionPath() != null) {
					if(e.getSource() == addSubordinateMenuItem) {
						Employee supervisor = (Employee) employeeTree.getSelectionPath().getLastPathComponent();
						directSupervisorLabel.setText(supervisor.getFullName());
						int result = JOptionPane.showConfirmDialog(null, inputs, "Hiring", JOptionPane.PLAIN_MESSAGE);
						if (result == JOptionPane.OK_OPTION) {
							Employee employee = new Employee();
							employee.setFullName(fullNameTextField.getText());
							employee.setSex((Sex) sexComboBox.getSelectedItem());
							employee.setAge(Integer.parseInt(ageTextField.getText()));
							employee.setUnfireable((Boolean)unfireableComboBox.getSelectedItem());
							employee.setPosition(positionTextField.getText());
							employee.setEmploymentForm((EmploymentForm)employmentFormComboBox.getSelectedItem());
							employee.setSalary(Integer.parseInt(salaryTextField.getText()));
							supervisor.addSubordinate(employee);
							employeeTree.updateUI();
							fullNameTextField.setText("");
							ageTextField.setText("");
							positionTextField.setText("");
							salaryTextField.setText("");
						} else {
							JOptionPane.showMessageDialog(null, "New employee is NOT added");
						}
					} else if(e.getSource() == removeEmployeeMenuItem) {
						TreePath treePath = employeeTree.getSelectionPath();
						int count = treePath.getPathCount();
						if(count >= 2) {
							Employee employee = (Employee) treePath.getPathComponent(count - 2);
							Employee fired = (Employee)treePath.getLastPathComponent();
							if(fired.isUnfireable()) {
								JOptionPane.showMessageDialog(null, "This employee is unfireable");
							} else {
								employee.removeSubordinate(fired);
							}
							employeeTree.setSelectionPath(null);
							employeeTree.updateUI();
						} else {
							JOptionPane.showMessageDialog(null, "Firing director is not an option");
						}
					} else if(e.getSource() == employeeInfoMenuItem) {
						Employee employee = (Employee)employeeTree.getSelectionPath().getLastPathComponent();
						StringBuilder sb = new StringBuilder(employee.getFullName());
						sb.append('\n');
						sb.append("Sex: ");
						sb.append(employee.getSex());
						sb.append('\n');
						sb.append("Age: ");
						sb.append(employee.getAge());
						sb.append('\n');
						sb.append("Is unfireable: ");
						if(employee.isUnfireable()) sb.append("Yes");
						else sb.append("No");
						sb.append('\n');
						sb.append("Position: ");
						sb.append(employee.getPosition());
						sb.append('\n');
						sb.append("Employment form: ");
						sb.append(employee.getEmploymentForm());
						sb.append('\n');
						sb.append("Salary: ");
						sb.append(employee.getSalary());
						sb.append('$');
						JOptionPane.showMessageDialog(null, sb.toString());
					}
				} else {
					JOptionPane.showMessageDialog(null, "Action is not allowed if no employee selected");
				}
			} else JOptionPane.showMessageDialog(null, "Action is not allowed if no file opened");
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
		} catch (Exception ex) {
			JOptionPane.showMessageDialog(null, "Unsupported exception: " + ex.getMessage());
		}
	}
}
