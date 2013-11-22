import java.io.*;
import java.net.*;
import java.util.*;

public class WebServer
{
	public static void main(String argv[]) throws Exception
	{
		String request_message_line;	// variable to hold request line
		String filename;				// variable to hold filename
		
		ServerSocket listen_socket = new ServerSocket(6789);	// creates socket to listen on
		Socket connection_socket = listen_socket.accept();		// creates an additional socket dedicated for data transfer
		
		BufferedReader in_from_client = 													// create input stream that reads
			new BufferedReader(new InputStreamReader(connection_socket.getInputStream()));	// from connection socket
		DataOutputStream out_to_client =								// create output stream that will
			new DataOutputStream(connection_socket.getOutputStream());	// output to connection socket to client
		
		request_message_line = in_from_client.readLine();	// get request line from input stream declared above; of the form "GET file_name HTTP/1.0"
		StringTokenizer tokenized_line =				// create variable to hold tokenized results
			new StringTokenizer(request_message_line);	// of request line
		
		if (tokenized_line.nextToken().equals("GET"))	// checks if request is a GET command
		{
			filename = tokenized_line.nextToken();		// if so, then next token is file name
			
			if (filename.startsWith("/") == true)		// if file name starts with slash, remove it
				filename = filename.substring(1);
			
			File file = new File(filename);				// creates file
			int num_of_bytes = (int) file.length();		// saves size of file
			
			FileInputStream in_file = new FileInputStream(filename);	// attaches a stream to in_file
			byte[] file_in_bytes = new byte[num_of_bytes];				// construct an array of bytes of the size of the file
			in_file.read(file_in_bytes);								// reads stream in_file to array of bytes
			
			out_to_client.writeBytes("HTTP/1.0 200 Document Follows\r\n");	// start sending out HTTP response header lines
			if (filename.endsWith(".jpg"))
				out_to_client.writeBytes("Content-Type: image/jpeg\r\n");	// NOTE: no content line is sent if the object is neither
																			//       a jpeg or a gif
			if (filename.endsWith(".gif"))
				out_to_client.writeBytes("Content-Type: image/gif\r\n");
			
			out_to_client.writeBytes("Content-Length: " + num_of_bytes + "\r\n");
			out_to_client.writeBytes("\r\n");
			out_to_client.write(file_in_bytes, 0, num_of_bytes);
			
			connection_socket.close();
		}  // if statement
		else
			System.out.println("Bad Request Message");
	}  // main
}  // WebServer class declaration