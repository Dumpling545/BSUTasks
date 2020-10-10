package tp3_2;

import javax.swing.Icon;
import javax.swing.ImageIcon;

public class Tour {
	public Icon flag;
	public String description;
	public Integer price;
	public Boolean included;
	public Tour(String flagSource, String description, int price) {
		flag = new ImageIcon(flagSource);
		this.description = description;
		this.price = price;
		included = false;
	}
}
