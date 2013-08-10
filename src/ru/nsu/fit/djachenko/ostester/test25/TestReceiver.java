package ru.nsu.fit.djachenko.ostester.test25;

import java.io.*;
import java.net.ServerSocket;
import java.net.Socket;

public class TestReceiver extends Thread
{
	public static int PORT = 5679;

	private Socket socket;

	TestReceiver(Socket socket)
	{
		this.socket = socket;
	}

	@Override
	public void run()
	{
		try
		{
			BufferedReader in = new BufferedReader(new InputStreamReader(socket.getInputStream()));

			String string;

			int id = Integer.parseInt(in.readLine());

			System.out.println(id + " connected");

			for (int i = 0; ; i++)
			{
				string = in.readLine();

				if (string == null)
				{
					break;
				}
				else
				{
					if (id != Integer.parseInt(string))
					{
						System.out.println("Fail");
					}
				}

				if (i % 10 == 0)
				{
				//	System.out.println(id + " read " + i + " times");
				}
			}
		}
		catch (IOException e)
		{
			e.printStackTrace();
		}
	}

	public static void main(String[] args)
	{
		try (ServerSocket serverSocket = new ServerSocket(PORT))
		{
			while (true)
			{
				new TestReceiver(serverSocket.accept()).start();
			}
		}
		catch (IOException e)
		{
			e.printStackTrace();
		}
	}
}
