package com.ucv.apd.homework.model;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;

public class MatrixFileReader {
    public static final String SEPARATOR = " ";

    public float[][] readMatrix(String fileName, int rows, int columns) {
        InputStream inputStream = getFileFromResources(fileName);
        float[][] matrix;
        try {
            BufferedReader bufferedReader = new BufferedReader(new InputStreamReader(inputStream));
            matrix = getMatrix(rows, columns, bufferedReader);
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
        return matrix;
    }

    private static float[][] getMatrix(int rows, int columns, BufferedReader bufferedReader) throws IOException {
        float[][] matrix = new float[rows][columns];
        for (int i = 0; i < rows; i++) {
            String[] row = bufferedReader.readLine().split(SEPARATOR);
            for (int j = 0; j < columns; j++) {
                matrix[i][j] = Integer.parseInt(row[j]);
            }
        }
        return matrix;
    }

    private InputStream getFileFromResources(String fileName) {
        ClassLoader classloader = Thread.currentThread().getContextClassLoader();
        return classloader.getResourceAsStream(fileName);
    }
}
