package ru.nsu.fit.g1201.races.model;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.Collections;
import java.util.List;
import java.util.Scanner;

public class TopScores {

    private static int TOP_SIZE = 10;
    private int currentSize;
    private List<Result> topScores;

    public TopScores() {
        topScores = new ArrayList<>(TOP_SIZE);
        File topScoresFile = new File("res/TopScores.txt");

        try (Scanner scanner = new Scanner(topScoresFile)) {
            while (scanner.hasNext()) {
                Result result = new Result();
                result.setNickname(scanner.next());
                result.setScores(scanner.nextLong());
                result.setMap(scanner.next());
                topScores.add(result);
                ++currentSize;
            }
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        }
        Collections.sort(topScores);
    }

    public boolean isTop(long scores) {
        return (scores > topScores.get(currentSize - 1).getScores());
    }

    public void addResult(Result result) {
        if (topScores.size() == TOP_SIZE) {
            topScores.remove(currentSize - 1);
            --currentSize;
        }
        topScores.add(result);
        Collections.sort(topScores);
        ++currentSize;
    }

    public List<Result> getTopScores() {
        return topScores;
    }

    public int size() {
        return currentSize;
    }

}
