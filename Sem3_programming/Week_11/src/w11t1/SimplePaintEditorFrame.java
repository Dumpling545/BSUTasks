package w11t1;

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Dimension;
import java.awt.EventQueue;

import javax.imageio.ImageIO;
import javax.swing.BorderFactory;
import javax.swing.ButtonGroup;
import javax.swing.JButton;
import javax.swing.JFileChooser;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JRadioButton;
import javax.swing.border.EmptyBorder;
import javax.swing.plaf.basic.BasicBorders.RadioButtonBorder;

import java.awt.GridBagLayout;
import java.awt.Point;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.MouseEvent;
import java.awt.event.MouseMotionListener;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;

import javax.swing.JScrollPane;
import javax.swing.JTextArea;

import java.awt.GridBagConstraints;

public class SimplePaintEditorFrame extends JFrame implements ActionListener{

	private JPanel contentPane;
	private DrawPane drawPane;
	private JLabel labelSize;
	private JScrollPane scrollPane;
	private JRadioButton redButton;
	private JRadioButton greenButton;
	private JRadioButton blueButton;
	private ButtonGroup group;
	private JButton openButton;
	private JButton saveButton;
	private final Dimension DEFAULT_PAINT_SIZE = new Dimension(640, 480);
	/**
	 * Launch the application.
	 */
	public static void main(String[] args) {
		EventQueue.invokeLater(new Runnable() {
			public void run() {
				try {
					SimplePaintEditorFrame frame = new SimplePaintEditorFrame();
					frame.setVisible(true);
				} catch (Exception e) {
					e.printStackTrace();
				}
			}
		});
	}

	/**
	 * Create the frame.
	 */
	public SimplePaintEditorFrame() {
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		setBounds(100, 100, 450, 300);
		contentPane = new JPanel();
		contentPane.setBorder(new EmptyBorder(5, 5, 5, 5));
		setContentPane(contentPane);
		contentPane.setLayout(new GridBagLayout());
		drawPane = new DrawPane(DEFAULT_PAINT_SIZE);
		scrollPane = new JScrollPane(drawPane);
		scrollPane.setBorder(BorderFactory.createLineBorder(Color.black));
		GridBagConstraints gbc= new GridBagConstraints();
		gbc.fill = GridBagConstraints.BOTH;
		gbc.gridx = 0;
		gbc.gridy = 0;
		gbc.gridwidth = 1;
		gbc.gridheight = 10;
		gbc.weightx = 1;
		gbc.weighty = 1;
		contentPane.add(scrollPane, gbc);
		labelSize = new JLabel("Set Color:");
		gbc.fill = GridBagConstraints.NONE;
		gbc.gridx = 1;
		gbc.gridy = 0;
		gbc.gridheight = 1;
		gbc.weightx = 0;
		gbc.weighty = 0;
		contentPane.add(labelSize, gbc);
		redButton = new JRadioButton("Red");
		redButton.setSelected(true);
		redButton.addActionListener(this);
		greenButton = new JRadioButton("Green");
		greenButton.addActionListener(this);
		blueButton = new JRadioButton("Blue");
		blueButton.addActionListener(this);
		group = new ButtonGroup();
		group.add(redButton);
		group.add(greenButton);
		group.add(blueButton);
		gbc.gridx = 1;
		gbc.gridy = 1;
		gbc.weightx = 0;
		gbc.weighty = 0;
		contentPane.add(redButton, gbc);
		gbc.gridx = 1;
		gbc.gridy = 2;
		gbc.weightx = 0;
		gbc.weighty = 0;
		contentPane.add(greenButton, gbc);
		gbc.gridx = 1;
		gbc.gridy = 3;
		gbc.weightx = 0;
		gbc.weighty = 0;
		contentPane.add(blueButton, gbc);
		openButton = new JButton("Open Image");
		openButton.addActionListener(this);
		gbc.gridx = 1;
		gbc.gridy = 4;
		gbc.weightx = 0;
		gbc.weighty = 0;
		contentPane.add(openButton, gbc);
		saveButton = new JButton("Save Image");
		saveButton.addActionListener(this);
		gbc.gridx = 1;
		gbc.gridy = 5;
		gbc.weightx = 0;
		gbc.weighty = 0;
		contentPane.add(saveButton, gbc);
	}

	@Override
	public void actionPerformed(ActionEvent e) {
		if(redButton.isSelected()) {
			drawPane.setDrawColor(Color.red);
			drawPane.requestFocus();
		} else if(greenButton.isSelected()) {
			drawPane.setDrawColor(Color.green);
			drawPane.requestFocus();
		} else if(blueButton.isSelected()) {
			drawPane.setDrawColor(Color.blue);
			drawPane.requestFocus();
		}
		if(e.getSource() == openButton) {
			JFileChooser chooser = new JFileChooser();
			if(chooser.showOpenDialog(null) == JFileChooser.APPROVE_OPTION) {
				File file = chooser.getSelectedFile();
				try {
					drawPane.loadImage(file);
					scrollPane.setViewportView(drawPane);
				} catch(IOException ex) {
					JOptionPane.showMessageDialog(null, "Something wrong: " + ex.getMessage());
				}
			}
		} else if(e.getSource() == saveButton) {
			JFileChooser chooser = new JFileChooser();
			if(chooser.showSaveDialog(null) == JFileChooser.APPROVE_OPTION) {
				File file = chooser.getSelectedFile();
				try {
					drawPane.saveImage(file);
				} catch(IOException ex) {
					JOptionPane.showMessageDialog(null, "Something wrong: " + ex.getMessage());
				}
			}
		}
		
	}

}
