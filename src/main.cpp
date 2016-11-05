//ALL SFML DEPENDENCIES CURRENTLY MOVED TO gui.cpp TO COMPILE NORMALLY.
//Let's work on keeping all gui stuff in that file and referencing it here as a plugin
//All calls to gui files preceeded by "sfml: "
//Please install SFML for when we do implement it.

/*#include <SFML/Graphics.hpp>
#include "ResourcePath.hpp"*/
#include <ctime>
#include <iostream>
#include <sstream>
#include <string>
#include <stack>
#include <main.h>
#include "board.h"
#include "deck.h"
#include "card.h"
#include "gui.cpp"

using namespace std;

/*
sf::Texture tileTextures[25];       // array to hold tile textures
sf::RectangleShape tiles[25];       // array of textured rectangles a.k.a. tiles
*/

Deck deck;							// deck of cards
Board board;						// tiles are currently on the board

int main(int, char const**)
{
	//Temporary exit condition until sfml added back
	bool exit = 0;

	// Start the game loop
	// sfml: create the main window
    // sfml: load tile textures
 	// sfml: Implement for loop to draw tiles
*
    
    // Create a graphical text to display
    sf::Font font;
    if (!font.loadFromFile(resourcePath() + "sansation.ttf")) {
        return EXIT_FAILURE;
    }
    
    sf::Text text("", font, 27);
    text.setStyle(sf::Text::Bold);
    text.setFillColor(sf::Color::Yellow);
    text.move(25,1075);
   
    
    // load in the deck images, generate deck.
    sf::RectangleShape deckTopTile(sf::Vector2f(size * 1.75, size * 1.75));
    deckTopTile.setPosition(225, 1035);
    
    //
    sf::Texture pieceImg;
    if (    !pieceImg.loadFromFile(resourcePath()  + "p1.png") )
    {
        exit(1);
    }
    pieceImg.setSmooth(true);
    double radius = (size - 10) / 10;
    sf::CircleShape circle(radius);
    circle.setTexture(&pieceImg);
    
    double resizeWidth = -1;
    double resizeHeight = -1;

    // Start the game loop
    while (1) //(window.isOpen())
    {
        // Process events
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close window: exit
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            // Escape pressed: exit
            else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                window.close();
            }
            else if (event.type == sf::Event::Resized) {
                resizeWidth = event.size.width / 1000.0;
                resizeHeight = event.size.height / 1200.0;
            }
        
        }

        sf::Vector2i localPosition = sf::Mouse::getPosition(window);
        int row = (localPosition.y / resizeHeight) / int(size + 5);
        int col = (localPosition.x / resizeWidth) / int(size + 5);
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && window.hasFocus()) {
            cout << "y = " << abs(row) << " x = " << abs(col) << endl;

            if( possibleMoves->get(abs(col), abs(row)) == 1) {
    
                board->set(abs(col), abs(row), deck.top() );
                possibleMoves->set(abs(col), abs(row), 0 );
                popCardOffDeck();
                //board->printBoard();
                
            }
            int deg = 90;
            if(abs(col) == 3 && abs(row) == 12) {
                deckTopTile.rotate(deg % 360);
                deg += 90;
            }
        }
        

        // Clear screen
        window.clear();
        
        // draw tiles remaining string
        text.setString( getDeckString() );
        window.draw( text );
        
        // draw the tile on top of the deck
        deckTopTile.setTexture( &tileTextures[ deck.top() ] );
        window.draw( deckTopTile );
        
        setPossibleMoves();
        // Draw tiles on board
        for(int i = 0; i < 11; i++) {
            for(int j = 0; j < 11; j++) {
                if( board->get(i, j) > 0 ) {
                    tiles[ board->get(i, j) ].setPosition(i * (size + 1) + 5, j * (size + 1) + 5);
                    window.draw( tiles[ board->get(i, j) ] );
                }
                if( possibleMoves->get(i, j) == 1 ) {
                    circle.setPosition(i * (size + 1) + 35, j * (size + 1) + 35);
                    window.draw( circle );
                }
            }
        }
        
        // Update the window
        window.display();
    }

    return EXIT_SUCCESS;
*/
	}
}

