Tiger-Zone - TEAM H Repository
==================

## **Member List**

|     Name    	| Username 	    |
|:-----------:	|:----------:	  |
| Evan Amstutz  | EvanMAmstutz	|
| Bronson Davis | drace128 	    |
| Sarah Garcia  | SarahmGarcia  |
| Thomas Palmer | thomas1242    |
| Zachary Taylor| taylorz0917   |
| Kurt Yilmaz   | KurtYilmaz    |

## **Architecture/Design Documentation**
-Include UML
-Activity Diagram Updated?

## **Source Code**
- Code is in C++ and is cointained in 'src'.
- An implementation with the testable GUI (and no client) is in the 'game_with_GUI' folder.

## **Class Descriptions**
- Main
- Game
- Player
- Board
  -Subclass
- Deck (only for non-client version)
- Card
- Input/Output
  -Subclass
## **Compilation and Run Instructions**
- Client based code
..* Compile in any C++ compiler with the -std=c++11 tag. I.e. 'g++ -o tiger -std=c++11'
..* Run with 

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
    - SFML Dependencies: http://www.sfml-dev.org/tutorials/2.4/
    - use main_with_GUI.cpp instead of main.cpp
  
- Test Server

## **Testing**
### Unit Testing
#### Googletest
..* ![Google Test](https://github.com/thomas1242/Tiger-Zone/blob/master/Images/googletest.png?raw=true)
..* Additional print statements are output within code.

### Integration Testing
#### Testing client with a mock server
![Server](https://github.com/thomas1242/Tiger-Zone/blob/master/Images/client_mock_server%20communication.png)
..* Included Test folder showcasing tests

### Acceptptance Testing
#### GUI plugin (Not compatible with server)
..* SFML dependencies required. To compile, see Compilation and Run Instructions.
  
## **Current Bugs**
- Timeout issue in input.cpp
