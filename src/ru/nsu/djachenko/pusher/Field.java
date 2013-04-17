package ru.nsu.djachenko.pusher;

import ru.nsu.djachenko.pusher.exceptions.PusherException;

import java.io.*;
import java.util.Scanner;

public class Field
{
	public enum States
	{
		WALL,
		FLOOR,
		PUSHER,
		BLOCK,
		POINT
	}

	private States [][] field = null;

	public Field()
	{
	}

	public Field(int x, int y)
	{
		field = new States[y][x];
	}

	public void init(String configFile) throws IOException
	{
		BufferedReader reader = new BufferedReader(new FileReader(configFile));

		{
			Scanner tempScanner = new Scanner(reader.readLine());

			int width = tempScanner.nextInt();
			int height = tempScanner.nextInt();

			field = new States[height][width];
		}

		int x = 0;
		int y = 0;

		readLoop: while (true)
		{
			switch (reader.read())
			{
				case -1:
					break readLoop;
				case 'x':
					field[y][x] = States.WALL;
					break;
				case '.':
					field[y][x] = States.FLOOR;
					break;
				case 't':
					field[y][x] = States.PUSHER;
					break;
				case '*':
					field[y][x] = States.BLOCK;
					break;
				case '&':
					field[y][x] = States.POINT;
					break;
				default:
					break;
			}
		}
	}

	public States getCell(int x, int y) throws PusherException
	{
		if (x < 0 || x > this.getWidth() || y < 0 || y > this.getHeight())
		{
			throw new PusherException("Index out of field bounds");
		}

		return field[y][x];
	}

	public void setCell(int x, int y, States state) throws PusherException//maybe delete?
	{
		if (x < 0 || x > this.getWidth() || y < 0 || y > this.getHeight())
		{
			throw new PusherException("Index out of field bounds");
		}

		field[y][x] = state;
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

		for (States[] i : field)
		{
			for (States j : i)
			{
				if (j == States.BLOCK)
				{
					result++;
				}
			}
		}

		return result;
	}
}
