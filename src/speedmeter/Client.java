package speedmeter;

import java.io.IOException;
import java.io.OutputStream;
import java.net.Socket;
import java.net.UnknownHostException;
import java.util.Scanner;

public class Client
{
	public static void main(String[] args)
	{
		try (Socket socket = new Socket("localhost",7651))
		{
			Scanner input = new Scanner(socket.getInputStream());
			OutputStream output = socket.getOutputStream();

			byte [] buffer = new byte[1024];

			long start = System.currentTimeMillis();

			output.write(buffer);

			int num;
			long end;

			if (input.hasNextInt())
			{
				num = input.nextInt();
			}
			else
			{
				throw new Exception("Unable to read num");
			}

			if (input.hasNextLong())
			{
				end = input.nextLong();
			}
			else
			{
			    throw new Exception("Unable to read end");
			}

			double speed = (double)(end - start) / num;

			System.out.println(num);
			System.out.println(start);
			System.out.println(end);
			System.out.println(speed);
		}
		catch (UnknownHostException e)
		{
			e.printStackTrace();
		}
		catch (IOException e)
		{
			e.printStackTrace();
		}
		catch (Exception e)
		{
			System.err.println(e.getLocalizedMessage());

			e.printStackTrace();
		}

	}
}
