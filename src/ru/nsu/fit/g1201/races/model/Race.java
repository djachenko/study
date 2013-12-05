package ru.nsu.fit.g1201.races.model;

import ru.nsu.fit.g1201.races.communication.MessageChannel;
import ru.nsu.fit.g1201.races.communication.MessageToView;

import java.util.Random;
import java.util.Timer;
import java.util.TimerTask;

public class Race
{
	private Road road;
	private Car car;

	private Timer timer;
	private MessageChannel<MessageToView> channel;

	private Random random = new Random();

	public Race(MessageChannel<MessageToView> channel)
	{
		this.car = new Car(this, 4, 0);
		this.road = new Road(this, 9);
		this.channel = channel;

		timer = new Timer();
	}

	public void start()
	{
		road.draw(car);

		TimerTask task = new TimerTask()
		{
			private int iterationCount = 0;

			@Override
			public void run()
			{
				iteration(iterationCount++);
			}
		};
		timer.scheduleAtFixedRate(task,	0, 200);
	}

	public boolean ableToMove(int x, int y, Direction direction)
	{
		return road.ableToMove(x, y, direction);
	}

	public void move(int x, int y, Direction direction)
	{
		if (road != null)
		{
			road.move(x, y, direction);
		}
	}

	public void moveCar(Direction direction)
	{
		if (car != null)
		{
			car.move(direction);
		}
	}

	void iteration(int index)
	{
		if (index % 10 == 0 && road != null)
		{
			road.add(new Barrier(random.nextInt(road.getWidth() - 2), 15 + index, 2, 2, this));
		}

		moveCar(Direction.FORWARD);

		if (road != null)
		{
			road.shift();

			road.print();
		}
	}

	public void crash()
	{
		timer.cancel();
		timer = null;
		car = null;
		road = null;
	}

	void send(MessageToView messageToView)
	{
		channel.set(messageToView);
	}

	public Road getRoad()
	{
		return road;
	}

	public Car getCar()
	{
		return car;
	}
}
