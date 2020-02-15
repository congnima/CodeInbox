tcpserver:tcpserver.cpp
	gcc -o tcpserver tcpserver.cpp

tcpclient:
	gcc -o tcpclient tcpclient.cpp

all:
	tcpserver
	tcpclient

#clean:
	#rm tcpserver tcpclient
