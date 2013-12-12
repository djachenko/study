package ru.nsu.fit.g1201.races.view;

import ru.nsu.fit.g1201.races.ResultController;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class PauseView extends JDialog {

    private JButton continueButton;
    private JButton restartButton;
    private JButton topScoresButton;
    private JButton exitButton;

    public PauseView() {

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

        setResizable(false);
        setModalityType(ModalityType.APPLICATION_MODAL);
        setTitle("Pause menu");
        setDefaultCloseOperation(DISPOSE_ON_CLOSE);
        setLocationRelativeTo(null);
        setVisible(true);

    }

    public void continueRace() {}

    public void restartRace() {}

    public void showTopScores() {
        new TopScoresView(new ResultController());
    }

    public void leaveRace() {}

}
