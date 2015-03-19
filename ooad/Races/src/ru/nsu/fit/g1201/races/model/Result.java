package ru.nsu.fit.g1201.races.model;

public class Result implements Comparable<Result>{

    private String nickname;
    private long score;
    private int mapIndex;

    public String getNickname() {
        return nickname;
    }

    public long getScore() {
        return score;
    }

    public int getMapIndex() {
        return mapIndex;
    }

    public void setNickname(String nickname) {
        this.nickname = nickname;
    }

    public void setScore(long score) {
        this.score = score;
    }

    public void setMapIndex(int mapIndex) {
        this.mapIndex = mapIndex;
    }


    @Override
    public int compareTo(Result result) {
        if (score < result.getScore()) {
            return 1;
        }
        if (score > result.getScore()) {
            return -1;
        }
        return 0;
    }

	@Override
	public String toString()
	{
		return nickname + " " + score + " " + mapIndex;
	}
}
