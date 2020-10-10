package tp3;
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
	public static void read(Map<String, String> countryFlagMap, Map<String, String> countryCapitalMap) 
									throws ParserConfigurationException, SAXException, IOException, NumberFormatException {
		File file = new File("countries.xml");
        DocumentBuilderFactory factory = DocumentBuilderFactory.newInstance();
        DocumentBuilder builder = factory.newDocumentBuilder();
        Document document = builder.parse(file);
        NodeList countries = document.getDocumentElement().getElementsByTagName("country");
        for (int i = 0; i < countries.getLength(); i++) {
            Node countryNode = countries.item(i);
            NamedNodeMap attributes = countryNode.getAttributes();
            String country = attributes.getNamedItem("name").getNodeValue();
            country = country.substring(0, country.indexOf(","));
            String capital = attributes.getNamedItem("capital").getNodeValue();
            StringBuilder sb = new StringBuilder("img\\");
            sb.append(attributes.getNamedItem("cca3").getNodeValue().toLowerCase());
            sb.append(".jpg");
            String flag = sb.toString();
            countryFlagMap.put(country, flag);
            countryCapitalMap.put(country, capital);
        }
    }
}