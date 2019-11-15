package w9t1;

import java.io.FileWriter;
import java.io.IOException;

public abstract class Sequence {
	protected int n;
	protected double first, coefficient;
	public double getFirst() {
		return first;
	}
	public void setFirst(double first) {
		this.first = first;
	}
	public double getCoefficient() {
		return coefficient;
	}
	public void setCoefficient(double coefficient) {
		this.coefficient = coefficient;
	}

	public Sequence(int n, double first, double coefficient) throws SequenceOutOfBoundsException{
		if(n <= 0) throw new SequenceOutOfBoundsException();
		this.n = n;
		this.first = first;
		this.coefficient = coefficient;
	}
	@Override
	public String toString() {
		StringBuffer sb = new StringBuffer();
		for(int i = 1; i <= n - 1; i++) {
			sb.append(element(i));
			sb.append(",  ");
		}
		sb.append(element(n));
		return sb.toString();
	}
	public void save(String savePath) throws IOException {
		FileWriter fw = new FileWriter(savePath);
		fw.write(toString());
		fw.close();
	}
	public abstract double element(int index) throws SequenceOutOfBoundsException;
	public double sum() {
		double sum = 0;
		for(int i = 1; i <= n; i++) {
			sum += element(i);
		}
		return sum;
	}
	public int getN() {
		return n;
	}

	public void setN(int n) throws SequenceOutOfBoundsException{
		if(n <= 0) throw new SequenceOutOfBoundsException();
		this.n = n;
	} 
}
