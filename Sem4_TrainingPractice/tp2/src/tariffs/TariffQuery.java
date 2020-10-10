package tariffs;

import java.util.NoSuchElementException;
import java.util.StringTokenizer;

public class TariffQuery {
	private enum TariffType{
		PHONE_CALL_TARIFF("PHONECALL"),
		SMS_TARIFF("SMS"),
		INTERNET_TARIFF("INTERNET");
		private String name;
		 
		TariffType(String name) {
	        this.name = name;
	    }
		public String getName() {
	        return name;
	    }
	};
	private TariffType type;
	private int [][] parameters;
	public TariffQuery(String query) throws NoSuchElementException, NullPointerException, InvalidQueryException{
		StringTokenizer st = new StringTokenizer(query);
		String header = st.nextToken();
		for(TariffType tt : TariffType.values())
		{
		    if(tt.getName().equals(header)) {
		    	type = tt;
		    }
		}
		switch(type) {
			case PHONE_CALL_TARIFF:
				parameters = new int[2][2];
				if(st.nextToken().equals("WITHIN-NETWORK-MINUTES")) {
					String str = st.nextToken();
					if(str.equals("FROM")) {
						parameters[0][0] = Integer.parseInt(st.nextToken());
						String word = st.nextToken();
						if(word.equals("TO")) {
							parameters[0][1] = Integer.parseInt(st.nextToken());
						} else {
							throw new InvalidQueryException();
						}
					} else {
						throw new InvalidQueryException();
					}
					if(st.nextToken().equals("ALL-NETWORKS-MINUTES")) {
						str = st.nextToken();
						if(str.equals("FROM")) {
							parameters[1][0] = Integer.parseInt(st.nextToken());
							String word = st.nextToken();
							if(word.equals("TO")) {
								parameters[1][1] = Integer.parseInt(st.nextToken());
							} else {
								throw new InvalidQueryException();
							}
						} else {
							throw new InvalidQueryException();
						}
					} else {
						throw new InvalidQueryException();
					}
				} else {
					throw new InvalidQueryException();
				}
				break;
			case SMS_TARIFF:
				parameters = new int[1][2];
				if(st.nextToken().equals("MESSAGES")) {
					String str = st.nextToken();
					if(str.equals("FROM")) {
						parameters[0][0] = Integer.parseInt(st.nextToken());
						String word = st.nextToken();
						if(word.equals("TO")) {
							parameters[0][1] = Integer.parseInt(st.nextToken());
						} else {
							throw new InvalidQueryException();
						}
					} else {
						throw new InvalidQueryException();
					}
				} else {
					throw new InvalidQueryException();
				}
				break;
			case INTERNET_TARIFF:
				parameters = new int[1][2];
				if(st.nextToken().equals("MBS")) {
					String str = st.nextToken();
					if(str.equals("FROM")) {
						parameters[0][0] = Integer.parseInt(st.nextToken());
						String word = st.nextToken();
						if(word.equals("TO")) {
							parameters[0][1] = Integer.parseInt(st.nextToken());
						} else {
							throw new InvalidQueryException();
						}
					} else {
						throw new InvalidQueryException();
					}
				} else {
					throw new InvalidQueryException();
				}
				break;
		}
	}
	boolean match(BaseTariff tariff){
		boolean result = false;
		switch(type) {
			case PHONE_CALL_TARIFF:
				if(tariff instanceof PhoneCallTariff) {
					PhoneCallTariff pct = (PhoneCallTariff) tariff;
					result = (pct.withinNetworkNumberOfMinutes >= parameters[0][0]) && 
							(pct.withinNetworkNumberOfMinutes <= parameters[0][1]) &&
							(pct.allNetworksNumberOfMinutes >= parameters[1][0]) &&
							(pct.allNetworksNumberOfMinutes <= parameters[1][1]);
				}
				break;
			case SMS_TARIFF:
				if(tariff instanceof SMSTariff) {
					SMSTariff smst = (SMSTariff) tariff;
					result = (smst.numberOfMessages >= parameters[0][0]) && 
							(smst.numberOfMessages <= parameters[0][1]);
				}
				break;
			case INTERNET_TARIFF:
				if(tariff instanceof InternetTariff) {
					InternetTariff nett = (InternetTariff) tariff;
					result = (nett.numberOfMBs >= parameters[0][0]) && 
							(nett.numberOfMBs <= parameters[0][1]);
				}
				break;
		}
		return result;
	}
}
