package ru.nsu.fit.djachenko.pusher.view;

import ru.nsu.fit.djachenko.pusher.model.RecordTable;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class ChampionView extends JDialog
{
	private int level;
	private long time;
	private int count;

	public ChampionView(int level, long time, int count)
	{
		this.level = level;
		this.time = time;
		this.count = count;

		initUI();
	}

	public void initUI()
	{
		setLayout(new BoxLayout(getContentPane(), BoxLayout.Y_AXIS));

		add(Box.createRigidArea(new Dimension(0, 10)));

		JLabel name = new JLabel("Enter your name, please:");
		{
			name.setAlignmentX(CENTER_ALIGNMENT);
		}
		add(name);

		add(Box.createRigidArea(new Dimension(0, 10)));

		final JTextField field = new JTextField(20);
		{
			field.setAlignmentX(CENTER_ALIGNMENT);

			GridBagConstraints c = new GridBagConstraints();
			c.gridwidth = GridBagConstraints.REMAINDER;

			c.fill = GridBagConstraints.HORIZONTAL;
			//add(field, c);
		}
		add(field);

		add(Box.createRigidArea(new Dimension(0, 10)));

		JButton close = new JButton("Ok");
		{
			close.addActionListener(new ActionListener()
			{
				public void actionPerformed(ActionEvent event)
				{
					RecordTable.getInstance().update(level, field.getText(), time, count);
					dispose();
				}
			});

			close.setAlignmentX(CENTER_ALIGNMENT);
		}
		add(close);

		add(Box.createRigidArea(new Dimension(0, 10)));

		setModalityType(ModalityType.APPLICATION_MODAL);
		setTitle("You're a champion!");
		setDefaultCloseOperation(DISPOSE_ON_CLOSE);
		setLocationRelativeTo(null);
		pack();
	}
}
