package lab1;

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Component;
import java.awt.Graphics;
import java.awt.Insets;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.WindowEvent;
import java.awt.event.WindowListener;
import java.util.HashMap;
import java.util.Map;
import java.util.StringTokenizer;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

import javax.swing.BorderFactory;
import javax.swing.BoxLayout;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JMenu;
import javax.swing.JMenuBar;
import javax.swing.JMenuItem;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.WindowConstants;

public class ReplacerFrame extends JFrame implements ActionListener, WindowListener{
	//WINDOW DIMENSIONS
	private final int DEFAULT_WIDTH = 1080;
	private final int DEFAULT_HEIGHT = 675;
	//PATTERNS
	private final String REPLACE_RULE_PATTERN = "^((\\b\\w+)>(\\w+)[\\n](?![\\s\\S]*\\b\\2>))*$";
	private final String WORD_PATTERN = "\\b\\w+\\b";
	//MAIN HEADERS
	private final String APP_HEADER = "Replacer";
	private final String REPLACE_RULE_HEADER = "Replace Rule";
	private final String TEXT_HEADER = "Text";
	
	private final String DISCLAIMER = "<html>WORD is a non-empty sequence of alphanumeric symbols "
			+ "bounded by non-alphanumeric symbols and/or beginning/end of document.<br/>"
			+ "RULE is a set of subrules, "
			+ "where each subrule replaces any WORD with ONE WORD.<br/>"
			+ "Two or more subrules can't replace the same word. "
			+ "Subrules in text file is divided by newline symbol(\\n). <br/>"
			+ "There must be newline symbol after last subrule. "
			+ "Subrule format in text file looks like the following way: <br/>wordToReplace>replacement</html>";
	//MENU HEADERS
	private final String MENU_NAME = "File";
	
	private final String OPEN_REPLACE_RULE_MENU_ITEM_NAME = "Open replace rule...";
	private final String SAVE_REPLACE_RULE_MENU_ITEM_NAME = "Save replace rule";
	private final String SAVE_AS_REPLACE_RULE_MENU_ITEM_NAME = "Save replace rule as...";
	
	private final String OPEN_TEXT_MENU_ITEM_NAME = "Open text...";
	private final String SAVE_TEXT_MENU_ITEM_NAME = "Save text";
	private final String SAVE_AS_TEXT_MENU_ITEM_NAME = "Save text as...";
	
	private final String REPLACE_MENU_ITEM_NAME = "Replace";
	
