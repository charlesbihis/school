/* Author: CPSC213 Course Developer

   This code is to be used for lab 7. */

#include "Socket.h"
#include "SocketStruct.h"

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <ctype.h>
#include <string.h>
#include <arpa/inet.h>

/* The max size of a message */
#define nT 1024

int main(int argc, char* argv[])
{
  int nS = 0;   /* # of bytes sent */
  int nR = 0;   /* # of bytes received */
  int port;     /* port # */
  char strR[nT];  /* receive string */
  int i;  /* for loop counter */

  if (argc == 1) {
    printf("Server: give port # as argument!"); 
    return -1;
  }
  
  port = atoi(argv[1]); 

  printf ("Server: Calling createServerSocket(%d)\n", port);

  struct Socket* server = createServerSocket(port);

  if (server == NULL) {
    printf("Server: Could not open port\n");
    return 0-errno;
  }

  while (1) { 

    printf("Server: Waiting for connection\n");
  
    struct Socket* client = socketAccept(server);
    
    printf("Server: Accept connection from client %s port %d\n",
           inet_ntoa(client->remoteSockAddr.sin_addr), 
           client->remoteSockAddr.sin_port);

    if (client) {

      nR = socketRecv(client, strR, nT); /* receive message */

      if (nR < 0) {
        perror("Server: receive error.\n");
        continue;
      }

      strR[nR] = '\0';
  
      printf("Server: Client sent: ^%s^\n", strR);

      if (strcmp(strR, "BYE") == 0) {
        socketClose(client);
        socketClose(server);
        free(server); server = NULL;
        free(client); client = NULL;
        return 0;
      }
     
      for (i = 0; i < nR; i++) {
        strR[i] = toupper(strR[i]);  /* convert to uppercase */
      }
 
      printf("Server: Going to send ^%s^\n", strR);
  
      nS = socketSend(client, strR, strlen(strR)); 

      if (nS < 0) {
        perror("Server: send error.\n");
        continue;
      }
  
      printf("Server: Sent %d bytes\n", nS);
  
      nS = socketClose(client); /* close socket, terminate connection. */
      if (nS < 0) {
        perror("Server: close error.\n");
        continue;
      }
      
    }

    else {
      printf("Server: connection failed\n");
    }
  }

}

