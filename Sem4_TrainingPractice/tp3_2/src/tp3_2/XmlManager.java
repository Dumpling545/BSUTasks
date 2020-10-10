package tp3_2;
import java.io.File;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;
import java.util.Map;

import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;
import javax.xml.parsers.ParserConfigurationException;

import org.w3c.dom.Document;
import org.w3c.dom.NamedNodeMap;
import org.w3c.dom.Node;
import org.w3c.dom.NodeList;
import org.xml.sax.SAXException;

public class XmlManager {
	public XmlManager() {}
	public static ArrayList<Tour> read() 
									throws ParserConfigurationException, SAXException, IOException, NumberFormatException {
		File file = new File("tours.xml");
		ArrayList<Tour> tours = new ArrayList<Tour>();
        DocumentBuilderFactory factory = DocumentBuilderFactory.newInstance();
        DocumentBuilder builder = factory.newDocumentBuilder();
        Document document = builder.parse(file);
        NodeList tourNodes = document.getDocumentElement().getElementsByTagName("tour");
        for (int i = 0; i < tourNodes.getLength(); i++) {
            Node tourNode = tourNodes.item(i);
            NamedNodeMap attributes = tourNode.getAttributes();
            String flag = attributes.getNamedItem("flag").getNodeValue();
            String description = attributes.getNamedItem("description").getNodeValue();
            int price = Integer.parseInt(attributes.getNamedItem("price").getNodeValue());
            tours.add(new Tour(flag, description, price));
        }
		return tours;
    }
}