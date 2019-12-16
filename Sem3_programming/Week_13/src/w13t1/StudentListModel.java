package w13t1;

import java.util.ArrayList;
import java.util.Collections;

import javax.swing.AbstractListModel;

public class StudentListModel extends AbstractListModel<String> {
	private ArrayList<Student> studentArray;
	public StudentListModel() {
		super();
		studentArray = new ArrayList<Student>();
	}
	@Override
	public int getSize() {
		return studentArray.size();
	}

	@Override
	public String getElementAt(int index) {
		return studentArray.get(index).toString();
	}

	public void add(Student s) {
		int bs = Collections.binarySearch(studentArray, s);
		int index = (bs < 0) ? -bs - 1: bs;
		studentArray.add(index, s);
		fireIntervalAdded(this, index, index);
	}
	
	public void clear() {
		if(!studentArray.isEmpty()) {
			fireIntervalRemoved(this, 0, studentArray.size() - 1);
			studentArray.clear();
		}
	}
}
