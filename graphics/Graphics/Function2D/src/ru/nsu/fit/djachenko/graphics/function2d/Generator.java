package ru.nsu.fit.djachenko.graphics.function2d;

import java.awt.*;
import java.io.*;

public class Generator
{
	public static void main(String[] args)
	{
		try (PrintStream stream = new PrintStream(new FileOutputStream("function2d/res/colors")))
		{
			int colorCount = 16;

			stream.println(colorCount);

			for (int i = 0; i < colorCount; i++)
			{
				Color color = new Color(i * 255 / colorCount, i * 255 / colorCount, i * 255 / colorCount);

				stream.println(color.getRed() + " " + color.getGreen() + " " + color.getBlue());
			}
		}
		catch (IOException e)
		{
			e.printStackTrace();
		}
	}
}
