#include <iostream>
#include <thread>
#include <numeric>
#include <fstream>
#include <vector>

// Funcția pentru calculul sumei elementelor unei porțiuni a matricei
int calculateSum(const int* matrix, int numColumns, int startRow, int endRow) {
    int sum = 0;
    for (int i = startRow; i <= endRow; ++i) {
        for (int j = 0; j < numColumns; ++j) {
            sum += matrix[i * numColumns + j];
        }
    }
    return sum;
}

// Funcția de calcul paralel al sumei elementelor matricei
int parallelMatrixSum(const int* matrix, int numRows, int numColumns, int numThreads) {
    int segmentSize = numRows / numThreads;

    std::vector<std::thread> threads;
    std::vector<int> threadSums(numThreads);

    // Crearea firelor de execuție pentru calculul sumei parțiale
    for (int i = 0; i < numThreads - 1; ++i) {
        int startRow = i * segmentSize;
        int endRow = (i + 1) * segmentSize - 1;
        threads.emplace_back([matrix, numColumns, startRow, endRow, &threadSums, i]() {
            threadSums[i] = calculateSum(matrix, numColumns, startRow, endRow);
            });
    }
    // Ultimul fir de execuție poate avea dimensiunea diferită
    int startRow = (numThreads - 1) * segmentSize;
    int endRow = numRows - 1;
    threads.emplace_back([matrix, numColumns, startRow, endRow, &threadSums, numThreads]() {
        threadSums[numThreads - 1] = calculateSum(matrix, numColumns, startRow, endRow);
        });

    // Așteptarea terminării tuturor firelor de execuție
    for (auto& thread : threads) {
        thread.join();
    }

    // Calculul sumei finale
    int totalSum = std::accumulate(threadSums.begin(), threadSums.end(), 0);

    return totalSum;
}

int* readMatrixFromFile(const std::string& filename, int& numRows, int& numColumns) {
    std::ifstream file(filename);
    if (file.is_open()) {
        file >> numRows >> numColumns;

        int* matrix = new int[numRows * numColumns];
        for (int i = 0; i < numRows; ++i) {
            for (int j = 0; j < numColumns; ++j) {
                file >> matrix[i * numColumns + j];
            }
        }

        file.close();
        return matrix;
    }
    return nullptr;
}

int main() {
    std::string filename = "matrice1000.txt";

    int numRows, numColumns;
    int* matrix = readMatrixFromFile(filename, numRows, numColumns);
    auto start = std::chrono::high_resolution_clock::now();

    int numThreads = 3;

    int sum = parallelMatrixSum(matrix, numRows, numColumns, numThreads);

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    std::cout << "Suma elementelor matricei: " << sum << std::endl;
    std::cout << "Timpul de executie: " << duration.count() << " secunde" << std::endl;

    delete[] matrix;

    return 0;
}
