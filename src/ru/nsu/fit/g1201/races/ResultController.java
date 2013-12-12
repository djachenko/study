package ru.nsu.fit.g1201.races;

import ru.nsu.fit.g1201.races.model.Result;
import ru.nsu.fit.g1201.races.model.TopScores;

import java.util.List;

public class ResultController {

    private TopScores topScores;

    public ResultController(){
        topScores = new TopScores();
    }

    public void newScores(long newScores) {
        if (topScores.isTop(newScores)) {
            //TODO: запилить вызов формы ввода
            Result result = new Result();
            result.setNickname("test");
            result.setScores(newScores);
            result.setMap("test.map"); //TODO: взять мапу из race
            topScores.addResult(result);
        }
    }

    public List<Result> getTopScores() {
        return topScores.getTopScores();
    }

    public int getTopScoresSize() {
        return topScores.size();
    }
}
