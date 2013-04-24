package ru.nsu.djachenko.pusher;


import ru.nsu.djachenko.pusher.cells.Cell;
import ru.nsu.djachenko.pusher.cells.Floor;

import java.io.*;
import java.util.Scanner;

public class Field
{
	private Cell[][] field = null;

	public Field()
	{
	}

	public Field(int x, int y)
	{
		field = new Cell[y][x];
	}

	public void init(String configFile) throws IOException
	{
		BufferedReader reader = new BufferedReader(new FileReader(configFile));

		{
			Scanner tempScanner = new Scanner(reader.readLine());

			int width = tempScanner.nextInt();
			int height = tempScanner.nextInt();

			field = new Cell[height][width];
		}

		int x = 0;
		int y = 0;

		readLoop: while (true)
		{
			switch (reader.read())
			{
				case -1:
					break readLoop;
			}
		}
	}

	public int getWidth()
	{
		if (field.length > 0)
		{
			return field[0].length;
		}
		else
		{
			return 0;
		}
	}

	public int getHeight()
	{
		return field.length;
	}

	public int countBlocks()
	{
		int result = 0;

		for (Cell[] i : field)
		{
			for (Cell j : i)
			{
				if (j == Cell.BLOCK)
				{
					result++;
				}
			}
		}

		return result;
	}

	public boolean ableToMove(int x, int y, Direction dir, int strength)
	{
		return field[ x + dir.getDx() ][ y + dir.getDy() ].ableToMove(dir, strength);
	}

	public void move(int x, int y, Direction dir)
	{
		field[ x + dir.getDx() ][ y + dir.getDy() ].move();
		field[ x + dir.getDx() ][ y + dir.getDy() ] = field[x][y];

		field[x][y] = new Floor();
	}
}
