import java.util.ArrayList;
import java.util.List;
import javax.swing.table.AbstractTableModel;

public class TagTableModel extends AbstractTableModel {
    private List<Tag> list;

    public TagTableModel() {
        list = new ArrayList<Tag>();
    }

    @Override
    public int getColumnCount() {
        return 5;
    }

    @Override
    public int getRowCount() {
        return list.size();
    }

    @Override
    public Object getValueAt(int row, int col) {
        Object ob = null;
        switch (col) {
            case 0:
                ob = list.get(row).getFullName();
                break;
            case 1:
                ob = list.get(row).getStartLine();
                break;
            case 2:
                ob = list.get(row).getStartColumn();
                break;
            case 3:
                ob = list.get(row).getEndLine();
                break;
            case 4:
                ob = list.get(row).getEndColumn();
                break;
        }
        return ob;
    }

    @Override
    public Class<?> getColumnClass(int columnIndex) {
        Class<?> c = null;
        if (columnIndex == 0) {
            c = String.class;
        } else {
            c = Integer.class;
        }
        return c;
    }

    @Override
    public String getColumnName(int column) {
        String cname = null;
        switch (column) {
            case 0:
                cname = "Tag";
                break;
            case 1:
                cname = "Start line";
                break;
            case 2:
                cname = "Start column";
                break;
            case 3:
                cname = "End line";
                break;
            case 4:
                cname = "End column";
                break;
        }
        return cname;
    }

    public void addTag(Tag tag) {
        list.add(tag);
        fireTableRowsInserted(list.size() - 1, list.size() - 1);
    }

    public void clear() {
        list.clear();
    }
}
