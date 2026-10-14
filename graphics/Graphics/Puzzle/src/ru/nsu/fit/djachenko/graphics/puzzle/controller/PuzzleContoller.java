package ru.nsu.fit.djachenko.graphics.puzzle.controller;

import ru.nsu.fit.djachenko.graphics.puzzle.model.Picture;
import ru.nsu.fit.djachenko.graphics.puzzle.model.Triangle;
import ru.nsu.fit.djachenko.graphics.puzzle.view.Canvas;
import ru.nsu.fit.djachenko.graphics.puzzle.view.ControlPanel;
import ru.nsu.fit.djachenko.graphics.puzzle.view.TriangleView;

import javax.swing.*;
import java.awt.geom.Point2D;
import java.awt.image.BufferedImage;
import java.util.LinkedList;
import java.util.List;

public class PuzzleContoller
{
	private static final int GRIDWIDTH = 4;
	private static final int GRIDHEIGHT = 4;

	private static final double AMPLITUDE = 64;
	private static final int DISTANCE = 64;

	private static final int STEP_COUNT = 180;

	private final Picture image;

	private final Triangle[][][] triangleGrid;

	private int index = 0;

	private final ControlPanel controlPanel;
	private final Canvas canvas;

	private final Timer timer = new Timer(10, e->iteration());
	
	public PuzzleContoller(BufferedImage source)
	{
		image = new Picture(source);

		List<TriangleView> triangles = new LinkedList<>();
		triangleGrid = new Triangle[GRIDHEIGHT][GRIDWIDTH][2];

		for (int y = 0; y < GRIDHEIGHT; y++)
		{
			for (int x = 0; x < GRIDWIDTH; x++)
			{
				triangleGrid[y][x][0] = new Triangle(new Point2D.Double(x * source.getWidth() / GRIDWIDTH, y * source.getHeight() / GRIDHEIGHT),
				                                     new Point2D.Double((x + 1) * source.getWidth() / GRIDWIDTH - 1, y * source.getHeight() / GRIDHEIGHT),
				                                     new Point2D.Double(x * source.getWidth() / GRIDWIDTH, (y + 1) * source.getHeight() / GRIDHEIGHT - 1),
				                                     image);

				triangleGrid[y][x][1] = new Triangle(new Point2D.Double((x + 1) * source.getWidth() / GRIDWIDTH, (y + 1) * source.getHeight() / GRIDHEIGHT),
				                                     new Point2D.Double((x + 1) * source.getWidth() / GRIDWIDTH, y * source.getHeight() / GRIDHEIGHT),
				                                     new Point2D.Double(x * source.getWidth() / GRIDWIDTH, (y + 1) * source.getHeight() / GRIDHEIGHT),
				                                     image);

				triangles.add(new TriangleView(triangleGrid[y][x][0]));
				triangles.add(new TriangleView(triangleGrid[y][x][1]));
			}
		}

		canvas = new Canvas(image.getWidth(), image.getHeight(), triangles);

		controlPanel = new ControlPanel(this);
	}

	private void iteration()
	{
		index = (index + 1) % (2 * STEP_COUNT);

		step(index);
		controlPanel.setSlider(index);
	}

	public void step(int t)
	{
		t %= 2 * STEP_COUNT;

		double straight = (STEP_COUNT - Math.abs(STEP_COUNT - (t % (2 * STEP_COUNT)))) * DISTANCE / STEP_COUNT;
		double wave = AMPLITUDE * (Math.sin(t * 2 * Math.PI / STEP_COUNT));

		for (int y = 0; y < triangleGrid.length; y++)
		{
			for (int x = 0; x < triangleGrid[y].length; x++)
			{
				if (x < GRIDWIDTH / 2)
				{
					if (y < GRIDHEIGHT / 2)
					{
						triangleGrid[y][x][0].move(-wave, -straight);
						triangleGrid[y][x][1].move(wave, -straight);
					}
					else
					{
						triangleGrid[y][x][0].move(-straight, -wave);
						triangleGrid[y][x][1].move(-straight, wave);
					}
				}
				else
				{
					if (y < GRIDHEIGHT / 2)
					{
						triangleGrid[y][x][0].move(straight, -wave);
						triangleGrid[y][x][1].move(straight, wave);
					}
					else
					{
						triangleGrid[y][x][0].move(-wave, straight);
						triangleGrid[y][x][1].move(wave, straight);
					}
				}

				triangleGrid[y][x][0].turn(Math.toRadians(-10 * t));
				triangleGrid[y][x][1].turn(Math.toRadians(t));
			}
		}

		index = t;
	}

	public void reset()
	{
		step(0);

		index = 0;

		controlPanel.setSlider(0);
	}

	public void start()
	{
		timer.start();
	}

	public void stop()
	{
		timer.stop();
	}

	public void setIndex(int t)
	{
		index = t;
	}

	public void enableBlending()
	{
		canvas.enableBlending();
	}

	public void disableBlending()
	{
		canvas.disableBlending();
	}

	public void enableBiline()
	{
		image.enableBiline();
	}

	public void disableBiline()
	{
		image.disableBiline();
	}

	public ControlPanel getControlPanel()
	{
		return controlPanel;
	}

	public Canvas getCanvas()
	{
		return canvas;
	}
}
