package lab3;

import java.awt.Component;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.PrintWriter;
import java.lang.reflect.InvocationTargetException;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.text.DateFormat;
import java.text.NumberFormat;
import java.util.ArrayList;
import java.util.Currency;
import java.util.Date;
import java.util.Enumeration;
import java.util.List;
import java.util.Locale;
import java.util.Map;
import java.util.PropertyResourceBundle;
import java.util.Random;
import java.util.ResourceBundle;
import java.util.TreeMap;
import java.net.URL;
import java.net.URLClassLoader;
import javax.swing.BoxLayout;
import javax.swing.ButtonGroup;
import javax.swing.JButton;
import javax.swing.JFileChooser;
import javax.swing.JFrame;
import javax.swing.JMenu;
import javax.swing.JMenuBar;
import javax.swing.JMenuItem;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JRadioButtonMenuItem;
import javax.swing.SwingUtilities;
import javax.swing.UIManager;
import javax.swing.text.NumberFormatter;

public class StaticFunctionInterpreterFrame extends JFrame implements ActionListener, LanguageSettable {
	private final int DEFAULT_WIDTH = 1080;
	private final int DEFAULT_HEIGHT = 675;
	private final String FUNCTION_FILES_HEADER_BK = "FunctionFilesHeader";
	private final String JAVA_FILES_HEADER_BK = "JavaFilesHeader";
	private final String FUNCTION_EXTENSION = "properties";
	private final String JAVA_EXTENSION = "java";
	private final String DEFAULT_DIRECTORY = "/home/yan/Projects/git-repositories/BSUTasks"
			+ "/BSUTasks/Sem5_programming/Lab3/input/";
	private JMenu langMenu;
	private JMenuItem langBeBYItem, langUkUAItem, langEnGBItem;
	private FileListPanel functionPanel, javaPanel;
	private JButton runButton;
	private ResourceBundle bundle;

	public StaticFunctionInterpreterFrame() {
		setSize(DEFAULT_WIDTH, DEFAULT_HEIGHT);
		JPanel contentPane = new JPanel();
		setContentPane(contentPane);
		JMenuBar bar = new JMenuBar();
		setJMenuBar(bar);
		langMenu = new JMenu();
		bar.add(langMenu);
		ButtonGroup bg = new ButtonGroup();
		langBeBYItem = new JRadioButtonMenuItem();
		langUkUAItem = new JRadioButtonMenuItem();
		langEnGBItem = new JRadioButtonMenuItem();
		JMenuItem[] items = { langBeBYItem, langUkUAItem, langEnGBItem };
		for (var item : items) {
			bg.add(item);
			item.addActionListener(this);
			langMenu.add(item);
		}
		contentPane.setLayout(new BoxLayout(contentPane, BoxLayout.PAGE_AXIS));
		runButton = new JButton();
		runButton.setAlignmentX(Component.CENTER_ALIGNMENT);
		contentPane.add(runButton);
		functionPanel = new FileListPanel(FUNCTION_FILES_HEADER_BK, FUNCTION_EXTENSION);
		contentPane.add(functionPanel);
		javaPanel = new FileListPanel(JAVA_FILES_HEADER_BK, JAVA_EXTENSION);
		contentPane.add(javaPanel);
		langEnGBItem.setSelected(true);
		setLanguage(new Locale("en", "GB"));
		runButton.addActionListener(this);
	}

