package ru.nsu.fit.djachenko.graphics.function2d.view;

import javax.swing.*;
import java.awt.*;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import java.util.function.Consumer;

public class SettingsDialog extends JDialog
{
	public SettingsDialog(JFrame frame, Consumer<Canvas.Mode> modeSetter, Consumer<Boolean> isolinesSetter, Consumer<Boolean> gridSetter)
	{
		super(frame, "The Dialog Title", false);
		
		Container container = getContentPane();

		JList<String> list = new JList<>(new String[]{"Areas", "Interpolated", "Dithering"});

		list.setSelectionMode(ListSelectionModel.SINGLE_SELECTION);
		list.addListSelectionListener(e -> {
			switch (list.getSelectedIndex())
			{
				case 0:
					modeSetter.accept(Canvas.Mode.AREAS);
					break;
				case 1:
					modeSetter.accept(Canvas.Mode.INTERPOLATION);
					break;
				case 2:
					modeSetter.accept(Canvas.Mode.DITHERING);
					break;
				default:
					break;
			}
		});

		GridBagConstraints listConstraints = new GridBagConstraints();

		listConstraints.gridheight = 2;
		listConstraints.weightx = 1;
		listConstraints.weighty = 1;
		listConstraints.anchor = GridBagConstraints.CENTER;

		JCheckBox isolineCheckbox = new JCheckBox("Isolines");

		isolineCheckbox.addActionListener(e -> isolinesSetter.accept(isolineCheckbox.isSelected()));

		GridBagConstraints isolineCheckboxConstraints = new GridBagConstraints();

		isolineCheckboxConstraints.gridx = 1;
		isolineCheckboxConstraints.weightx = 1;
		isolineCheckboxConstraints.weighty = 1;
		isolineCheckboxConstraints.anchor = GridBagConstraints.CENTER;

		JCheckBox gridCheckbox = new JCheckBox("Grid");

		gridCheckbox.addActionListener(e -> gridSetter.accept(gridCheckbox.isSelected()));

		GridBagConstraints gridCheckboxConstraints = new GridBagConstraints();

		gridCheckboxConstraints.gridx = 1;
		gridCheckboxConstraints.gridy = 1;
		gridCheckboxConstraints.weightx = 1;
		gridCheckboxConstraints.weighty = 1;
		gridCheckboxConstraints.anchor = GridBagConstraints.CENTER;

		setLayout(new GridBagLayout());

		container.add(list, listConstraints);
		container.add(isolineCheckbox, isolineCheckboxConstraints);
		container.add(gridCheckbox, gridCheckboxConstraints);

		setSize(new Dimension(200, 100));
		setLocationRelativeTo(null);

		addWindowListener(new WindowAdapter()
		{
			@Override
			public void windowClosing(WindowEvent e)
			{
				setVisible(false);
			}
		});
	}
}
