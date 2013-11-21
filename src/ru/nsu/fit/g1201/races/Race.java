package ru.nsu.fit.g1201.races;

public class Race
{
	private Road road;
	private Car car;

	public boolean ableToMove(int x, int y, Direction direction)
	{
		return road.ableToMove(x, y, direction);
	}

	public void move(int x, int y, Direction direction)
	{
		road.move(x, y, direction);
	}

	void moveCar(Direction direction)
	{
		car.move(direction);
	}
}
