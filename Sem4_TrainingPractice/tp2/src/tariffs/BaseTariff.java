package tariffs;

public abstract class BaseTariff {
	protected String name;
	protected int regularPayment;
	protected int numberOfSubscribers;
	public int getRegularPayment() {
		return regularPayment;
	}
	public int getNumberOfSubscribers() {
		return numberOfSubscribers;
	}
	public String getName() {
		return name;
	}
	
	@Override
	public String toString() {
		StringBuilder sb = new StringBuilder("Tariff:\n Name: ");
		sb.append(name);
		sb.append("\n Regular payment: ");
		sb.append(regularPayment);
		sb.append("\n Number of subscribers: ");
		sb.append(numberOfSubscribers);
		return  sb.toString();
	}
}
