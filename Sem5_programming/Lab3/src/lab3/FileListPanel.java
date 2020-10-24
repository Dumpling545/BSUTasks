package lab3;

import java.awt.Color;
import java.awt.Component;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.File;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.Enumeration;
import java.util.List;
import java.util.Locale;
import java.util.PropertyResourceBundle;
import java.util.ResourceBundle;
import java.util.Set;
import javax.swing.Action;
import javax.swing.BoxLayout;
import javax.swing.DefaultListModel;
import javax.swing.JButton;
import javax.swing.JFileChooser;
import javax.swing.JLabel;
import javax.swing.JList;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.ListCellRenderer;
import javax.swing.SwingUtilities;
import javax.swing.UIManager;
import javax.swing.filechooser.FileFilter;
import javax.swing.filechooser.FileNameExtensionFilter;
import javax.swing.filechooser.FileSystemView;

public class FileListPanel extends JPanel implements LanguageSettable {
    private final String DEFAULT_DIRECTORY = "/home/yan/Projects/git-repositories/BSUTasks"
            + "/BSUTasks/Sem5_programming/Lab3/input/";
    private JList<File> list;
    private JLabel headerLabel;
    private JButton addButton, removeButton;
    private ResourceBundle bundle;
    private String extension, headerBK;
    private FileFilter filter;
    public FileListPanel(String headerBK, String extension) {
        this.extension = extension;
        this.headerBK = headerBK;
        setLayout(new BoxLayout(this, BoxLayout.Y_AXIS));
        headerLabel = new JLabel();
        headerLabel.setAlignmentX(Component.CENTER_ALIGNMENT);
        add(headerLabel);
        list = new JList<File>(new DefaultListModel<File>());
        list.setAlignmentX(Component.CENTER_ALIGNMENT);
        list.setCellRenderer(new ListCellRenderer<File>() {
            @Override
            public Component getListCellRendererComponent(JList<? extends File> list, File value,
                    int index, boolean isSelected, boolean cellHasFocus) {
                JLabel label = new JLabel(value.getName());
                if (isSelected)
                    label.setForeground(Color.GREEN);
                label.setIcon(FileSystemView.getFileSystemView().getSystemIcon(value));
                return label;
            }
        });
        JScrollPane scroll = new JScrollPane(list);
        add(scroll);
        JPanel managementPanel = new JPanel();
        managementPanel.setAlignmentX(Component.CENTER_ALIGNMENT);
        managementPanel.setLayout(new BoxLayout(managementPanel, BoxLayout.X_AXIS));
        add(managementPanel);
        addButton = new JButton();
        addButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent event) {
                JFileChooser fileOpener = new JFileChooser(DEFAULT_DIRECTORY);
                fileOpener.setMultiSelectionEnabled(true);
                fileOpener.setAcceptAllFileFilterUsed(false);
                fileOpener.setFileFilter(filter);
                int res = fileOpener.showOpenDialog(null);
                if (res == JFileChooser.APPROVE_OPTION) {
                    ((DefaultListModel<File>) list.getModel())
                            .addAll(Arrays.asList(fileOpener.getSelectedFiles()));
                }
            }
        });
        managementPanel.add(addButton);
        removeButton = new JButton();
        setLanguage(new Locale("en", "GB"));
        removeButton.addActionListener(new ActionListener() {

            @Override
            public void actionPerformed(ActionEvent event) {
                if (list.isSelectionEmpty()) {
                    JOptionPane.showMessageDialog(null,
                            bundle.getString("NoSelectionException.Desc"),
                            bundle.getString("NoSelectionException.Header"),
                            JOptionPane.ERROR_MESSAGE);
                } else {
                    int[] indices = list.getSelectedIndices();
                    DefaultListModel<File> model = (DefaultListModel<File>) list.getModel();
                    for (int i = indices.length - 1; i >= 0; i--) {
                        model.remove(indices[i]);
                    }
                }
            }
        });
        managementPanel.add(removeButton);
    }

    public List<File> getFileList() {
        DefaultListModel<File> model = (DefaultListModel<File>) list.getModel();
        List<File> fileList = new ArrayList<>(model.getSize());
        for (int i = 0; i < model.getSize(); i++) {
            fileList.add(model.getElementAt(i));
        }
        return fileList;
    }

    @Override
    public void setLanguage(Locale locale) {
        bundle = PropertyResourceBundle.getBundle("MessageBundle", locale);
        addButton.setText(bundle.getString("addButton"));
        removeButton.setText(bundle.getString("removeButton"));
        headerLabel.setText(bundle.getString(headerBK));
        //fileOpener.setDialogTitle(bundle.getString("fileOpener.Title"));
        filter = new FileNameExtensionFilter(
                bundle.getString("onlyThisTypeIsAllowed") + ": ." + extension, extension);
    }
}
