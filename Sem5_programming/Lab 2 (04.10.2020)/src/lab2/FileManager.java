package lab2;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.util.List;

public class FileManager {
	private SaveState state;
	private File currentFile;
	public SaveState getState() {
		return state;
	}
	public FileManager() {
		state = SaveState.SAVED_OR_SAVE_CAN_BE_IGNORED;
	}
	public void save(List<Product> products) throws NullPointerException, FileNotFoundException, IOException{
		save(currentFile, products);
	}
	public void save(File file, List<Product> products) throws NullPointerException, FileNotFoundException, IOException{
		ObjectOutputStream stream = new ObjectOutputStream(new FileOutputStream(file));
		stream.writeObject(products);
		stream.close();
		state = SaveState.SAVED_OR_SAVE_CAN_BE_IGNORED;
		currentFile = file;
	}
	public List<Product> open(File file) throws NullPointerException, FileNotFoundException, IOException, ClassNotFoundException{
		ObjectInputStream stream = new ObjectInputStream(new FileInputStream(file));
		List<Product> result = (List<Product>) stream.readObject();
		stream.close();
		currentFile = file;
		state = SaveState.SAVED_OR_SAVE_CAN_BE_IGNORED;
		return result;
	}
	public boolean hasCurrentFile() {
		return currentFile!=null;
	}
	public void notifyUpdate() {
		state = SaveState.NOT_SAVED;
	}
	public void ignoreSaving() {
		state = SaveState.SAVED_OR_SAVE_CAN_BE_IGNORED;
	}
	
}
 