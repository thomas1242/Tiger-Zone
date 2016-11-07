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
#include "main.h"
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

int main(int, char const**) {




	//Temporary exit condition until sfml added back
	bool exit = 0;
	// Start the game loop
	while(exit == 0) {
		
	// sfml: create the main window
    // sfml: load tile textures
 	// sfml: Implement for loop to draw tiles
	// sfml: Create a graphical text to display
	// sfml: load in the deck images
	// Generate deck
	// sfml: Clear screen
	// sfml: draw tiles remaining string
	// sfml: draw the tile on top of the deck
	// sfml: Draw tiles on board
	// sfml: Update the window
	}
}

