package ru.nsu.fit.g1201.races.model;

import java.io.File;
import java.io.FilenameFilter;

public class MapList {

    private String[] maps;
	private static final MapList instance = new MapList();

    private MapList() {
        File mapDir = new File("res/maps");
        FilenameFilter filter = new FilenameFilter() {
            @Override
            public boolean accept(File dir, String name) {
                return name.endsWith(".map");
            }
        };
        maps = mapDir.list(filter);
    }

	public static MapList getInstance()
	{
		return instance;
	}

    public String[] getMapList() {
        return maps;
    }
}
