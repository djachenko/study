package ru.nsu.djachenko.pusher.model.cells;

import ru.nsu.djachenko.pusher.model.Field;

public class Block extends Cell
{
	public Block(Field field, int x, int y)
	{
		super(Type.BLOCK, field, x, y);
	}

	@Override
	public boolean isBlock()
	{
		return true;
	}
}

/*
1. хранить передвигающиеся блоки отдельно от поля, поле - только стены и пространство
2. блоки только в поле
3. и там, и там.
что будет лучше?
и что делать с точками?
*/
