package org.example;

import java.util.List;

public class Multiplication implements Runnable {
    Matrix a, b, c;
    List<int[]> indexes;

    Multiplication(Matrix a, Matrix b, Matrix c, List<int[]> indexes) {
        this.a = a;
        this.b = b;
        this.c = c;
        this.indexes = indexes;
    }

    @Override
    public void run() {
        for (int[] p : indexes) {
            calc(a, b, c, p);
        }
    }

    void calc(Matrix a, Matrix b, Matrix c, int[] row_col) {
        for (int i = 0; i < 9; ++i)
            c.m[row_col[0]][row_col[1]] += a.m[row_col[0]][i] * b.m[i][row_col[1]];
    }
}
