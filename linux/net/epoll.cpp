#include <sys/socket.h>
#include <sys/epoll.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <signal.h>
#include <unistd.h>
#include <assert.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <fcntl.h>

#define MAX_EVENT_NUMBER 1024
#define BUFFER_SIZE 10
struct fds
{
	int epollfd;
	int sockfd;
};

int setnonblocking( int fd ){
	int old_option = fcntl( fd, F_GETFL );
	int new_option = old_option | O_NONBLOCK;
	fcntl( fd, F_SETFL, new_option );
	return old_option;
}

void addfd( int epollfd, int fd, bool enable_et ){
	// sys/epoll.h
	//typedef union epoll_data
	//{
	  //void *ptr;
	  //int fd;
	  //uint32_t u32;
	  //uint64_t u64;
	//} epoll_data_t;

	//struct epoll_event
	//{
	  //uint32_t events;	[> Epoll events <]
	  //epoll_data_t data;	[> User data variable <]
	//} __EPOLL_PACKED;
	epoll_event event;
	event.data.fd = fd;
	event.events = EPOLLIN;
	if ( enable_et ){
		event.events |= EPOLLET;
	}
	epoll_ctl( epollfd, EPOLL_CTL_ADD, fd, &event );
	setnonblocking( fd );
}

// LT 模式的工作流程
void lt( epoll_event* events, int number, int epollfd, int listenfd ){
	char buf[ BUFFER_SIZE ];
	for ( int i = 0; i < number; ++i ){
		int sockfd = events[i].data.fd;
		if ( sockfd == listenfd ){
			struct sockaddr_in client_address;
			socklen_t client_addrlength = sizeof( client_address );
			int connfd = accept( listenfd, ( struct sockaddr* )&client_address, &client_addrlength );
			addfd( epollfd, connfd, false );
		} else if ( events[i].events & EPOLLIN ){
			printf( "event trigger once\n" );
			memset( buf, '\0', BUFFER_SIZE );
			int ret = recv( sockfd, buf, BUFFER_SIZE - 1, 0 );
			if ( ret <= 0 ){
				close( sockfd );
				continue;
			}
			printf( "get %d bytes of content: %s\n", ret, buf );
		}else{
			printf( "something else happended \n" );
		}
	}
}

// ET 模式的工作流程
void et( epoll_event* events, int number, int epollfd, int listenfd ){
	char buf[ BUFFER_SIZE ];
	for ( int i = 0; i < number; ++i ){
		int sockfd = events[i].data.fd;
		if ( sockfd == listenfd ){
			struct sockaddr_in client_address;
			socklen_t client_addrlength = sizeof( client_address );
			int connfd = accept( listenfd, ( struct sockaddr* )&client_address, &client_addrlength );
			addfd( epollfd, connfd, true );
		} else if ( events[i].events & EPOLLIN ){
			printf( "event trigger once\n" );
			while( 1 ){
				memset( buf, '\0', BUFFER_SIZE );
				int ret = recv( sockfd, buf, BUFFER_SIZE - 1, 0 );
				if ( ret < 0 ){
					// 对于非阻塞 IO，下面的条件成立表示数据已经全部读取完毕。此后，epoll 就能再次触 发 sockfd 上的 EPOLLIN 事件，以驱动下一次读操作
					if ( ( errno == EAGAIN ) || ( errno == EWOULDBLOCK ) ){
						printf( "read later\n" );
						break;
					}
					close( sockfd );
					break;
				}else if (ret == 0){
					close( sockfd );
				}else{
					printf( "get %d bytes of content: %s\n", ret, buf );
				}
			}
		}else{
			printf( "something else happended \n" );
		}
	}
}

int main( int argc, char* argv[] ){
	
	char* ip = (char*)"127.0.0.1";
	int port = 6000;

	struct sockaddr_in address;
	bzero( &address, sizeof( address ) );
	address.sin_family = AF_INET;
	inet_pton( AF_INET, ip, &address.sin_addr );
	address.sin_port = htons( port );

	int listenfd = socket( PF_INET, SOCK_STREAM, 0 );
	assert( listenfd >= 0 );

	int ret = bind( listenfd, ( struct sockaddr* )&address, sizeof( address ) );
	assert( ret != -1 );

	ret = listen( listenfd, 5 );
	assert( ret != -1 );

	epoll_event events[ MAX_EVENT_NUMBER ];
	int epollfd = epoll_create( 5 );
	assert( epollfd != -1 );
	addfd( epollfd, listenfd, true );

	while ( 1 ) {
		int ret = epoll_wait( epollfd, events, MAX_EVENT_NUMBER, -1 );

		if ( ret < 0 ) {
			printf( "epoll failuere\n" );
			break;
		}
		//lt( events, ret, epollfd, listenfd );	// 使用 LT 模式
		et( events, ret, epollfd, listenfd );	// 使用 ET 模式
	}

	close( listenfd );
	return 0;
}
