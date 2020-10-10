package lab2;

import java.awt.Component;
import java.awt.FlowLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.WindowEvent;
import java.awt.event.WindowListener;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.text.NumberFormat;
import java.text.ParseException;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.StringTokenizer;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

import javax.swing.BoxLayout;
import javax.swing.JButton;
import javax.swing.JComponent;
import javax.swing.JFileChooser;
import javax.swing.JFormattedTextField;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JMenu;
import javax.swing.JMenuBar;
import javax.swing.JMenuItem;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JSpinner;
import javax.swing.JTable;
import javax.swing.JTextField;
import javax.swing.ListSelectionModel;
import javax.swing.WindowConstants;
import javax.swing.table.TableCellRenderer;
import javax.swing.text.NumberFormatter;



public class WarehouseFrame extends JFrame implements WindowListener, ActionListener {
	private  final String DEFAULT_DIRECTORY = "D:\\”Õ»¬≈–\\Sem5_programming\\Lab 2 (04.10.2020)\\examples";
	//WINDOW DIMENSIONS
	private final int DEFAULT_WIDTH = 1080;
	private final int DEFAULT_HEIGHT = 675;
	
	//STRING CONSTANTS: MENU HEADERS
	private final String MENU_NAME = "File";
	private final String OPEN_FILE_MENU_ITEM_NAME = "Open file...";
	private final String SAVE_FILE_MENU_ITEM_NAME = "Save file";
	private final String SAVE_AS_FILE_MENU_ITEM_NAME = "Save file as...";
	//STRING CONSTANTS: TRY TO SAVE DIALOG
	private final String[] TRY_TO_SAVE_DIALOG_OPTIONS = {"Save", "Don't save"};
	private final String TRY_TO_SAVE_DIALOG_MESSAGE = "File you're quitting isn't saved";
	private final String TRY_TO_SAVE_DIALOG_HEADER = "Quitting a File";
	//STRING CONSTANTS: EXCEPTION DIALOG
	private final String FILE_EXCEPTION_DIALOG_HEADER = "File Error";
	private final String PARSE_EXCEPTION_DIALOG_HEADER = "Parse Error";
	//STRING CONSTANTS: ADD PRODUCT_DIALOG
	private final String ADD_PRODUCT_NAME = "Name:";
	private final String ADD_PRODUCT_QUANTITY = "Quantity (positive integer only):";
	private final String ADD_PRODUCT_HEADER = "Add product";
	//STRING CONSTANTS: OTHERS
	private final String APP_HEADER = "Warehouse";
	private final String SEARCH_LABEL_TEXT = "Search:";
	private final String SEARCH_BUTTON_TEXT = "Go!";
	private final String RESET_BUTTON_TEXT = "Reset search";
	private final String ADD_BUTTON_TEXT = "Add product";
	private final String SET_QUANTITY_BUTTON_TEXT = "Set quantity";
	private final String DELETE_BUTTON_TEXT = "Delete";
	private final String ADD_ERROR_HEADER = "Add existing product";
	private final String ADD_ERROR_MESSAGE = "You can't re-add product that already exist. Try set quantity instead.";
	private final String NO_SELECTION_ERROR_HEADER = "Select product";
	private final String NO_SELECTION_ERROR_MESSAGE = "To set quantity of product, select it and then click button.";
	//JMENUBAR COMPONENTS
	private JMenuItem  openFileMenuItem, saveFileMenuItem, saveAsFileMenuItem;
	//MANAGER
	private FileManager manager;
	//PRODUCTS
	private List<Product> products;
	//CONTENT COMPONENTS
	private JLabel searchLabel;
	private JTextField searchField;
	private JTable table;
	private ProductTableModel tableModel;
	private JButton searchButton, resetButton, addButton, setQuantityButton, deleteButton;
	//ADD DIALOG COMPONENTS
	private JTextField nameField;
	private JFormattedTextField quantityField;
	// FORMATTER
	 private NumberFormatter formatter;
	public WarehouseFrame() {
		setTitle(APP_HEADER);
		setDefaultCloseOperation(WindowConstants.DO_NOTHING_ON_CLOSE);
		setSize(DEFAULT_WIDTH, DEFAULT_HEIGHT);
		addWindowListener(this);
		JMenuBar bar = new JMenuBar();
		JMenu menu = new JMenu(MENU_NAME);
		bar.add(menu);
		setJMenuBar(bar);
		openFileMenuItem = new JMenuItem(OPEN_FILE_MENU_ITEM_NAME);
		openFileMenuItem.addActionListener(this);
		menu.add(openFileMenuItem);
		
		saveFileMenuItem = new JMenuItem(SAVE_FILE_MENU_ITEM_NAME);
		saveFileMenuItem.addActionListener(this);
		menu.add(saveFileMenuItem);
		
		saveAsFileMenuItem = new JMenuItem(SAVE_AS_FILE_MENU_ITEM_NAME);
		saveAsFileMenuItem.addActionListener(this);
		menu.add(saveAsFileMenuItem);
		
		JPanel contentPane = new JPanel();
		setContentPane(contentPane);
		contentPane.setLayout(new BoxLayout(contentPane, BoxLayout.PAGE_AXIS));
		 
		JPanel searchPanel = new JPanel();
		contentPane.add(searchPanel);
		searchPanel.setLayout(new FlowLayout(FlowLayout.CENTER));
		
		manager = new FileManager(); 
		products = new ArrayList<Product>();
		searchLabel = new JLabel(SEARCH_LABEL_TEXT);
		searchPanel.add(searchLabel);
		searchField = new JTextField(50);
		searchPanel.add(searchField);
		searchButton = new JButton(SEARCH_BUTTON_TEXT);
		searchButton.addActionListener(this);
		searchPanel.add(searchButton);
		
		resetButton = new JButton(RESET_BUTTON_TEXT);
		resetButton.addActionListener(this);
		searchPanel.add(resetButton);
		
		tableModel = new ProductTableModel(products, manager);
		table = new JTable(tableModel);
		JScrollPane scrollPane = new JScrollPane(table);
		table.setFillsViewportHeight(true);
		table.setSelectionMode(ListSelectionModel.SINGLE_SELECTION);
		contentPane.add(scrollPane);
		
		JPanel managementPanel = new JPanel();
		contentPane.add(managementPanel);
		managementPanel.setLayout(new BoxLayout(managementPanel, BoxLayout.X_AXIS));
		addButton = new JButton(ADD_BUTTON_TEXT);
		addButton.addActionListener(this);
		managementPanel.add(addButton);
		setQuantityButton = new JButton(SET_QUANTITY_BUTTON_TEXT);
		setQuantityButton.addActionListener(this);
		managementPanel.add(setQuantityButton);
		deleteButton = new JButton(DELETE_BUTTON_TEXT);
		deleteButton.addActionListener(this);
		managementPanel.add(deleteButton);
		NumberFormat format = NumberFormat.getInstance();
	    formatter = new NumberFormatter(format);
	    formatter.setValueClass(Integer.class);
	    formatter.setMinimum(1);
	    formatter.setMaximum(Integer.MAX_VALUE);
	    formatter.setAllowsInvalid(false);
	    formatter.setCommitsOnValidEdit(true);
	    
		nameField = new JTextField();
		quantityField = new JFormattedTextField(formatter);
	}
	@Override
	public void actionPerformed(ActionEvent e) {
		try {
			if(e.getSource() == openFileMenuItem) {
				tryToSaveBeforeQuit();
				if(manager.getState() == SaveState.SAVED_OR_SAVE_CAN_BE_IGNORED) {
					JFileChooser chooser = new JFileChooser(DEFAULT_DIRECTORY);
					int result = chooser.showOpenDialog(null);
					if(result == JFileChooser.APPROVE_OPTION) {
						List<Product> temp = manager.open(chooser.getSelectedFile());
						products.clear();
						products.addAll(temp);	
						tableModel.updateQuery(searchField.getText());
					}
				}
			} else if(e.getSource() == saveFileMenuItem) {
				if(!manager.hasCurrentFile()) {
					saveAs();
				} else {
					manager.save(products);
				}
			} else if(e.getSource() == saveAsFileMenuItem) {
				saveAs();
			} else if(e.getSource() == addButton) {
				JComponent[] inputs = new JComponent[] {
				        new JLabel(ADD_PRODUCT_NAME),
				        nameField,
				        new JLabel(ADD_PRODUCT_QUANTITY),
				        quantityField
				};
				int result = JOptionPane.showConfirmDialog(null, inputs, ADD_PRODUCT_HEADER, JOptionPane.PLAIN_MESSAGE);
				if (result == JOptionPane.OK_OPTION) {
					String name = nameField.getText();
					int quantity = (int) formatter.stringToValue(quantityField.getText());
					int index = (int) products.stream().takeWhile(p -> !p.getName().equals(name)).count();
					if(index < products.size()) {
						JOptionPane.showMessageDialog(null,
							    ADD_ERROR_MESSAGE,
							    ADD_ERROR_HEADER,
							    JOptionPane.ERROR_MESSAGE);
					} else {
						products.add(new Product(name, quantity));
						tableModel.updateQuery(searchField.getText());
					    manager.notifyUpdate();
					}
				}
			} else if(e.getSource() == setQuantityButton) {
				if(table.getSelectedRow() != -1) {
					int index = (int) products.stream().takeWhile(p -> !p.getName().equals((String)table.getValueAt(table.getSelectedRow(), 0))).count();
					JComponent[] inputs = new JComponent[] {
					        new JLabel(ADD_PRODUCT_NAME + " " + products.get(index).getName()),
					        new JLabel(ADD_PRODUCT_QUANTITY),
					        quantityField
					};
					quantityField.setText(formatter.valueToString(products.get(index).getQuantity()));
					int result = JOptionPane.showConfirmDialog(null, inputs, ADD_PRODUCT_HEADER, JOptionPane.PLAIN_MESSAGE);
					if (result == JOptionPane.OK_OPTION) {
						products.get(index).setQuantity((int) formatter.stringToValue(quantityField.getText()));
						tableModel.updateQuery(searchField.getText());
					    manager.notifyUpdate();
					}
				} else {
					JOptionPane.showMessageDialog(null,
							NO_SELECTION_ERROR_MESSAGE,
							NO_SELECTION_ERROR_HEADER,
						    JOptionPane.ERROR_MESSAGE);
				}
			} else if(e.getSource() == searchButton) {
				tableModel.updateQuery(searchField.getText());
			} else if(e.getSource() == deleteButton) {
				if(table.getSelectedRow() != -1) {
					int index = (int) products.stream().takeWhile(p -> !p.getName().equals((String)table.getValueAt(table.getSelectedRow(), 0))).count();
					products.remove(index);
					tableModel.updateQuery(searchField.getText());
					manager.notifyUpdate();
				} else {
					JOptionPane.showMessageDialog(null,
							NO_SELECTION_ERROR_MESSAGE,
							NO_SELECTION_ERROR_HEADER,
						    JOptionPane.ERROR_MESSAGE);
				}
			} else if(e.getSource() == resetButton) {
				searchField.setText("");
				tableModel.updateQuery(searchField.getText());
			}
		} catch (NullPointerException | ClassNotFoundException | IOException ex) {
			showExceptionDialog(ex, FILE_EXCEPTION_DIALOG_HEADER);
		} catch (ParseException ex) {
			showExceptionDialog(ex, PARSE_EXCEPTION_DIALOG_HEADER);
		}
	}
	private void tryToSaveBeforeQuit() {
		try {
			if(manager.getState() == SaveState.NOT_SAVED) {
				int optionDialogResult = JOptionPane.showOptionDialog(null,
				TRY_TO_SAVE_DIALOG_MESSAGE,
				TRY_TO_SAVE_DIALOG_HEADER,
				JOptionPane.YES_NO_OPTION,
				JOptionPane.QUESTION_MESSAGE,
				null,     
				TRY_TO_SAVE_DIALOG_OPTIONS,  
				TRY_TO_SAVE_DIALOG_OPTIONS[0]); 
				if(optionDialogResult == JOptionPane.YES_OPTION) {
					if(!manager.hasCurrentFile()) {
						saveAs();
					} else {
						manager.save(products);
					}
				} else {
					manager.ignoreSaving();
				}
			}
		} catch (NullPointerException | IOException ex) {
			showExceptionDialog(ex, FILE_EXCEPTION_DIALOG_HEADER);
		}
	}
	private void showExceptionDialog(Exception ex, String dialogHeader) {
		JOptionPane.showMessageDialog(null,
			    ex.getMessage(),
			    dialogHeader,
			    JOptionPane.ERROR_MESSAGE);
	}
	private void saveAs() throws NullPointerException, FileNotFoundException, IOException {
		JFileChooser chooser = new JFileChooser(DEFAULT_DIRECTORY);
		int result = chooser.showSaveDialog(null);
		if(result == JFileChooser.APPROVE_OPTION) {
			manager.save(chooser.getSelectedFile(), products);
		}
	}
	@Override
	public void windowOpened(WindowEvent e) {}
	@Override
	public void windowClosing(WindowEvent e) {
		tryToSaveBeforeQuit();
		if(manager.getState() == SaveState.SAVED_OR_SAVE_CAN_BE_IGNORED) e.getWindow().dispose();
	}
	@Override
	public void windowClosed(WindowEvent e) {}
	@Override
	public void windowIconified(WindowEvent e) {}
	@Override
	public void windowDeiconified(WindowEvent e) {}
	@Override
	public void windowActivated(WindowEvent e) {}
	@Override
	public void windowDeactivated(WindowEvent e) {}
}
