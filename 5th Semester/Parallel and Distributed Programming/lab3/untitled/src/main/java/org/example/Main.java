package org.example;

import java.util.Objects;

public class Main {
    public static void main(String[] args) {
        String scenario = System.getProperty("scenario");
        if (Objects.equals(scenario, "threadPool"))
            ThreadPool.runThreadPool();
        else
            IndividualThreads.runIndividualThreads(scenario);
    }
}