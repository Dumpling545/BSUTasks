package tp9;

import java.time.LocalDate;
import java.time.format.DateTimeFormatter;
import java.time.format.DateTimeFormatterBuilder;
import java.time.format.DateTimeParseException;
import java.util.ArrayList;
import java.util.List;
import java.util.NoSuchElementException;
import java.util.StringTokenizer;
import java.util.function.Function;

public class Parser {
	private final String MIN = "MIN";
	private final String MAX = "MAX";
	private final String SEPARATORS = " ";
	private final String DATE_FORMAT = "dd.MM.yyyy";
	private ExcelTableModel tableModel;
	private DateTimeFormatter parseFormatter;
	public Parser(ExcelTableModel tableModel) {
		this.tableModel = tableModel;
		parseFormatter = DateTimeFormatter.ofPattern(DATE_FORMAT);
	}
	private static LocalDate min(ValueFunctionInput input) {
		List<Node> observables = input.getObservables();
		List<LocalDate> constants = input.getConstants();
		LocalDate minimal = LocalDate.MAX;
		int counter = 0;
		for(Node observable : observables) {
			if(observable.getValue() != null) {
				counter++;
				if(minimal.isAfter(observable.getValue())) {
					minimal = observable.getValue();
				}
			}
		}
		for(LocalDate constant : constants) {
			if(minimal.isAfter(constant)) {
				minimal = constant;
			}
		}
		if(counter == 0 && constants.isEmpty()) minimal = null;
		return minimal;
	}
	private static LocalDate max(ValueFunctionInput input) {
		List<Node> observables = input.getObservables();
		List<LocalDate> constants = input.getConstants();
		LocalDate maximal = LocalDate.MIN;
		int counter = 0;
		for(Node observable : observables) {
			if(observable.getValue() != null) {
				counter++;
				if(maximal.isBefore(observable.getValue())) {
					maximal = observable.getValue();
				}
			}
		}
		for(LocalDate constant : constants) {
			if(maximal.isBefore(constant)) {
				maximal = constant;
			}
		}
		if(counter == 0 && constants.isEmpty()) maximal = null;
		return maximal;
	}
	private static LocalDate addition(ValueFunctionInput input) {
		List<Node> observables = input.getObservables();
		List<LocalDate> constants = input.getConstants();
		int numberParameter = input.getNumberParameter();
		LocalDate result = observables.isEmpty() ? constants.get(0) : observables.get(0).getValue();
		if(result != null) result = result.plusDays(numberParameter);
		return result;
	}
	public void parse(String content, Node contentOwner) throws IndexOutOfBoundsException, NumberFormatException, NoSuchElementException, DateTimeParseException, InvalidOperationException, TooFewArgumentsException, NoSuchColumnException {
		if(content != null) {
			content = content.strip();
			StringTokenizer tokenizer;
			List<Node> observables = new ArrayList<Node>();
			List<LocalDate> constants = new ArrayList<LocalDate>();
			Function<ValueFunctionInput, LocalDate> valueFunction;
			int numberParameter = 0;
			if(content.startsWith(MIN)) {
				tokenizer = new StringTokenizer(content.substring(MIN.length()), SEPARATORS);
				if(!tokenizer.hasMoreTokens()) {
					throw new TooFewArgumentsException();
				}
				while(tokenizer.hasMoreTokens()) {
					String token = tokenizer.nextToken();
					if(token.contains(".")) {
						constants.add(LocalDate.parse(token, parseFormatter));
					} else {
						observables.add(parseAsNode(token));
					}
				}
				valueFunction = Parser::min;
			} else if(content.startsWith(MAX)) {
				tokenizer = new StringTokenizer(content.substring(MAX.length()), SEPARATORS);
				if(!tokenizer.hasMoreTokens()) {
					throw new TooFewArgumentsException();
				}
				while(tokenizer.hasMoreTokens()) {
					String token = tokenizer.nextToken();
					if(token.contains(".")) {
						constants.add(LocalDate.parse(token, parseFormatter));
					} else {
						observables.add(parseAsNode(token));
					}
				}
				valueFunction = Parser::max;
			} else {
				String s;
				if(content.contains(".")) {
					constants.add(LocalDate.parse(content.substring(0, DATE_FORMAT.length()), 
																	parseFormatter));
					s = content.substring(DATE_FORMAT.length()).strip();
				} else {
					int endIndex  = 0;
					for(; endIndex < content.length(); endIndex++) {
						if(content.charAt(endIndex) == ' ' 
								|| content.charAt(endIndex) == '+' 
								|| content.charAt(endIndex) == '-') {
							break;
						}
					}
					observables.add(parseAsNode(content.substring(0, endIndex)));
					s = content.substring(endIndex).strip();
				}
				if(!s.isEmpty()) {
					if(s.charAt(0) == '+') {
						numberParameter = Integer.parseInt(s.substring(1).strip());
					} else if(s.charAt(0) == '-') {
						numberParameter = -Integer.parseInt(s.substring(1).strip());
					} else {
						throw new InvalidOperationException();
					}
				}
				valueFunction = Parser::addition;
			}
			contentOwner.setObservables(observables);
			contentOwner.setConstants(constants);
			contentOwner.setNumberParameter(numberParameter);
			contentOwner.setValueFunction(valueFunction);
		}
	}
	private Node parseAsNode(String token) throws IndexOutOfBoundsException, NumberFormatException, NoSuchColumnException {
		int digitStart = 0;
		for(; digitStart < token.length(); digitStart++) {
			if(Character.isDigit(token.charAt(digitStart))) break;
		}
		int columnIndex = tableModel.findColumn(token.substring(0, digitStart));
		int rowIndex = Integer.parseInt(token.substring(digitStart, token.length()));
		if(columnIndex == -1) throw new NoSuchColumnException(token.substring(0, digitStart));
		return (Node) tableModel.getValueAt(rowIndex, columnIndex);
	}
}
