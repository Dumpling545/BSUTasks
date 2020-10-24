#define _CRT_SECURE_NO_WARNINGS
#include <mpi.h>
#include <math.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
void distributeRows(int remainingRows, int size, int &rowsPerProcess, int &remainderOfRows)
{
	if (remainingRows % size == 0)
	{
		rowsPerProcess = remainingRows / size;
		remainderOfRows = rowsPerProcess;
	}
	else
	{
		rowsPerProcess = remainingRows / size + 1;
		remainderOfRows = remainingRows - rowsPerProcess * (size - 1);
	}
}
int main(int argc, char *argv[])
{
	MPI_Init(&argc, &argv);
	int size;
	int processRank;
	int rowsPerProcess;
	int remainderOfRows;
	int *matrix = NULL;
	int *inverse = NULL;
	int *partialMatrix = NULL;
	int *partialInverse = NULL;
	int matrixSize = 0;
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &processRank);
	if (processRank == 0)
	{
		std::ifstream fin("input.txt");
		fin >> matrixSize;
		distributeRows(matrixSize, size, rowsPerProcess, remainderOfRows);
		if (size > 1)
			MPI_Send(&remainderOfRows, 1, MPI_INT, size - 1, 0, MPI_COMM_WORLD);
		matrix = new int[matrixSize * matrixSize];
		for (int i = 0; i < matrixSize; i++)
		{
			for (int j = 0; j < matrixSize; j++)
			{
				fin >> matrix[i * matrixSize + j];
			}
		}
		inverse = new int[matrixSize*matrixSize];
		fin.close();
	}
	else if (processRank == size - 1)
	{
		MPI_Recv(&remainderOfRows, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
	}
	MPI_Bcast(&matrixSize, 1, MPI_INT, 0, MPI_COMM_WORLD);
	MPI_Bcast(&rowsPerProcess, 1, MPI_INT, 0, MPI_COMM_WORLD);
	partialMatrix = new int[rowsPerProcess * matrixSize];
	partialInverse = new int[rowsPerProcess * matrixSize];
	secondMatrix = (processRank == 0) ? secondMatrix : new int[matrixSize * matricesSizing[2]];
	MPI_Scatter(firstMatrix, rowsPerProcess * matrixSize, MPI_INT,
				partialFirstMatrix, rowsPerProcess * matrixSize, MPI_INT, 0, MPI_COMM_WORLD);
	MPI_Bcast(secondMatrix, matrixSize * matricesSizing[2], MPI_INT, 0, MPI_COMM_WORLD);
	double time = MPI_Wtime();
	int realRowsPerProcess = ((processRank == size - 1) ? remainderOfRows : rowsPerProcess);
	for (int i = 0; i < realRowsPerProcess; i++)
	{
		for (int j = 0; j < matricesSizing[2]; j++)
		{
			partialResultMatrix[i * matricesSizing[2] + j] = 0;
			for (int k = 0; k < matrixSize; k++)
			{
				partialResultMatrix[i * matricesSizing[2] + j] +=
					partialFirstMatrix[i * matrixSize + k] * secondMatrix[k * matricesSizing[2] + j];
			}
		}
	}
	double time_end = MPI_Wtime();
	std::cout << "calculation time of process " << processRank << ": " << time_end - time << '\n';
	MPI_Gather(partialResultMatrix, rowsPerProcess * matrixSize, MPI_INT,
			   resultMatrix, rowsPerProcess * matrixSize, MPI_INT, 0, MPI_COMM_WORLD);
	MPI_Barrier(MPI_COMM_WORLD);
	MPI_Finalize();
	if (processRank == 0)
	{
		std::ofstream fout("output.txt");
		for (int i = 0; i < matrixSize; i++)
		{
			for (int j = 0; j < matricesSizing[2]; j++)
			{
				fout << resultMatrix[i * matricesSizing[2] + j] << ' ';
			}
			fout << '\n';
		}
		fout.close();
	}
}