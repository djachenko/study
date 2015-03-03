package ru.nsu.fit.djachenko.pusher.model;

import ru.nsu.fit.djachenko.pusher.model.cells.*;

import java.io.*;
import java.util.ArrayList;

public class Field
{
	private Cell[][] field = null;
	private Pusher pusher;

	public Field()
	{
	}

	public void init(String configFile) throws IOException
	{
		try(BufferedReader reader = new BufferedReader(new FileReader(configFile)))
		{
			ArrayList<Cell[]> column = new ArrayList<>();
			ArrayList<Cell> line = new ArrayList<>();

			int x = 0;
			int y = 0;

			readLoop: while (true)
			{
				switch (reader.read())
				{
					case -1:
						column.add(line.toArray(new Cell[line.size()]));
						break readLoop;
					case 'x':
						line.add(new Wall(this, x, y));
						x++;
						break;
					case '.':
						line.add(new Floor(this, x, y));
						x++;
						break;
					case 't':
						pusher = new Pusher(this, x, y);
						line.add(pusher);
						x++;
						break;
					case '*':
						Block block = new Block(this, x, y);
						line.add(block);
						x++;
						break;
					case '&':
						line.add(new Point(this, x, y));
						x++;
						break;
					case '\n':
						column.add(line.toArray(new Cell[line.size()]));
						line = new ArrayList<>();

						x = 0;
						y++;
						break;
					default:
						break;
				}
			}

			field = column.toArray(new Cell[column.size()][]);
		}
	}

	public boolean ableToMove(int x, int y, Direction dir, int strength)
	{
		return field[ y + dir.getDy() ][ x + dir.getDx() ].ableToMove(dir, strength);
	}

	public void move(int x, int y, Direction dir, int strength)
	{
		boolean isPoint = field[ y + dir.getDy() ][ x + dir.getDx() ].isOnPoint();

		field[ y + dir.getDy() ][ x + dir.getDx() ].move(dir, strength);
		field[ y + dir.getDy() ][ x + dir.getDx() ] = field[y][x];

		if (field[y][x].isOnPoint())
		{
			field[y][x] = new Point(this, x, y);
		}
		else
		{
			field[y][x] = new Floor(this, x, y);
		}

		field[ y + dir.getDy() ][ x + dir.getDx() ].setOnPoint(isPoint);
	}

	public Cell getCell(int x, int y)
	{
		return field[y][x];
	}

	public Pusher getPusher()
	{
		return pusher;
	}

	public int height()
	{
		return field.length;
	}

	public int width()
	{
		return field[0].length;
	}

	public int freePoints()
	{
		int count = 0;

		for (Cell[] row : field)
		{
			for (Cell cell : row)
			{
				if (cell.isOnPoint() && !cell.isBlock())
				{
					count++;
				}
			}
		}

		return count;
	}

	public void print()
	{
		StringBuilder temp = new StringBuilder();

		for (int j = 0; j < height(); j++)
		{
			for (int i = 0; i < width(); i++)
			{
				temp.append(getCell(i, j).type.representation);
			}

			temp.append('\n');
		}

		System.out.print(temp);
	}
}
