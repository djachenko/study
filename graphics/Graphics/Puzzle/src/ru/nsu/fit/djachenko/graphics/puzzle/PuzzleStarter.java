package ru.nsu.fit.djachenko.graphics.puzzle;

import ru.nsu.fit.djachenko.graphics.puzzle.view.Window;
import ru.nsu.fit.djachenko.graphics.puzzle.controller.PuzzleContoller;

import javax.imageio.ImageIO;
import java.io.File;
import java.io.IOException;

class PuzzleStarter
{
	public static void main(String[] args) throws IOException
	{
		Window window = new Window(new PuzzleContoller(ImageIO.read(new File("puzzle/res/img/puzzle.png"))));

		window.setVisible(true);
	}
}
