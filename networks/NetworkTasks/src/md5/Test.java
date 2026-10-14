package md5;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.util.Arrays;

public class Test
{
	private static final char [] GENES = {'A', 'C', 'G', 'T'};

	private static String codeToString(int code, int length)
	{
		StringBuilder string = new StringBuilder();

		for (int i = 0; i < length; i++)
		{
			string.append(GENES[code % 4]);
			code /= 4;
		}

		return String.valueOf(string.reverse());
	}

	public static void main(String[] args)
	{
		try (BufferedReader reader = new BufferedReader(new InputStreamReader(System.in)))
		{
			String string = reader.readLine();

			MessageDigest MD5Counter = MessageDigest.getInstance("MD5");

			byte [] hash = MD5Counter.digest(string.getBytes());

			int length = string.length();

			int max = (int)Math.pow(4, length);

			for (int i = 0; i < max; i++)
			{
				String tempString = codeToString(i, length);

				byte [] temp = MD5Counter.digest(tempString.getBytes());

				if (Arrays.equals(hash, temp))
				{
					System.out.println("done " + tempString);

					System.exit(0);
				}
			}

			System.out.println("fail");
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
