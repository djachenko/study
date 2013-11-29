package ru.nsu.fit.g1201.races.model;

import java.util.Timer;
import java.util.TimerTask;

public class Race
{
	private Road road;
	private Car car;

	Race()
	{
		this.car = new Car(this, 6, 0);
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
	}

	public boolean ableToMove(int x, int y, Direction direction)
	{
		return road.ableToMove(x, y, direction);
	}

	public void move(int x, int y, Direction direction)
	{
		road.move(x, y, direction);
	}

	void iteration(int iteration)
	{
		car.move(Direction.FORWARD);

		road.shift();

		road.print();
	}
}
