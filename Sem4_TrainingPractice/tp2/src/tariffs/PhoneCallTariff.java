package tariffs;

public class PhoneCallTariff extends BaseTariff {
	protected int withinNetworkNumberOfMinutes;
	protected int allNetworksNumberOfMinutes;
	public int getWithinNetworkNumberOfMinutes() {
		return withinNetworkNumberOfMinutes;
	}
	public int getAllNetworksNumberOfMinutes() {
		return allNetworksNumberOfMinutes;
	}
	@Override
	public String toString() {
		StringBuilder sb = new StringBuilder(super.toString());
		sb.append("\n Number of minutes within network: ");
		sb.append(withinNetworkNumberOfMinutes);
		sb.append("\n Number of minutes to all networks: ");
		sb.append(allNetworksNumberOfMinutes);
		return  sb.toString();
	}
}
