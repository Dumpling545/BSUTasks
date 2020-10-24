package lab2;

import java.io.Serializable;

public class Product implements Serializable{
	private String name;
	private int quantity;
	public Product(String name, int quantity) {
		this.name = name;
		this.quantity = quantity;
	}
	public String getName() {
		return name;
	}
	public int getQuantity() {
		return quantity;
	}
	public void setQuantity(int quantity) {
		this.quantity = quantity;
	}
	
}
