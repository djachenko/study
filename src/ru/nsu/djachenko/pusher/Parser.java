package ru.nsu.djachenko.pusher;

import java.io.*;

public class Parser
{
	public static void main(String[] args) throws IOException
	{
		try (BufferedReader reader = new BufferedReader(new FileReader("input.txt")))
		{
			try (PrintWriter writer = new PrintWriter("level.pshr"))
			{
				boolean in = false;

				StringBuilder stringBuilder = new StringBuilder();

				int i = 1;

				while (i == 1)
				{
					int c = reader.read();

					switch (c)
					{
						case -1:
							i = 2;
							break;
						case ' ':
							if (in)
							{
								stringBuilder.append('.');
							}
							else
							{
								stringBuilder.append('x');
							}

							break;
						case 'X':
							stringBuilder.append('x');
							in = true;
							break;
						case '@':
							stringBuilder.append('t');
							break;
						case '.':
							stringBuilder.append('&');
							break;
						case '*':
							stringBuilder.append('*');
							break;
						case '\n':
	                        stringBuilder.append('\n');
							in = false;
					}
				}

				writer.println(stringBuilder);
			}
		}
		catch (FileNotFoundException e)
		{
			e.printStackTrace();
		}
		catch (IOException e)
		{
			e.printStackTrace();
		}
	}
}
