import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.Stack;
import java.util.regex.Matcher;
import java.util.regex.Pattern;
import javax.swing.JFileChooser;
import javax.swing.JFrame;
import javax.swing.JMenu;
import javax.swing.JMenuBar;
import javax.swing.JMenuItem;
import javax.swing.JOptionPane;
import javax.swing.JScrollPane;
import javax.swing.JTable;

public class XmlViewerFrame extends JFrame implements ActionListener {
    private final int DEFAULT_WIDTH = 1080;
    private final int DEFAULT_HEIGHT = 675;
    private final String TITLE = "Xml Viewer";
    private final String INCORRECT_XML_DIALOG_MESSAGE =
            "Xml file you trying to analyze is" + " incorrect. Try another one.";
    private final String INCORRECT_XML_DIALOG_TITLE = "Incorrect xml";
    private final String DEFAULT_DIRECTORY =
            "/home/yan/Projects/git-repositories/BSUTasks" + "/BSUTasks/Sem5_programming/Lab4/xml/";
    private JFileChooser fileOpener;
    private TagTableModel tagTableModel;
    private final String TAG_PATTERN =
            "(<(\\/)?([a-zA-Z_:][\\w:\\-\\.]*)( [a-zA-Z_:][\\w:\\-\\.]*=([\"\']).*\\5)*>)|"
                    + "(<([a-zA-Z_:][\\w:\\-\\.]*)( [a-zA-Z_:][\\w:\\-\\.]*=([\"\']).*\\9)*\\/>)|"
                    + "(\\R)";
    private Stack<Tag> tagStack;

    public XmlViewerFrame() {
        setTitle(TITLE);
        setSize(DEFAULT_WIDTH, DEFAULT_HEIGHT);
        tagStack = new Stack<Tag>();
        JMenuBar bar = new JMenuBar();
        setJMenuBar(bar);
        JMenu menu = new JMenu("File");
        bar.add(menu);
        JMenuItem item = new JMenuItem("Open");
        menu.add(item);
        item.addActionListener(this);
        tagTableModel = new TagTableModel();
        JTable table = new JTable(tagTableModel);
        table.setAutoCreateRowSorter(true);
        table.getTableHeader().setReorderingAllowed(false);
        setContentPane(new JScrollPane(table));
        fileOpener = new JFileChooser(DEFAULT_DIRECTORY);
    }

    @Override
    public void actionPerformed(ActionEvent e) {
        int res = fileOpener.showOpenDialog(this);
        if (res == JFileChooser.APPROVE_OPTION) {
            try {
                tagStack.clear();
                tagTableModel.clear();
                Path path = Paths.get(fileOpener.getSelectedFile().getPath());
                String content = new String(Files.readAllBytes(path));
                Pattern pattern = Pattern.compile(TAG_PATTERN);
                Matcher matcher = pattern.matcher(content);
                int line = 1;
                int previousLineLastCharacterPosition = -1;
                while (matcher.find()) {
                    if (matcher.group(10) != null) {
                        ++line;
                        previousLineLastCharacterPosition = matcher.start(10);
                    } else if (matcher.group(1) != null) {
                        boolean isOpeningTagFound = matcher.group(2) == null;
                        if (isOpeningTagFound) {
                            tagStack.push(new Tag(matcher.group(3), line,
                                    matcher.start() - previousLineLastCharacterPosition,
                                    matcher.group()));
                        } else {
                            if (!tagStack.empty()
                                    && tagStack.peek().isOpeningTagOf(matcher.group(3))) {
                                tagStack.peek().close(line,
                                        matcher.start() - previousLineLastCharacterPosition);
                                tagTableModel.addTag(tagStack.pop());
                            } else {
                                tagStack.clear();
                                tagTableModel.clear();
                                JOptionPane.showMessageDialog(this, INCORRECT_XML_DIALOG_MESSAGE,
                                        INCORRECT_XML_DIALOG_TITLE, JOptionPane.ERROR_MESSAGE);
                                break;
                            }
                        }
                    } else if (matcher.group(6) != null) {
                        int col = matcher.start() - previousLineLastCharacterPosition;
                        tagTableModel.addTag(new Tag (line, col, line, col, matcher.group()));
                    }
                }
            } catch (IOException ex) {
                JOptionPane.showMessageDialog(null, ex.getMessage(), ex.getClass().getName(),
                        JOptionPane.ERROR_MESSAGE);
            }
        }
    }
}
