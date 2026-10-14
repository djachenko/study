package ru.nsu.fit.djachenko.tetragon.view;

import javax.swing.*;
import java.awt.*;
import java.io.IOException;

public class MainWindow extends JFrame
{
	public MainWindow() throws IOException
	{
		initUI();
	}

	private void initUI() throws IOException
	{
		setLayout(new GridBagLayout());

		Scene scene = new Scene();

		GridBagConstraints sceneConstraints = new GridBagConstraints();

		sceneConstraints.anchor = GridBagConstraints.CENTER;
		sceneConstraints.gridx = 0;
		sceneConstraints.gridy = 0;
		sceneConstraints.weightx = 1;
		sceneConstraints.weighty = 0.8;
		sceneConstraints.fill = GridBagConstraints.BOTH;

		add(scene, sceneConstraints);

		JCheckBox filterCheckBox = new JCheckBox("Filter");

		filterCheckBox.addActionListener(e -> scene.setFilter(filterCheckBox.isSelected()));

		GridBagConstraints filterChechBoxConstraints = new GridBagConstraints();

		filterChechBoxConstraints.anchor = GridBagConstraints.CENTER;
		filterChechBoxConstraints.gridx = 0;
		filterChechBoxConstraints.gridy = 1;
		filterChechBoxConstraints.insets = new Insets(10, 10, 10, 10);

		add(filterCheckBox, filterChechBoxConstraints);

		JButton clearButton = new JButton("Clear");

		clearButton.addActionListener(e -> scene.clear());

		GridBagConstraints clearButtonConstaints = new GridBagConstraints();

		clearButtonConstaints.anchor = GridBagConstraints.CENTER;
		clearButtonConstaints.gridx = 0;
		clearButtonConstaints.gridy = 2;
		clearButtonConstaints.weightx = 1;
		clearButtonConstaints.weighty = .1;
		clearButtonConstaints.fill = GridBagConstraints.BOTH;
		clearButtonConstaints.insets = new Insets(10, 10, 10, 10);

		add(clearButton, clearButtonConstaints);

		JButton generateButton = new JButton("Generate");

		generateButton.addActionListener(e -> scene.addRandomTriangle());

		GridBagConstraints generateButtonConstaints = new GridBagConstraints();

		generateButtonConstaints.anchor = GridBagConstraints.CENTER;
		generateButtonConstaints.gridx = 0;
		generateButtonConstaints.gridy = 3;
		generateButtonConstaints.weightx = 1;
		generateButtonConstaints.weighty = .1;
		generateButtonConstaints.fill = GridBagConstraints.BOTH;
		generateButtonConstaints.insets = new Insets(0, 10, 10, 10);

		add(generateButton, generateButtonConstaints);

		pack();
		setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);
		setLocationRelativeTo(null);
	}
}
