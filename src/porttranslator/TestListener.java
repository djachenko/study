package porttranslator;

import java.io.*;
import java.net.ServerSocket;
import java.net.Socket;
import java.net.UnknownHostException;

public class TestListener
{
	public static void main(String[] args)
	{
		try(Socket socket = new ServerSocket(Integer.parseInt(args[0])).accept())
		{
			PrintWriter out = new PrintWriter(new OutputStreamWriter(System.out));
			BufferedReader in = new BufferedReader(new InputStreamReader(socket.getInputStream()));

			String string;

			while (true)
			{
				string = in.readLine();

				if (string == null)
				{
					break;
				}
				else
				{
					out.println(string);
					out.flush();
				}
			}
		}
		catch (UnknownHostException e)
		{
			e.printStackTrace();
		}
		catch (IOException e)
		{
			e.printStackTrace();
		}
	}
}