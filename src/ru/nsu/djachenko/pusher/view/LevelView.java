package ru.nsu.djachenko.pusher.view;

import ru.nsu.djachenko.pusher.model.Level;
import ru.nsu.djachenko.pusher.model.Transfer;
import ru.nsu.djachenko.pusher.model.cells.Cell;

import javax.swing.*;
import java.util.HashMap;
import java.util.Map;
import java.util.Set;

public class LevelView extends JPanel
{
	private Level origin;
	private Transfer transfer;

	private Map<Cell, ActiveCellView> activeCells;
	private Map<ActiveCellView, D> offsets;

	class D
	{
		int dx;
		int dy;
	}

	public LevelView(Level origin, Transfer transfer)
	{
		this.origin = origin;
		this.transfer = transfer;

		this.activeCells = new HashMap<>();
		this.offsets = new HashMap<>();

		setLayout(null);

		for (int j = 0; j < origin.height(); j++)
		{
			for (int i = 0; i < origin.width(); i++)
			{
				Cell originCell = origin.getCell(i,j);

				switch (originCell.type)
				{
					case WALL:
						add(new CellView(CellView.Type.WALL, i, j));
						break;
					case FLOOR:
						add(new CellView(CellView.Type.FLOOR, i, j));//background cell
						break;
					case POINT:
						add(new CellView(CellView.Type.POINT, i, j));
						break;
					default://active cell - pusher or block
					   	add(new CellView(CellView.Type.FLOOR, i, j));

						CellView.Type type = null;

						switch (originCell.type)
						{
							case BLOCK:
								type = CellView.Type.BLOCK;
								break;
							case PUSHER:
								type = CellView.Type.PUSHER;
								break;
						}

						ActiveCellView activeCell = new ActiveCellView(originCell, type);

						add(activeCell);
						setComponentZOrder(activeCell, type.order);

						activeCells.put(originCell, activeCell);
						offsets.put(activeCell, new D());
				}
			}
		}
	}

	public void run()
	{
		while (true)
		{
			synchronized (origin)
			{
				try
				{
					origin.wait();
				}
				catch (InterruptedException e)
				{
					e.printStackTrace();
				}
			}

			for (Map.Entry<Cell, ActiveCellView> i : activeCells.entrySet())
			{
				ActiveCellView active = i.getValue();

				offsets.get(active).dx = i.getKey().getX() - active.X();
				offsets.get(active).dy = i.getKey().getY() - active.Y();
			}

			Set<ActiveCellView> cells = offsets.keySet();

			for (int i = 0; i < CellView.GRIDSIZE; i++)
			{
				for (ActiveCellView cell : cells)
				{
					cell.setLocation(cell.getX() + offsets.get(cell).dx, cell.getY() + offsets.get(cell).dy);
					setComponentZOrder(cell, cell.type.order);
				}
			}

			for (ActiveCellView cell : cells)
			{
				cell.moveCell(offsets.get(cell).dx, offsets.get(cell).dy);
			}
		}
	}
}
