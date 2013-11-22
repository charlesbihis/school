import java.io.*;
import java.net.*;

public class TCP_Client 
{
  public static void main (String argv[]) throws Exception
  {
	  String message_send;			// the message to be sent to the server
	  String message_receive;		// the message received from the server
	  
	  Socket client_socket = new Socket ("localhost", 6789);		// socket to connect to the server on
	  
	  BufferedReader in_from_user = 								// the input stream from standard in
		  new BufferedReader(new InputStreamReader (System.in));	// for the message to be sent from the user
	  DataOutputStream out_to_server =								// the output stream from the socket 
		  new DataOutputStream (client_socket.getOutputStream());	// for the message to be sent to the server
	  BufferedReader in_from_server = 													// the input stream from the socket for
		  new BufferedReader (new InputStreamReader(client_socket.getInputStream()));	// the message to be received from the server
	 
	  System.out.println("Client running...\n");
	  message_send = in_from_user.readLine();			// read message to be sent from standard in
	  out_to_server.writeBytes(message_send + '\n');	// send message through output stream declared earlier
	  
	  message_receive = in_from_server.readLine();		// receive message from input stream declared earlier
	  System.out.println("Server: " + message_receive);	// print received message
	  client_socket.close();							// close socket
  }  // main
}  // TCP_Client