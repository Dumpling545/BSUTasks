package tp3;

import java.awt.Component;
import java.awt.Image;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;
import java.util.Map;

import javax.imageio.ImageIO;
import javax.swing.DefaultListCellRenderer;
import javax.swing.DefaultListModel;
import javax.swing.Icon;
import javax.swing.ImageIcon;
import javax.swing.JComponent;
import javax.swing.JLabel;
import javax.swing.JList;
import javax.swing.ListSelectionModel;
import javax.swing.event.ListSelectionEvent;
import javax.swing.event.ListSelectionListener;

public class CountriesList extends JList<String> {
	private int height = 16;
	private class IconListRenderer extends DefaultListCellRenderer {

		private Map<String, String> iconSrc = null;
		
		public IconListRenderer(Map<String, String> iconSrc) {
			this.iconSrc = iconSrc;
		}
		
		@Override
		public Component getListCellRendererComponent(
			JList list, Object value, int index, 
			boolean isSelected, boolean cellHasFocus) {
			JLabel label = 
				(JLabel) super.getListCellRendererComponent(list, 
					value, index, isSelected, cellHasFocus);
			ImageIcon icon = new ImageIcon(iconSrc.get(value));
			Image img = icon.getImage();
			Image compressedImage = img.getScaledInstance(height * icon.getIconWidth() / icon.getIconHeight(), 
															height, 
															Image.SCALE_SMOOTH);
			label.setIcon(new ImageIcon(compressedImage));
			return label;
		}
	}
	CountriesList(Map<String, String> countryFlagMap){
		super();
		setSelectionMode(ListSelectionModel.SINGLE_SELECTION);
		setCellRenderer(new IconListRenderer(countryFlagMap));
		DefaultListModel<String> model = new DefaultListModel<>();
		model.addAll(countryFlagMap.keySet());
		setModel(model);
	}

}
