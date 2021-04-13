#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <signal.h>
#include <unistd.h>
#include <assert.h>
#include <string.h>
#include <stdio.h>

int main( int argc, char** argv ) {
	char* ip = (char*)"127.0.0.1";
	int port = 6000;

	int sock = socket(PF_INET, SOCK_STREAM, 0);
	assert( sock > 0 );

	struct sockaddr_in server_address;
	bzero(&server_address, sizeof(server_address));
	server_address.sin_family = AF_INET;
	inet_pton( AF_INET, ip, &server_address.sin_addr );
	server_address.sin_port = htons( port );

	// sys/socket.h
	/* Open a connection on socket FD to peer at ADDR (which LEN bytes long).
	   For connectionless socket types, just set the default address to send to
	   and the only address from which to accept transmissions.
	   Return 0 on success, -1 for errors.

	   This function is a cancellation point and therefore not marked with
	   __THROW.  */
	//extern int connect (int __fd, __CONST_SOCKADDR_ARG __addr, socklen_t __len);
	if ( connect( sock, (struct sockaddr*)&server_address, sizeof(server_address) ) ){
		printf("connect %s:%d error!", ip, port);
	}

	return 0;
}
