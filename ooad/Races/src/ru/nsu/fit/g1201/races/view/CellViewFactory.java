package ru.nsu.fit.g1201.races.view;

import ru.nsu.fit.g1201.races.model.cells.Cell;

public class CellViewFactory
{
	private static CellViewFactory instance;

	private CellViewFactory(){}

	public static CellViewFactory getInstance()
	{
		if (instance == null)
		{
			synchronized (CellViewFactory.class)
			{
				if (instance == null)
				{
					instance = new CellViewFactory();
				}
			}
		}

		return instance;
	}

	CellView getCellView(Cell origin, int x, int y)
	{
		CellView.Type type = null;

		switch (origin.getRepresentation())
		{
			case '#':
				type = CellView.Type.BORDER;
				break;
			case 'r':
				type = CellView.Type.CAR;
				break;
			case ' ':
				type = CellView.Type.ASPHALT;
				break;
			default:
				break;
		}

		return getCellView(type, x, y);
	}

	CellView getCellView(CellView.Type type, int x, int y)
	{
		return new CellView(type, x, y);
	}
}
