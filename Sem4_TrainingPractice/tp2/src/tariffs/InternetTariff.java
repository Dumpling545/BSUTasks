package tariffs;

public class InternetTariff extends BaseTariff {
	protected int numberOfMBs;

	public int getNumberOfMBs() {
		return numberOfMBs;
	}
	@Override
	public String toString() {
		StringBuilder sb = new StringBuilder(super.toString());
		sb.append("\n Number of MBs: ");
		sb.append(numberOfMBs);
		return  sb.toString();
	}
}
