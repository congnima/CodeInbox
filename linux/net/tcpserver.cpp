//#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <signal.h>
#include <unistd.h>
#include <assert.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <argp.h>

const char *argp_program_version = "tcpserver 1.0";
const char *argp_program_bug_address = "luogary6@gmail.com";
static char doc[] = "A Simple TCP Server";
static char args_doc[] = "ARG1 ARG2";
static struct argp_option options[] = {
    {"host",  'h', "host",      0,  "listen host" },
    {"port",  'p', "port",      0,  "listen port" },
    { 0 }
};
struct arguments
{
    char *args[32];                /* arg1 & arg2 */
    char *host;
    int port;
};

static error_t
parse_opt (int key, char *arg, struct argp_state *state)
{
    /* Get the input argument from argp_parse, which we
     *      know is a pointer to our arguments structure. */
    struct arguments *arguments = (struct arguments*)(state->input);

    switch (key)
    {
        case 'h':
            arguments->host = arg;
            break;
        case 'p':
            arguments->port = arg ? atoi(arg) : 0;
            break;

        //case ARGP_KEY_ARG:
            //if (state->arg_num >= 2)
                //[> Too many arguments. <]
                //argp_usage (state);

            //arguments->args[state->arg_num] = arg;

            //break;

        //case ARGP_KEY_END:
            //if (state->arg_num < 2)
                //[> Not enough arguments. <]
                //argp_usage (state);
            //break;

        default:
            return ARGP_ERR_UNKNOWN;
    }
    return 0;
}
static struct argp argp = { options, parse_opt, args_doc, doc };

static bool stop = false;
static void handle_term( int sig )
{
	printf("handle_term: bye~\n");
	stop = true;
}

int main(int argc, char** argv) {

    struct arguments arguments;
    argp_parse (&argp, argc, argv, 0, 0, &arguments);
    printf("listen on - host:%s, port:%d\n", arguments.host, arguments.port);

	signal( SIGTERM, handle_term );


	//char* ip = (char*)"127.0.0.1";
	//int port = 6000;
	int backlog = 5;

	// sys/socket.h
	// extern int socket (int __domain, int __type, int __protocol) __THROW;
	int sock = socket(PF_INET, SOCK_STREAM, 0);
	assert( sock > 0 );

	// bits/sockaddr.h
	//	#define	__SOCKADDR_COMMON(sa_prefix) \
	  //sa_family_t sa_prefix##family

	// netinet/in.h:
	//struct sockaddr_in
	  //{
		//__SOCKADDR_COMMON (sin_);
		//in_port_t sin_port;			[> Port number.  <]
		//struct in_addr sin_addr;		[> Internet address.  <]

		//[> Pad to size of `struct sockaddr'.  <]
		//unsigned char sin_zero[sizeof (struct sockaddr) -
				   //__SOCKADDR_COMMON_SIZE -
				   //sizeof (in_port_t) -
				   //sizeof (struct in_addr)];
	  //};
	struct sockaddr_in address;
	bzero(&address, sizeof(address));
	address.sin_family = AF_INET;
	// arpa/inet.h
	/* Convert from presentation format of an Internet number in buffer
	   starting at CP to the binary network format and store result for
	   interface type AF in buffer starting at BUF.  */
	//extern int inet_pton (int __af, const char *__restrict __cp,
				  //void *__restrict __buf) __THROW;
	inet_pton( AF_INET, arguments.host, &address.sin_addr );
	address.sin_port = htons( arguments.port );

	// sys/socket.h
	/* Give the socket FD the local address ADDR (which is LEN bytes long).  */
	//extern int bind (int __fd, __CONST_SOCKADDR_ARG __addr, socklen_t __len)
     //__THROW;
	int ret = bind( sock, (struct sockaddr*)&address, sizeof(address) );
	assert( ret != -1 );

	ret = listen( sock, backlog );
	assert ( ret != -1 );

	while ( !stop ) {
		//sleep(1);
		struct sockaddr_in client;
		socklen_t client_addrlength = sizeof( client );
		int connfd = accept( sock,  ( struct sockaddr* )&client, &client_addrlength );
		if ( connfd < 0 ) {
			printf( "errno is: %d\n", errno );
		} else {
			char remote[ INET_ADDRSTRLEN ];
			printf( "connected with ip: %s and port: %d\n", inet_ntop( AF_INET, &client.sin_addr, remote, INET_ADDRSTRLEN ), ntohs( client.sin_port ) );
			close( connfd );
		}
	}

	close( sock );
	return 0;
}
