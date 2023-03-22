package com.ucv.apd.homework.model;

public class Calculator {

    public float calculateSum(float[][] matrix) {
        float sum = 0;
        for (float[] row : matrix) {
            for (float element : row) {
                sum += element;
            }
        }
        return sum;
    }
}
