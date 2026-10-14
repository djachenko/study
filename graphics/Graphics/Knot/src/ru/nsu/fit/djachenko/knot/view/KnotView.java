package ru.nsu.fit.djachenko.knot.view;

import ru.nsu.fit.djachenko.knot.model.Knot;
import ru.nsu.fit.djachenko.knot.model.MyPoint3D;
import ru.nsu.fit.djachenko.knot.model.Spline;

import javax.swing.*;
import java.awt.*;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.awt.event.MouseMotionListener;
import java.awt.geom.Point2D;

public class KnotView extends JComponent
{
	public static final int WIDTH = 200;
	public static final int HEIGHT = 200;

	public static final int dEye = 100;
	public static final int dPlos = 30;

	private final Knot knot;

	private boolean boxEnabled = true;
	private CubeView box;

	private Point2D pressed = new Point2D.Double();

	public KnotView(Knot knot)
	{
		this.knot = knot;

		box = new CubeView(knot.getBounds());

		initUI();
	}

	private void initUI()
	{
		addMouseWheelListener(e -> {
			int delta = e.getWheelRotation();
			knot.move(0, 0, delta);
			repaint();
		});

		addMouseListener(new MouseAdapter()
		{
			@Override
			public void mousePressed(MouseEvent e)
			{
				super.mousePressed(e);
				pressed = new Point2D.Double(e.getX(), e.getY());
			}
		});

		addMouseMotionListener(new MouseMotionListener()
		{
			@Override
			public void mouseDragged(MouseEvent e)
			{
				double beta = (e.getX() - pressed.getX());
				double alpha = (e.getY() - pressed.getY());

				pressed = new Point2D.Double(e.getX(), e.getY());

				knot.turn(alpha / 30, - beta / 30, 0);

				repaint();
			}

			@Override
			public void mouseMoved(MouseEvent e) {}
		});

		setPreferredSize(new Dimension(WIDTH, HEIGHT));

		repaint();
	}

	@Override
	protected void paintComponent(Graphics g)
	{
		super.paintComponent(g);

		int splineCount = 256;

		double step = (knot.to() - knot.from()) / splineCount;

		double start = knot.from();

		int splinePointsCount = 4;

		MyPoint3D[] container = new MyPoint3D[splinePointsCount];

		for (int i = 0; i < splineCount; i++)
		{
			double t = start + step * i;

			double splineStep = step / (splinePointsCount - 1);

			for (int j = 0; j < splinePointsCount; j++)
			{
				container[j] = knot.count(t + splineStep * j);
			}

			Spline spline = new Spline(container);

			drawSpline(g, spline);
		}

		if (boxEnabled)
		{
			box.paintComponent(g);
		}
	}

	private void drawSpline(Graphics g, Spline spline)
	{
		int pointCount = 128;

		double step = 1.0 / pointCount;

		MyPoint3D[] container = new MyPoint3D[2];

		container[1] = spline.count(0);

		for (int i = 1; i < pointCount; i++)
		{
			container[0] = container[1];
			container[1] = spline.count(i * step);

			drawThread(g, container);
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

	public void setBoxEnabled(boolean enabled)
	{
		boxEnabled = enabled;
	}
}
