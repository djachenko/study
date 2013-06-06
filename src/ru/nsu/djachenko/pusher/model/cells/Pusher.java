package ru.nsu.djachenko.pusher.model.cells;

import ru.nsu.djachenko.pusher.model.Direction;
import ru.nsu.djachenko.pusher.model.Field;

public class Pusher extends Cell//толкатель - это просто управляемый блок. Или нет - вопрос в обработке коллизий
{
	int strength = 1;

    public Pusher(Field field, int x, int y)
	{
		super(0, field, x, y);
	}

	public void move(Direction dir)
	{
		System.out.println("pusher.move");
		super.move(dir, strength);
	}
}
