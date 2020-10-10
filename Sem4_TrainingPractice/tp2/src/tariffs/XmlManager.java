package tariffs;
import java.io.File;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

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
	public static List<BaseTariff> read(String src) throws ParserConfigurationException, SAXException, IOException, NumberFormatException {
		File file = new File(src);
		List<BaseTariff> tariffs = new ArrayList<BaseTariff>();
        DocumentBuilderFactory factory = DocumentBuilderFactory.newInstance();
        DocumentBuilder builder = factory.newDocumentBuilder();
        Document document = builder.parse(file);
        NodeList internetTariffs = document.getDocumentElement().getElementsByTagName("Internet");
        NodeList phoneCallTariffs = document.getDocumentElement().getElementsByTagName("PhoneCall");
        NodeList smsTariffs = document.getDocumentElement().getElementsByTagName("SMS");
        for (int i = 0; i < internetTariffs.getLength(); i++) {
            Node tariffNode = internetTariffs.item(i);
            InternetTariff internetTariff = new InternetTariff();
            NamedNodeMap attributes = tariffNode.getAttributes();
            internetTariff.name = attributes.getNamedItem("name").getNodeValue();
            internetTariff.regularPayment = 
            		Integer.parseInt(attributes.getNamedItem("payment").getNodeValue());
            internetTariff.numberOfSubscribers = 
            		Integer.parseInt(attributes.getNamedItem("subscribers").getNodeValue());
            internetTariff.numberOfMBs = 
            		Integer.parseInt(attributes.getNamedItem("mbs").getNodeValue());
            tariffs.add(internetTariff);
        }
        for (int i = 0; i < smsTariffs.getLength(); i++) {
            Node tariffNode = smsTariffs.item(i);
            SMSTariff smsTariff = new SMSTariff();
            NamedNodeMap attributes = tariffNode.getAttributes();
            smsTariff.name = attributes.getNamedItem("name").getNodeValue();
            smsTariff.regularPayment = 
            		Integer.parseInt(attributes.getNamedItem("payment").getNodeValue());
            smsTariff.numberOfSubscribers = 
            		Integer.parseInt(attributes.getNamedItem("subscribers").getNodeValue());
            smsTariff.numberOfMessages = 
            		Integer.parseInt(attributes.getNamedItem("messages").getNodeValue());
            tariffs.add(smsTariff);
        }
        for (int i = 0; i < phoneCallTariffs.getLength(); i++) {
            Node tariffNode = phoneCallTariffs.item(i);
            PhoneCallTariff phoneCallTariff = new PhoneCallTariff();
            NamedNodeMap attributes = tariffNode.getAttributes();
            phoneCallTariff.name = attributes.getNamedItem("name").getNodeValue();
            phoneCallTariff.regularPayment = 
            		Integer.parseInt(attributes.getNamedItem("payment").getNodeValue());
            phoneCallTariff.numberOfSubscribers = 
            		Integer.parseInt(attributes.getNamedItem("subscribers").getNodeValue());
            phoneCallTariff.withinNetworkNumberOfMinutes = 
            		Integer.parseInt(attributes.getNamedItem("wminutes").getNodeValue());
            phoneCallTariff.allNetworksNumberOfMinutes = 
            		Integer.parseInt(attributes.getNamedItem("aminutes").getNodeValue());
            tariffs.add(phoneCallTariff);
        }
        return tariffs;
    }
}