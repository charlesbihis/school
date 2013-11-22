/* Author: CPSC213 Course Developer

   This code is to be used in lab 7. */

#include "Socket.h"
#include "SocketStruct.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <errno.h>


#define nT 1024

int main(int argc, char* argv[])
{
  char strR[nT];  /* receive string */
  char strS[nT];  /* send string */
  char *host; // hostname

  int port, nS = 0, nR = 0;
	
  if (argc != 3) {
    printf("Client: usage testClient hostname port");
    return -1;
  }
  host = argv[1];
  port = atoi(argv[2]);

  printf("Client: Calling createClientSocket(\"%s\", %d)\n", 
         host, port);
	
  struct Socket *soc = createClientSocket(host, port);

  if (soc == NULL) {
    printf("Client: could not construct socket");
    return 0-errno;
  }
  
  if (soc && (soc->sType == ACTIVE_SOCKET)) {

    printf("Client: Reading from standard input\n");
    gets(strS);
  
    printf("Client: Read ^%s^\n", strS);  

    nS = socketSend(soc, strS, strlen(strS)); /* send message */

    if (nS < 0) {
      perror("Client: send error.\n");
      return nS; 
    }

    printf("Client: Sending: ^%s^\n", strS);

    printf("Client: About to read\n");

    nR = socketRecv(soc, strR, nT);   
   
    if (nR < 0) {
      perror("Client: receive error.\n");
      return nR;
    }
    if (nR == 0) {
      printf("Client: Server shut down!\n");
      return -1;
    }
  
    printf("Client: Read %d bytes\n", nR);

    strR[nR] = '\0';

    printf("Client: Message Received:^%s^\n\n\n", strR);

    nR = socketClose(soc); // close socket, terminate connection.

    if (nR < 0) {
      perror("Client: close error.\n");
      return nR;
    }
  }

  else {
    printf("Client: connection failed\n");
  }

  free(soc);
  soc = NULL;

  return 0;
}



