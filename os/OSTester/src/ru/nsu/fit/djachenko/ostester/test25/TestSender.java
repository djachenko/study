package ru.nsu.fit.djachenko.ostester.test25;

import java.io.*;
import java.net.Socket;

public class TestSender extends Thread
{
	public static final int SENDERSCOUNT = 10;

	private Integer id;
	private static int PORT = 5678;
	private static String ADDRESS = "localhost";

	TestSender(int id)
	{
		this.id = id;
	}

	@Override
	public void run()
	{
		System.out.println(id + " started");

		try(Socket socket = new Socket(ADDRESS, PORT))
		{
			PrintWriter out = new PrintWriter(new OutputStreamWriter(socket.getOutputStream()));

			String string = id.toString();

			while (true)
			{
				out.println(string);
				out.flush();
			}
		}
		catch (IOException e)
		{
			e.printStackTrace();
		}
	}

	public static void main(String[] args)
	{
		for (int i = 0; i < SENDERSCOUNT; i++)
		{
			new TestSender(i).start();
		}
	}
}
