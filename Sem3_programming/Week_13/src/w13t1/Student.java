package w13t1;

import java.util.NoSuchElementException;
import java.util.StringTokenizer;

public class Student {

	private int id;
	private String surname;
	private int year;
	private int group;
	protected final static int MINIMAL_YEAR = 1;
	protected final static int MAXIMAL_YEAR = 6;
	protected final static int MINIMAL_GROUP = 1;
	protected final static int MINIMAL_ID = 0;
	
	public Student(int id, String surname, int year, int group) throws NumberFormatException{
		this.id = id;
		this.surname = surname;
		this.year = year;
		this.group = group;
		if(!isCorrect()) {
			throw new NumberFormatException();
		}
	}
	public Student(String src) throws NoSuchElementException, NullPointerException, NumberFormatException{
		StringTokenizer st = new StringTokenizer(src);
		this.id = Integer.parseInt(st.nextToken());
		this.surname = st.nextToken();
		this.year = Short.parseShort(st.nextToken());
		this.group = Short.parseShort(st.nextToken());
		if(!isCorrect()) {
			throw new NumberFormatException();
		}
	}
	
	private boolean isCorrect() {
		return !(year < MINIMAL_YEAR || year > MAXIMAL_YEAR ||
				group < MINIMAL_GROUP || id < MINIMAL_ID);
	}
	
	@Override
	public String toString() {
		return "Номер зачётки: " + id + ", Фамилия: " + surname + ", курс: " + year + ", группа: " + group;
	}

	public int getId() {
		return id;
	}

	public void setId(int id) {
		this.id = id;
	}

	public String getSurname() {
		return surname;
	}

	public void setSurname(String surname) {
		this.surname = surname;
	}

	public int getYear() {
		return year;
	}

	public void setYear(int year) {
		this.year = year;
	}

	public int getGroup() {
		return group;
	}

	public void setGroup(int group) {
		this.group = group;
	}
}
