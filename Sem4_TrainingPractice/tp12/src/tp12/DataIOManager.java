package tp12;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.IOException;

import javax.xml.parsers.ParserConfigurationException;
import javax.xml.transform.TransformerException;

import org.xml.sax.SAXException;

public abstract class DataIOManager {
	protected File file =null;
	public abstract void save(Employee director) throws NullPointerException, FileNotFoundException, IOException, ParserConfigurationException, TransformerException;
	public abstract Employee read() throws NullPointerException, FileNotFoundException, IOException, ClassNotFoundException, ParserConfigurationException, SAXException, NumberFormatException;
	public void setFile(File file) {
		this.file = file;
	}
	public File getFile() {
		return file;
	}
}
