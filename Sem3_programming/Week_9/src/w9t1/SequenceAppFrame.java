package w9t1;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.beans.PropertyChangeEvent;
import java.beans.PropertyChangeListener;
import java.io.IOException;
import java.text.DecimalFormat;
import java.text.NumberFormat;

import javax.swing.JFrame;
import javax.swing.BoxLayout;
import javax.swing.ButtonGroup;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JTextField;
import javax.swing.event.ChangeEvent;
import javax.swing.event.ChangeListener;

import javax.swing.text.NumberFormatter;


import javax.swing.JRadioButton;
import javax.swing.JButton;
import javax.swing.JFileChooser;
import javax.swing.JFormattedTextField;

public class SequenceAppFrame extends JFrame {
	private Sequence sequence = new ArithmeticSequence(10, 0.0, 2.0);
	private JTextField txtFirstElement;
	private JTextField txtCoefficient;
	private JFormattedTextField txtN;
	private JTextField txtSum;
	private JTextField txtPrint;
	public SequenceAppFrame(){
		super("Sequence app");
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		getContentPane().setLayout(new BoxLayout(getContentPane(), BoxLayout.Y_AXIS));
		
		JLabel lblFirstElement = new JLabel("First Element:");
		getContentPane().add(lblFirstElement);
		
		txtFirstElement = new JFormattedTextField();
		txtFirstElement.setText(Double.toString(sequence.getFirst()));
		getContentPane().add(txtFirstElement);
		txtFirstElement.setColumns(1);
		txtFirstElement.addPropertyChangeListener("value", new PropertyChangeListener() {	
			@Override
			public void propertyChange(PropertyChangeEvent evt) {
				try {
					sequence.setFirst(Double.parseDouble(txtFirstElement.getText()));
					refresh();
				} catch(NumberFormatException ex) {
					JOptionPane.showMessageDialog(null, "Only decimal numbers are allowed!");
					txtFirstElement.setText(Double.toString(sequence.getFirst()));
				}
			}
		});
		
		JLabel lblCoefficient = new JLabel("Coefficient:");
		getContentPane().add(lblCoefficient);
		
		txtCoefficient = new JFormattedTextField();
		txtCoefficient.setText(Double.toString(sequence.getCoefficient()));
		getContentPane().add(txtCoefficient);
		txtCoefficient.setColumns(1);
		txtCoefficient.addPropertyChangeListener("value", new PropertyChangeListener() {	
			@Override
			public void propertyChange(PropertyChangeEvent evt) {
				try{
					sequence.setCoefficient(Double.parseDouble(txtCoefficient.getText()));
					refresh();
				} catch(NumberFormatException ex) {
					JOptionPane.showMessageDialog(null, "Only decimal numbers are allowed!");
					txtCoefficient.setText(Double.toString(sequence.getCoefficient()));
				}
				
			}
		});
		
		JLabel lblN = new JLabel("N:");
		getContentPane().add(lblN);
		NumberFormatter integerFormatter = new NumberFormatter(NumberFormat.getIntegerInstance());
		integerFormatter.setValueClass(Integer.class);
		integerFormatter.setAllowsInvalid(false);
		txtN = new JFormattedTextField(integerFormatter);
		txtN.setValue(sequence.getN());
		getContentPane().add(txtN);
		txtN.setColumns(1);
		txtN.addPropertyChangeListener("value", new PropertyChangeListener() {	
			@Override
			public void propertyChange(PropertyChangeEvent evt) {
				sequence.setN((int)txtN.getValue());
				refresh();
				
			}
		});
		
		JLabel lblSequenceType = new JLabel("Sequence type:");
		getContentPane().add(lblSequenceType);
		
		JRadioButton rdbtnArithmetic = new JRadioButton("Arithmetic");
		rdbtnArithmetic.setSelected(true);
		rdbtnArithmetic.addChangeListener(new ChangeListener() {
			@Override
			public void stateChanged(ChangeEvent e) {
				if(rdbtnArithmetic.isSelected()) {
					sequence = new ArithmeticSequence(sequence.getN(), sequence.getFirst(), sequence.getCoefficient());
					refresh();
				}
			}
		});
		getContentPane().add(rdbtnArithmetic);
				
		JRadioButton rdbtnGeometric = new JRadioButton("Geometric");
		rdbtnGeometric.addChangeListener(new ChangeListener() {
			@Override
			public void stateChanged(ChangeEvent e) {
				if(rdbtnGeometric.isSelected()) {
					sequence = new GeometricSequence(sequence.getN(), sequence.getFirst(), sequence.getCoefficient());
					refresh();
				}
			}
		});
		getContentPane().add(rdbtnGeometric);
		
		ButtonGroup group = new ButtonGroup();
		group.add(rdbtnArithmetic);
		group.add(rdbtnGeometric);
		
		JLabel lblSum = new JLabel("Sum:");
		getContentPane().add(lblSum);
		
		txtSum = new JTextField();
		txtSum.setEditable(false);
		getContentPane().add(txtSum);
		txtSum.setColumns(1);
		
		JLabel lblFirstNElements = new JLabel("First N elements of sequence:");
		getContentPane().add(lblFirstNElements);
		
		txtPrint = new JTextField();
		txtPrint.setEditable(false);
		getContentPane().add(txtPrint);
		txtPrint.setColumns(10);
		
		JLabel lblSaveFirstN = new JLabel("Save first N elements to file:");
		getContentPane().add(lblSaveFirstN);
		
		JButton btnSave = new JButton("Save");
		btnSave.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				JFileChooser fileChooser = new JFileChooser();
				int state = fileChooser.showSaveDialog(null);
				if(state == JFileChooser.APPROVE_OPTION) {
					try {
					    sequence.save(fileChooser.getSelectedFile()+".txt");
					} catch(IOException ex) {
						JOptionPane.showMessageDialog(null, ex.getMessage());
					}
				}
			}
		});
		getContentPane().add(btnSave);
		refresh();
		
	}
	private void refresh() {
		txtSum.setText(Double.toString(sequence.sum()));
		txtPrint.setText(sequence.toString());
	}

}
