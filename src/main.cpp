#include "game.h"
#include <iostream>
#include <sstream>
#include <unistd.h>
#include <SFML/Graphics.hpp>
#include "ResourcePath.hpp"
using namespace std;

static inline std::string int2Str(int x) {
    std::stringstream type;
    type << x;
    return type.str();
}

int main() {
    
    Game * game = new Game();               // create the game
    game->startGame();
    
    sf::Texture tileTextures[25];       // array to hold tile textures
    sf::RectangleShape tiles[25];       // array of textured rectangles a.k.a. tiles
    sf::Font font;
    
    sf::RenderWindow window(sf::VideoMode(1000, 1200), "SFML window");    // create the main window
    
    window.setFramerateLimit(5);
    
    
    
    if (    !tileTextures[ 1].loadFromFile(resourcePath()  + "1.png")      // load tile textures
        
        || !tileTextures[ 2].loadFromFile(resourcePath()  + "2.png")
        
        || !tileTextures[ 3].loadFromFile(resourcePath()  + "3.png")
        
        || !tileTextures[ 4].loadFromFile(resourcePath()  + "4.png")
        
        || !tileTextures[ 5].loadFromFile(resourcePath()  + "5.png")
        
        || !tileTextures[ 6].loadFromFile(resourcePath()  + "6.png")
        
        || !tileTextures[ 7].loadFromFile(resourcePath()  + "7.png")
        
        || !tileTextures[ 8].loadFromFile(resourcePath()  + "8.png")
        
        || !tileTextures[ 9].loadFromFile(resourcePath()  + "9.png")
        
        || !tileTextures[10].loadFromFile(resourcePath() + "10.png")
        
        || !tileTextures[11].loadFromFile(resourcePath() + "11.png")
        
        || !tileTextures[12].loadFromFile(resourcePath() + "12.png")
        
        || !tileTextures[13].loadFromFile(resourcePath() + "13.png")
        
        || !tileTextures[14].loadFromFile(resourcePath() + "14.png")
        
        || !tileTextures[15].loadFromFile(resourcePath() + "15.png")
        
        || !tileTextures[16].loadFromFile(resourcePath() + "16.png")
        
        || !tileTextures[17].loadFromFile(resourcePath() + "17.png")
        
        || !tileTextures[18].loadFromFile(resourcePath() + "18.png")
        
        || !tileTextures[19].loadFromFile(resourcePath() + "19.png")
        
        || !tileTextures[20].loadFromFile(resourcePath() + "20.png")
        
        || !tileTextures[21].loadFromFile(resourcePath() + "21.png")
        
        || !tileTextures[22].loadFromFile(resourcePath() + "22.png")
        
        || !tileTextures[23].loadFromFile(resourcePath() + "23.png")
        
        || !tileTextures[24].loadFromFile(resourcePath() + "24.png")
        
        )
    
    {
        
        exit(1);
        
    }

    const double size = (800 - 60) / 11.0;
    
    for (int i = 1; i < 25; i++) {      // used when drawing tiles on the board
        sf::RectangleShape tile(sf::Vector2f(size, size));
        tile.setTexture( &tileTextures[ i ] );
        tiles[i] = tile;
    }
    
    
    // Create a graphical text to display
    if (!font.loadFromFile(resourcePath() + "sansation.ttf")) {
        return EXIT_FAILURE;
    }

    
    sf::Text text("", font, 27);
    text.setStyle(sf::Text::Bold);
    text.setFillColor(sf::Color::Yellow);
    text.move(25,1050);
    
    sf::RectangleShape deckTopTile(sf::Vector2f(size * 1.75, size * 1.75));
    deckTopTile.setPosition(275, 1065);
    deckTopTile.setOrigin((size * 1.75/2), (size * 1.75/2));
    deckTopTile.setTexture( &tileTextures[1] );

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
    while (window.isOpen())
    {
        // Process events
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close window: exit
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                window.close();
            }
            else if (event.type == sf::Event::Resized) {
                    resizeWidth = event.size.width / 1000.0;
                    resizeHeight = event.size.height / 800.0;
            }
        }
        
        sf::Vector2i localPosition = sf::Mouse::getPosition(window);
        int row = (localPosition.y / resizeHeight) / int(size + 5);
        int col = (localPosition.x / resizeWidth) / int(size + 5);

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && window.hasFocus()) {
          //  cout << "click at row = " << abs(row) << " col = " << abs(col) << endl;
            if(abs(row) >= 0 && abs(col) >= 0 && abs(row) < 11 && abs(col) < 11) {  // for GUI, if user clicks on the board
                game->playTurn(abs(row), abs(col));
            }
            if(abs(row) >= 13 && abs(row) <= 15 && abs(col) >= 2 && abs(col) <= 4 ) {
                cout << "ROTATE!!" << endl;
                game->rotateCard();                                                 // rotate current card
                deckTopTile.rotate( game->getPlayer()->getCard()->getOrient() );    // rotate visual tile
            }

            
        }

        game->playTurn();   // draw a card if the player needs
        
        // Clear screen
        window.clear();

        // Draw the string
        string score = "cards left: " + int2Str( game->getBoard()->getDeck()->getSize() );
        text.setString( score );
        window.draw(text);
        
       // bool * b = game->getBoard()->getPossibleMoves();
        for(int i = 0; i < 11; i++) {
            for(int j = 0; j<11; j++) {
                if( game->getBoard()->getCard(i, j).getId() > -1 ) {
                    tiles[ game->getBoard()->getCard(i, j).getId() + 1 ] .setPosition(j * (size + 1) + 10, i * (size + 1) + 10);
                    window.draw( tiles[ game->getBoard()->getCard(i, j).getId() + 1 ] );
                }
            }
        }
        
        deckTopTile.setTexture( &tileTextures[ game->getCurrCardID() + 1 ] );
        
        window.draw( deckTopTile );
        // Update the window
        window.display();
    }

    return 0;
}
