#include "game.h"
#include <sstream>
#include <stdio.h>
#include <iostream>         //allows for basic input/output
#include <stdlib.h>         //allows for use of the exit() function
#include <sys/types.h>      //allows for creation of a TCP socket
#include <sys/socket.h>     //allows for creation of a TCP socket
#include <netinet/in.h>     //allows for use of structs such as sockaddr, sockaddr_in, in_addr
#include <unistd.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>
#include <string>
using namespace std;

//SOCKET MAIN


/*argv[0] is the name of the executable*/
/*argv[1] will be the IP address*/
/*argv[2] will be the port number*/
/*argv[3] will be the tournament password*/
/*argv[4] will be our username*/
/*argv[5] will be our password*/

/*
int main(int argc, char *argv[]) 
{
    struct sockaddr_in clientAddress;
    int dataLength = 1000;
    //char *data = new char[dataLength];
    char data[dataLength];
    string str = "";
    Input in;
    Output *out = new Output();
    int portNumber = atoi(argv[2]);
    int sock = socket(AF_INET, SOCK_STREAM, 0);

    if(sock < 0)
    {
        cout << "exit on socket" << endl;
        exit(1);
    }

    clientAddress.sin_addr.s_addr = inet_addr(argv[1]);
    clientAddress.sin_family = AF_INET;
    clientAddress.sin_port = htons(portNumber);

    int length, checkConnection;
    length = sizeof(clientAddress);
    checkConnection = connect(sock, (struct sockaddr*)&clientAddress, length);

    if(checkConnection < 0)
    {
        cout << "exit on checkConnection" << endl;
        exit(1);
    }
    else
    {
        cout << "tcp connection established" << endl;
    }

    //Tournament Setup Logging Junk

    recv(sock, data, dataLength, 0);
    cout << "server=> " << data << endl;

    str = "Join ";
    str.append(argv[3]);
    cout << "client=> " << str << endl;
    send(sock, str.c_str(), dataLength, 0);

    recv(sock, data, dataLength, 0);
    cout << "server=> " << data << endl;
    str = string(data);
    in.takeInput(str);  

    str = "I AM ";
    str.append(argv[4]);
    str.append(" ");
    str.append(argv[5]);

    cout << "client=> " << str << endl;
    send(sock, str.c_str(), dataLength, 0); 

    recv(sock, data, dataLength, 0);
    cout << "server=> " << data << endl;        //"please wait for the next challenge"
    str = string(data);
    in.takeInput(str);


    /*Here is where the loop will begin*/
/*
    while(in.tournyOpen)
    {
        recv(sock, data, dataLength, 0);
        cout << "server=> " << data << endl;
        str = string(data);
        in.takeInput(str);

        while(in.challengeOpen)
        {

            Game *game1 = new Game();
            Game *game2 = new Game();

            game2->setStartingPlayer(false);
            
            int x = 0;
            while(x < 3)
            {
                recv(sock, data, dataLength, 0);
                cout << "server=> " << data << endl;
                str = string(data);
                in.takeInput(str);
                x++;
            }

            /*Last message received up to this point is: starting tile is XXXX*/

/*
            int row, col = 0;
            int track_rot = 0;
            string choice;
            string space = " ";
            

            recv(sock, data, dataLength, 0);
            cout << "server=> " << data << endl;
            str = string(data);
            in.takeInput(str);  

            //Last message received up to this point is: THE REMAINING X TILES ARE [...]*/
/*
            recv(sock, data, dataLength, 0);
            cout << "server=> " << data << endl;
            str = string(data);
            in.takeInput(str);
*/
            //Last message received up to this point is: MATCH BEGINS IN 15 SECONDS*/



            //15 seconds later......*/
/*
            while(in.gameOpen)
            {
                recv(sock, data, dataLength, 0);
                cout << "server=> " << data << endl;
                str = string(data);
                in.takeInput(str);
            

                //AT THIS POINT THE AI WILL HAVE TO TAKE THE INPUT PARAMETERS AND MAKE A MOVE

                if(in.game == 'A')
                {
                    game1->giveCard(in.tile, out);
                    /*AI IMPLEMENTATION MAKING A MOVE*/
/*                    game1->giveTurn(out->coord.first, out->coord.second);

                }
                else if(in.game == 'B')
                {

                    game2->giveCard(in.tile, out);
                    /*AI IMPLEMENTATION MAKING A MOVE*/
/*                    game2->giveTurn(out->coord.first, out->coord.second);
                }
                    

                //THE FOLLOWING LINE OF CODE WILL BE REPLACED WITH in.outputFunc();

                str = out->outputFunc(out->coord.first, out->coord.second, out->orientation);
                cout << "client=> " << str << endl;
                send(sock, str.c_str(), dataLength, 0);         
            }
        }
    }
    return 0;
}
*/

int main() {
    
    Game * game = new Game();               // create the game
    game->startGame();
    int row, col, orientation;
    string choice;
    
    
    
    
    
    while ( game->status() == ON )  // Start the game loop
    {      
        game->giveCard();   // draw a card if the player needs
        while((game->player_one->hasCard == false && game->player_two->hasCard == false) || game->deck->isEmpty()) {
           game->current_turn = !game->current_turn;
           game->giveCard();
        }    

        if ( game->getCurrTurn() ) { cout << "\nPlayer 1's turn" << endl; }
        else                       { cout << "\nPlayer 2's turn" << endl; }
        cout << "enter '0' to place current card on the board" << endl;
        cout << "enter '1' to rotate current card" << endl;
        cout << "enter '2' to print the board\n" << endl;
        
        cin >> choice;

        if ( choice == "0" ) {
            cout << "row? ";
            cin >> row;
            cout << "col? ";
            cin >> col;
            cout << "orientation? ";
            cin >> orientation;
            game->giveTurn(row, col, orientation);
        }
        else if( choice == "1") {
            game->rotateCard();
        }
        else if( choice == "2") {
            game->printBoard();
        }
    }

    return 0;
}
