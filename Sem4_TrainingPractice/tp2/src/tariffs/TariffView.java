package tariffs;

import java.io.IOException;
import java.util.List;
import java.util.NoSuchElementException;

import javax.xml.parsers.ParserConfigurationException;

import org.xml.sax.SAXException;

public class TariffView {
	TariffManager manager;
	public TariffView() throws NumberFormatException, ParserConfigurationException, SAXException, IOException {
		manager = new TariffManager("tariffs.xml");
	}
	public void printHelp() {
		System.out.println("----------------------------------------HELP------------------------------------------------");
		System.out.println("\nWithout parameters:\n");
		System.out.println("HELP -- print these hints again");
		System.out.println("SUBSCRIBERS -- get number of subscribers");
		System.out.println("GET SORTED -- print sorted by regular payment tarrifs");
		System.out.println("GET -- print in default order");
		System.out.println("\n\nWith parameters:\n");
		System.out.println("SMS MESSAGES FROM 100 TO 200 -- get sms tarrifs with m messages, where m in [100; 200]");
		System.out.println("INTERNET MBS FROM 100 TO 200 -- get internet tarrifs with m megabytes, where m in [100; 200]");
		System.out.println("PHONECALL WITHIN-NETWORK-MINUTES FROM 100 TO 200 ALL-NETWORKS-MINUTES FROM 50 TO 90");
		System.out.println("-- get phone call tarrifs with m minites wihin network and n minutes to all networks,");
		System.out.println("where m in [100; 200], n in [50; 90]\n");
		System.out.println("--------------------------------------------------------------------------------------------");
	}
	public void executeCommand(String str) {
		if(str.equals("HELP")) {
			printHelp();
		}else if(str.equals("SUBSCRIBERS")) {
			System.out.println(manager.getNumberOfSubscribers());
		} else if(str.equals("GET SORTED")) {
			List<BaseTariff> tariffs = manager.getSortedByPaymentTariffList();
			for(BaseTariff tariff : tariffs) {
				System.out.println(tariff.toString());
			}
		}  else if(str.equals("GET")) {
			List<BaseTariff> tariffs = manager.getTariffs();
			for(BaseTariff tariff : tariffs) {
				System.out.println(tariff.toString());
			}
		}else {
			try {
				TariffQuery tariffQuery = new TariffQuery(str);
				List<BaseTariff> tariffs = manager.getTariffs(tariffQuery);
				for(BaseTariff tariff : tariffs) {
					System.out.println(tariff.toString());
				}
			} catch(NoSuchElementException|NullPointerException|InvalidQueryException ex) {
				System.out.print("\nException: ");
				System.out.print(ex.getMessage());
			}
		}
	}
}
