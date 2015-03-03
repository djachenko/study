package speedmeter;

import java.io.IOException;
import java.io.OutputStream;
import java.net.Socket;
import java.util.Scanner;

public class Client
{
	private static final int BUFFERSIZE = 256 * 1024;
	private static final int TRIES = 25;

	public static void main(String[] args)
	{
		try (Socket socket = new Socket("wsc203",7651))
		{
			Scanner input = new Scanner(socket.getInputStream());
			OutputStream output = socket.getOutputStream();

			byte [] buffer = new byte[BUFFERSIZE];

			long [] starts = new long[TRIES];
			int [] nums = new int[TRIES];
			long [] ends = new long[TRIES];

			for (int i = 0; i < TRIES; i++)
			{
				System.out.print(i +"... ");

				starts[i] = System.currentTimeMillis();

				output.write(buffer);

				System.out.println();

				if (input.hasNextInt())
				{
					nums[i] = input.nextInt();
					System.out.println(nums[i]);
				}
				else
				{
					throw new Exception("Unable to read num");
				}

				if (input.hasNextLong())
				{
					ends[i] = input.nextLong();
				}
				else
				{
				    throw new Exception("Unable to read end");
				}
			}

			//System.out.println();

			double averageNum = 0;
			double averageTime = 0;

			for (int i = 0; i < TRIES; i++)
			{
				averageNum += nums[i];
				averageTime += ends[i] - starts[i];
			}

			averageNum /= TRIES;
			averageTime /= TRIES;


			double speed = averageNum / averageTime;

			System.out.println("Number of bytes: " + averageNum);
			System.out.println("Transfer time: " + averageTime + " milliseconds");
			System.out.println("Speed: " + speed + " bytes/millisecond");
			System.out.println("Speed: " + speed / 1024 * 1000 + " Kbytes/second");
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
