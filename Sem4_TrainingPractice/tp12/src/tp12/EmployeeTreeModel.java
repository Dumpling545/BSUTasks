package tp12;

import java.io.File;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

import javax.swing.event.TreeModelListener;
import javax.swing.tree.TreeModel;
import javax.swing.tree.TreePath;
import javax.xml.parsers.ParserConfigurationException;

import org.xml.sax.SAXException;


public class EmployeeTreeModel implements TreeModel {
	private Employee director;
	public EmployeeTreeModel(DataIOManager dataIOManager) throws NumberFormatException, ParserConfigurationException, SAXException, IOException, NullPointerException, ClassNotFoundException {
		director = dataIOManager.read();
	}
	public EmployeeTreeModel(Employee director) {
		this.director = director;
	}
	@Override
	public Object getRoot() {
		return director;
	}

	@Override
	public Object getChild(Object parent, int index) {
		Employee employee = (Employee) parent;
		return employee.getSubordinates().get(index);
	}

	@Override
	public int getChildCount(Object parent) {
		Employee employee = (Employee) parent;
		return employee.getSubordinates().size();
	}

	@Override
	public boolean isLeaf(Object node) {
		return getChildCount(node) == 0;
	}

	@Override
	public void valueForPathChanged(TreePath path, Object newValue) {}

	@Override
	public int getIndexOfChild(Object parent, Object child) {
		Employee employee = (Employee) parent;
		return employee.getSubordinates().indexOf(child);
	}

	@Override
	public void addTreeModelListener(TreeModelListener l) {}

	@Override
	public void removeTreeModelListener(TreeModelListener l) {}

}
