all: tcpserver tcpclient epoll

tcpserver:tcpserver.cpp
	gcc -g -o tcpserver tcpserver.cpp

tcpclient:tcpclient.cpp
	gcc -g -o tcpclient tcpclient.cpp

epoll:epoll.cpp
	gcc -g -o epoll epoll.cpp

.PHONY: clean
clean:
	-rm *.o
	-rm tcpserver
	-rm tcpclient
	-rm epoll
