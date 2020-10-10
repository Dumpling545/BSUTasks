package tp12;

import org.xml.sax.Attributes;
import org.xml.sax.SAXException;
import org.xml.sax.helpers.DefaultHandler;

public class XmlInfromationExtractor extends DefaultHandler {
	private int minSalary;
	private int maxSalary;
	private double avgSalary;
	private int minAge;
	private int maxAge;
	private double avgAge;
	private int numberOfEmployees;
	private boolean activeElementIsSalary;
	@Override
	public void startDocument() throws SAXException {
		minSalary = Integer.MAX_VALUE;
		maxSalary = Integer.MIN_VALUE;
		avgSalary = 0;
		minAge = Integer.MAX_VALUE;
		maxAge = Integer.MIN_VALUE;
		avgAge = 0;
		numberOfEmployees = 0;
		activeElementIsSalary = false;
		super.startDocument();
	}
	@Override
	public void startElement(String uri, String localName, String qName, Attributes attributes) throws SAXException {
		if(qName.equals("employee")) {
			int age = Integer.parseInt(attributes.getValue("age"));
			avgAge += age;
			minAge = Math.min(age, minAge);
			maxAge = Math.max(age, maxAge);
			numberOfEmployees++;
		} else if(qName.equals("salary")) {
			activeElementIsSalary = true;
		}
		super.startElement(uri, localName, qName, attributes);
	}
	@Override
	public void endDocument() throws SAXException {
		avgSalary /= numberOfEmployees;
		avgAge /= numberOfEmployees;
		super.endDocument();
	}
	@Override
	public void endElement(String uri, String localName, String qName) throws SAXException {
		if(qName.equals("salary")) {
			activeElementIsSalary = false;
		}
		super.endElement(uri, localName, qName);
	}
	@Override
	public void characters(char[] ch, int start, int length) throws SAXException, NumberFormatException {
		if(activeElementIsSalary) {
			int salary = Integer.parseInt((new String(ch, start, length)).trim());
			minSalary = Math.min(minSalary, salary);
			maxSalary = Math.max(maxSalary, salary);
			avgSalary += salary;
		}
		super.characters(ch, start, length);
	}
	public int getMinSalary() {
		return minSalary;
	}
	public int getMaxSalary() {
		return maxSalary;
	}
	public double getAvgSalary() {
		return avgSalary;
	}
	public int getMinAge() {
		return minAge;
	}
	public int getMaxAge() {
		return maxAge;
	}
	public double getAvgAge() {
		return avgAge;
	}
	public int getNumberOfEmployees() {
		return numberOfEmployees;
	}
	
}
