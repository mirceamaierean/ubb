package org.example;

class Matrix {
    int[][] m = new int[9][9];

    Matrix() {
        reset();
    }

    void reset() {
        for (int i = 0; i < 9; ++i)
            for (int j = 0; j < 9; ++j)
                m[i][j] = 0;
    }

    void set() {
        for (int i = 0; i < 9; ++i)
            for (int j = 0; j < 9; ++j)
                m[i][j] = i * 9 + j;
    }
}
