package w13t1;

import org.w3c.dom.Document;
import org.w3c.dom.NamedNodeMap;
import org.w3c.dom.Node;
import org.w3c.dom.NodeList;
import org.xml.sax.SAXException;

import javax.swing.*;
import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;
import javax.xml.parsers.ParserConfigurationException;
import java.io.File;
import java.io.FileOutputStream;
import java.io.FileWriter;
import java.io.IOException;
import java.io.OutputStreamWriter;
import java.nio.charset.Charset;
import java.util.Iterator;
import java.util.TreeSet;

public class XmlManager {
	public XmlManager() {}
	public TreeSet<Student> read(File file) throws ParserConfigurationException, SAXException, IOException, NumberFormatException,  AlreadyInCollectionException{
        TreeSet<Student> students = new TreeSet<Student>(new StudentComparator());
        DocumentBuilderFactory factory = DocumentBuilderFactory.newInstance();
        DocumentBuilder builder = factory.newDocumentBuilder();
        Document document = builder.parse(file);
        NodeList studentNodes = document.getDocumentElement().getElementsByTagName("Student");
        for (int i = 0; i < studentNodes.getLength(); i++) {
            Node product = studentNodes.item(i);
            NamedNodeMap attributes = product.getAttributes();
            int id = Integer.parseInt(attributes.getNamedItem("id").getNodeValue());
            String surname = attributes.getNamedItem("surname").getNodeValue();
            int year = Integer.parseInt(attributes.getNamedItem("year").getNodeValue());
            int group = Integer.parseInt(attributes.getNamedItem("group").getNodeValue());  
            boolean isNewElement = students.add(new Student(id, surname, year, group));
            if(!isNewElement) {
            	throw new AlreadyInCollectionException();
            }
        }
        return students;
    }
	public void write(File file, Iterator<Student> iterator) throws IOException {
		String fn = file.getName();
		String ext = fn.substring(fn.lastIndexOf('.'));
		if(!ext.equals(".xml")) {
			throw new IOException("Only .xml extension is allowed");
		}
		OutputStreamWriter fw = new OutputStreamWriter(
											     new FileOutputStream(file),
											     Charset.forName("UTF-16").newEncoder());
		fw.write("<?xml version=\"1.0\"?>\n");
		fw.write("<Students>\n");
		while(iterator.hasNext()) {
			Student s = iterator.next();
			fw.write("\t");
			fw.write(getStudentNode(s));
			fw.write('\n');
		}
		fw.write("</Students>");
		fw.close();
	}
	private String getStudentNode(Student s) {
		StringBuilder sb = new StringBuilder("<Student id='");
		sb.append(s.getId());
		sb.append("' surname='");
		sb.append(s.getSurname());
		sb.append("' year='");
		sb.append(s.getYear());
		sb.append("' group='");
		sb.append(s.getGroup());
		sb.append("'/>");
		return sb.toString();
	}
}
