package ru.nsu.fit.g1201.races.model;

import java.util.Timer;
import java.util.TimerTask;

public class Race
{
	private Road road;
	private Car car;

	public Race()
	{
		this.car = new Car(this, 4, 0);
		this.road = new Road(9);
		this.road.draw(car);
		this.road.print();

		new Timer().scheduleAtFixedRate(
				new TimerTask()
				{
					private int count = 0;

					@Override
					public void run()
					{
						iteration(count++);
					}
				},
				0,
				500
		);

		for (int i = 0; i < 5; i++)
		{
			road.add(new Barrier(6, 15 + i * 5, 2, 2));
		}
	}

	public boolean ableToMove(int x, int y, Direction direction)
	{
		return road.ableToMove(x, y, direction);
	}

	public void move(int x, int y, Direction direction)
	{
		road.move(x, y, direction);
	}

	public void moveCar(Direction direction)
	{
		car.move(direction);
	}

	void iteration(int iteration)
	{
		car.move(Direction.FORWARD);

		road.shift();

		road.print();
	}
}
