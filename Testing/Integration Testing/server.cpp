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
		strcpy(data, "WELCOME TEAMH PLEASE WAIT FOR THE NEXT CHALLENGE");
        send(sock_server, data, dataLength, 0);
        cout << "server=> " << data << endl;


        while(1)
        {
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
	        	for(int moveCount = 1; moveCount < 7; moveCount++)
	        	{
	    			recv(sock_server, data, dataLength, 0);
					cout << "client=> " << data << endl;  
					cin >> crap;
					if(crap == "q"){close(sock_server); exit(1);}      		
	        		if(moveCount == 1)
	        		{
						strcpy(data, "GAME A MOVE 1 PLAYER Red PLACED TLTTP AT 0 1 90 TIGER 8");
						send(sock_server, data, dataLength, 0);
						cout << "server=> " << data << endl;

						cin >> crap;
						if(crap == "q"){close(sock_server); exit(1);}
						strcpy(data, "GAME B MOVE 1 PLAYER Blue PLACED TLTTP AT 0 1 90 TIGER 8");
						send(sock_server, data, dataLength, 0);
						cout << "server=> " << data << endl;

						cin >> crap;
						if(crap == "q"){close(sock_server); exit(1);}
						strcpy(data, "MAKE YOUR MOVE IN GAME B WITHIN 1 SECOND: MOVE 2 PLACE LJTJ-");
				        send(sock_server, data, dataLength, 0);
				        cout << "server=> " << data << endl;
				    }
	        		else if(moveCount == 2)
	        		{
						strcpy(data, "GAME A MOVE 2 PLAYER Blue PLACED LJTJ- AT 0 2 180 TIGER 8");
						send(sock_server, data, dataLength, 0);
						cout << "server=> " << data << endl;

						cin >> crap;
						if(crap == "q"){close(sock_server); exit(1);}
						strcpy(data, "GAME B MOVE 2 PLAYER Red PLACED LJTJ- AT 0 2 180 TIGER 8");
						send(sock_server, data, dataLength, 0);
						cout << "server=> " << data << endl;

						cin >> crap;
						if(crap == "q"){close(sock_server); exit(1);}
						strcpy(data, "MAKE YOUR MOVE IN GAME A WITHIN 1 SECOND: MOVE 3 PLACE JLJL-");
				        send(sock_server, data, dataLength, 0);
				        cout << "server=> " << data << endl;
				    }		
	        		else if(moveCount == 3)
	        		{
						strcpy(data, "GAME A MOVE 3 PLAYER Red PLACED JLJL- AT 1 0 0 NONE");
						send(sock_server, data, dataLength, 0);
						cout << "server=> " << data << endl;

						cin >> crap;
						if(crap == "q"){close(sock_server); exit(1);}
						strcpy(data, "GAME B MOVE 3 PLAYER Blue PLACED JLJL- AT 1 0 0 TIGER 4");
						send(sock_server, data, dataLength, 0);
						cout << "server=> " << data << endl;

						cin >> crap;
						if(crap == "q"){close(sock_server); exit(1);}
						strcpy(data, "MAKE YOUR MOVE IN GAME B WITHIN 1 SECOND: MOVE 4 PLACE JJTJX");
				        send(sock_server, data, dataLength, 0);
				        cout << "server=> " << data << endl;
				    }	
	        		else if(moveCount == 4)
	        		{
						strcpy(data, "GAME A MOVE 4 PLAYER Blue PLACED JJTJX AT 1 1 270 TIGER 5");
						send(sock_server, data, dataLength, 0);
						cout << "server=> " << data << endl;

						cin >> crap;
						if(crap == "q"){close(sock_server); exit(1);}
						strcpy(data, "GAME B MOVE 4 PLAYER Red PLACED JJTJX AT 1 1 270 TIGER 5");
						send(sock_server, data, dataLength, 0);
						cout << "server=> " << data << endl;

						cin >> crap;
						if(crap == "q"){close(sock_server); exit(1);}
						strcpy(data, "MAKE YOUR MOVE IN GAME A WITHIN 1 SECOND: MOVE 5 PLACE JLTTB");
				        send(sock_server, data, dataLength, 0);
				        cout << "server=> " << data << endl;
				    }
	        		else if(moveCount == 5)
	        		{
						strcpy(data, "GAME A MOVE 5 PLAYER Red PLACED JLTTB AT 2 0 180 TIGER 1");
						send(sock_server, data, dataLength, 0);
						cout << "server=> " << data << endl;

						cin >> crap;
						if(crap == "q"){close(sock_server); exit(1);}
						strcpy(data, "GAME B MOVE 5 PLAYER Blue PLACED JLTTB AT 2 0 180 TIGER 1");
						send(sock_server, data, dataLength, 0);
						cout << "server=> " << data << endl;

						cin >> crap;
						if(crap == "q"){close(sock_server); exit(1);}
						strcpy(data, "MAKE YOUR MOVE IN GAME B WITHIN 1 SECOND: MOVE 6 PLACE TLLT-");
				        send(sock_server, data, dataLength, 0);
				        cout << "server=> " << data << endl;
				    }		
	        		else
	        		{
						strcpy(data, "GAME A MOVE 6 PLAYER Blue PLACED TLLT- AT 0 -1 180 CROCODILE");
						send(sock_server, data, dataLength, 0);
						cout << "server=> " << data << endl;

						cin >> crap;
						if(crap == "q"){close(sock_server); exit(1);}
						strcpy(data, "GAME B MOVE 6 PLAYER Red PLACED TLLT- AT 0 -1 180 TIGER 3");
						send(sock_server, data, dataLength, 0);
						cout << "server=> " << data << endl;

						cin >> crap;
						if(crap == "q"){close(sock_server); exit(1);}
						strcpy(data, "GAME A OVER PLAYER Red 6 PLAYER Blue 14");
				        send(sock_server, data, dataLength, 0);
				        cout << "server=> " << data << endl;

						cin >> crap;
						if(crap == "q"){close(sock_server); exit(1);}
						strcpy(data, "GAME B OVER PLAYER Red 20 PLAYER Blue 19");
				        send(sock_server, data, dataLength, 0);
				        cout << "server=> " << data << endl;	

						cin >> crap;
						if(crap == "q"){close(sock_server); exit(1);}
						strcpy(data, "END OF ROUND 1 OF 1");
				        send(sock_server, data, dataLength, 0);
				        cout << "server=> " << data << endl;			        		        
				    }			    		    	    
	        	}

	        	cout << "successfully made it through one round of the game" << endl;
	        	break;
	        }
	    }
	}
	close(sock_server);
	return 0;
}
