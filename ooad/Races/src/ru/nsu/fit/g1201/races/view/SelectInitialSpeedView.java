package ru.nsu.fit.g1201.races.view;

import ru.nsu.fit.g1201.races.StarterController;
import ru.nsu.fit.g1201.races.model.RaceParameters;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public final class SelectInitialSpeedView extends JDialog
{
    RaceParameters raceParameters;

    private JButton okButton;
    private JButton cancelButton;
    private ButtonGroup buttonGroup;
    private ActionListener buttonActionListener;
	private StarterController controller;

    public SelectInitialSpeedView(RaceParameters raceParameters, StarterController controller)
    {
        this.raceParameters = raceParameters;
	    this.controller = controller;

        setLayout(new FlowLayout());

        String[] values = {"1", "2", "3", "4", "5", "6", "7", "8", "9"};

        buttonGroup = new ButtonGroup();
        boolean isSelected = false;

        for(String val: values)
        {
            JRadioButton radioButton = new JRadioButton(val);
            radioButton.setActionCommand(val);

            if (!isSelected)
            {
                radioButton.setSelected(true);
                isSelected = true;
            }

            buttonGroup.add(radioButton);
            add(radioButton);
        }

        buttonActionListener = new ActionListener()
        {
	        @Override
	        public void actionPerformed(ActionEvent e)
	        {
		        if (okButton == e.getSource())
		        {
			        OK();
		        }

		        cancel();
	        }
        };


	    okButton = new JButton("Ok");
        okButton.addActionListener(buttonActionListener);

	    cancelButton = new JButton("Cancel");
        cancelButton.addActionListener(buttonActionListener);

	    add(okButton);
        add(cancelButton);

        setSize(new Dimension(360, 100));
        setResizable(false);
        setModalityType(ModalityType.APPLICATION_MODAL);
        setTitle("Select initial speed");
        setDefaultCloseOperation(DISPOSE_ON_CLOSE);
        setLocationRelativeTo(null);
        setVisible(true);
    }

    public void OK()
    {
        raceParameters.setSpeed(Integer.parseInt(buttonGroup.getSelection().getActionCommand()));
    }

    public void cancel()
    {
        dispose();

	    controller.startNewRace(raceParameters);
    }
}
