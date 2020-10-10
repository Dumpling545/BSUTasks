package tp12;

import java.io.Serializable;
import java.util.HashMap;
import java.util.Map;

public enum EmploymentForm {
	FULL_TIME("full-time"), 
    PART_TIME("part-time"),
    TEMPORARY("temporary");
    private String form;
    EmploymentForm(String form) {
        this.form = form;
    }
    public String toString() {
        return form;
    }
    private static final Map<String, EmploymentForm> lookup = new HashMap<>();
    static
    {
        for(EmploymentForm ef : EmploymentForm.values())
        {
            lookup.put(ef.toString(), ef);
        }
    }
      public static EmploymentForm get(String ef) 
    {
        return lookup.get(ef);
    }
}
