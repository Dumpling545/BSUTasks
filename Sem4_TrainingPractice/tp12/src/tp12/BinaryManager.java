package tp12;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;

public class BinaryManager extends DataIOManager{
	public BinaryManager() {} 
	@Override
	public Employee read() throws NullPointerException, FileNotFoundException, IOException, ClassNotFoundException {
		FileInputStream fileIn = new FileInputStream(file);
        ObjectInputStream in = new ObjectInputStream(fileIn);
        Employee employee = (Employee) in.readObject();
        in.close();
        fileIn.close();
		return employee;
	}
	
	@Override
	public void save(Employee director) throws NullPointerException, FileNotFoundException, IOException{
		FileOutputStream fileOut = new FileOutputStream(file);
		ObjectOutputStream out = new ObjectOutputStream(fileOut);
		out.writeObject(director);
		out.close();
		fileOut.close();
	}
}
