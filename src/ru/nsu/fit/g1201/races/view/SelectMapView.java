package ru.nsu.fit.g1201.races.view;

import ru.nsu.fit.g1201.races.StarterController;
import ru.nsu.fit.g1201.races.model.MapList;
import ru.nsu.fit.g1201.races.model.RaceParameters;

import javax.swing.*;
import javax.swing.table.AbstractTableModel;
import java.awt.*;
import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;

public final class SelectMapView extends JPanel
{
    private String selectedMapName;

    private JTable mapList;

	private RaceParameters raceParameters = new RaceParameters();
	private StarterController controller;

    public SelectMapView(StarterController controller)
    {
	    this.controller = controller;

	    initUI();
    }

	private void initUI()
	{
        setLayout(new BoxLayout(this, BoxLayout.Y_AXIS));

        mapList = new JTable(new MapListModel());
        mapList.setPreferredScrollableViewportSize(new Dimension(600, 300));
        mapList.setSelectionMode(ListSelectionModel.SINGLE_SELECTION);

	    mapList.addMouseListener(new MouseAdapter()
        {
            public void mouseClicked(MouseEvent e)
            {
                if (e.getClickCount() == 2)
                {
                    selectedMapName = mapList.getModel().getValueAt(mapList.getSelectedRow(), 0).toString();
                    OK();
                }
            }
        });

        mapList.addKeyListener(new KeyListener()
        {

            @Override
            public void keyTyped(KeyEvent e)
            {
            }

            @Override
            public void keyPressed(KeyEvent e)
            {
                if (e.getKeyCode() == KeyEvent.VK_ENTER)
                {
                    selectedMapName = mapList.getModel().getValueAt(mapList.getSelectedRow(), 0).toString();
                    OK();
                }
            }

            @Override
            public void keyReleased(KeyEvent e)
            {
            }
        });

	    JScrollPane scrollPane = new JScrollPane(mapList);
        scrollPane.setMaximumSize(mapList.getPreferredScrollableViewportSize());
        add(scrollPane);
    }

    public void OK()
    {
        raceParameters.setMapName(selectedMapName);
        new SelectInitialSpeedView(raceParameters, controller);
    }

    private class MapListModel extends AbstractTableModel
    {
        @Override
        public final int getRowCount()
        {
            return MapList.getInstance().getMapList().length;
        }

        @Override
        public final int getColumnCount()
        {
            return 1;
        }

        @Override
        public final Object getValueAt(int r, int c)
        {
            switch (c)
            {
                case 0:
                    return MapList.getInstance().getMapList()[r];
                default:
                    return "";
            }
        }

        @Override
        public final String getColumnName(int c)
        {
            switch (c)
            {
                case 0:
                    return "Maps";
                default:
                    return "";
            }
        }
    }
}
