package tariffs;

public class SMSTariff extends BaseTariff {
	protected int numberOfMessages;

	public int getNumberOfMessages() {
		return numberOfMessages;
	}
	@Override
	public String toString() {
		StringBuilder sb = new StringBuilder(super.toString());
		sb.append("\n Number of Messages: ");
		sb.append(numberOfMessages);
		return  sb.toString();
	}
}
