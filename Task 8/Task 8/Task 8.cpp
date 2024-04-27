#include <iostream>  
#include <pthread.h> 
#include <cstdlib>   

// Constants of matrix dimensions
const int rowsA = 3;  // Number of rows for matrix A
const int colsA = 4;  // Number of columns for matrix A (also rows for matrix B)
const int colsB = 3;  // Number of columns for matrix B

// matrix definitions
int matrixA[rowsA][colsA] = { {1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12} };  // initialise matrix A with values
int matrixB[colsA][colsB] = { {16, 12, 8}, {15, 11, 7}, {14, 10, 6}, {13, 9, 5} };  // initialise matrix B with values
int matrixC[rowsA][colsB] = { 0 };  // Result matrix, initialized with zero

// Struct to hold thread data
struct ThreadData {
    int row;  // stores the specific row index to be processed by each thread 
};

// thread function to multiply one row of matrixA with matrixB
// The void* pointer is used in pthreads as a way to pass any data type to threads.
// The pthread_create() function is flexible and is able to run any function, regardless of the data it requires.
void* multi(void* arg) {
    ThreadData* data = (ThreadData*)arg;  // cast void* back to ThreadData* type to access the row data,
    int row = data->row;  // Extract row index from struct

    // Loop over each column of matrixB
    for (int j = 0; j < colsB; j++) {
        matrixC[row][j] = 0;  // Initialize result cell to zero
        // Perform dot product of the row from matrixA and column from matrixB
        for (int k = 0; k < colsA; k++) {
            matrixC[row][j] += matrixA[row][k] * matrixB[k][j];
        }
    }
    return NULL;  // NULL return (required by the pthreads function signature)
}

int main() {
    pthread_t threads[rowsA];  // array to store thread identifiers
    ThreadData threadData[rowsA];  // array of structs to hold the data for each thread

    // creating a thread for each row of matrix A
    for (int i = 0; i < rowsA; i++) {
        threadData[i].row = i;  // set the row index for each struct
        pthread_create(&threads[i], NULL, multi, (void*)&threadData[i]);  // start new thread
    }

    // wait for threads to finish
    for (int i = 0; i < rowsA; i++) {
        pthread_join(threads[i], NULL);  //block until specified thread has completed
    }

    // outputting matrix A and matrix B and the result
    std::cout << "Matrix A:\n";
    for (int i = 0; i < rowsA; i++) {
        for (int j = 0; j < colsA; j++) {
            std::cout << matrixA[i][j] << " ";
        }
        std::cout << "\n";
    }

    std::cout << "\nMatrix B:\n";
    for (int i = 0; i < colsA; i++) {
        for (int j = 0; j < colsB; j++) {
            std::cout << matrixB[i][j] << " ";
        }
        std::cout << "\n";
    }

    std::cout << "\nResult Matrix:\n";
    for (int i = 0; i < rowsA; i++) {
        for (int j = 0; j < colsB; j++) {
            std::cout << matrixC[i][j] << " ";
        }
        std::cout << "\n";
    }

    return 0;  
}