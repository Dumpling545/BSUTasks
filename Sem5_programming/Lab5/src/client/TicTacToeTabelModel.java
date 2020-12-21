package client;

import javax.swing.table.AbstractTableModel;

public class TicTacToeTabelModel extends AbstractTableModel {
    String[][] data;

    public TicTacToeTabelModel(int rows, int cols) {
        data = new String[rows][cols];
    }

    @Override
    public int getColumnCount() {
        return data[0].length;
    }

    @Override
    public int getRowCount() {
        return data.length;
    }

    @Override
    public Object getValueAt(int rowIndex, int columnIndex) {
        return data[rowIndex][columnIndex];
    }

    @Override
    public void setValueAt(Object aValue, int rowIndex, int columnIndex) {
        data[rowIndex][columnIndex] = (String) aValue;
    }
    
}
