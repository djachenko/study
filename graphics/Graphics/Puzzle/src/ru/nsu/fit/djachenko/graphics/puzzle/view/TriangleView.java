package ru.nsu.fit.djachenko.graphics.puzzle.view;

import ru.nsu.fit.djachenko.graphics.puzzle.model.Triangle;

import java.awt.*;
import java.awt.geom.Point2D;
import java.util.Arrays;

public class TriangleView
{
	private final Triangle source;

	private int totalPixelCount = 0;
	private int edgePixelCount = 0;
	private int opaquePixelCount = 0;

	public TriangleView(Triangle source)
	{
		this.source = source;
	}

	public void draw(Canvas canvas, int xOffset, int yOffset)
	{
		Point2D.Double[] vertices = source.getVertices();

		opaquePixelCount = 0;
		totalPixelCount = 0;

		texture(canvas, vertices, xOffset, yOffset);

		edgePixelCount = 0;

		for (int i = 0; i < 3; i++)
		{
			bresenham(canvas, vertices[i], vertices[(i + 1) % 3], xOffset, yOffset);
		}
	}

	private int sgn(double a)
	{
		if (a > 0)
		{
			return 1;
		}
		else if (a < 0)
		{
			return -1;
		}

		return 0;
	}

	private void bresenham(Canvas canvas, Point2D.Double point1, Point2D.Double point2, int xOffset, int yOffset)
	{
		double x1 = point1.getX();
		double y1 = point1.getY();

		double x2 = point2.getX();
		double y2 = point2.getY();

		int lengthX = (int)Math.round(x2 - x1);
		int lengthY = (int)Math.round(y2 - y1);

		int sgnX = sgn(lengthX);
		int sgnY = sgn(lengthY);

		lengthX = Math.abs(lengthX);
		lengthY = Math.abs(lengthY);

		int deltaX;
		int deltaY;

		int shiftX;
		int shiftY;

		double deltaErr;
		int parameterLimit;

		if (lengthX >= lengthY)
		{
			deltaX = sgnX;
			deltaY = 0;

			shiftX = 0;
			shiftY = sgnY;

			deltaErr = 1.0 * lengthY / lengthX;
			parameterLimit = lengthX;
		}
		else
		{
			deltaX = 0;
			deltaY = sgnY;

			shiftX = sgnX;
			shiftY = 0;

			deltaErr = 1.0 * lengthX / lengthY;
			parameterLimit = lengthY;
		}

		int x = (int)Math.round(x1);
		int y = (int)Math.round(y1);

		double err = 0;

		int black = Color.black.getRGB();

		for (int t = 0; t <= parameterLimit; t++)
		{
			canvas.setPixel(x + xOffset, y + yOffset, black);

			err += deltaErr;

			if (err > 0.5)
			{
				err -= 1;

				x += shiftX;
				y += shiftY;
			}

			x += deltaX;
			y += deltaY;

			edgePixelCount++;
		}
	}

	private void texture(Canvas canvas, Point2D.Double[] vertices, int xOffset, int yOffset)
	{
		Arrays.sort(vertices, (o1, o2)->{
			double res = o1.getY() - o2.getY();

			if (Math.abs(res) < 0.00001)
			{
				return 0;
			}
			else if (res < 0)
			{
				return -1;
			}
			else
			{
				return 1;
			}
		});

		double deltaX01 = 1.0 * (vertices[1].getX() - vertices[0].getX()) / Math.abs(vertices[1].getY() - vertices[0].getY());
		double deltaX02 = 1.0 * (vertices[2].getX() - vertices[0].getX()) / Math.abs(vertices[2].getY() - vertices[0].getY());

		int y0 = (int)Math.round(vertices[0].getY());
		double x0 = vertices[0].getX();

		double y1 = vertices[1].getY();

		double leftDx = deltaX01 < deltaX02 ? deltaX01 : deltaX02;
		double rightDx = deltaX01 < deltaX02 ? deltaX02 : deltaX01;

		for (int t = 1; t < y1 - y0; t++)
		{
			int y = y0 + t;

			int leftX = (int)Math.round(x0 + leftDx * t);
			int rightX = (int)Math.round(x0 + rightDx * t);

			for (int x = leftX; x <= rightX; x++)
			{
				canvas.setPixel(x + xOffset, y + yOffset, source.getPixel(x, y));

				totalPixelCount++;

				if ((source.getPixel(x, y) >> 24 & 0xFF) == 0xFF)
				{
					opaquePixelCount++;
				}
			}
		}

		double deltaX21 = 1.0 * (vertices[1].getX() - vertices[2].getX()) / Math.abs(vertices[1].getY() - vertices[2].getY());
		double deltaX20 = -deltaX02;

		int y2 = (int)Math.round(vertices[2].getY());
		double x2 = vertices[2].getX();

		leftDx = deltaX21 < deltaX20 ? deltaX21 : deltaX20;
		rightDx = deltaX21 < deltaX20 ? deltaX20 : deltaX21;

		for (int t = 1; t <= y2 - y1; t++)
		{
			int y = y2 - t;

			int leftX = (int)Math.round(x2 + leftDx * t);
			int rightX = (int)Math.round(x2 + rightDx * t);

			for (int x = leftX; x <= rightX; x++)
			{
				canvas.setPixel(x + xOffset, y + yOffset, source.getPixel(x, y));

				totalPixelCount++;

				if ((source.getPixel(x, y) >> 24 & 0xFF) == 0xFF)
				{
					opaquePixelCount++;
				}
			}
		}
	}

	public boolean contains(int x, int y)
	{
		Point2D.Double point = new Point2D.Double(x, y);
		Point2D.Double[] vertices = source.getVertices();

		double sum = 0;

		for (int i = 0; i < 3; i++)
		{
			sum += square(vertices[i], vertices[(i + 1) % 3], point);
		}

		return Math.abs(square(vertices[0], vertices[1], vertices[2]) - sum) < 0.0001;
	}

	private double square(Point2D.Double a, Point2D.Double b, Point2D.Double c)
	{
		return Math.abs((a.getX() - c.getX()) * (b.getY() - c.getY()) + (b.getX() - c.getX()) * (c.getY() - a.getY()));
	}

	public int getTotalPixelCount()
	{
		return totalPixelCount;
	}

	public int getEdgePixelCount()
	{
		return edgePixelCount;
	}

	public int getOpaquePixelCount()
	{
		return opaquePixelCount;
	}
}
