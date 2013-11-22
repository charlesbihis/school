import java.io.*;
import java.net.*;

public class TCP_Server 
{	
  public static void main (String argv[]) throws Exception
  {
	  String message_send;			// the message to be sent to the client
	  String message_receive;		// the message received from the client
	  
	  ServerSocket listening_socket = new ServerSocket (6789);
	  
	  System.out.println("Server running...\n");
	  while (true)
	  {
		  Socket connection_socket = listening_socket.accept();	// create new socket dedicated to the connection
		  														// this leaves listening_socket open for more connections
		  BufferedReader in_from_client =														// input stream that reads from 
			  new BufferedReader(new InputStreamReader(connection_socket.getInputStream()));	// connection socket
		  DataOutputStream out_to_client = 									// output stream that will send on
			  new DataOutputStream(connection_socket.getOutputStream());	// connection socket as well
		  
		  message_receive = in_from_client.readLine();				// receive message from input stream declared earlier
		  message_send = message_receive.toUpperCase() + '\n';		// change received message to all uppercase
		  
		  out_to_client.writeBytes(message_send);					// send modified message through output stream declared earlier
	  }  // while loop
  }  // main
}  // TCP_Server
