import java.util.ArrayList;

public class BinaryTree<T extends Comparable<T>>
{
	class Node{
		protected Node left, right;
		Node(T value){
			this.value = value;
		}
		T value;
	};
	public enum TraverseOrder{
		NLR, LNR, LRN;		
	};
	public void add(T addvalue){
		if(root != null) {
			root = add(addvalue, root);
		} else {
			root = new Node(addvalue);
		}
	}
	
	private Node add(T value, Node parent){
		if(value.compareTo(parent.value) < 0) {
			if(parent.left == null) {
				parent.left = new Node(value);
			} else {
				parent.left = add(value, parent.left);
			}
		} else if(value.compareTo(parent.value) > 0){
			if(parent.right == null) {
				parent.right = new Node(value);
			} else {
				parent.right = add(value, parent.right);
			}
		}
		return parent;
	}
	
	public boolean contains(T value) {
		boolean result = false;
		if(root != null) { 
			result = contains(value, root);
		}
		return result; 
	}
	public ArrayList<T> traverse(TraverseOrder order) {
		ArrayList<T> result = new ArrayList<T>();
		if(order == TraverseOrder.NLR) {
			result = nlr(root);
		} else if(order == TraverseOrder.LNR) {
			result = lnr(root);
		} else {
			result = lrn(root);
		}
		return result;
		
	}
	private ArrayList<T> nlr(Node parent) {
		ArrayList<T> result = new ArrayList<T>();
		if(parent != null) {
			result.add(parent.value);
			result.addAll(nlr(parent.left));
			result.addAll(nlr(parent.right));
		}
		return result;
	}
	private ArrayList<T> lnr(Node parent) {
		ArrayList<T> result = new ArrayList<T>();
		if(parent != null) {
			result.addAll(lnr(parent.left));
			result.add(parent.value);
			result.addAll(lnr(parent.right));
		}
		return result;
	}
	private ArrayList<T> lrn(Node parent) {
		ArrayList<T> result = new ArrayList<T>();
		if(parent != null) {
			result.addAll(lrn(parent.left));
			result.addAll(lrn(parent.right));
			result.add(parent.value);
		}
		return result;
	}
	private boolean contains(T value, Node parent) {
		boolean result = false;
		if(value.compareTo(parent.value) < 0 && parent.left != null) {
			result = contains(value, parent.left);
		} else if(value.compareTo(parent.value) > 0 && parent.right != null) {
			result = contains(value, parent.right);
		} else {
			result = value.compareTo(parent.value) == 0;
		}
		return result;
	}
	
	private Node root;
};
