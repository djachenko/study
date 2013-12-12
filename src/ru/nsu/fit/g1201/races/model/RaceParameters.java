package ru.nsu.fit.g1201.races.model;

public class RaceParameters {

    private String mapName;
    private int speed;

    public void setMapName(String mapName) {
        this.mapName = mapName;
    }

    public void setSpeed(int speed) {
        this.speed = speed;
    }

    public String getMapName() {
        return mapName;
    }

    public int getSpeed() {
        return speed;
    }
}
