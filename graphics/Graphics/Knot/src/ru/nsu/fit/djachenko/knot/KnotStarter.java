package ru.nsu.fit.djachenko.knot;

import ru.nsu.fit.djachenko.knot.model.TrefoilKnot;
import ru.nsu.fit.djachenko.knot.view.MainWindow;

import javax.swing.*;

public class KnotStarter
{
	public static void main(String[] args)
	{
		JFrame window = new MainWindow(new TrefoilKnot());
		window.setVisible(true);
	}
}
