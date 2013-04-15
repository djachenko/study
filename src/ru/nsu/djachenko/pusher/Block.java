package ru.nsu.djachenko.pusher;

public class Block
{
	private Field field = null;
	private int x = -1;
	private int y = -1;

	public Block(Field iField, int iX, int iY)
	{
		this.field = iField;
		this.x = iX;
		this.y = iY;
	}

	public void moveLeft()
	{
		if (field.getCell(x - 1, y) == Field.States.FLOOR)
		{
			x--;
		}
	}

	public void moveRight()
	{
		switch (field.getCell(x + 1, y))
		{
			case FLOOR:
			{
				x++;

				break;
			}
			case BLOCK:
			{

			}
		}
	}

	public void moveUp()
	{
		if (field.getCell(x, y + 1) == Field.States.FLOOR)
		{
			y++;
		}
	}

	public void moveDown()
	{
		if (field.getCell(x, y - 1) == Field.States.FLOOR)
		{
			y--;
		}
	}

/*
1. хранить передвигающиеся блоки отдельно от поля, поле - только стены и пространство
2. блоки только в поле
3. и там, и там.
что будет лучше?
и что делать с точками?
*/
}
