package md5;

import com.sun.javafx.scene.EnteredExitedHandler;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.ServerSocket;
import java.net.Socket;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;

class ClientHandler extends Thread
{
	private Socket socket;

	public ClientHandler(Socket socket)
	{
		this.socket = socket;
	}

	@Override
	public void run()
	{
		if (!Server.isFinished())
		{

		}
	}
}

public class Server
{
	private static boolean finished = false;
	private static int start = 0;

	public static in

	public static boolean isFinished()
	{
		return finished;
	}

	public static void main(String[] args)
	{
		try (BufferedReader reader = new BufferedReader(new InputStreamReader(System.in)))
		{
			System.out.print("Enter your string, please:\n> ");

			String string = reader.readLine();

			byte[] hash = MessageDigest.getInstance("MD5").digest(string.getBytes());
			int length = string.length();

			try (ServerSocket socket = new ServerSocket(7846))
			{
				new
			}
		}
		catch (IOException e)
		{
			e.printStackTrace();
		}
		catch (NoSuchAlgorithmException e)
		{
			e.printStackTrace();
		}
	}
}
