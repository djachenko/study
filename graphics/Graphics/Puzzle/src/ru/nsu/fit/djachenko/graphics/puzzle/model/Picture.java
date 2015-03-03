package ru.nsu.fit.djachenko.graphics.puzzle.model;

import java.awt.image.BufferedImage;

public class Picture
{
	private int[][] display;

	private boolean bilineEnabled = false;

	public Picture(BufferedImage image)
	{
		display = new int[image.getHeight()][image.getWidth()];

		for (int y = 0; y < display.length; y++)
		{
			for (int x = 0; x < display[y].length; x++)
			{
				display[y][x] = image.getRGB(x, y);
			}
		}
	}

	public int getPixel(double x, double y)
	{
		if (bilineEnabled)
		{
			int resX = (int)Math.round(x);
			int resY = (int)Math.round(y);

			if (resY >= display.length)
			{
				resY = display.length - 1;
			}
			if (resX >= display[0].length)
			{
				resX = display[0].length - 1;
			}
			if (resY <= 0)
			{
				resY = 0;
			}
			if (resX <= 0)
			{
				resX = 0;
			}

			return display[resY][resX];
		}
		else
		{
			return biline(x, y);
		}
	}
	
	private int biline(double x, double y)
	{
		int left = (int)Math.floor(x);
		int top = (int)Math.floor(y);

		double deltaX = x - Math.floor(x);
		double deltaY = y - Math.floor(y);

		if (left >= display.length)
		{
			left = display.length - 1;
		}
		if (top >= display[0].length)
		{
			top = display[0].length - 1;
		}
		if (left <= 0)
		{
			left = 0;
		}
		if (top <= 0)
		{
			top = 0;
		}

		int right = (left < display.length - 1) ? left + 1 : left;
		int bottom = (top < display[0].length - 1) ? top + 1 : top;

		int result = 0;

		for (int i = 0; i < 4; i++)
		{
			result |= ((int)(((display[top][left] >> i * 8) & 0xFF) * (1 - deltaX) * (1 - deltaY)
			                 + ((display[top][right] >> i * 8) & 0xFF) * (deltaX) * (1 - deltaY)
			                 + ((display[bottom][left] >> i * 8) & 0xFF) * (1 - deltaX) * (deltaY)
			                 + ((display[bottom][right] >> i * 8) & 0xFF) * (deltaX) * (deltaY)) << i * 8);
		}

		return result;
	}

	public int getWidth()
	{
		return getHeight() > 0 ? display[0].length : 0;
	}

	public int getHeight()
	{
		return display != null ? display.length : 0;
	}

	public void enableBiline()
	{
		bilineEnabled = true;
	}

	public void disableBiline()
	{
		bilineEnabled = false;
	}
}
