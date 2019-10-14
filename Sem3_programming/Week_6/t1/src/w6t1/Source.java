package w6t1;

import java.util.StringTokenizer;

public class Source {
	public static int compute(String expr) {
		if(contai(expr.charAt(expr.length()-1))) {
			
		}
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
					result += sign*Integer.parseInt(s);
					break;
			}
			if(signCounter > 1) {
				throw new RuntimeException("Two or more signs in a row are not allowed!");
			}
		}
		return result;
	}
	public static void main(String[] args) {
		for(int i = 0; i < args.length; i++) {
			System.out.print(args[i]);
			System.out.print(" = ");
			System.out.println(compute(args[i]));
		}

	}

}
