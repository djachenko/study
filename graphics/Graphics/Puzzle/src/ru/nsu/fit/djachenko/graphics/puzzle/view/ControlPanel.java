package ru.nsu.fit.djachenko.graphics.puzzle.view;

import ru.nsu.fit.djachenko.graphics.puzzle.controller.PuzzleContoller;

import javax.swing.*;
import java.awt.*;

public class ControlPanel extends JPanel
{
    private static final int ROTATION_MIN  = 0;
    private static final int ROTATION_MAX  = 360;
    private static final int ROTATION_INIT = 0;

    private JCheckBox filterCheckBox  = new JCheckBox("Filter");
    private JCheckBox blendCheckBox   = new JCheckBox("Blend");
    private JButton   initButton      = new JButton("Init");
    private JButton   startButton     = new JButton("Start");
    private JButton   stopButton      = new JButton("Stop");
    private JSlider   animationSlider = new JSlider(ROTATION_MIN, ROTATION_MAX, ROTATION_INIT);

    public ControlPanel(final PuzzleContoller puzzleController)
    {
        setBorder(BorderFactory.createEtchedBorder());

        animationSlider.setMajorTickSpacing(ROTATION_MAX / 2);
        animationSlider.setMinorTickSpacing(10);
        animationSlider.setPaintTicks(true);
        animationSlider.setAutoscrolls(true);

	    setLayout(new BoxLayout(this, BoxLayout.X_AXIS));

	    add(Box.createRigidArea(new Dimension(10, 20)));
	    add(filterCheckBox);
	    add(blendCheckBox);
	    add(Box.createRigidArea(new Dimension(10, 20)));
	    add(startButton);
	    add(stopButton);
	    add(initButton);
	    add(Box.createRigidArea(new Dimension(10, 20)));
	    add(animationSlider);



        filterCheckBox.addItemListener(e->{
            if (filterCheckBox.isSelected())
            {
					puzzleController.enableBiline();
            }
            else
            {
                puzzleController.disableBiline();
            }
        });

        blendCheckBox.addItemListener(e->{
            if (blendCheckBox.isSelected())
            {
                puzzleController.enableBlending();
            }
            else
            {
                puzzleController.disableBlending();
            }
        });

        startButton.addActionListener(e->puzzleController.start());

        stopButton.addActionListener(e->puzzleController.stop());

        initButton.addActionListener(e->{
            puzzleController.stop();
            puzzleController.reset();

            setSlider(0);
        });

        animationSlider.addChangeListener(e->{
            int t = ((JSlider) e.getSource()).getValue();

	        puzzleController.setIndex(t);
            puzzleController.step(t);
        });
    }

    public void setSlider(int step)
    {
        animationSlider.setValue(step);
    }
}
