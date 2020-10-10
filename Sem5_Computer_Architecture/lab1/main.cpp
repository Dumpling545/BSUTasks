#define _CRT_SECURE_NO_WARNINGS
#include <mpi.h>
#include <math.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
int main(int argc, char *argv[])
{
	MPI_Init(&argc, &argv);
	int size;
	int processRank;
	int rowsPerProcess;
	int reminderOfRows;
	int* firstMatrix = NULL;
	int* secondMatrix = NULL;
	int* resultMatrix = NULL;
	int* partialFirstMatrix = NULL;
	int* partialResultMatrix = NULL;
	int* matricesSizing = new int[3];
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &processRank);
	if (processRank == 0) {
		std::ifstream fin("input.txt");
		fin >> matricesSizing[0] >> matricesSizing[1] >> matricesSizing[2];
		if (matricesSizing[0] % size == 0) {
			rowsPerProcess = matricesSizing[0] / size;
			reminderOfRows = rowsPerProcess;
		}
		else {
			rowsPerProcess = matricesSizing[0] / size + 1;
			reminderOfRows = matricesSizing[0] - rowsPerProcess * (size - 1);
		}
		if (size > 1) MPI_Send(&reminderOfRows, 1, MPI_INT, size - 1, 0, MPI_COMM_WORLD);
		firstMatrix = new int[(matricesSizing[0] + rowsPerProcess - reminderOfRows)* matricesSizing[1]];
		for (int i = 0; i < matricesSizing[0]; i++) {
			for (int j = 0; j < matricesSizing[1]; j++) {
				fin >> firstMatrix[i*matricesSizing[1] + j];
			}
		}

		secondMatrix = new int[matricesSizing[1] * matricesSizing[2]];
		for (int i = 0; i < matricesSizing[1]; i++) {
			for (int j = 0; j < matricesSizing[2]; j++) {
				fin >> secondMatrix[i*matricesSizing[2] + j];
			}
		}

		resultMatrix = new int[(matricesSizing[0] + rowsPerProcess - reminderOfRows) * matricesSizing[2]];
		fin.close();
	}
	else if (processRank == size - 1) {
		MPI_Recv(&reminderOfRows, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
	}
	MPI_Bcast(matricesSizing, 3, MPI_INT, 0, MPI_COMM_WORLD);
	MPI_Bcast(&rowsPerProcess, 1, MPI_INT, 0, MPI_COMM_WORLD);
	partialFirstMatrix = new int[rowsPerProcess*matricesSizing[1]];
	partialResultMatrix = new int[rowsPerProcess*matricesSizing[2]];
	secondMatrix = (processRank == 0) ? secondMatrix : new int[matricesSizing[1] * matricesSizing[2]];
	MPI_Scatter(firstMatrix, rowsPerProcess*matricesSizing[1], MPI_INT, 
		partialFirstMatrix, rowsPerProcess*matricesSizing[1], MPI_INT, 0, MPI_COMM_WORLD);
	MPI_Bcast(secondMatrix, matricesSizing[1] * matricesSizing[2], MPI_INT, 0, MPI_COMM_WORLD);
	double time = MPI_Wtime();
	int realRowsPerProcess = ((processRank == size - 1) ? reminderOfRows : rowsPerProcess);
	for (int i = 0; i < realRowsPerProcess; i++) {
		for (int j = 0; j < matricesSizing[2]; j++) {
			partialResultMatrix[i*matricesSizing[2] + j] = 0;
			for (int k = 0; k < matricesSizing[1]; k++) {
				partialResultMatrix[i*matricesSizing[2] + j] += 
					partialFirstMatrix[i*matricesSizing[1] + k] * secondMatrix[k*matricesSizing[2] + j];
			}
		}
	}
	double time_end = MPI_Wtime();
	std::cout << "calculation time of process " << processRank << ": " << time_end - time << '\n';
	MPI_Gather(partialResultMatrix, rowsPerProcess*matricesSizing[1], MPI_INT, 
		resultMatrix, rowsPerProcess*matricesSizing[1], MPI_INT, 0, MPI_COMM_WORLD);
	MPI_Barrier(MPI_COMM_WORLD);
	MPI_Finalize();
	if (processRank == 0) {
		std::ofstream fout("output.txt");
		for (int i = 0; i < matricesSizing[0]; i++) {
			for (int j = 0; j < matricesSizing[2]; j++) {
				fout << resultMatrix[i*matricesSizing[2] + j] << ' ';
			}
			fout << '\n';
		}
		fout.close();
	}
}