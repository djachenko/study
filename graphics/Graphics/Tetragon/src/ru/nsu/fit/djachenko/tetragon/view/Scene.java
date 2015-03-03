package ru.nsu.fit.djachenko.tetragon.view;

import ru.nsu.fit.djachenko.tetragon.model.MIP;
import ru.nsu.fit.djachenko.tetragon.model.Tetragon;

import javax.imageio.ImageIO;
import javax.swing.*;
import java.awt.*;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.awt.geom.Point2D;
import java.io.File;
import java.io.IOException;
import java.util.LinkedList;
import java.util.List;

public class Scene extends JPanel
{
	public static final int DEFAULT_WIDTH = 512;
	public static final int DEFAULT_HEIGHT = 512;

	private final List<TetragonView> tetragons = new LinkedList<>();
	private final TetragonGenerator generator = new TetragonGenerator();
	private final MIP mip;

	public Scene() throws IOException
	{
		mip = new MIP(ImageIO.read(new File("tetragon/res/earth3.png")));

		initUI();
	}

	private void initUI()
	{
		setPreferredSize(new Dimension(DEFAULT_WIDTH, DEFAULT_HEIGHT));
		setSize(DEFAULT_WIDTH, DEFAULT_HEIGHT);

		addMouseListener(new MouseAdapter()
		{
			private final Point2D.Double[] tempPoints = new Point2D.Double[4];
			private int tempCount = 0;

			@Override
			public void mousePressed(MouseEvent e)
			{
				tempPoints[tempCount] = new Point2D.Double(1.0 * e.getX() / getWidth(), 1.0 * e.getY() / getHeight());
				tempCount++;

				if (tempCount == 4)
				{
					add(new TetragonView(new Tetragon(tempPoints[0],
					                                  tempPoints[1],
					                                  tempPoints[2],
					                                  tempPoints[3])));
					repaint();

					tempCount = 0;
				}
			}
		});

		repaint();
	}

	public void add(TetragonView tetragonView)
	{
		tetragons.add(tetragonView);
		repaint();
	}

	public void addRandomTriangle()
	{
		Tetragon tetragon = generator.generate();
		add(new TetragonView(tetragon));
	}

	public void clear()
	{
		tetragons.clear();
		repaint();
	}

	@Override
	protected void paintComponent(Graphics g)
	{
		super.paintComponent(g);

		for (TetragonView tetragon : tetragons)
		{
			tetragon.paint(g, this, mip);
		}
	}

	void setFilter(boolean state)
	{
		mip.setFilterEnabled(state);
		repaint();
	}
}
