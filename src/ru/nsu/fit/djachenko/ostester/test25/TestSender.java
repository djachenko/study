package ru.nsu.fit.djachenko.ostester.test25;

import java.io.*;
import java.net.Socket;

public class TestSender extends Thread
{
	public static final int SENDERSCOUNT = 510;

	private Integer id;
	private int port;
	private String address;

	TestSender(int id, String address, int port)
	{
		this.id = id;
		this.address = address;
		this.port = port;
	}

	@Override
	public void run()
	{
		try(Socket socket = new Socket(address, port))
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
			new TestSender(i, "localhost", 0).start();
		}
	}
}
