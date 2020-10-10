package tp12;

import java.io.Serializable;
import java.util.ArrayList;
import java.util.List;

public class Employee implements Serializable{
	private String fullName;
	private Sex sex;
	private int age;
	private boolean unfireable;
	private String position;
	private EmploymentForm employmentForm;
	private int salary;
	private List<Employee> subordinates;
	public Employee() {
		subordinates = new ArrayList<Employee>();
	}
	public String getFullName() {
		return fullName;
	}
	public Sex getSex() {
		return sex;
	}
	public int getAge() {
		return age;
	}
	public boolean isUnfireable() {
		return unfireable;
	}
	public String getPosition() {
		return position;
	}
	public EmploymentForm getEmploymentForm() {
		return employmentForm;
	}
	public int getSalary() {
		return salary;
	}
	public List<Employee> getSubordinates() {
		return subordinates;
	}
	public void setFullName(String fullName) {
		this.fullName = fullName;
	}
	public void setSex(Sex sex) {
		this.sex = sex;
	}
	public void setAge(int age) {
		this.age = age;
	}
	public void setUnfireable(boolean unfireable) {
		this.unfireable = unfireable;
	}
	public void setPosition(String position) {
		this.position = position;
	}
	public void setEmploymentForm(EmploymentForm employmentForm) {
		this.employmentForm = employmentForm;
	}
	public void setSalary(int salary) {
		this.salary = salary;
	}
	public void addSubordinate(Employee employee) {
		subordinates.add(employee);
	}
	public void removeSubordinate(Employee employee) {
		subordinates.remove(employee);
	}
	@Override
	public String toString() {
		return fullName + " : " + position;
	}
	
}
