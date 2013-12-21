package ru.nsu.fit.g1201.races.view;

import ru.nsu.fit.g1201.races.ResultController;
import ru.nsu.fit.g1201.races.model.Direction;
import ru.nsu.fit.g1201.races.model.Race;

import javax.swing.*;
import java.awt.*;
import java.awt.event.*;

public class PauseView extends JDialog {

    private JButton continueButton;
    private JButton restartButton;
    private JButton topScoresButton;
    private JButton exitButton;

	private Race race;

    public PauseView(Race race)
    {
	    this.race = race;

	    initUI();
    }

	private void initUI()
	{
        setLayout(new GridLayout(2, 2));
        setSize(new Dimension(300, 120));

        continueButton = new JButton("Continue");
        restartButton = new JButton("Restart race");
        topScoresButton = new JButton("Top Scores");
        exitButton = new JButton("Leave track");

        continueButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                continueRace();
            }
        });
        restartButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                restartRace();
            }
        });
        topScoresButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                showTopScores();
            }
        });
        exitButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                leaveRace();
            }
        });

        add(continueButton);
        add(topScoresButton);
        add(restartButton);
        add(exitButton);

		addKeyListener(new KeyListener()
		{
			@Override
			public void keyTyped(KeyEvent e)
			{}

			@Override
			public void keyPressed(KeyEvent e)
			{
				int key = e.getKeyCode();

				System.out.println(key + " press");

				switch (key)
				{
					case KeyEvent.VK_ESCAPE:
						continueRace();
					default:
						break;
				}
			}

			@Override
			public void keyReleased(KeyEvent e)
			{}
		});

		addWindowListener(new WindowAdapter()
		{
			@Override
			public void windowClosing(WindowEvent e)
			{
				race.pause();
			}
		});

        setResizable(false);
        setModalityType(ModalityType.APPLICATION_MODAL);
        setTitle("Pause menu");
        setDefaultCloseOperation(DISPOSE_ON_CLOSE);
        setLocationRelativeTo(null);
        requestFocus();
    }

    public void continueRace()
    {
	    race.pause();
	    dispose();
    }

    public void restartRace()
    {
	    race.stop();
	    dispose();
	    race.start();
    }

    public void showTopScores()
    {
        new TopScoresView(new ResultController());
    }

    public void leaveRace()
    {
	    race.stop();
    }
}
