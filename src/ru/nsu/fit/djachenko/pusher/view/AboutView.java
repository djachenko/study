package ru.nsu.fit.djachenko.pusher.view;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class AboutView extends JDialog
{
	private static AboutView instance = new AboutView();
	private String[] about = {"Pusher game.", "Looks like Frankenstein's dream.", "Made just for fun.", "© 2013"};

	public static AboutView getInstance()
	{
		return instance;
	}

	private AboutView()
	{
		initUI();
	}

	public void initUI()
	{
		setLayout(new BoxLayout(getContentPane(), BoxLayout.Y_AXIS));

		add(Box.createRigidArea(new Dimension(0, 10)));

		JLabel name = new JLabel("About");
		{
			name.setAlignmentX(CENTER_ALIGNMENT);
			name.setFont(name.getFont().deriveFont(Font.BOLD));
		}
		add(name);

		add(Box.createRigidArea(new Dimension(0, 10)));

		for (String string : about)
		{
			JLabel text = new JLabel(string);
			{
				text.setAlignmentX(CENTER_ALIGNMENT);
			}
			add(text);
		}

		add(Box.createRigidArea(new Dimension(0, 10)));

		JButton close = new JButton("Close");
		{
			close.addActionListener(new ActionListener()
			{
				public void actionPerformed(ActionEvent event)
				{
					dispose();
				}
			});

			close.setAlignmentX(CENTER_ALIGNMENT);
		}
		add(close);

		add(Box.createRigidArea(new Dimension(0, 10)));

		setModalityType(ModalityType.APPLICATION_MODAL);
		setTitle("Help");
		setDefaultCloseOperation(DISPOSE_ON_CLOSE);
		setLocationRelativeTo(null);
		pack();
	}
}