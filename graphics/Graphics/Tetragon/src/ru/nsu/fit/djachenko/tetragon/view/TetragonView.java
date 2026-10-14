package ru.nsu.fit.djachenko.tetragon.view;

import ru.nsu.fit.djachenko.tetragon.model.MIP;
import ru.nsu.fit.djachenko.tetragon.model.Tetragon;

import javax.swing.*;
import java.awt.*;
import java.awt.geom.Ellipse2D;
import java.awt.geom.Point2D;
import java.util.Collections;
import java.util.List;
import java.util.function.Function;

public class TetragonView extends JComponent
{
	private final Tetragon origin;

	public TetragonView(Tetragon origin)
	{
		this.origin = origin;

		initUI();
	}

	private void initUI()
	{
		setPreferredSize(new Dimension(512, 512));
		setOpaque(true);
	}

	protected void paint(Graphics g, Container canvas, MIP mip)
	{
		super.paintComponent(g);

		List<Point2D.Double> points = origin.getPoints();

		double xMax = 0;
		double xMin = 0;
		double yMax = 0;
		double yMin = 0;

		for (Point2D.Double point : points)
		{
			xMin = point.x < xMin ? point.x : xMin;
			xMax = point.x > xMax ? point.x : xMax;

			yMin = point.y < yMin ? point.y : yMin;
			yMax = point.y > yMax ? point.y : yMax;
		}

		g.setColor(Color.BLACK);

		int width = canvas.getWidth();
		int height = canvas.getHeight();

		Tetragon tetragon = new Tetragon(new Point2D.Double(points.get(0).x * width, points.get(0).y * height),
		                                 new Point2D.Double(points.get(1).x * width, points.get(1).y * height),
		                                 new Point2D.Double(points.get(2).x * width, points.get(2).y * height),
		                                 new Point2D.Double(points.get(3).x * width, points.get(3).y * height));

		Function<Point2D.Double, Point2D.Double> triangleToTexture = tetragon.getAMapper();

		drawTexture(g, tetragon.getA().getPoints(), triangleToTexture, mip);

		triangleToTexture = tetragon.getBMapper();

		drawTexture(g, tetragon.getB().getPoints(), triangleToTexture, mip);

		g.setColor(Color.BLACK);

		for (int i = 0; i < points.size(); i++)
		{
			Point2D.Double a = points.get(i);
			Point2D.Double b = points.get((i + 1) % points.size());

			int ax = (int)Math.round(a.x * width);
			int ay = (int)Math.round(a.y * height);

			int bx = (int)Math.round(b.x * width);
			int by = (int)Math.round(b.y * height);

			g.drawLine(ax, ay, bx, by);
		}

		Graphics2D g2d = (Graphics2D)g;
		g2d.setColor(Color.RED);
		Ellipse2D.Double circle = new Ellipse2D.Double(points.get(0).x * width - 5, points.get(0).y * height - 5, 10, 10);
		g2d.fill(circle);

		g2d.setColor(Color.BLUE);
		circle = new Ellipse2D.Double(points.get(1).x * width - 5, points.get(1).y * height - 5, 10, 10);
		g2d.fill(circle);
	}

	private void drawTexture(Graphics g, List<Point2D.Double> vertices, Function<Point2D.Double, Point2D.Double> transform, MIP mip)
	{
		Collections.sort(vertices, (o1, o2) -> {
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

		double deltaX01 = 1.0 * (vertices.get(1).getX() - vertices.get(0).getX()) / Math.abs(vertices.get(1).getY() - vertices.get(0).getY());
		double deltaX02 = 1.0 * (vertices.get(2).getX() - vertices.get(0).getX()) / Math.abs(vertices.get(2).getY() - vertices.get(0).getY());

		int y0 = (int)Math.round(vertices.get(0).getY());
		double x0 = vertices.get(0).getX();

		double y1 = vertices.get(1).getY();

		double leftDx = deltaX01 < deltaX02 ? deltaX01 : deltaX02;
		double rightDx = deltaX01 < deltaX02 ? deltaX02 : deltaX01;

		Point2D.Double transportPoint = new Point2D.Double();

		for (int t = 1; t < y1 - y0; t++)
		{
			int y = y0 + t;

			int leftX = (int)Math.round(x0 + leftDx * t);
			int rightX = (int)Math.round(x0 + rightDx * t);

			for (int x = leftX; x <= rightX; x++)
			{
				transportPoint.x = x;
				transportPoint.y = y;

				Point2D.Double a = transform.apply(transportPoint);

				transportPoint.x++;
				transportPoint.y++;

				Point2D.Double b = transform.apply(transportPoint);

				double delta = Math.max(b.x - a.x, b.y - a.y);

				setPixel(g, x, y, mip.getRGB(a, delta));
			}
		}

		double deltaX21 = 1.0 * (vertices.get(1).getX() - vertices.get(2).getX()) / Math.abs(vertices.get(1).getY() - vertices.get(2).getY());
		double deltaX20 = -deltaX02;

		int y2 = (int)Math.round(vertices.get(2).getY());
		double x2 = vertices.get(2).getX();

		leftDx = deltaX21 < deltaX20 ? deltaX21 : deltaX20;
		rightDx = deltaX21 < deltaX20 ? deltaX20 : deltaX21;

		for (int t = 1; t <= y2 - y1; t++)
		{
			int y = y2 - t;

			int leftX = (int)Math.round(x2 + leftDx * t);
			int rightX = (int)Math.round(x2 + rightDx * t);

			for (int x = leftX; x <= rightX; x++)
			{
				transportPoint.x = x;
				transportPoint.y = y;

				Point2D.Double a = transform.apply(transportPoint);

				transportPoint.x++;
				transportPoint.y++;

				Point2D.Double b = transform.apply(transportPoint);

				double delta = Math.max(b.x - a.x, b.y - a.y);

				setPixel(g, x, y, mip.getRGB(a, delta));
			}
		}
	}/**/

	private void setPixel(Graphics g, Point2D.Double pixel, int rgb)
	{
		setPixel(g, (int)Math.round(pixel.x), (int)Math.round(pixel.y), rgb);
	}

	private void setPixel(Graphics g, int x, int y, int rgb)
	{
		g.setColor(new Color(rgb));
		g.drawLine(x, y, x, y);
	}
}
