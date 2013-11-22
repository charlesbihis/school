// Socket.h

#ifndef _SOCKETSTRUCT_H
#define _SOCKETSTRUCT_H

#include <sys/socket.h>

typedef enum { ACTIVE_SOCKET = 234,
               LISTENING_SOCKET,
               BROKEN_SOCKET
} socketType;


struct Socket {
  int sockFD;        // The file descriptor associated with this socket
  socketType sType;  // The type of this socket, it must assigned a value 
                     //  from the enumerated type, socketType.
  struct sockaddr_in remoteSockAddr; // This is a convenience field that 
                                     // can be used to store addresses 
                                     // for setting up a connection or 
                                     // for storing the address of a 
                                     // received connection. 
};

#endif // _SOCKET_H


