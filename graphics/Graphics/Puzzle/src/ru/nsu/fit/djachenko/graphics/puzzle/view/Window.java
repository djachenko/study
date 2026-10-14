package ru.nsu.fit.djachenko.graphics.puzzle.view;

import ru.nsu.fit.djachenko.graphics.puzzle.controller.PuzzleContoller;

import javax.swing.*;

public class Window extends JFrame
{
	public Window(PuzzleContoller contoller)
	{
		initUI(contoller);
	}

	private void initUI(PuzzleContoller contoller)
	{
		setLayout(new BoxLayout(this.getContentPane(), BoxLayout.Y_AXIS));

		final Canvas canvas = contoller.getCanvas();

		add(canvas);
		add(contoller.getControlPanel());

		new Timer(50, e->canvas.redraw()).start();

		setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);

		pack();

		setLocationRelativeTo(null);
		repaint();
	}
}
