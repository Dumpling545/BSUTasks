public class ComplexNumber implements Comparable<ComplexNumber> {
	private double real;
	private double imaginary;
	@Override
	public int compareTo(ComplexNumber o) {
		int result;
		double sqrabs1 = this.squaredAbs();
		double sqrabs2 = o.squaredAbs();
		/*
		 * if(sqrabs1 < sqrabs2) { result = -1; } else if(sqrabs1 == sqrabs2) { result =
		 * 0; } else { result = 1; } return result;
		 */
		return Double.compare(sqrabs1, sqrabs2);
	}
	public double squaredAbs() {
		return real*real + imaginary*imaginary;
	}
	public double getReal() {
		return real;
	}
	@Override
	public String toString() {
		String s;
		if(imaginary < 0) {
			s = String.format("%s - %s*i", real, -imaginary);
		} else {
			s = String.format("%s + %s*i", real, imaginary);
		}
		return s;
	}
	public void setReal(double real) {
		this.real = real;
	}
	public double getImaginary() {
		return imaginary;
	}
	public void setImaginary(double imaginary) {
		this.imaginary = imaginary;
	}

}
