package ru.nsu.fit.djachenko.graphics.puzzle.view;

import javax.swing.*;
import java.awt.*;

class InfoPanel extends JPanel
{
	private JLabel title = new JLabel();
	private JLabel total = new JLabel();
	private JLabel edge = new JLabel();
	private JLabel opaque = new JLabel();

	InfoPanel()
	{
		initUI();
	}

	private void initUI()
	{
		setLayout(new BoxLayout(this, BoxLayout.Y_AXIS));

		add(title);
		add(total);
		add(edge);
		add(opaque);

		setPreferredSize(new Dimension(75, 128));

		stash();
	}

	void stash()
	{
		title.setText("No triangle aimed");
		total.setText("Total pixels: 0");
		edge.setText("Edge pixels: 0");
		opaque.setText("Opaque pixels: 0");
	}

	void set(int totalValue, int edgeValue, int opaqueValue)
	{
		title.setText("Triangle aimed");
		total.setText("Total pixels: " + totalValue);
		edge.setText("Edge pixels: " + edgeValue);
		opaque.setText("Opaque pixels: " + opaqueValue);
	}
}
