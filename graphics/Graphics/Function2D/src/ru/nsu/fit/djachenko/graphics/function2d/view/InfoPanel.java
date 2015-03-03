package ru.nsu.fit.djachenko.graphics.function2d.view;

import javax.swing.*;

class InfoPanel extends JPanel
{
	private final JLabel value = new JLabel();

	InfoPanel()
	{
		initUI();
	}

	private void initUI()
	{
		setLayout(new BoxLayout(this, BoxLayout.Y_AXIS));

		add(value);

		stash();
	}

	void stash()
	{
		value.setText("function(undefined, undefined): undefined");
	}

	void set(int x, int y, double function)
	{
		value.setText("function(" + x + ", " + y + "): " + function);
	}
}
