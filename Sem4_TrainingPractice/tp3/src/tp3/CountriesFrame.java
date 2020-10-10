package tp3;

import java.awt.BorderLayout;
import java.awt.Dimension;
import java.awt.EventQueue;
import java.awt.FlowLayout;
import java.io.IOException;
import java.util.HashMap;
import java.util.Map;
import java.util.TreeMap;

import javax.swing.BoxLayout;
import javax.swing.JFrame;
import javax.swing.JList;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.border.EmptyBorder;
import javax.swing.event.ListSelectionEvent;
import javax.swing.event.ListSelectionListener;
import javax.xml.parsers.ParserConfigurationException;

import org.xml.sax.SAXException;

public class CountriesFrame extends JFrame implements ListSelectionListener {

	private JPanel contentPane;
	private JScrollPane scrollListPane;
	private JList<String> countriesList;
	private CountryPanel countryPanel;
	private Map<String, String> countryFlagMap;
	private Map<String, String> countryCapitalMap;
	public static void main(String[] args) {
			CountriesFrame frame;
			try {
				frame = new CountriesFrame();
				frame.setVisible(true);
			} catch (NumberFormatException | ParserConfigurationException | SAXException | IOException e) {
				System.out.println(e.getMessage());
			}
			
	}

	public CountriesFrame() throws NumberFormatException, ParserConfigurationException, SAXException, IOException {
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		setSize(640, 480);
		setTitle("Countries");
		contentPane = new JPanel();
		contentPane.setLayout(new BoxLayout(contentPane, BoxLayout.X_AXIS));
		countryFlagMap = new TreeMap<String, String>();
		countryCapitalMap = new TreeMap<String, String>();
		XmlManager.read(countryFlagMap, countryCapitalMap);
		countriesList = new CountriesList(countryFlagMap);
		countriesList.addListSelectionListener(this);
		scrollListPane = new JScrollPane(countriesList);
		contentPane.add(scrollListPane);
		countryPanel = new CountryPanel();
		contentPane.add(countryPanel);
		setContentPane(contentPane);
	}

	@Override
	public void valueChanged(ListSelectionEvent e) {
		if(countriesList.getSelectedValue() != null) {
			String country = countriesList.getSelectedValue();
			String capital = countryCapitalMap.get(country);
			String imagePath = countryFlagMap.get(country);
			countryPanel.changeCountry(country, capital, imagePath);
		}
		
	}

}
