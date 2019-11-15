package w9t1;

import java.awt.Dimension;
import java.io.IOException;
import java.util.Scanner;
import java.util.StringTokenizer;

import javax.swing.JFrame;

public class Source {

	public static void main(String[] args) {
		JFrame frame = new SequenceAppFrame();
		frame.setPreferredSize(new Dimension(600, 400));
		frame.pack();
		frame.setVisible(true);
	}
}
