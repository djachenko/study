package ru.nsu.fit.djachenko.ostester.test25;

import java.io.*;
import java.net.ServerSocket;
import java.net.Socket;

public class TestReceiver extends Thread
{
	public static int PORT = 7777;

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

			while (true)
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
