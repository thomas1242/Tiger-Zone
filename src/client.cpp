#include <iostream>			//allows for basic input/output
#include <stdlib.h>			//allows for use of the exit() function
#include <sys/types.h>		//allows for creation of a TCP socket
#include <sys/socket.h>		//allows for creation of a TCP socket
#include <netinet/in.h>		//allows for use of structs such as sockaddr, sockaddr_in, in_addr
#include <unistd.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>
using namespace std;

int main(int argc, char *argv[])
{
	int sock;
	int portNumber = 1500;
	struct sockaddr_in clientAddress;
	struct hostent *host;
	int dataLength = 100;
	char data[dataLength];
	
	//instantiate a new socket
	
	sock = socket(AF_INET, SOCK_STREAM, 0);		

	if(sock < 0)				//confirm socket was created correctly
	{
		cout << "Failed to create a socket" << endl;
		exit(1);
	}

	cout << "Socket successfully created" << endl;

	host = gethostbyname(argv[1]);
	memcpy(&clientAddress.sin_addr, host->h_addr, host->h_length);
	clientAddress.sin_family = AF_INET; 			//specifies address for client
	clientAddress.sin_port = htons(portNumber);		//translates port for host byte to network byte

	//now to connect to the server...

	int checkConnection;
	int length = sizeof(clientAddress);
	checkConnection = connect(sock, (struct sockaddr*)&clientAddress, length);
	if(checkConnection < 0)
	{
		cout << "failed to connect" << endl;
		exit(1);
	}

	//Once connected, wait to receive from the server

	cout << "Looking for connection to server..." << endl;

	
/*
	strcpy(data, "Connection established!");
	sentData = send(sock, data, dataLength, 0);		//this will fill the data buffer with information from the server

	if(sentData < 0)
	{
		cout << "failed to send data" << endl;
		exit(1);
	}
*/
	int sent, received;
	while(1)
	{
		recv(sock, data, dataLength, 0);

		cout << "server=> " << data << endl;
		cout << "client=> ";
		cin >> data;

		send(sock, data, dataLength, 0);

	}

	close(sock);
	return 0;
}