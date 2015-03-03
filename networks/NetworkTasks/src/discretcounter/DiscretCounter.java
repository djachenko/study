package discretcounter;

import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.util.ArrayList;

public class DiscretCounter
{
	public static void main(String[] args)
			throws Exception
	{
		DatagramSocket socket = new DatagramSocket(4446);
		InetAddress address = InetAddress.getByName("192.168.1.255"); //count

		System.out.println(socket.getLocalPort());

		Runtime.getRuntime().addShutdownHook(new ShutdownHook(socket, address));

		byte[] sendData = "IBORN".getBytes();
		DatagramPacket sendPacket = new DatagramPacket(sendData, sendData.length, address, socket.getLocalPort());
		socket.send(sendPacket);

		byte[] receiveData = new byte[1024];
		DatagramPacket receivePacket = new DatagramPacket(receiveData, receiveData.length);
		socket.receive(receivePacket);

		ArrayList<InetAddress> holder = new ArrayList<>();

		sendData = "ILIVE".getBytes();
		sendPacket.setData(sendData);

		for ( ;  ; )
		{
			socket.receive(receivePacket);

			String message = new String(receivePacket.getData(), receivePacket.getOffset(), receivePacket.getLength());

			if (message.equals("IBORN") || message.equals("ILIVE"))
			{
				holder.add(receivePacket.getAddress());

				if (message.equals("IBORN"))
				{
					System.out.println("born");

					sendPacket.setAddress(receivePacket.getAddress());
					sendPacket.setPort(receivePacket.getPort());

					socket.send(sendPacket);
				}
			}
			else if (message.equals("IDEAD"))
			{
				System.out.println("dead");

				holder.remove(receivePacket.getAddress());
			}
			else
			{
				System.out.println("Something strange came...");
			}

			for (InetAddress addressIterator : holder)
			{
				System.out.println(addressIterator.toString());
			}
		}
	}
}

class ShutdownHook extends Thread
{
	DatagramSocket socket;
	InetAddress address;

	ShutdownHook(DatagramSocket socket, InetAddress address)
	{
		this.socket = socket;
		this.address = address;
	}

	public void run()
	{
		String message = "IDEAD";

		byte[] sendData = message.getBytes();

		DatagramPacket sendPacket = new DatagramPacket(sendData, sendData.length, address, socket.getLocalPort());

		try
		{
			System.out.println("I dead...");

			socket.send(sendPacket);
		}
		catch (IOException excptn)
		{
			System.err.println("Unable to send packet on shutdown");
		}
    }
}

