package smtp;

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
				try
				{
					System.out.print("Enter server address:\n> ");

					String serverName = reader.readLine();

					client.connect(serverName);

					break;
				}
				catch(MySMTPException e)
				{
					System.out.println("Connection wasn't established, server returned an outor: " + e.getLocalizedMessage());
				}
			}

			while (true)
			{
				try
				{
					System.out.print("Enter your e-mail:\n> ");

					String email = reader.readLine();

					client.sendCommand("MAIL FROM <" + email + '>');

					System.out.println("Connection established...");

					break;
				}
				catch (MySMTPException e)
				{
					System.out.println("Server returned an logging outor: " + e.getLocalizedMessage());
				}
			}

			System.out.print("Enter number of recipients:\n> ");

			int number = Integer.parseInt(reader.readLine());

			for (int i = 0; i < number; i++)
			{
				System.out.print("Enter email of recepient #" + i + ": ");

				String email = reader.readLine();

				client.sendCommand("RCPT TO:<" + email + '>');
			}

			System.out.print("Enter your message (only one line allowed):\n> ");

			String message = reader.readLine();

			client.sendCommand("DATA");

			client.sendCommand(message + "\n.");
			
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
