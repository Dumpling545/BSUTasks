package w9t1;

public class GeometricSequence extends Sequence {

	public GeometricSequence(int n, double first, double coefficient) throws SequenceOutOfBoundsException{
		super(n, first, coefficient);
	}

	@Override
	public double element(int index) throws SequenceOutOfBoundsException{
		if(index <= 0) throw new SequenceOutOfBoundsException();
		double result = first;
		for(int i = 2; i <= index; i++) {
			result *= coefficient;
		}
		return result;
	}

}
