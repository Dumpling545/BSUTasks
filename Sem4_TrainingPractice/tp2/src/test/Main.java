package test;

import java.io.IOException;
import java.util.Scanner;

import javax.xml.parsers.ParserConfigurationException;

import org.xml.sax.SAXException;

import tariffs.TariffView;

public class Main {

	public static void main(String[] args) {
		TariffView tariffView;
		try {
			tariffView = new TariffView();
			Scanner sc = new Scanner(System.in);
			tariffView.printHelp();
			 while(sc.hasNext()) {
				 tariffView.executeCommand(sc.nextLine());
			 }
		} catch (NumberFormatException | ParserConfigurationException | SAXException | IOException e) {
			System.out.println("Something wrong with XML:" + e.getMessage());
		}
	}

}
