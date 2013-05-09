package md5;

import java.io.*;
import java.net.InetAddress;
import java.net.Socket;
import java.net.UnknownHostException;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;

public class Client
{
	static String host;
	static int port;

	private static String codeToString(int code, int length)
	{
		StringBuilder string = new StringBuilder();

		for (int i = 0; i < length; i++)
		{
			switch (code % 4)
			{
				case 0:
					string.append('A');
					break;
				case 1:
					string.append('C');
					break;
				case 2:
					string.append('G');
					break;
				case 3:
					string.append("T");
					break;
				default:
					System.err.println("IMPOSSIBLE");
			}

			code /= 4;
		}

		return String.valueOf(string);
	}

	public static void main(String[] args)
	{
		try (Socket socket = new Socket(host, port))
		{
			BufferedReader reader = new BufferedReader(new InputStreamReader(socket.getInputStream()));
			PrintWriter writer = new PrintWriter(new OutputStreamWriter(socket.getOutputStream()));

			MessageDigest MD5Counter = MessageDigest.getInstance("MD5");

			int length = Integer.parseInt(reader.readLine());

			for ( ; ; )
			{
				switch (reader.readLine())
				{
					case "STOP":
						return;
					case "WORK":
						int start = Integer.parseInt(reader.readLine());
						int end = Integer.parseInt(reader.readLine());

						byte [] hash = reader.readLine().getBytes();

						for (int code = start; code < end; code++)
						{
							String temp = codeToString(code, length);

							MD5Counter.update(temp.getBytes());

							if (hash.equals(MD5Counter.digest()))
							{
								writer.println("SUCCESS");
								writer.println(temp);
								writer.flush();

								return;
							}
						}

						writer.println("UNSUCCESS");
						writer.flush();
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
		catch (NoSuchAlgorithmException e)
		{
			e.printStackTrace();
		}
	}
}
