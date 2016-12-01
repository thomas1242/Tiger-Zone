#include <iostream>			//allows for basic input/output
#include <stdlib.h>			//allows for use of the exit() function
#include <sys/types.h>		//allows for creation of a TCP socket
#include <sys/socket.h>		//allows for creation of a TCP socket
#include <netinet/in.h>		//allows for use of structs such as sockaddr, sockaddr_in, in_addr
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
using namespace std;

int main()
{
	int portNumber = 1500;
	struct sockaddr_in serverAddress;
	int dataLength = 1000;
	char data[dataLength];
	char crap[dataLength];
	
	/*instantiate a new socket...*/
	
	int sock_client = socket(AF_INET, SOCK_STREAM, 0);		

	if(sock_client < 0)				//confirm socket was created correctly
	{
		cout << "Failed to create a socket" << endl;
		exit(1);
	}

	cout << "Socket successfully created" << endl;

	serverAddress.sin_family = AF_INET; 			//specifies address domain for client
	serverAddress.sin_port = htons(portNumber);		//translates port for host byte to network byte
	serverAddress.sin_addr.s_addr = INADDR_ANY;		//allows it to work with any connecting addresses

	//serverAddress.sin_addr.s_addr = inet_addr("10.0.0.1");
	//bzero(&serverAddress.sin_zero, 8);
	
	/*Binding to address...*/

	socklen_t length = sizeof(serverAddress);	
	int checkBinding = bind(sock_client, (struct sockaddr*)&serverAddress, length);

	if(checkBinding < 0)
	{
		cout << "Failed to bind" << endl;
		exit(1);
	}

	/*now to listen for client connection...*/

	int checkListening = listen(sock_client, 1);

	/*now to accept the client connection*/

	int sock_server;
	sock_server = accept(sock_client, (struct sockaddr*)&serverAddress, &length);
	if(sock_server != -1)
	{
		cout << "tcp connection established" << endl;
	}

	while(1)
	{
		//server:
		cin >> data;
		strcpy(data, "THIS IS SPARTA!");
        send(sock_server, data, dataLength, 0);
        cout << "server=> " << data << endl;

        //client:
		recv(sock_server, data, dataLength, 0);
		cout << "client=> " << data << endl;

		//server:
		cin >> data;
		strcpy(data, "HELLO!");
        send(sock_server, data, dataLength, 0);
        cout << "server=> " << data << endl;

        //client:
		recv(sock_server, data, dataLength, 0);
		cout << "client=> " << data << endl;

		//server:
		cin >> data;
		strcpy(data, "WELCOME <pid> PLEASE WAIT FOR THE NEXT CHALLENGE");
        send(sock_server, data, dataLength, 0);
        cout << "server=> " << data << endl;

		//server:
		cin >> data;
		strcpy(data, "NEW CHALLENGE 1 YOU WILL PLAY 1 MATCH");
        send(sock_server, data, dataLength, 0);
        cout << "server=> " << data << endl;

		//server:
		cin >> data;
		strcpy(data, "BEGIN ROUND 1 OF 1");
        send(sock_server, data, dataLength, 0);
        cout << "server=> " << data << endl;

		//server:
		cin >> data;
		strcpy(data, "YOUR OPPONENT IS PLAYER Blue");
        send(sock_server, data, dataLength, 0);
        cout << "server=> " << data << endl;

		//server:
		cin >> data;
		strcpy(data, "STARTING TILE IS TLTJ- AT 0 0 0");
        send(sock_server, data, dataLength, 0);
        cout << "server=> " << data << endl;

		//server:
		cin >> data;
		strcpy(data, "THE REMAINING 6 TILES ARE [ TLTTP LJTJ- JLJL- JJTJX JLTTB TLLT- ]");
        send(sock_server, data, dataLength, 0);
        cout << "server=> " << data << endl;

		//server:
		cin >> data;
		strcpy(data, "MATCH BEGINS IN 15 SECONDS");
        send(sock_server, data, dataLength, 0);
        cout << "server=> " << data << endl;

		//server:
		cin >> data;
		strcpy(data, "MAKE YOUR MOVE IN GAME A WITHIN 1 SECOND: MOVE 1 PLACE TLTTP");
        send(sock_server, data, dataLength, 0);
        cout << "server=> " << data << endl;

        while(1)
        {
        	recv(sock_server, data, dataLength, 0);
			cout << "client=> " << data << endl;

			cout << "server=> ";
			cin >> crap;
			send(sock_server, data, dataLength, 0);
        }
	}
	close(sock_server);
	return 0;
}
