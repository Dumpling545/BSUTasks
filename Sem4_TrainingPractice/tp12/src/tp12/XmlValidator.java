package tp12;

import java.io.File;
import java.io.IOException;

import javax.xml.transform.stream.StreamSource;
import javax.xml.validation.Schema;
import javax.xml.validation.SchemaFactory;

import org.xml.sax.SAXException;

public class XmlValidator {
	private Schema schema;
	public XmlValidator() throws SAXException {
		SchemaFactory factory = SchemaFactory.newInstance("http://www.w3.org/2001/XMLSchema");
        schema = factory.newSchema(getClass().getResource("schema.xsd"));
	}
	public String validate(File file) {
		try {
			schema.newValidator().validate(new StreamSource(file));
		} catch (Exception e) {
			return e.getMessage();
		} 
		return "XML File is valid";
	}
}
