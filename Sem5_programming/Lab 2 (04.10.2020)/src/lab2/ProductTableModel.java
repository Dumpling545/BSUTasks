package lab2;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.List;
import java.util.stream.Collectors;

import javax.swing.JButton;
import javax.swing.JComponent;
import javax.swing.JSpinner;
import javax.swing.SpinnerModel;
import javax.swing.SpinnerNumberModel;
import javax.swing.event.ChangeEvent;
import javax.swing.event.ChangeListener;
import javax.swing.table.AbstractTableModel;

public class ProductTableModel extends AbstractTableModel {
	private List<Product> products;
	private List<Product> query;
	private FileManager manager;
	private final String[] COLUMNS = {"Name", "Quantity"};
	public ProductTableModel(List<Product> products, FileManager manager) {
		this.products = products;
		this.manager = manager;
		query = products;
	}
	public void updateQuery(String searchQuery) {
		query = products.stream().filter(p -> p.getName().startsWith(searchQuery)).collect(Collectors.toList());
		fireTableDataChanged();
	}
	@Override
	public int getRowCount() {
		return query.size();
	}

	@Override
	public int getColumnCount() {
		return COLUMNS.length;
	}

	@Override
	public Object getValueAt(int rowIndex, int columnIndex) {
		switch(columnIndex) {
			case 0:
				return query.get(rowIndex).getName();
			case 1:	
				return query.get(rowIndex).getQuantity();
		}
		return null;
	}

	@Override
	public String getColumnName(int column) {
		return COLUMNS[column];
	}

	@Override
	public Class<?> getColumnClass(int columnIndex) {
		switch(columnIndex) {
			case 0: 
				return String.class;
			case 1:
				return Integer.class;
		}
		return null;
	}

	@Override
	public boolean isCellEditable(int rowIndex, int columnIndex) {
		return false;
	}
	
}
