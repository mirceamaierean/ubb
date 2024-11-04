package org.example;

import java.util.ArrayList;
import java.util.List;

public class IndividualThreads {
    public static void runIndividualThreads(String scenario) {
        Matrix a = new Matrix();
        Matrix b = new Matrix();
        Matrix c = new Matrix();
        a.set();
        b.set();

        List<List<int[]>> indexes = new ArrayList<>();
        for (int i = 0; i < 4; ++i)
            indexes.add(new ArrayList<>());

        switch (scenario) {
            case "first":
                generateFirstDistribution(indexes.get(0), 0, 19);
                generateFirstDistribution(indexes.get(1), 20, 39);
                generateFirstDistribution(indexes.get(2), 40, 59);
                generateFirstDistribution(indexes.get(3), 60, 80);
                executeTask(a, b, c, indexes);
                break;

            case "second":
                generateSecondDistribution(indexes.get(0), 0, 19);
                generateSecondDistribution(indexes.get(1), 20, 39);
                generateSecondDistribution(indexes.get(2), 40, 59);
                generateSecondDistribution(indexes.get(3), 60, 80);
                executeTask(a, b, c, indexes);
                break;

            case "third":
                generateThirdDistribution(indexes);
                executeTask(a, b, c, indexes);
                break;

            case "threadPool":
        }



    }

    static void generateFirstDistribution(List<int[]> indexes, int start, int end) {
        for (int i = start; i <= end; ++i)
            indexes.add(new int[] { i / 9, i % 9 });
    }

    static void generateSecondDistribution(List<int[]> indexes, int start, int end) {
        for (int i = start; i <= end; ++i)
            indexes.add(new int[] { i % 9, i / 9 });
    }

    static void generateThirdDistribution(List<List<int[]>> indexes) {
        for (int i = 0; i < 81; ++i) {
            int row = i / 9, col = i % 9;
            indexes.get(i % 4).add(new int[] { row, col });
        }
    }

    static void executeTask(Matrix a, Matrix b, Matrix c, List<List<int[]>> indexes) {
        Thread[] threads = new Thread[4];

        threads[0] = new Thread(new Multiplication(a, b, c, indexes.get(0)));
        threads[1] = new Thread(new Multiplication(a, b, c, indexes.get(1)));
        threads[2] = new Thread(new Multiplication(a, b, c, indexes.get(2)));
        threads[3] = new Thread(new Multiplication(a, b, c, indexes.get(3)));

        for (Thread t : threads)
            t.start();

        for (Thread t : threads) {
            try {
                t.join();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }

        for (int i = 0; i < 9; ++i) {
            for (int j = 0; j < 9; ++j)
                System.out.print(c.m[i][j] + " ");
            System.out.println();
        }
    }
}
