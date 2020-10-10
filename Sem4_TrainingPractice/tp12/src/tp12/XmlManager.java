package tp12;

import java.io.File;
import java.io.IOException;

import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;
import javax.xml.parsers.ParserConfigurationException;
import javax.xml.transform.Transformer;
import javax.xml.transform.TransformerConfigurationException;
import javax.xml.transform.TransformerException;
import javax.xml.transform.TransformerFactory;
import javax.xml.transform.dom.DOMSource;
import javax.xml.transform.stream.StreamResult;

import org.w3c.dom.Attr;
import org.w3c.dom.Document;
import org.w3c.dom.Element;
import org.w3c.dom.NamedNodeMap;
import org.w3c.dom.Node;
import org.w3c.dom.NodeList;
import org.w3c.dom.Text;
import org.xml.sax.SAXException;



public class XmlManager extends DataIOManager{
	private File file =null;
	private final String SEX_ATTR_NAME = "sex";
	private final String AGE_ATTR_NAME = "age";
	private final String UNFIREABLE_ATTR_NAME = "unfireable";
	
	private final String POSITION_ELEMENT_NAME = "position";
	private final String EMPLOYMENT_FORM_ELEMENT_NAME = "employmentForm";
	private final String SALARY_ELEMENT_NAME = "salary";
	private final String SUBORDINATES_ELEMENT_NAME = "subordinates";
	
	private final String EMPLOYEE_ELEMENT_NAME = "employee";
	
	public XmlManager() {
	}
	@Override
	public Employee read() throws ParserConfigurationException, SAXException, IOException, NumberFormatException {
        DocumentBuilderFactory factory = DocumentBuilderFactory.newInstance();
        DocumentBuilder builder = factory.newDocumentBuilder();
        Document document = builder.parse(file);
        Node rootNode = document.getDocumentElement();
        Employee director = new Employee();
        readEmployee(director, rootNode);
        return director;
    }
	private void readEmployee(Employee employee, Node node) {
		//read attributes
		NamedNodeMap attributes = node.getAttributes();
		employee.setSex(Sex.get(attributes.getNamedItem(SEX_ATTR_NAME).getNodeValue()));
		employee.setAge(Integer.parseInt(attributes.getNamedItem(AGE_ATTR_NAME).getNodeValue()));
		employee.setUnfireable(Boolean.parseBoolean(attributes.getNamedItem(UNFIREABLE_ATTR_NAME).getNodeValue()));
		//read content 
		NodeList nodeList = node.getChildNodes();
		employee.setFullName(nodeList.item(0).getTextContent().trim());
	    for (int i = 1; i < nodeList.getLength(); ++i) {
	        Node child = nodeList.item(i);
	        if(child.getNodeType() == Node.ELEMENT_NODE) {
	        		switch(child.getNodeName()) {
		        		case POSITION_ELEMENT_NAME:
		        			employee.setPosition(child.getTextContent().trim());
		        			break;
		        		case EMPLOYMENT_FORM_ELEMENT_NAME:
		        			employee.setEmploymentForm(EmploymentForm.get(child.getTextContent().trim()));
		        			break;
		        		case SALARY_ELEMENT_NAME:
		        			employee.setSalary(Integer.parseInt(child.getTextContent().trim()));
		        			break;
		        		case SUBORDINATES_ELEMENT_NAME:
		        			NodeList subordinateList = child.getChildNodes();
		        			for(int j = 0; j < subordinateList.getLength(); j++) {
		        				Node subordinateNode = subordinateList.item(j);
		        				if(subordinateNode.getNodeName().equals(EMPLOYEE_ELEMENT_NAME)) {
			        				Employee subordinate = new Employee();
			        				readEmployee(subordinate, subordinateNode);
			        				employee.addSubordinate(subordinate);
		        				}
		        			}
		        			break;
	        		}
	        }	              
	    }
	}
	@Override
	public void save(Employee director) throws ParserConfigurationException, TransformerException {
		   DocumentBuilderFactory docFactory = DocumentBuilderFactory.newInstance();
		    DocumentBuilder docBuilder = docFactory.newDocumentBuilder();
		    Document document = docBuilder.newDocument();
		    Element rootElement = document.createElement(EMPLOYEE_ELEMENT_NAME);
		    document.appendChild(rootElement);
		    saveEmployee(director, rootElement, document);
		    TransformerFactory transformerFactory = TransformerFactory.newInstance();
		    Transformer transformer = transformerFactory.newTransformer();
		    DOMSource source = new DOMSource(document);
		    StreamResult result = new StreamResult(file);
		    transformer.transform(source, result);
	}
	private void saveEmployee(Employee employee, Element element, Document document) {
		element.setAttribute(SEX_ATTR_NAME, employee.getSex().toString());
		element.setAttribute(AGE_ATTR_NAME, Integer.toString(employee.getAge()));
		element.setAttribute(UNFIREABLE_ATTR_NAME, Boolean.toString(employee.isUnfireable()));
		
		Text fullNameText = document.createTextNode(employee.getFullName());
		element.appendChild(fullNameText);
		
		Element position = document.createElement(POSITION_ELEMENT_NAME);
		position.setTextContent(employee.getPosition());
		element.appendChild(position);
		
		Element employmentForm = document.createElement(EMPLOYMENT_FORM_ELEMENT_NAME);
		employmentForm.setTextContent(employee.getEmploymentForm().toString());
		element.appendChild(employmentForm); 
		
		Element salary = document.createElement(SALARY_ELEMENT_NAME);
		salary.setTextContent(Integer.toString(employee.getSalary()));
		element.appendChild(salary); 
		
		Element subordinates = document.createElement(SUBORDINATES_ELEMENT_NAME);
		for(int i = 0; i < employee.getSubordinates().size(); i++) {
			Element subordinate = document.createElement(EMPLOYEE_ELEMENT_NAME);
			saveEmployee(employee.getSubordinates().get(i), subordinate, document);
			subordinates.appendChild(subordinate);
		}
		element.appendChild(subordinates); 
	}
	public void setFile(File file) {
		this.file = file;
	}
	public File getFile() {
		return file;
	}
}
