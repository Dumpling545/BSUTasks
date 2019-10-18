package w6t1;

import java.util.StringTokenizer;

public class Source {
	public static int compute(String expr) throws NotEnoughOperandsException, InvalidExpressionException{
		StringTokenizer tokenizer = new StringTokenizer(expr, "+-", true);
		int result = 0;
		int sign = 1;
		short signCounter = 0;
		while(tokenizer.hasMoreTokens()) {
			String s = tokenizer.nextToken();
			switch(s.charAt(0)) {
				case '+':
					sign = 1;
					signCounter++;
					break;
				case '-':
					sign = -1;
					signCounter++;
					break;
				default:
					signCounter = 0;
					try {
						result += sign*Integer.parseInt(s);
					}catch(NumberFormatException ex) {
						throw new InvalidExpressionException(expr);
					}
					break;
			}
			if(signCounter > 1) {
				throw new NotEnoughOperandsException(expr);
			}
		} 
		if(signCounter != 0) {
			throw new NotEnoughOperandsException(expr);
		}
		return result;
	}
	public static void main(String[] args) {
		try {
			for(int i = 0; i < args.length; i++) {
				int res = compute(args[i]);
				System.out.print(args[i]);
				System.out.print(" = ");
				System.out.println(res);
			}
		} catch(NotEnoughOperandsException ex) {
			System.out.println(ex.getMessage());
		} catch(InvalidExpressionException ex) {
			System.out.println(ex.getMessage());
		}
	}

}
