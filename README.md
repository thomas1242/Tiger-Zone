Tiger-Zone - TEAM H Repository
==================

## **Member List**

|     Name    	| Username 	    |
|:-----------:	|:----------:	|
| Evan Amstutz  | EvanMAmstutz	|
| Bronson Davis | drace128 	    |
| Sarah Garcia  | SarahmGarcia  |
| Thomas Palmer | thomas1242    |
| Zachary Taylor| taylorz0917   |
| Kurt Yilmaz   | KurtYilmaz    |

## **Architecture/Design Documentation**
![UML with Client](https://github.com/thomas1242/Tiger-Zone/blob/master/Images/Client%20UML.png?raw=true)
                                            UML with Client


## **Source Code**
- Code is in C++ and is cointained in 'src'.
- An implementation with the testable GUI (and no client) is in the 'game_with_GUI' folder.

## **Class Descriptions**
Main

- Highest level.
- Controls two games, and and Input/Output class.
- Manages connection with server via TCP socket.

Game

- Second highest level architecturally.
- Gives abilitity for players to make moves.
- Contains Board (and Deck in non-client versions).

Player

- Changes both the board and card objects.
- Makes decisions based on the Board's possible moves.

Board

- Contains matrix of cards.
- Keeps track of terrain and tiger locations.
- Stores a 2D array of possible moves.
..* AI players can use this array to make decisions.

Deck (only for non-client version)

- Stack of cards to be drawn by the game and given to the Player.

Card

- Contains edges with terrain types.
- Is passed from Server->Main->Game->Player->Board.
- A unique ID can be passed through the server.

Input/Output

- Utilized by server to store or queue relevant data for server connection.

## **Compilation and Run Instructions**
- Client based code
1. Navigate to Tiger-Zone/src
2. Compile in any C++ compiler with the -std=c++11 tag. I.e. 'g++ -o tiger -std=c++11'
3. Run on a TigerZone Server with the following arguments i.e. './tiger 100.32.100.961 4444 TIGERZONE TEAMH IAMH'
1. The IP address of the server
2. The port number of the server
3. The tournament password
4. Your username
5. Your user password

### __Official Version__
#### **Without GUI (client version)**
1. Navigate to Tiger-Zone/src in a command line interface, or an IDE capable of compiling c++ code.
2. Compile with the following tags: '-o tiger -std=c++11' i.e. 'g++ -o tiger -std=c++11'
3. Run on a TigerZone Server with the following arguments i.e. './tiger 100.32.100.961 4444 TIGERZONE TEAMH IAMH'
 1. The IP address of the server
 2. The port number of the server
 3. The tournament password
 4. Your username
 5. Your user password
  

### __Extra Stuff__
- With GUI (no client)
    ..* SFML Dependencies: http://www.sfml-dev.org/tutorials/2.4/
    ..* use main_with_GUI.cpp instead of main.cpp
  
- Test Server
  ..* Compile with 'g++ -o server server.cpp'
  ..* Run with ./server
  ..* Press any key to iterate through messages once connected by TCP socket.
  
## **Testing**
### Unit Testing
#### Googletest
..* ![Google Test](https://github.com/thomas1242/Tiger-Zone/blob/master/Images/googletest.png?raw=true)
..* Additional print statements are output within code.

### Integration Testing
#### Testing client with a mock server
![Server](https://github.com/thomas1242/Tiger-Zone/blob/master/Images/client_mock_server%20communication.png)
..* Included Test folder showcasing tests

### Acceptance Testing
#### GUI plugin (Not compatible with server)
..* SFML dependencies required. http://www.sfml-dev.org/tutorials/2.4/
  
   ![Google Test](https://github.com/thomas1242/Tiger-Zone/Images/move_0_a.png)
  
## **Current Bugs**
- Timeout issue in input.cpp
