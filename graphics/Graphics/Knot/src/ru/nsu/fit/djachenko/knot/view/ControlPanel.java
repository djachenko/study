package ru.nsu.fit.djachenko.knot.view;

import javax.swing.*;
import java.awt.*;

public class ControlPanel extends JPanel
{
    private JCheckBox boxCheckBox = new JCheckBox("Box");

    public ControlPanel(final KnotView knotView)
    {
        setBorder(BorderFactory.createEtchedBorder());

	    boxCheckBox.setSelected(true);

	    setLayout(new BoxLayout(this, BoxLayout.X_AXIS));

	    add(Box.createRigidArea(new Dimension(10, 20)));
	    add(boxCheckBox);
	    add(Box.createRigidArea(new Dimension(10, 20)));

        boxCheckBox.addItemListener(e -> {
	        knotView.setBoxEnabled(boxCheckBox.isSelected());
	        knotView.repaint();
        });
    }
}
