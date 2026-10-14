package ru.nsu.fit.djachenko.graphics.function2d;

import ru.nsu.fit.djachenko.graphics.function2d.view.ISWindow;

import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.util.Scanner;

public class Function2DStarter
{
	public static void main(String[] args)
	{
		try (Scanner scanner = new Scanner(new FileInputStream("function2d/res/colors")))
		{
			int colorCount = scanner.nextInt();

			int[] colors = new int[colorCount];

			for (int i = 0; i < colorCount; i++)
			{
				colors[i] = 0;

				for (int j = 2; j >= 0; j--)
				{
					colors[i] |= (scanner.nextInt() & 0xFF) << (j * 8);
				}
			}

			new ISWindow(colors).setVisible(true);
		}
		catch (FileNotFoundException e)
		{
			e.printStackTrace();
		}
	}
}
