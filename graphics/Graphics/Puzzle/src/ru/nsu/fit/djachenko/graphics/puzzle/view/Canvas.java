package ru.nsu.fit.djachenko.graphics.puzzle.view;

import javax.swing.*;
import java.awt.*;
import java.awt.event.MouseEvent;
import java.awt.event.MouseMotionAdapter;
import java.awt.image.BufferedImage;
import java.util.List;

public class Canvas extends JPanel
{
	private List<TriangleView> triangles;
	private BufferedImage canvas;

	private int imageHeight;
	private int imageWidth;
	private final int white = Color.white.getRGB();

	private int offsetX;
	private int offsetY;

	private boolean blending = false;

	public Canvas(int width, int height, List<TriangleView> triangles)
	{
		this.triangles = triangles;

		canvas = new BufferedImage(width * 2, height * 2, BufferedImage.TYPE_INT_ARGB);

		imageWidth = width * 2;
		imageHeight = height * 2;

		offsetX = width / 2;
		offsetY = height / 2;

		initUI();
	}

	private void initUI()
	{
		setLayout(new BoxLayout(this, BoxLayout.X_AXIS));

		final InfoPanel infoPanel = new InfoPanel();

		JLabel imageLabel = new JLabel(new ImageIcon(canvas));

		add(infoPanel);
		add(imageLabel);
		setPreferredSize(new Dimension(imageWidth, imageHeight));

		imageLabel.addMouseMotionListener(new MouseMotionAdapter()
		{
			@Override
			public void mouseMoved(MouseEvent e)
			{
				TriangleView aim = findTriangle(e.getX() - offsetX, e.getY() - offsetY);

				if (aim == null)
				{
					infoPanel.stash();
				}
				else if (blending)
				{
					infoPanel.set(aim.getTotalPixelCount(), aim.getEdgePixelCount(), aim.getOpaquePixelCount());
				}
				else
				{
					infoPanel.set(aim.getTotalPixelCount(), aim.getEdgePixelCount(), aim.getTotalPixelCount());
				}
			}
		});

		redraw();
		repaint();
	}

	public void setPixel(int x, int y, int rgb)
	{
		if (x >= 0 && x < canvas.getWidth() && y >= 0 && y < canvas.getHeight())
		{
			double srcAlpha = 1;
			int canvasRGB = canvas.getRGB(x, y);

			if (blending)
			{
				srcAlpha = ((rgb >> 24) & 0xFF) / 255.0;
			}

			int resultColor = 0xFF << 24;

			for (int i = 0; i < 3; ++i)
			{
				resultColor |= (((int)(((canvasRGB >> i * 8) & 0xFF) * (1 - srcAlpha) + ((rgb >> i * 8) & 0xFF) * srcAlpha)) << i * 8);
			}

			rgb = resultColor;

			canvas.setRGB(x, y, rgb);
		}
	}

	public void enableBlending()
	{
		blending = true;

		redraw();
	}

	public void disableBlending()
	{
		blending = false;

		redraw();
	}

	void redraw()
	{
		clear();

		for (TriangleView triangle : triangles)
		{
			triangle.draw(this, offsetX, offsetY);
		}

		repaint();
	}

	void clear()
	{
		for (int y = 0; y < imageHeight; y++)
		{
			for (int x = 0; x < imageWidth; x++)
			{
				canvas.setRGB(x, y, white);
			}
		}
	}

	private TriangleView findTriangle(int x, int y)
	{
		for (TriangleView triangle : triangles)
		{
			if (triangle.contains(x, y))
			{
				return triangle;
			}
		}

		return null;
	}
}
