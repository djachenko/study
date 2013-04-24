package ru.nsu.djachenko.pusher.cells;

import ru.nsu.djachenko.pusher.Field;

public class Pusher extends Cell//толкатель - это просто управляемый блок. Или нет - вопрос в обработке коллизий
{
    public Pusher(Field field, int x, int y)
	{
		super(0, field, x, y);
	}
}
