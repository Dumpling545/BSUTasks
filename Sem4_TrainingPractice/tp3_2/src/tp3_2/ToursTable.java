package tp3_2;

import java.awt.Component;
import java.io.IOException;

import javax.swing.JTable;
import javax.swing.table.TableColumn;
import javax.xml.parsers.ParserConfigurationException;

import org.xml.sax.SAXException;

public class ToursTable extends JTable {
	private ToursTableModel model;
	private int descriptionColumnWidth = 200;
	private int defaultColumnWidth = 100;
	public ToursTable() throws NumberFormatException, ParserConfigurationException, SAXException, IOException {
		super();
		model = new ToursTableModel();
		setModel(model);
		updateCellSize(0);
		
	}
	public void setEditMode(boolean mode) {
		model.setEditMode(mode);
	}
	public void addTour(Tour tour) {
		model.addTour(tour);
		updateCellSize(model.getRowCount() - 2);
	}
	private void updateCellSize(int rowStart)
	{
	    for (int row = rowStart; row < getRowCount(); row++)
	    {
	        int rowHeight = getRowHeight();

	        for (int column = 0; column < getColumnCount(); column++)
	        {
	            Component comp = prepareRenderer(getCellRenderer(row, column), row, column);
	            rowHeight = Math.max(rowHeight, comp.getPreferredSize().height);
	        }
	        setRowHeight(row, rowHeight);
	    }
	    TableColumn column = null;
	    for (int i = 0; i < getColumnCount(); i++) {
	        column = getColumnModel().getColumn(i);
	        if (i == 1) {
	            column.setPreferredWidth(descriptionColumnWidth); 
	        } else {
	            column.setPreferredWidth(defaultColumnWidth);
	        }
	    }
	}
}
