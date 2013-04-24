package ru.nsu.djachenko.pusher.cells;

import ru.nsu.djachenko.pusher.Field;

public class Block extends Cell
{
	public Block(Field field, int x, int y)
	{
		super(1, field, x, y);
	}
}

/*
1. хранить передвигающиеся блоки отдельно от поля, поле - только стены и пространство
2. блоки только в поле
3. и там, и там.
что будет лучше?
и что делать с точками?
*/
