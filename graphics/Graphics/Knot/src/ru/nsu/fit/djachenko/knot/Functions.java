package ru.nsu.fit.djachenko.knot;

import java.awt.*;

public class Functions
{
	public static int sgn(double a)
	{
		if (a > 0)
		{
			return 1;
		}
		else if (a == 0)
		{
			return 0;
		}
		else
		{
			return -1;
		}
	}

	public static void setPixel(Graphics g, int x, int y)
	{
		g.drawLine(x, y, x, y);
	}
}
