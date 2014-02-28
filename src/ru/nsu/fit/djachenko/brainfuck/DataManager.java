package ru.nsu.fit.djachenko.brainfuck;

//import org.apache.log4j.Logger;

public class DataManager
{
	private int[] data;
	private int pointer;

	public DataManager()
	{
		data = new int[30000];
		pointer = 0;
	}

	public void incrementData()
	{
		data[pointer]++;
	}

	public void decrementData()
	{
		data[pointer]--;
	}

	public void incrementPointer()
	{
		pointer++;
	}

	public void decrementPointer()
	{
		pointer--;
	}

	public int out()
	{
		return data[pointer];
	}

	public void write(int a)
	{
		data[pointer] = a;
	}
}
