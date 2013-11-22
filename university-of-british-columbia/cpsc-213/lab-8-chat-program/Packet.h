
#ifndef _PACKET_H_
#define _PACKET_H_


typedef enum {
	HELLO = 30,
	CONTINUE,
	MSG,
	DISPLAY,
	BYE
} PACKET_TYPE;

#define MAX_BYTES  256

typedef struct {
	PACKET_TYPE       ptype;
	unsigned long     data_len;
	unsigned char     data[MAX_BYTES];
} PACKET;

#endif 
