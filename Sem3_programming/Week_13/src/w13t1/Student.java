package w13t1;

import java.util.NoSuchElementException;
import java.util.StringTokenizer;

public class Student implements Comparable<Student>{
	private int id;
	private String surname;
	private short year;
	private short group;
	private final int MINIMAL_YEAR = 1;
	private final int MAXIMAL_YEAR = 6;
	private final int MINIMAL_GROUP = 1;
	private final int MINIMAL_ID = 0;
	
	public Student(String src) throws NoSuchElementException, NullPointerException, NumberFormatException{
		StringTokenizer st = new StringTokenizer(src);
		this.id = Integer.parseInt(st.nextToken());
		this.surname = st.nextToken();
		this.year = Short.parseShort(st.nextToken());
		this.group = Short.parseShort(st.nextToken());
		if(year < MINIMAL_YEAR || year > MAXIMAL_YEAR ||
				group < MINIMAL_GROUP || id < MINIMAL_ID) {
			throw new NumberFormatException();
		}
	}

	@Override
	public String toString() {
		return "Номер зачётки: " + id + ", Фамилия: " + surname + ", курс: " + year + ", группа: " + group;
	}

	@Override
	public int compareTo(Student s) {
		int result = group - s.group;
		if(result == 0) result = surname.compareTo(s.surname);
		return result;
	}
}
