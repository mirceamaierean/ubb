package org.example;

import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.Executors;
import java.util.concurrent.ThreadPoolExecutor;

public class ThreadPool {
    public static void runThreadPool() {
        Matrix a = new Matrix();
        Matrix b = new Matrix();
        Matrix c = new Matrix();
        a.set();
        b.set();

        ThreadPoolExecutor executor = (ThreadPoolExecutor) Executors.newFixedThreadPool(8);


        for (int i = 0; i < 81; ++i) {
            List<int[]> indexes = new ArrayList<>();
            indexes.add(new int[]{i / 9, i % 9});
            Multiplication multiplication = new Multiplication(a, b, c, indexes);
            executor.execute(multiplication);
        }

        executor.shutdown();

        for (int i = 0; i < 9; ++i) {
            for (int j = 0; j < 9; ++j)
                System.out.print(c.m[i][j] + " ");
            System.out.println();
        }
    }


}
