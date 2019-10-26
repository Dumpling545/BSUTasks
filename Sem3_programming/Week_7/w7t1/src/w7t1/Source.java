package w7t1;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.InputMismatchException;
import java.util.NoSuchElementException;
import java.util.Scanner;
import java.lang.Math;

public class Source{
	public static void printMatrix(double[][] matrix){
		int cols = matrix[0].length;
	    int[] iWidths = new int[cols];
	    int[] fWidths = new int[cols];
	    for (double[] row : matrix) {
	        for (int c = 0; c < cols; c++) {
	            String[] parts = String.valueOf(row[c]).split("\\.");
	            iWidths[c] = Math.max(iWidths[c], parts[0].length());
	            fWidths[c] = Math.max(fWidths[c], parts[1].length());
	        }
	    }
	    for (double[] row : matrix) {
	        for (int c = 0; c < cols; c++) {
	            String[] parts = String.valueOf(row[c]).split("\\.");
	            int lp = iWidths[c] - parts[0].length();
	            int rp = fWidths[c] - parts[1].length();
	            String fmt = String.format("%s%%%ss%%s.%%s%%%ss%s",
	                    c == 0 ? "|" : "  ",
	                    lp == 0 ? "" : lp,
	                    rp == 0 ? "" : rp,
	                    c < cols - 1 ? "" : "|%n");
	            System.out.printf(fmt, "", parts[0], parts[1], "");
	        }
	    }
		System.out.print("\n\n");
	}
	public static double[][] loadMatrix(String filename) throws  InputMismatchException, NoSuchElementException, FileNotFoundException{
		Scanner scanner = new Scanner(new File(filename));
		int n = scanner.nextInt();
		double[][] matrix = new double[n][n];
		for(int i = 0; i < n; i++) {
			for(int j = 0; j < n; j++) {
				matrix[i][j] = scanner.nextInt();
			}
		}
		return matrix;
	}
	public static double[][] createAugmentedMatrix(double[][] matrix){
		int n = matrix.length;
		double[][] augmentedMatrix = new double[n][2*n];
		for(int i = 0; i < n; i++) {
			for(int j = 0; j < n; j++) {
				augmentedMatrix[i][j] = matrix[i][j];
			}
			for(int j = n; j < 2*n; j++) {
				if(i + n == j) {
					augmentedMatrix[i][j] = 1;
				} else {
					augmentedMatrix[i][j] = 0;
				}
			}
		}
		return augmentedMatrix;
	}
	public static double[][] swapLines(double [][] augmentedMatrix, int fi, int si){
		int n = augmentedMatrix.length;
		double[][] result = augmentedMatrix;
	    if(fi != si){
	    	double temp;
	        for(int i = 0; i < 2*n; i++){
	            temp = augmentedMatrix[fi][i];
	            augmentedMatrix[fi][i] = augmentedMatrix[si][i];
	            augmentedMatrix[si][i] = temp;
	        }
	    }
	    return result;
	}
	public static int maxElementInColumnIndex(double[][] augmentedMatrix, int colIndex){
		int n = augmentedMatrix.length;
		int max = colIndex;
		for(int i = colIndex + 1; i < n; i++) {
			if(Math.abs(augmentedMatrix[max][colIndex]) < Math.abs(augmentedMatrix[i][colIndex])) {
				max = i;
			}
		}
		return max;
	}
	public  static double[][]  forwardElimination(double[][] augmentedMatrix){
		int n = augmentedMatrix.length;
		for(int i = 0; i < n; i++) {
			int max = maxElementInColumnIndex(augmentedMatrix, i);
			augmentedMatrix = swapLines(augmentedMatrix, i, max);
			for(int t = i + 1; t < 2*n; t++) {
				augmentedMatrix[i][t] /= augmentedMatrix[i][i];
			}
			augmentedMatrix[i][i] = 1;
			for(int j = i+1; j < n; j++) {
				double l = augmentedMatrix[j][i];
				augmentedMatrix[j][i] = 0;
				for(int k = i+1; k < 2*n; k++) {
					augmentedMatrix[j][k] -= l*augmentedMatrix[i][k];
				}
			}
		}
		return augmentedMatrix;
	}
	public static double[][] backSubstitution(double[][] augmentedMatrix){
		int n = augmentedMatrix.length;
		for(int i = n - 1; i >=0; i--) {
			for(int j = i - 1; j >=0; j--) {
				double l = augmentedMatrix[j][i];
				augmentedMatrix[j][i] = 0;
				for(int k = i + 1; k < 2*n; k++) {
					augmentedMatrix[j][k] -= l*augmentedMatrix[i][k];
				}
			}
		}
		return augmentedMatrix;
	}
	public static double[][] inverse(double[][] matrix){
		int n = matrix.length;
		double[][] augmentedMatrix = createAugmentedMatrix(matrix);
		augmentedMatrix = forwardElimination(augmentedMatrix);
		augmentedMatrix = backSubstitution(augmentedMatrix);
		for(int i = 0; i < n; i++) {
			for(int j = n; j < 2*n; j++) {
				matrix[i][j-n] = augmentedMatrix[i][j];
			}
		}
		return matrix;
	}
	public static void main(String[] args) {
		try {
			String filename = "input.txt";
			double[][] matrix = loadMatrix(filename);
			double[][] result = inverse(matrix);
			printMatrix(result);
		} catch (FileNotFoundException e) {
			System.out.println(e.getMessage());
		} catch (InputMismatchException e) {
			System.out.println(e.getMessage());
		} catch (NoSuchElementException e) {
			System.out.println(e.getMessage());
		}

	}

}
