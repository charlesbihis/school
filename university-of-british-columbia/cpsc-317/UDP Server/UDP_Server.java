import java.net.*;

public class UDP_Server 
{
	public static void main (String args[]) throws Exception
	{
		DatagramSocket server_socket =		// socket open for all incoming and outgoing data 
			new DatagramSocket(9876);		// note: we do not create new socket for transfer of data
		
		byte[] send_data = new byte[1024];		// variable to hold message to send
		byte[] receive_data = new byte[1024];	// variable to hold message received
		
		System.out.println("Server running...\n");
		while (true)
		{
			DatagramPacket receive_packet = 							// create packet to hold data
				new DatagramPacket(receive_data, receive_data.length);	// received
			server_socket.receive(receive_packet);		// receive the packet
			
			String message_receive = new String(receive_packet.getData());	// parse the packet to
			InetAddress ip_address = receive_packet.getAddress();			// its constituent parts
			int port = receive_packet.getPort();							// -> data, ip address, port #
			
			String message_send = message_receive.toUpperCase();	// create message to send
			send_data = message_send.getBytes();					// type conversion from string to array of bytes
			
			DatagramPacket send_packet =											// create packet to hold 
				new DatagramPacket(send_data, send_data.length, ip_address, port);	// data to send
			server_socket.send(send_packet);			// send the packet
		}  // while loop
	}  // main
}  // UDP_Server class declaration