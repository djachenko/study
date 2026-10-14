package ru.nsu.fit.djachenko.graphics.function2d.view;

import javax.swing.*;
import java.awt.*;

public class ISWindow extends JFrame
{
	public ISWindow(int[] colors)
	{
		initUI(colors);
	}

	private void initUI(int[] colors)
	{
		Container container = getContentPane();

		container.setLayout(new GridBagLayout());

		InfoPanel infoPanel = new InfoPanel();
		Canvas canvas = new Canvas(colors, infoPanel);

		JButton settingsButton = new JButton("Settings");
		settingsButton.setPreferredSize(new Dimension(settingsButton.getWidth(), 30));

		JDialog dialog = new SettingsDialog(this, canvas::setMode, canvas::setIsolinesEnabled, canvas::setGridEnabled);

		settingsButton.addActionListener(e -> dialog.setVisible(true));

		GridBagConstraints infoPanelConstraints = new GridBagConstraints();

		infoPanelConstraints.gridy = 1;
		infoPanelConstraints.fill = GridBagConstraints.HORIZONTAL;


		container.add(infoPanel, infoPanelConstraints);

		GridBagConstraints canvasConstraints = new GridBagConstraints();

		canvasConstraints.gridy = 2;
		canvasConstraints.weightx = 1;
		canvasConstraints.weighty = 1;
		canvasConstraints.fill = GridBagConstraints.BOTH;

		container.add(canvas, canvasConstraints);

		GridBagConstraints legendConstraints = new GridBagConstraints();

		legendConstraints.gridheight = 2;
		legendConstraints.gridx = 1;
		legendConstraints.gridy = 1;
		legendConstraints.fill = GridBagConstraints.VERTICAL;

		container.add(new Legend(colors), legendConstraints);

		GridBagConstraints buttonConstraints = new GridBagConstraints();

		buttonConstraints.gridwidth = 2;
		buttonConstraints.fill = GridBagConstraints.HORIZONTAL;
		buttonConstraints.insets = new Insets(5, 10, 5, 10);

		container.add(settingsButton, buttonConstraints);

		setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);

		pack();
		setLocationRelativeTo(null);

		repaint();
	}
}