package ru.nsu.fit.g1201.races.model;

public class Result implements Comparable<Result>{

    private String nickname;
    private long scores;
    private String map;

    public String getNickname() {
        return nickname;
    }

    public long getScores() {
        return scores;
    }

    public String getMap() {
        return map;
    }

    public void setNickname(String nickname) {
        this.nickname = nickname;
    }

    public void setScores(long scores) {
        this.scores = scores;
    }

    public void setMap(String map) {
        this.map = map;
    }


    @Override
    public int compareTo(Result result) {
        if (scores < result.getScores()) {
            return 1;
        }
        if (scores > result.getScores()) {
            return -1;
        }
        return 0;
    }
}
