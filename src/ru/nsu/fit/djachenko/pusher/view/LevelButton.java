package ru.nsu.fit.djachenko.pusher.view;

import javax.swing.*;

public class LevelButton extends JButton
{
	public final int index;//because we need index for every button

	public LevelButton(String text, int index)
	{
		super(text);

		this.index = index;
	}
}
