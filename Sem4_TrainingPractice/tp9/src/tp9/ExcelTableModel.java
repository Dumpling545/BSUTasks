package tp9;

import java.time.format.DateTimeParseException;
import java.util.List;
import java.util.NoSuchElementException;

import javax.swing.table.AbstractTableModel;

public class ExcelTableModel extends AbstractTableModel {
	private Node[][] nodes;
	private int rows;
	private int columns;
	public ExcelTableModel(int rows, int columns) {
		this.rows = rows;
		this.columns = columns;
		Parser parser = new Parser(this);
		nodes = new Node[rows][columns];
		for(int i = 0; i < rows; i++) {
			for(int j = 0; j < columns; j++) {
				nodes[i][j] = new Node(parser);
			}
		}
	}
	@Override
	public int getRowCount() {
		return rows;
	}

	@Override
	public int getColumnCount() {
		return columns;
	}

	@Override
	public Object getValueAt(int rowIndex, int columnIndex) {
		return nodes[rowIndex][columnIndex];
	}
	
	@Override
	public boolean isCellEditable(int rowIndex, int columnIndex) {
		return true;
	}
	
	@Override
	public void setValueAt(Object aValue, int rowIndex, int columnIndex) throws CircularDependencyException,  IndexOutOfBoundsException, NumberFormatException, NoSuchElementException, DateTimeParseException, InvalidOperationException, TooFewArgumentsException, NoSuchColumnException{
		nodes[rowIndex][columnIndex].setContent((String) aValue);
		fireTableDataChanged();
	}

}
