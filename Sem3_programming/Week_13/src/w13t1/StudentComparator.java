package w13t1;

import java.util.Comparator;

public class StudentComparator implements Comparator<Student> {

	public StudentComparator() {}
	@Override
	public int compare(Student s1, Student s2) {
		if(s1.getId() == s2.getId()) {
			return 0;
		}else if(s1.getGroup() - s2.getGroup() != 0) {
			return s1.getGroup() - s2.getGroup();
		} else if(s1.getSurname().compareTo(s2.getSurname()) != 0){
			return s1.getSurname().compareTo(s2.getSurname());
		}
		//Люди из одной группы с одинаковыми фамилиями не обязательно один и тот же человек?
		return s1.getId() - s2.getId();
	}

}
