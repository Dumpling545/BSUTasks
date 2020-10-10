package tariffs;

import java.io.IOException;
import java.util.ArrayList;
import java.util.List;
import java.util.NoSuchElementException;
import java.util.stream.Collectors;

import javax.xml.parsers.ParserConfigurationException;

import org.xml.sax.SAXException;

public class TariffManager {
	private List<BaseTariff> tariffs;
	public TariffManager(String source) throws NumberFormatException, ParserConfigurationException, SAXException, IOException {
		tariffs = new ArrayList<BaseTariff>();
		tariffs.addAll(XmlManager.read(source));
	}
	int getNumberOfSubscribers() {
		return tariffs.stream().mapToInt(BaseTariff::getNumberOfSubscribers).sum();
	}
	List<BaseTariff> getSortedByPaymentTariffList(){
		return tariffs.stream().sorted((a,b) -> {return a.regularPayment - b.regularPayment;}).collect(Collectors.toList());
	}
	List<BaseTariff> getTariffs(){
		List<BaseTariff> res = new ArrayList<BaseTariff>(tariffs);
		return res;
	}
	List<BaseTariff> getTariffs(TariffQuery tariffQuery){
		return tariffs.stream().filter(t -> {return tariffQuery.match(t);}).collect(Collectors.toList());
	}
}
