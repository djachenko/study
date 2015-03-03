package ru.nsu.djachenko.logoworld;

public class Drawer
{
	public static void draw(AP ap)
	{
		for (int i = 0; i < ap.getHeight(); i++)
		{
			for (int j = 0; j < ap.getWidth(); j++)
			{
				if (!ap.getCell(i, j))
				{
					System.out.print(' ');
				} else
				{
					System.out.print('X');
				}
			}

			System.out.println();
		}
	}
}
