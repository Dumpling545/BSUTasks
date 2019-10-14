package task1;

public class Source {
	public static double computeSeries(double x, double precision) throws NonPositivePrecisionException{
		if(precision <= 0) {
			throw new NonPositivePrecisionException();
		}
		double x2 = x*x;
		double element = 1;
		double sum = 0;
		int k = 1;
		do {
			element *= x2/2;
			element /= (k++);
			sum += element;
		}while(element >= precision);
		return sum;
	}
	public static void main(String[] args) throws InvalidParameterAmountException {
		try {
			if(args.length == 2) {
				double x = Double.parseDouble(args[0]);
				double precision = Double.parseDouble(args[1]);
				System.out.println("Sum = " + computeSeries(x, precision));
			} else {
				throw new InvalidParameterAmountException();
			}
		} catch(NumberFormatException ex) {
			System.out.println("Invalid parameters. Must be doubles");
		} catch(NonPositivePrecisionException ex) {
			System.out.println(ex.getMessage());
		} catch(InvalidParameterAmountException ex) {
			System.out.println(ex.getMessage());
		}
	}

}