	@Override
	public void actionPerformed(ActionEvent e) {
		if (e.getSource() == runButton) {
			List<File> javaFiles = javaPanel.getFileList();
			List<File> functionFiles = functionPanel.getFileList();
			if (functionFiles.size() == 0) {
				JOptionPane.showMessageDialog(null, bundle.getString("EmptyFunctionListException.Desc"),
						bundle.getString("EmptyFunctionListException.Header"), JOptionPane.ERROR_MESSAGE);
			} else {
				try {
					ClassLoader loader = SimpleClassCompiler.getClassLoaderWithPrecompiledJavaFiles(javaFiles);
					MethodParser methodParser = new MethodParser(loader);
					Map<String, Object> results = new TreeMap<>();
					for (int i = 0; i < functionFiles.size(); i++) {
						results.putAll(methodParser.parseAndRunMethods(functionFiles.get(i)));
					}
					saveResults(results);
				} catch (IOException ex) {
					showExceptionDialog(ex, "FileException");
				} catch (ClassNotFoundException | MethodParseException | SecurityException | NoSuchMethodException
						| IllegalArgumentException ex) {
					showExceptionDialog(ex, "ParseException");
				} catch (CannotCompileJavaFileException ex) {
					showExceptionDialog(ex, "CompileException");
				} catch (IllegalAccessException | InvocationTargetException ex) {
					showExceptionDialog(ex, "MethodInvocationException");
				}
			}
		} else if (e.getSource() == langBeBYItem) {
			setLanguage(new Locale("be", "BY"));
		} else if (e.getSource() == langUkUAItem) {
			setLanguage(new Locale("uk", "UA"));
		} else if (e.getSource() == langEnGBItem) {
			setLanguage(Locale.UK);
		}
	}

	private void saveResults(Map<String, Object> results) {
		JFileChooser fileSaver = new JFileChooser(DEFAULT_DIRECTORY);
		int result = fileSaver.showSaveDialog(null);
		if (result == JFileChooser.APPROVE_OPTION) {
			;
			try (PrintWriter pw = new PrintWriter(fileSaver.getSelectedFile())) {
				for (var entry : results.entrySet()) {
					pw.format("%s  ---->  %s%n", entry.getKey(), entry.getValue());
				}
			} catch (FileNotFoundException ex) {
				showExceptionDialog(ex, "FileException");
			}
		}
	}

	private void showExceptionDialog(Exception ex, String dialogHeaderBK) {
		JOptionPane.showMessageDialog(null, ex.getMessage(), bundle.getString(dialogHeaderBK),
				JOptionPane.ERROR_MESSAGE);
	}

	@Override
	public void setLanguage(Locale locale) {
		bundle = PropertyResourceBundle.getBundle("MessageBundle", locale);
		Locale.setDefault(locale);
		for (var key : bundle.keySet()) {
			UIManager.getDefaults().put(key, bundle.getString(key));
		}
		SwingUtilities.updateComponentTreeUI(this);
		setTitle(bundle.getString("title"));
		langMenu.setText(bundle.getString("langMenu"));
		langBeBYItem.setText(bundle.getString("langBeBYItem"));
		langUkUAItem.setText(bundle.getString("langUkUAItem"));
		langEnGBItem.setText(bundle.getString("langEnGBItem"));
		runButton.setText(bundle.getString("runButton"));
		for (var comp : getContentPane().getComponents()) {
			if (comp instanceof LanguageSettable) {
				((LanguageSettable) comp).setLanguage(locale);
			}
		}
		Currency currency = Currency.getInstance(locale);
		NumberFormat currencyFormattter = NumberFormat.getCurrencyInstance(locale);
		StringBuilder sb = new StringBuilder();
		DateFormat dateFormatter = DateFormat.getDateInstance(DateFormat.FULL, locale);
		sb.append(bundle.getString("CurrencyAndDate.CurrencyLocalName")).append(currency.getDisplayName(locale))
				.append('\n').append(bundle.getString("CurrencyAndDate.CurrencyEnglishName"))
				.append(currency.getDisplayName(Locale.UK)).append('\n')
				.append(bundle.getString("CurrencyAndDate.CurrencyCode")).append(currency.getCurrencyCode())
				.append('\n').append(bundle.getString("CurrencyAndDate.RandomCurrencyValue"))
				.append(currencyFormattter.format((new Random()).nextDouble() * 1000)).append('\n')
				.append(bundle.getString("CurrencyAndDate.LocalDate")).append(dateFormatter.format(new Date()));
		JOptionPane.showMessageDialog(null, sb.toString(), bundle.getString("CurrencyAndDate.Title"),
				JOptionPane.INFORMATION_MESSAGE);
	}
}
