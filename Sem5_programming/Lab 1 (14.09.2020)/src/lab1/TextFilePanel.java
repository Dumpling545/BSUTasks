package lab1;

import java.awt.Dimension;
import java.awt.LayoutManager;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.PrintWriter;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.stream.Stream;

import javax.swing.BoxLayout;
import javax.swing.JButton;
import javax.swing.JFileChooser;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTable;
import javax.swing.JTextArea;
import javax.swing.JTextField;
import javax.swing.event.DocumentEvent;
import javax.swing.event.DocumentListener;
import javax.swing.filechooser.FileNameExtensionFilter;
import javax.swing.table.DefaultTableModel;

public class TextFilePanel extends JPanel implements DocumentListener {
	private  String header;
	private final String DEFAULT_DIRECTORY = "D:\\”Õ»¬≈–\\Sem5_programming\\Lab 1 (14.09.2020)\\testcases";
	private File textFile;
	private boolean isSavedAtLeastOnce = false;
	private boolean isSavedAfterEditing = false;
	private String pattern ="^[\\s\\S]*$";
	
	private JTextArea textArea;
	private JLabel fileNameLabel;
	public TextFilePanel(String header, String pattern) {
		this.header = header;
		if(pattern != null) this.pattern = pattern;
		setLayout(new BoxLayout(this, BoxLayout.Y_AXIS));
		fileNameLabel = new JLabel();
		add(fileNameLabel);
		afterEdit();
		textArea = new JTextArea();
		textArea.getDocument().addDocumentListener(this);
		JScrollPane scroll = new JScrollPane (textArea, 
				   JScrollPane.VERTICAL_SCROLLBAR_ALWAYS, JScrollPane.HORIZONTAL_SCROLLBAR_ALWAYS);
		add(scroll);
	}
	public boolean remindToSave() {
		boolean res = true;
		if(!(isSavedAtLeastOnce && isSavedAfterEditing)) {
			Object[] options = {"Save",
            "Don't save"};
			int result = JOptionPane.showOptionDialog(null,
			"If you don't save file '"+ ((textFile == null) ? "<non-saved file>": textFile.getName()) +"', all progress will be lost.",
			"Saving a "+header+" File",
			JOptionPane.YES_NO_OPTION,
			JOptionPane.QUESTION_MESSAGE,
			null,     
			options,  
			options[0]); 
			if(result == JOptionPane.YES_OPTION) {
				res = saveFile();
			}
		} 
		return res;
	}
	public void openFile() {
		if(remindToSave()) {
			JFileChooser chooser = new JFileChooser(DEFAULT_DIRECTORY);
			FileNameExtensionFilter filter = new FileNameExtensionFilter("TEXT FILES", "txt", "text");
			chooser.setFileFilter(filter);
			int result = chooser.showOpenDialog(null);
			if(result == JFileChooser.APPROVE_OPTION) {
				String content = ""; 
		        try
		        {
		            content = new String (Files.readAllBytes(Paths.get(chooser.getSelectedFile().getPath())));
		        } 
		        catch (IOException e) 
		        {
		        	JOptionPane.showMessageDialog(null,
						    e.getMessage(),
						    "File error",
						    JOptionPane.ERROR_MESSAGE);
		        }
		        boolean shouldFileBeOpened = true;
		        if(!content.matches(pattern)) {
		        	Object[] options = {"Open anyway",
		            "Don't open"};
					int optionDialogResult = JOptionPane.showOptionDialog(null,
					"File you trying to open have wrong format",
					"Opening a "+header+" File",
					JOptionPane.YES_NO_OPTION,
					JOptionPane.QUESTION_MESSAGE,
					null,     
					options,  
					options[0]); 
					shouldFileBeOpened = optionDialogResult == JOptionPane.YES_OPTION;
		        }
		        if(shouldFileBeOpened) {
					textFile = chooser.getSelectedFile();
					textArea.setText(content);
					afterSaveOrOpen();
				}
			}
		}
	}
	private boolean writeStringToFile(File file) throws FileNotFoundException {
		boolean shouldFileBeSaved = false;
		try (PrintWriter out = new PrintWriter(file)) {
			shouldFileBeSaved = true;
	        if(!textArea.getText().matches(pattern)) {
	        	Object[] options = {"Save anyway",
	            "Don't save"};
				int optionDialogResult = JOptionPane.showOptionDialog(null,
				"File you trying to save have wrong format",
				"Saving a "+header+" File",
				JOptionPane.YES_NO_OPTION,
				JOptionPane.QUESTION_MESSAGE,
				null,     
				options,  
				options[0]); 
				shouldFileBeSaved = (optionDialogResult == JOptionPane.YES_OPTION);
	        }
	        if(shouldFileBeSaved) {
	        	 out.print(textArea.getText());
			}
		}
		return shouldFileBeSaved;
	}
	public boolean saveFile() {
		boolean result = false;
		if(!isSavedAtLeastOnce) {
			result = saveFileAs();
		} else {
			try {
				 result = writeStringToFile(textFile);
				if(result) afterSaveOrOpen();
			} catch (FileNotFoundException e) {
				JOptionPane.showMessageDialog(null,
					    e.getMessage(),
					    "File error",
					    JOptionPane.ERROR_MESSAGE);
			}
		}
		return result;
	}
	public boolean saveFileAs() {
		boolean res = false;
		JFileChooser chooser = new JFileChooser(DEFAULT_DIRECTORY);
		FileNameExtensionFilter filter = new FileNameExtensionFilter("TEXT FILES", "txt", "text");
		chooser.setFileFilter(filter);
		int result = chooser.showSaveDialog(null);
		if(result == JFileChooser.APPROVE_OPTION) {
			try {
				res = writeStringToFile(chooser.getSelectedFile());
				if(res) {
					textFile = chooser.getSelectedFile();
					afterSaveOrOpen();
				}
			} catch (FileNotFoundException e) {
				JOptionPane.showMessageDialog(null,
					    e.getMessage(),
					    "File error",
					    JOptionPane.ERROR_MESSAGE);
			}			
		}
		return res;
	}
	private void afterSaveOrOpen() {
		fileNameLabel.setText(header + ": " + textFile.getName()); 
		isSavedAtLeastOnce = true;
		isSavedAfterEditing = true;
	}
	private void afterEdit() {
		fileNameLabel.setText(header + ": *" + ((textFile == null) ? "<non-saved file>": textFile.getName())); 
		isSavedAfterEditing = false;
	}
	public String getText() {
		return textArea.getText();
	}
	public void setText(String str) {
		textArea.setText(str);
	}
	@Override
	public void insertUpdate(DocumentEvent e) {
		afterEdit();
	}
	@Override
	public void removeUpdate(DocumentEvent e) {
		afterEdit();	
	}
	@Override
	public void changedUpdate(DocumentEvent e) {}
}