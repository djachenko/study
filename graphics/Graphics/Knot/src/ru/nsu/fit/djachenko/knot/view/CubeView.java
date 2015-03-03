package ru.nsu.fit.djachenko.knot.view;

import ru.nsu.fit.djachenko.knot.Functions;
import ru.nsu.fit.djachenko.knot.model.Cube;
import ru.nsu.fit.djachenko.knot.model.MyPoint3D;

import javax.swing.*;
import java.awt.*;
import java.awt.geom.Point2D;

public class CubeView extends JComponent
{
	private final Cube origin;

	public static final int WIDTH = 200;
	public static final int HEIGHT = 200;

	public static final int dEye = 100;
	public static final int dPlos = 30;

	public CubeView(Cube origin)
	{
		this.origin = origin;

		initUI();
	}

	private void initUI()
	{
		setPreferredSize(new Dimension(WIDTH, HEIGHT));

		repaint();
	}

	@Override
	protected void paintComponent(Graphics g)
	{
		drawEdges(g);
	}

	private void drawEdges(Graphics g)
	{
		for (MyPoint3D[] edge : origin.getEdges())
		{
			drawThread(g, edge);
		}
	}

	private void drawThread(Graphics g, MyPoint3D[] gridLine)
	{
		int xOffset = WIDTH / 2;
		int yOffset = HEIGHT / 2;

		for (MyPoint3D point : gridLine)
		{
			point.z += dPlos + dEye;
		}

		Point2D.Double point1;
		Point2D.Double point2;

		if (gridLine[0].z * gridLine[1].z < 0)
		{
			MyPoint3D delta = new MyPoint3D((gridLine[1].x - gridLine[0].x),
			                                (gridLine[1].y - gridLine[0].y),
			                                (gridLine[1].z - gridLine[0].z));

			delta.multiply(1 / (gridLine[1].z - gridLine[0].z));

			if (gridLine[0].z < 0)
			{
				point1 = new Point2D.Double(gridLine[1].x - gridLine[1].z * delta.x,
				                            gridLine[1].y - gridLine[1].z * delta.y);

				point2 = new Point2D.Double(gridLine[1].x * dEye / (dEye + dPlos + gridLine[1].z),
				                            gridLine[1].y * dEye / (dEye + dPlos + gridLine[1].z));
			}
			else
			{
				point1 = new Point2D.Double(gridLine[0].x * dEye / (dEye + dPlos + gridLine[0].z),
				                            gridLine[0].y * dEye / (dEye + dPlos + gridLine[0].z));

				point2 = new Point2D.Double(gridLine[0].x - gridLine[0].z * delta.x,
				                            gridLine[0].y - gridLine[0].z * delta.y);
			}
		}
		else
		{
			if (gridLine[0].z < 0 && gridLine[1].z < 0)
			{
				point1 = new Point2D.Double(- xOffset - 1, - yOffset - 1);
				point2 = new Point2D.Double(- xOffset - 1, - yOffset - 1);
			}
			else
			{
				point1 = new Point2D.Double(gridLine[0].x * dEye / (dEye + dPlos + gridLine[0].z),
				                            gridLine[0].y * dEye / (dEye + dPlos + gridLine[0].z));
				point2 = new Point2D.Double(gridLine[1].x * dEye / (dEye + dPlos + gridLine[1].z),
				                            gridLine[1].y * dEye / (dEye + dPlos + gridLine[1].z));
			}
		}

		point1.x += xOffset;
		point1.y += yOffset;
		point2.x += xOffset;
		point2.y += yOffset;

		g.drawLine((int)Math.round(point1.x),
		           (int)Math.round(point1.y),
		           (int)Math.round(point2.x),
		           (int)Math.round(point2.y));

		for (MyPoint3D point : gridLine)
		{
			point.z -= dPlos + dEye;
		}
	}

	private void drawLine(Graphics g, double x1, double y1, double x2, double y2)
	{
		int lengthX = (int)Math.round(x2 - x1);
		int lengthY = (int)Math.round(y2 - y1);

		int sgnX = Functions.sgn(lengthX);
		int sgnY = Functions.sgn(lengthY);

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

		for (int t = 0; t <= parameterLimit; t++)
		{
			Functions.setPixel(g, x, y);

			err += deltaErr;

			if (err > 0.5)
			{
				err -= 1;

				x += shiftX;
				y += shiftY;
			}

			x += deltaX;
			y += deltaY;

		}
	}
}
