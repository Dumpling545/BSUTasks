package tp4_3;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;

import org.jfree.data.general.DefaultPieDataset;
import org.jfree.data.general.PieDataset;

import com.google.gson.Gson;
import com.google.gson.JsonIOException;
import com.google.gson.JsonSyntaxException;
import com.google.gson.stream.JsonReader;

public class Data {
	private String title;
	private String[] names;
	private double[] values;
	public Data(File file) throws FileNotFoundException, InvalidDataException, JsonSyntaxException, JsonIOException {
		Gson gson = new Gson();
		JsonReader reader = new JsonReader(new FileReader(file));
		Data parsedData = gson.fromJson(reader, Data.class);
		if(parsedData.title == null || parsedData.names == null || parsedData.values == null || 
				parsedData.names.length == 0 || parsedData.names.length != parsedData.values.length) {
			throw new InvalidDataException();
		} else {
			title = parsedData.title;
			names = parsedData.names;
			values = parsedData.values;
		}
	}
	public PieDataset createDataset() {
		DefaultPieDataset dataset = new DefaultPieDataset( );
		for(int i = 0; i < names.length; i++) {
			dataset.setValue(names[i], values[i]);
		}
		return dataset;
	}
	public String getTitle() {
		return title;
	}
	public String[] getNames() {
		return names;
	}
	public double[] getValues() {
		return values;
	}
}
