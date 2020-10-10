package tp3;

import javax.swing.BoxLayout;
import javax.swing.ImageIcon;
import javax.swing.JLabel;
import javax.swing.JPanel;
public class CountryPanel extends JPanel {
	private JLabel countryLabel;
	private JLabel capitalLabel;
	private JLabel flagLabel;
	public CountryPanel() {
		super();
		setLayout(new BoxLayout(this, BoxLayout.Y_AXIS));
		countryLabel = new JLabel("choose country in list");
		capitalLabel = new JLabel();
		flagLabel = new JLabel();
		add(countryLabel);
		add(capitalLabel);
		add(flagLabel);
	}
	public void changeCountry(String country, String capital, String imagePath) {
		countryLabel.setText("Country: " + country);
		capitalLabel.setText("Capital: " + capital);
		flagLabel.setIcon(new ImageIcon(imagePath));
	}
}
