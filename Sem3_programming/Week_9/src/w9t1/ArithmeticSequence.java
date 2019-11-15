package w9t1;

public class ArithmeticSequence extends Sequence {

	public ArithmeticSequence(int n, double first, double coefficient) throws SequenceOutOfBoundsException{
		super(n, first, coefficient);
	}

	@Override
	public double element(int index)  throws SequenceOutOfBoundsException{
		if(index <= 0) throw new SequenceOutOfBoundsException();
		return first + coefficient*(index - 1);
	}

	@Override
	public double sum() {
		return 0.5*n*(first + element(n));
	}

}
