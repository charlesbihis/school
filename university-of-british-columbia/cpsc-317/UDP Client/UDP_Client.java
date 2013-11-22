import java.io.*;
import java.net.*;

public class UDP_Client
{
  public static void main (String args[]) throws Exception
  {
	  BufferedReader in_from_user =									// creates input stream from standard in
		  new BufferedReader (new InputStreamReader (System.in));	// for user to input message
	  DatagramSocket client_socket = 								// creates socket for transfer of data
		  new DatagramSocket();										// NOTE: this call does not initiate a TCP 
	  																//       connection (no hostname or port as arguments)
	  InetAddress ip_address = InetAddress.getByName("localhost");	// takes argument of hostname and returns IP of given server
	  
	  byte[] send_data = new byte[1024];		// variable to hold message to send
	  byte[] receive_data = new byte[1024];		// variable to hold message received
	  
	  String message_send = in_from_user.readLine();	// read in the send message from standard in
	  send_data = message_send.getBytes();				// type conversion from string to array of bytes
	  
	  DatagramPacket send_packet =												// creates packet of data to 
		  new DatagramPacket (send_data, send_data.length, ip_address, 9876);	// send to server
	  DatagramPacket receive_packet = 									// creates packet of data to hold
		  new DatagramPacket (receive_data, receive_data.length);		// response from server
	  
	  client_socket.send(send_packet);			// sends packet to server so we can now wait for response from server
	  client_socket.receive(receive_packet);	// blocks until response received from server
	  
	  String message_receive = new String (receive_packet.getData());	// creates string to hold response from server
	  System.out.println("Server: " + message_receive);					// prints response to screen
	  
	  client_socket.close();	// close the socket
  }
}  // UDP_Client class declaration
