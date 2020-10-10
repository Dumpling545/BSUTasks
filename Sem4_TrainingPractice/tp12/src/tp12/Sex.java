package tp12;

import java.util.HashMap;
import java.util.Map;

public enum Sex{
	FEMALE("female"), 
    MALE("male");
    private String sex;
    Sex(String sex) {
        this.sex = sex;
    }
    public String toString() {
        return sex;
    }
    private static final Map<String, Sex> lookup = new HashMap<>();
    static
    {
        for(Sex sx : Sex.values())
        {
            lookup.put(sx.toString(), sx);
        }
    }
      public static Sex get(String sex) 
    {
        return lookup.get(sex);
    }
};