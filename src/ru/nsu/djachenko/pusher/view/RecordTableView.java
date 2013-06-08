package ru.nsu.djachenko.pusher.view;

import ru.nsu.djachenko.pusher.model.RecordTable;

import javax.swing.*;
import javax.swing.table.AbstractTableModel;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class RecordTableView extends JDialog
{
	public RecordTableView()
	{
		initUI();
	}

	class RecordTableModel extends AbstractTableModel
	{
		private String[] names = {"Level", "Name", "Time", "Steps"};
		private Object[][] data;

		public RecordTableModel()
		{
			data = new Object[RecordTable.getInstance().size() + 1][4];

			data[0] = names;

			for (int i = 0; i < data.length - 1; i++)
			{
				RecordTable.Entry entry = RecordTable.getInstance().getEntry(i);

				data[i + 1][0] = entry.level;

				if (entry.time > 0)
				{
					data[i + 1][1] = entry.name;
					data[i + 1][2] = entry.time / 1000.0;
					data[i + 1][3] = entry.count;
				}
				else
				{
					data[i + 1][1] = "No champion";
					data[i + 1][2] = 0;
					data[i + 1][3] = 0;
				}
			}
		}

		@Override
		public int getRowCount()
		{
			return data.length;
		}

		@Override
		public int getColumnCount()
		{
			return names.length;
		}

		@Override
		public Object getValueAt(int rowIndex, int columnIndex)
		{
			return data[rowIndex][columnIndex];
		}

		@Override
		public boolean isCellEditable(int rowIndex, int columnIndex)
		{
			return false;
		}
	}

	public void initUI()
	{
		setLayout(new BoxLayout(getContentPane(), BoxLayout.Y_AXIS));


		JTable table = new JTable(new RecordTableModel());

		add(table);

		add(Box.createRigidArea(new Dimension(0, 10)));

		JButton close = new JButton("Close");
		{
			close.addActionListener(new ActionListener()
			{
				@Override
				public void actionPerformed(ActionEvent e)
				{
					dispose();
				}
			});

			close.setAlignmentX(CENTER_ALIGNMENT);
		}
		add(close);

		add(Box.createRigidArea(new Dimension(0, 10)));

		pack();

		setLocationRelativeTo(null);
		setDefaultCloseOperation(DISPOSE_ON_CLOSE);
	}
}
