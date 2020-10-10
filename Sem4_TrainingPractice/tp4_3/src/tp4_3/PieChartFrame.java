package tp4_3;

import java.io.File;
import java.io.FileNotFoundException;

import javax.swing.JFileChooser;
import javax.swing.JFrame;
import javax.swing.JOptionPane;
import javax.swing.JPanel;

import org.jfree.chart.ChartFactory;
import org.jfree.chart.ChartPanel;
import org.jfree.chart.JFreeChart;

import com.google.gson.JsonIOException;
import com.google.gson.JsonSyntaxException;

public class PieChartFrame extends JFrame {
	private Data data;
	private final static String DEFAULT_FILE_SOURCE = "D:\\”Õ»¬≈–\\Sem4_TrainingPractice\\tp4_3\\src\\tp4_3\\automobiles.json";
	public PieChartFrame(Data data) {
	      super(data.getTitle()); 
	      this.data = data;
	      setContentPane(createChartPanel());
	   }	   	   
	   public JPanel createChartPanel() {
		  JFreeChart chart = ChartFactory.createPieChart(      
			       	 data.getTitle(),   
			         data.createDataset(),           
			         true,             
			         true, 
			         false);
	      return new ChartPanel(chart); 
	   }

	   public static void main(String[] args) {
		   try {
			  JFileChooser fc = new JFileChooser("D:\\”Õ»¬≈–\\Sem4_TrainingPractice\\tp4_3\\src\\tp4_3");
			  int result = fc.showOpenDialog(null);
			  Data data;
			  if(result == fc.APPROVE_OPTION) {
				  data = new Data(fc.getSelectedFile()); 
			  } else {
				  data = new Data(new File(DEFAULT_FILE_SOURCE));
			  }
			  PieChartFrame pieChartFrame = new PieChartFrame(data);
			  pieChartFrame.setSize(560 , 367);    
		      pieChartFrame.setVisible(true);
		   } catch(FileNotFoundException|InvalidDataException|JsonSyntaxException|JsonIOException ex) {
			   JOptionPane.showMessageDialog(null, ex.getMessage());
		   }
	   }
}