	//JMENUBAR COMPONENTS
	private JMenuItem  openReplaceRuleMenuItem, saveReplaceRuleMenuItem, saveAsReplaceRuleMenuItem;
	private JMenuItem  openTextMenuItem, saveTextMenuItem, saveAsTextMenuItem;
	private JMenuItem replaceMenuItem;
	//JCOMPONENTS
	private TextFilePanel replaceRulePanel, textPanel;
	//MAP
	private Map<String, String> map;
	public ReplacerFrame() {
		setTitle(APP_HEADER);
		setDefaultCloseOperation(WindowConstants.DO_NOTHING_ON_CLOSE);
		setSize(DEFAULT_WIDTH, DEFAULT_HEIGHT);
		map = new HashMap<String, String>();
		addWindowListener(this);
		JMenuBar bar = new JMenuBar();
		JMenu menu = new JMenu(MENU_NAME);
		bar.add(menu);
		setJMenuBar(bar);
		openReplaceRuleMenuItem = new JMenuItem(OPEN_REPLACE_RULE_MENU_ITEM_NAME);
		openReplaceRuleMenuItem.addActionListener(this);
		menu.add(openReplaceRuleMenuItem);
		
		saveReplaceRuleMenuItem = new JMenuItem(SAVE_REPLACE_RULE_MENU_ITEM_NAME);
		saveReplaceRuleMenuItem.addActionListener(this);
		menu.add(saveReplaceRuleMenuItem);
		
		saveAsReplaceRuleMenuItem = new JMenuItem(SAVE_AS_REPLACE_RULE_MENU_ITEM_NAME);
		saveAsReplaceRuleMenuItem.addActionListener(this);
		menu.add(saveAsReplaceRuleMenuItem);
		
		menu.addSeparator();
		
		openTextMenuItem = new JMenuItem(OPEN_TEXT_MENU_ITEM_NAME);
		openTextMenuItem.addActionListener(this);
		menu.add(openTextMenuItem);
		
		saveTextMenuItem = new JMenuItem(SAVE_TEXT_MENU_ITEM_NAME);
		saveTextMenuItem.addActionListener(this);
		menu.add(saveTextMenuItem);
		
		saveAsTextMenuItem = new JMenuItem(SAVE_AS_TEXT_MENU_ITEM_NAME);
		saveAsTextMenuItem.addActionListener(this);
		menu.add(saveAsTextMenuItem);
		
		menu.addSeparator();
		
		replaceMenuItem = new JMenuItem(REPLACE_MENU_ITEM_NAME);
		replaceMenuItem.addActionListener(this);
		menu.add(replaceMenuItem);
		
		JPanel contentPane = new JPanel();
		setContentPane(contentPane);
		contentPane.setLayout(new BoxLayout(contentPane, BoxLayout.PAGE_AXIS));
		
		JLabel disclaimerLabel = new JLabel(DISCLAIMER); 
		disclaimerLabel.setAlignmentX(Component.CENTER_ALIGNMENT);
		disclaimerLabel.setHorizontalAlignment(JLabel.CENTER);
		contentPane.add(disclaimerLabel);
		JPanel panel = new JPanel();
		contentPane.add(panel);
		panel.setLayout(new BoxLayout(panel, BoxLayout.X_AXIS));
		
		replaceRulePanel = new TextFilePanel(REPLACE_RULE_HEADER, REPLACE_RULE_PATTERN);
		panel.add(replaceRulePanel);
		
		textPanel = new TextFilePanel(TEXT_HEADER, null);
		panel.add(textPanel);
	}
	@Override
	public void actionPerformed(ActionEvent e) {
		if(e.getSource() == openReplaceRuleMenuItem) {
			replaceRulePanel.openFile();
		} else if(e.getSource() == saveReplaceRuleMenuItem) {
			replaceRulePanel.saveFile();
		} else if(e.getSource() == saveAsReplaceRuleMenuItem) {
			replaceRulePanel.saveFileAs();
		} else if(e.getSource() == openTextMenuItem) {
			textPanel.openFile();
		} else if(e.getSource() == saveTextMenuItem) {
			textPanel.saveFile();
		} else if(e.getSource() == saveAsTextMenuItem) {
			textPanel.saveFileAs();
		} else if(e.getSource() == replaceMenuItem) {
			if(replaceRulePanel.getText().matches(REPLACE_RULE_PATTERN)) {
				map.clear();
				StringTokenizer st = new StringTokenizer(replaceRulePanel.getText(),">\n");
				while(st.hasMoreTokens()) {
					map.put(st.nextToken(), st.nextToken());
				}
				Pattern wordPattern = Pattern.compile(WORD_PATTERN);
				Matcher matcher = wordPattern.matcher(textPanel.getText());
				String result = matcher.replaceAll(match -> (map.containsKey(match.group()) ? map.get(match.group()) : match.group()));
				textPanel.setText(result);
			} else {
				JOptionPane.showMessageDialog(null,
					   "Replace rule have wrong format. Replacement is impossible.",
					    "Replace rule error",
					    JOptionPane.ERROR_MESSAGE);
			}
		}
		
	}
	@Override
	public void windowOpened(WindowEvent e) {}
	@Override
	public void windowClosing(WindowEvent e) {
		if(replaceRulePanel.remindToSave() && textPanel.remindToSave()) e.getWindow().dispose();
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
