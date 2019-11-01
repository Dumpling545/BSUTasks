import java.util.ArrayList;
import java.util.Arrays;
import java.util.Scanner;
import java.util.StringTokenizer;

public class Source {

	public static void printPlain(ArrayList al) {
		for(Object obj : al) {
			System.out.print(obj);
			System.out.print(";   ");
		}
		System.out.print('\n');
	}
	public static void main(String[] args) {
		BinaryTree<ComplexNumber> cntree = new BinaryTree<ComplexNumber>();
		BinaryTree<Integer> itree = new BinaryTree<Integer>();
		BinaryTree tree = cntree;
		System.out.println("LIST OF COMMANDS:");
		System.out.println("CNTREE -- switch to complex number tree(default)");
		System.out.println("INTTREE -- switch to integer tree");
		System.out.println("ADD {ELEM} -- add complex number to binary tree");
		System.out.println("CONTAINS {ELEM} -- check if complex number is in binary tree");
		System.out.println("NLR -- print NLR-traversal of binary tree");
		System.out.println("LNR -- print LNR-traversal of binary tree");
		System.out.println("LRN -- print LRN-traversal of binary tree");
		System.out.println("END -- end programm");
		System.out.println("Impotant note: {ELEM} = {INTEGER} for integer tree");
		System.out.println("{ELEM} = {RE} {IM} for complex number tree");
		System.out.println("One more important note: complex numbers are compared by absolute value");
		System.out.println("So numbers -1 - i and 1 + i are equal (in this sense of 'equal')");
		Scanner scanner = new Scanner(System.in);
		String command = null;
		StringTokenizer tokenizer;
		ComplexNumber cn;
		boolean cnmode = true;
		while(!"END".equals(command)){
			try {
				System.out.print(">");
				command = scanner.nextLine();
				if("END".equals(command)) break;
				else if("CNTREE".equals(command)) {
					cnmode = true;
					tree = cntree;
				}else if("INTTREE".equals(command)) {
					cnmode = false;
					tree = itree;
				}else if("NLR".equals(command)) {
					printPlain(tree.traverse(BinaryTree.TraverseOrder.NLR));
				} else if("LNR".equals(command)) {
					printPlain(tree.traverse(BinaryTree.TraverseOrder.LNR));
				} else if("LRN".equals(command)) {
					printPlain(tree.traverse(BinaryTree.TraverseOrder.LRN));
				} else {
					tokenizer = new StringTokenizer(command);
					if(cnmode) {
						cn = new ComplexNumber();
						if(tokenizer.countTokens() != 3) {
							throw new RuntimeException();
						} else {
							command = tokenizer.nextToken();
							if("ADD".equals(command)) {
								cn.setReal(Double.parseDouble(tokenizer.nextToken()));
								cn.setImaginary(Double.parseDouble(tokenizer.nextToken()));
								tree.add(cn);
							} else if("CONTAINS".equals(command)) {
								cn.setReal(Double.parseDouble(tokenizer.nextToken()));
								cn.setImaginary(Double.parseDouble(tokenizer.nextToken()));
								System.out.println(tree.contains(cn));
							} else {
								throw new RuntimeException();
							}
						}
					} else {
						int i;
						if(tokenizer.countTokens() != 2) {
							throw new RuntimeException();
						} else {
							command = tokenizer.nextToken();
							if("ADD".equals(command)) {
								i = Integer.parseInt(tokenizer.nextToken());
								tree.add(i);
							} else if("CONTAINS".equals(command)) {
								i = Integer.parseInt(tokenizer.nextToken());
								System.out.println(tree.contains(i));
							} else {
								throw new RuntimeException();
							}
						}
					}
				}
			} catch(RuntimeException ex) {
				System.out.println("Invalid Command. Retry: ");
			}
		}
		scanner.close();
	}

}
