package com.ucv.apd.homework;

import com.ucv.apd.homework.model.Calculator;
import com.ucv.apd.homework.model.MatrixFileReader;

public class Main {
    public static final int ROWS = 320;
    public static final int COLUMNS = 320;

    public static void main(String[] args) {
        MatrixFileReader matrixFileReader = new MatrixFileReader();
        Calculator calculator = new Calculator();

        long startTime = System.currentTimeMillis();

        float[][] matrix = matrixFileReader.readMatrix("matrix.txt", ROWS, COLUMNS);
        float sum = calculator.calculateSum(matrix);
        System.out.println("The sum of the matrix elements is: " + sum);

        long endTime = System.currentTimeMillis();
        long executionTime = endTime - startTime;

        System.out.println("The execution time is: " + executionTime + " ms");
    }
}
