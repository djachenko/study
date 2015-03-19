package ru.nsu.fit.g1201.races.view;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;

import ru.nsu.fit.g1201.races.ResultController;

public class RecordNicknameView extends JDialog
{
	private final ResultController controller;

	public RecordNicknameView(ResultController controller)
	{
		this.controller = controller;

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
		}
		add(field);

		add(Box.createRigidArea(new Dimension(0, 10)));

		JButton close = new JButton("Ok");
		{
			close.addActionListener(new ActionListener()
			{
				public void actionPerformed(ActionEvent event)
				{
					controller.setNickname(field.getText());
					dispose();
				}
			});

			close.setAlignmentX(CENTER_ALIGNMENT);
		}
		add(close);

		addWindowListener(new WindowAdapter()
		{
			@Override
			public void windowClosing(WindowEvent e)
			{
				controller.setNickname(field.getText());
				dispose();

				super.windowClosing(e);
			}
		});

		add(Box.createRigidArea(new Dimension(0, 10)));

		setModalityType(ModalityType.APPLICATION_MODAL);
		setTitle("You're a champion!");
		setDefaultCloseOperation(DISPOSE_ON_CLOSE);
		setLocationRelativeTo(null);
		pack();
	}
}

