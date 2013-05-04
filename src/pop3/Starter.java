package pop3;

import java.io.*;

public class Starter 
{
	public static void main(String[] args)
	{
		Client client = new Client();
		
		try(BufferedReader reader = new BufferedReader(new InputStreamReader(System.in)))
		{
			while (true)
			{
				System.out.print("Enter server address:\n> ");

				String serverName = reader.readLine();

				try
				{
					client.connect(serverName);

					break;
				}
				catch(MyPOP3Exception e)
				{
					System.out.println("Connection wasn't established, server returned an outor: " + e.getLocalizedMessage());
				}
			}

			while (true)
			{
				System.out.print("Enter username:\n> ");

				String username = reader.readLine();

				System.out.print("Enter password:\n> ");

				String password = reader.readLine();

				try
				{
					client.login(username, password);

					System.out.println("Connection established...");

					while (true)
					{
						try
						{
							System.out.println("...you have " + client.countMessages() + " messages.");

							break;
						}
						catch (MyPOP3Exception e)
						{
							System.out.println("Server returned an message counting outor: " + e.getLocalizedMessage());
						}
					}

					break;
				}
				catch (MyPOP3Exception e)
				{
					System.out.println("Server returned an logging outor: " + e.getLocalizedMessage());
				}
			}

			int number;
			
			while (true)
			{
				System.out.print("Enter number of message (0 for end of work):\n> ");

				try
				{
					number = Integer.parseInt(reader.readLine());

					if (number == 0)
					{
						break;
					}
					else
					{
						try
						{
							System.out.println(client.getMessage(number));
						}
						catch(MyPOP3Exception e)
						{
							System.out.println("Server returned message retrieving outor: " + e.getLocalizedMessage());
						}
					}
				}
				catch (NumberFormatException e)
				{
					System.out.println("This is not a valid number");
				}
			}
			
			client.logout();
			client.disconnect();
			
			System.out.println("Goodbye!");
		}
		catch(Exception e)
		{
			e.printStackTrace();
		}
	}	
}
