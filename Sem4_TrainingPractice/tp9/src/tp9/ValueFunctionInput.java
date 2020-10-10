package tp9;

import java.time.LocalDate;
import java.util.List;

class ValueFunctionInput{
	private List<Node> observables;
	private List<LocalDate> constants;
	private int numberParameter;
	public ValueFunctionInput(List<Node> observables, List<LocalDate> constants, int numberParameter) {
		this.observables = observables;
		this.constants = constants;
		this.numberParameter = numberParameter;
	}
	public List<Node> getObservables() {
		return observables;
	}
	public List<LocalDate> getConstants() {
		return constants;
	}
	public int getNumberParameter() {
		return numberParameter;
	}
}