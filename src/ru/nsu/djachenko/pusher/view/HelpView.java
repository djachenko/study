package ru.nsu.djachenko.pusher.view;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class HelpView extends JDialog
{
	private static HelpView instance = new HelpView();
	private String[] help = {
			"White cell - pusher\n",
			"Yellow cells - blocks\n",
			"Green cells - blocks on points\n",
			"Red cells - points\n",
			"Control with arrows"};

	public static HelpView getInstance()
	{
		return instance;
	}

	private HelpView()
	{
		initUI();
	}

	public void initUI()
	{
		setLayout(new BoxLayout(getContentPane(), BoxLayout.Y_AXIS));

		add(Box.createRigidArea(new Dimension(0, 10)));

		JLabel name = new JLabel("Help");
		{
			name.setAlignmentX(CENTER_ALIGNMENT);
			name.setFont(name.getFont().deriveFont(Font.BOLD));
		}
		add(name);

		add(Box.createRigidArea(new Dimension(0, 10)));

		for (String string : help)
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
