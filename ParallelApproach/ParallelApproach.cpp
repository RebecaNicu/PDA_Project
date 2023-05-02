#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <iostream>
#include <iostream>

#define _CRT_SECURE_NO_WARNINGS

using namespace std;

int main() {
    int rows, cols;
    int size, rank, i, j, sum = 0;
    int** mat;
    // Initialize MPI
    MPI_Init(NULL, NULL);

    // Get the number of processes and the rank of the current process
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    FILE* fp = fopen("matrix.txt", "r");

    // Read the dimensions of the matrix from the file
    fscanf(fp, "%d %d", &rows, &cols);    

    // If the number of processes is greater than the number of rows,
    // reduce the number of processes to the number of rows
    if (size > rows) {
        size = rows;
    }

    // Calculate the number of rows each process will work on
    int rows_per_proc = rows / size;
    int start_row = rank * rows_per_proc;
    int end_row = start_row + rows_per_proc;

    // Dynamically allocate the matrix with random values
    mat = (int**)malloc(rows * sizeof(int*));
    for (i = 0; i < rows; i++) {
        mat[i] = (int*)malloc(cols * sizeof(int));
        for (j = 0; j < cols; j++) {
            fscanf(fp, "%d", &mat[i][j]);
        }
    }

    // Each process calculates the sum of its assigned rows
    int local_sum = 0;
    for (i = start_row; i < end_row; i++) {
        for (j = 0; j < cols; j++) {
            local_sum += mat[i][j];
        }
    }

    // Reduce the local sums to obtain the global sum
    MPI_Reduce(&local_sum, &sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    // Output the result from the root process
    if (rank == 0) {
        cout << "The sum of the matrix elements is: " << sum;
    }

    // Free the dynamically allocated memory
    for (i = 0; i < cols; i++) {
        free(mat[i]);
    }
    free(mat);

    // Finalize MPI
    MPI_Finalize();

    return 0;
}

