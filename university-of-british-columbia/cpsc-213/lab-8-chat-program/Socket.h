// Socket.h

#ifndef _SOCKET_H
#define _SOCKET_H

struct Socket *createServerSocket(const int port);
   // Construct a socket that can subsequently be used to accept a TCP/IP 
   // connection on the passed in port number. If such a socket cannot 
   // be created then  NULL is to be returned. The returned value can be 
   // passed to socketAccept() and socketClose(). Note: it is the
   // application's responsibility to call free() on the returned
   // value once socketClose() has been called on it.

struct Socket *createClientSocket(const char *hostname, const int port);
   // This call is to attempt to open an TCP/IP connection to the host 
   // identfied by hostname and on the port specified by port. The hostname 
   // can be a DNS name (e.g. www.cs.ubc.ca) or in dotted form
   // (e.g. 142.103.6.5). The value returned can be passed 
   // as the first parameter to the calls socketSend() and
   // socketRecv(0 to send and receive data and to socketClose() to
   // close the connection.  Note: it is the application's
   // responsibility to call free() on the returned value once
   // socketClose() has been called on it.

struct Socket *socketAccept(struct Socket *);
   // This routine takes as an argument the value returned by
   // createServerSocket() and waits for an incoming connection. If
   // for any reason the attempt to accept a new connection fails then
   // NULL is to be returned. Otherwise, the returned value returned
   // can be passed as the first parameter to the calls 
   // socketSend() and socketRecv(0 to send and receive data and to
   // socketClose() to close the connection. Note: it is the application's
   // responsibility to call free() on the returned value once
   // socketClose() has been called on it.


int socketSend(struct Socket * soc, const void *msg, const int msgSize); 
   // This routine takes as its first parameter the result returned by
   // socketAccept() or createClientSocket() and proceeds to send
   // msgSize bytes from the memory location identified by msg to the
   // underlying endpoint associated with the first parameter. The 
   // value to be returned corresponds to that described for the write()
   // system call. 


int socketRecv(struct Socket * soc, void *buf, int bufSize);
   // This routine takes as its first parameter the result returned by
   // socketAccept() or createClientSocket() and proceeds to receive upto
   // bufSize bytes into the memory location pointed to by buf from the
   // underlying endpoint associated with the first parameter. The 
   // value to be returned corresponds to that described for the read()
   // system call. 
			 		    
int socketClose(struct Socket *soc); 
   // This routine takes as its parameter the result returned by
   // socketAccept(), createServerSocket(), or createClientSocket()
   // and proceeds to close the underling endpoint associated with the
   // passed in parameter. The value returned corresponds to that
   // described for the close() system call.


#endif // _SOCKET_H


