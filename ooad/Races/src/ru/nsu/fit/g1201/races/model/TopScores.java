package ru.nsu.fit.g1201.races.model;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.Collections;
import java.util.List;
import java.util.Scanner;

public class TopScores {

	private static final String RESULTPATH= "res/TopScores.txt";
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
                result.setScore(scanner.nextLong());
                result.setMapIndex(scanner.nextInt());
                topScores.add(result);
                ++currentSize;
            }
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        }
        Collections.sort(topScores);
    }

    public boolean isTop(long scores) {
        return (scores > topScores.get(currentSize - 1).getScore());
    }

    public void addResult(Result result) {
        if (topScores.size() == TOP_SIZE) {
            topScores.remove(currentSize - 1);
            --currentSize;
        }
        topScores.add(result);
        Collections.sort(topScores);
        ++currentSize;

	    try (PrintWriter writer = new PrintWriter(new File(RESULTPATH)))
	    {
		    for (Result entry : topScores)
		    {
			    writer.println(entry.toString());
		    }

		    writer.flush();
	    }
	    catch (FileNotFoundException e)
	    {
		    e.printStackTrace();
	    }
    }

    public List<Result> getTopScores() {
        return topScores;
    }

    public int size() {
        return currentSize;
    }

}
