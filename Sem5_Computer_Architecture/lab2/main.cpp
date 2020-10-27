#define _CRT_SECURE_NO_WARNINGS
#include <fstream>
#include <iomanip>
#include <iostream>
#include <math.h>
#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
const double PRECISION = 1e-9;
const int PRINT_PRECISION = 9;
class Matrix {
  private:
	int rows, columns;

  public:
	double *pointer = NULL;
	Matrix() {}
	Matrix(int rows, int columns) {
		pointer = new double[2 * rows * columns];
		this->rows = rows;
		this->columns = columns;
	}

	double &get(int rIndex, int cIndex) const { return pointer[rows * cIndex + rIndex]; }

	static Matrix *initSystem(int size) {
		Matrix *s = new Matrix(size, 2 * size);
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < i; j++) {
				s->get(i, size + j) = 0;
			}
			s->get(i, size + i) = 1;
			for (int j = i + 1; j < size; j++) {
				s->get(i, size + j) = 0;
			}
		}
		return s;
	}

	static void getPartialSystemInfo(int processRank, int numberOfProcesses, int currentIndex,
									 int matrixSize, int &bufferSize, int &bufferOffset) {
		int remainingColumns = 2 * matrixSize - currentIndex;
		int bufferColumns = remainingColumns / numberOfProcesses;
		int bufferRemainder = remainingColumns % numberOfProcesses;
		bufferSize = bufferColumns * matrixSize;
		bufferOffset = currentIndex * matrixSize;
		if (processRank < bufferRemainder) {
			bufferSize += matrixSize;
			bufferOffset += bufferSize * processRank;
		} else {
			bufferOffset += (processRank * bufferColumns + bufferRemainder) * matrixSize;
		}
	}
	void inputSystem(std::istream &input) {
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < columns / 2; j++) {
				input >> get(i, j);
			}
		}
	}
	void printInverse(std::ostream &output) {
		output << std::fixed << std::setprecision(PRINT_PRECISION);
		for (int i = 0; i < rows; i++) {
			for (int j = columns / 2; j < columns; j++) {
				output << get(i, j) << ' ';
			}
			output << '\n';
		}
	}
};
int main(int argc, char *argv[]) {
	MPI_Init(&argc, &argv);
	int size;
	int processRank;
	double divisor = 0;
	Matrix *system = NULL;
	Matrix *chunk = NULL;
	double *coefficients = NULL;
	int *sendcounts = NULL;
	int *displacements = NULL;
	int matrixSize = 0;
	// get amount of processes and process id
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &processRank);
	if (processRank == 0) {
		std::ifstream fin("input.txt");
		fin >> matrixSize;
		// creating augmented n*2n matrix with right n*n part as identity matrix
		system = Matrix::initSystem(matrixSize);
		// input left n*n part of system from file
		system->inputSystem(fin);
		fin.close();
	}
	// allocating memory for arrays that 'll be used for MPI_Scatterv
	sendcounts = new int[size];
	displacements = new int[size];
	// sharing system size to processes
	MPI_Bcast(&matrixSize, 1, MPI_INT, 0, MPI_COMM_WORLD);
	if (processRank != 0) {
		system = new Matrix(matrixSize, matrixSize);
	}
	// allocating memory for subcolumn that 'll be used for gauss elimination
	coefficients = new double[matrixSize];
	// allocating memory for submatrix that 'll be distributed from whole n*2n augmented matrix via
	// MPI_Scatterv
	chunk = new Matrix(matrixSize, 2 * matrixSize);
	int i = 0;
	double time = MPI_Wtime();
	// FORWARD ELIMINATION
	for (; i < matrixSize; i++) {
		// calculating sizes and locations of submatrixes that augmented matrix 'll be divided in
		Matrix::getPartialSystemInfo(processRank, size, i, matrixSize, sendcounts[processRank],
									 displacements[processRank]);
		// sending this info to root process
		MPI_Gather(&sendcounts[processRank], 1, MPI_INT, sendcounts, 1, MPI_INT, 0, MPI_COMM_WORLD);
		MPI_Gather(&displacements[processRank], 1, MPI_INT, displacements, 1, MPI_INT, 0,
				   MPI_COMM_WORLD);
		// divide matrix in chunks(submatrixes) for each process
		MPI_Scatterv(system->pointer, sendcounts, displacements, MPI_DOUBLE, chunk->pointer,
					 sendcounts[processRank], MPI_DOUBLE, 0, MPI_COMM_WORLD);
		int notNullMinAbsIndex = 0;
		// root process finds (if exists) non-zero coefficient with lowest absolute value from
		// current column
		if (processRank == 0) {
			coefficients = &system->get(i, i);
			for (int t = 0; t < matrixSize - i; t++) {
				if ((fabs(coefficients[t]) >= PRECISION &&
					 fabs(coefficients[t]) < fabs(coefficients[notNullMinAbsIndex])) ||
					fabs(coefficients[notNullMinAbsIndex]) < PRECISION) {
					notNullMinAbsIndex = t;
				}
			}
			std::swap(coefficients[notNullMinAbsIndex], coefficients[0]);
			notNullMinAbsIndex += i;
		}
		// distribute current column and index of non-zero coefficient with lowest absolute value
		MPI_Bcast(coefficients, matrixSize - i, MPI_DOUBLE, 0, MPI_COMM_WORLD);
		MPI_Bcast(&notNullMinAbsIndex, 1, MPI_INT, 0, MPI_COMM_WORLD);
		// if all coefficients are ~zeros
		if (fabs(coefficients[0]) < PRECISION) {
			MPI_Barrier(MPI_COMM_WORLD);
			MPI_Finalize();
			if (processRank == 0)
				std::cout << "Matrix doesn't have inverse" << '\n';
			return 0;
		}
		// get index of last column relative to beginning of that column
		int columnRelativeIndex = sendcounts[processRank] / matrixSize - 1;
		for (; columnRelativeIndex >= 0; columnRelativeIndex--) {
			// swap active row with row  where non-zero coefficient with lowest absolute value were
			// found and normalizing it
			std::swap(chunk->get(notNullMinAbsIndex, columnRelativeIndex),
					  chunk->get(i, columnRelativeIndex));
			chunk->get(i, columnRelativeIndex) /= coefficients[0];
			for (int j = i + 1; j < matrixSize; j++) {
				chunk->get(j, columnRelativeIndex) -=
					chunk->get(i, columnRelativeIndex) * coefficients[j - i];
			}
		}
		// collect augmented matrix from submatrices
		MPI_Gatherv(chunk->pointer, sendcounts[processRank], MPI_DOUBLE, system->pointer,
					sendcounts, displacements, MPI_DOUBLE, 0, MPI_COMM_WORLD);
	}
	// distribute right part of augmented matrix between processes
	Matrix::getPartialSystemInfo(processRank, size, i, matrixSize, sendcounts[processRank],
								 displacements[processRank]);
	MPI_Gather(&sendcounts[processRank], 1, MPI_INT, sendcounts, 1, MPI_INT, 0, MPI_COMM_WORLD);
	MPI_Gather(&displacements[processRank], 1, MPI_INT, displacements, 1, MPI_INT, 0,
			   MPI_COMM_WORLD);
	MPI_Scatterv(system->pointer, sendcounts, displacements, MPI_DOUBLE, chunk->pointer,
				 sendcounts[processRank], MPI_DOUBLE, 0, MPI_COMM_WORLD);
	// send left part of augmented matrix to all processes
	MPI_Bcast(system->pointer, matrixSize * matrixSize, MPI_DOUBLE, 0, MPI_COMM_WORLD);
	int columnCount = sendcounts[processRank] / matrixSize;
	// BACK SUBSTITUTION
	for (int i = matrixSize - 1; i >= 0; i--) {
		for (int j = i - 1; j >= 0; j--) {
			for (int c = 0; c < columnCount; c++) {
				chunk->get(j, c) -= chunk->get(i, c) * system->get(j, i);
			}
		}
	}
	MPI_Gatherv(chunk->pointer, sendcounts[processRank], MPI_DOUBLE, system->pointer, sendcounts,
				displacements, MPI_DOUBLE, 0, MPI_COMM_WORLD);
	double time_end = MPI_Wtime();
	std::cout << "process " << processRank << " ended with time: " << time_end - time << 's'
			  << '\n';
	MPI_Barrier(MPI_COMM_WORLD);
	MPI_Finalize();
	if (processRank == 0) {
		std::ofstream fout("output.txt");
		system->printInverse(fout);
		fout.close();
	}
	return 0;
}