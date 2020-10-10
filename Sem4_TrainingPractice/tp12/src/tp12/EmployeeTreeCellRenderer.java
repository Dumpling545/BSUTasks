package tp12;

import java.awt.Component;

import javax.swing.ImageIcon;
import javax.swing.JTree;
import javax.swing.tree.DefaultTreeCellRenderer;

public class EmployeeTreeCellRenderer extends DefaultTreeCellRenderer {
	private ImageIcon femaleIcon;
	private ImageIcon maleIcon;
	public EmployeeTreeCellRenderer() {
		/*femaleIcon = new ImageIcon("images/female.png");
		maleIcon = new ImageIcon("images/male.png");*/
		femaleIcon = new ImageIcon(getClass().getResource("/images/female.png"));
		maleIcon = new ImageIcon(getClass().getResource("/images/male.png"));
	}
	@Override
	public Component getTreeCellRendererComponent(JTree tree, Object value, boolean sel, boolean expanded, boolean leaf,
			int row, boolean hasFocus) {
		super.getTreeCellRendererComponent(
                tree, value, sel,
                expanded, leaf, row,
                hasFocus);
		Employee employee = (Employee) value;
		if (employee.getSex() == Sex.FEMALE) {
            setIcon(femaleIcon);
        } else {
        	 setIcon(maleIcon);
        } 
		return this;
	}

}
