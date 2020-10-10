package tp3_2;

import java.io.IOException;
import java.util.ArrayList;

import javax.swing.Icon;
import javax.swing.table.AbstractTableModel;
import javax.xml.parsers.ParserConfigurationException;

import org.xml.sax.SAXException;

public class ToursTableModel extends AbstractTableModel {
	private String[] columnNames = {"Flag", "Description", "Price", "Include"};
	private ArrayList<Tour> tours;
	private boolean editMode = false;
	public  ToursTableModel() throws NumberFormatException, ParserConfigurationException, SAXException, IOException {
		tours = XmlManager.read();
	}
	@Override
	public int getRowCount() {
		return tours.size() + 1;
	}

	@Override
	public int getColumnCount() {
		return columnNames.length;
	}

	@Override
	public Object getValueAt(int rowIndex, int columnIndex) {
		Object value = null;
		if(rowIndex < tours.size()) {
			switch(columnIndex) {
				case 0:
					value = tours.get(rowIndex).flag; 
					break;
				case 1:
					value = tours.get(rowIndex).description; 
					break;
				case 2:
					value = tours.get(rowIndex).price; 
					break;
				case 3:
					value = tours.get(rowIndex).included; 
					break;
			}
		} else {
			switch(columnIndex) {
				case 1:
					value = "Overall price: "; 
					break;
				case 2:
					value = tours.stream().filter(t -> t.included).mapToInt(t -> t.price).sum(); 
					break;
				default:
					value = null;
					break;
			}
		}
		return value;
	}
	@Override
	public String getColumnName(int column) {
		return columnNames[column];
	}
	@Override
	public boolean isCellEditable(int rowIndex, int columnIndex) {
		return ((editMode && columnIndex != 0) || columnIndex == 3) && rowIndex < tours.size();
	}
	@Override
	public void setValueAt(Object aValue, int rowIndex, int columnIndex) {
		super.setValueAt(aValue, rowIndex, columnIndex);
		if(rowIndex < tours.size()) {
			switch(columnIndex) {
				case 1:
					tours.get(rowIndex).description = (String) aValue; 
					break;
				case 2:
					tours.get(rowIndex).price = (int) aValue; 
					break;
				case 3:
					tours.get(rowIndex).included = (boolean) aValue; 
					break;
			}
		}
		 fireTableCellUpdated(tours.size(), 2);
	}
	public void setEditMode(boolean editMode) {
		this.editMode = editMode;
	}
	public void addTour(Tour tour) {
		tours.add(tour);
		fireTableRowsInserted(tours.size() - 1, tours.size());
	}
	@Override
	public Class getColumnClass(int columnIndex) {
		switch(columnIndex) {
			case 0:
				return Icon.class;
			case 1:
				return String.class;
			case 2:
				return Integer.class;
			case 3:
				return Boolean.class;
		}
		return Object.class;
	}
}
