package ru.nsu.djachenko.pusher;

import ru.nsu.djachenko.pusher.cells.*;

import java.io.*;
import java.util.ArrayList;
import java.util.List;

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
		try(BufferedReader reader = new BufferedReader(new FileReader(configFile)))
		{
			List<Cell[]> column = new ArrayList();

			ArrayList<Cell> line = new ArrayList<>();

			int x = 0;
			int y = 0;

			readLoop: while (true)
			{
				switch (reader.read())
				{
					case -1:
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
						line.add(new Pusher(this, x, y));
						x++;
						break;
					case '*':
						line.add(new Block(this, x, y));
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
		return field[ x + dir.getDx() ][ y + dir.getDy() ].ableToMove(dir, strength);
	}

	public void move(int x, int y, Direction dir, int strength)
	{
		field[ x + dir.getDx() ][ y + dir.getDy() ].move(dir, strength);
		field[ x + dir.getDx() ][ y + dir.getDy() ] = field[x][y];

		field[x][y] = new Floor();
	}
}
