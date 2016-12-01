#include "game.h"
#include "player.h"

#include <iostream>
#include <sstream>
#include <unistd.h>
#include <SFML/Graphics.hpp>
#include "ResourcePath.hpp"
#include <stdio.h>
using namespace std;

static inline std::string int2Str(int x) {
    std::stringstream type;
    type << x;
    return type.str();
}

int main() {
    
    Game * game = new Game();               // create the game
    game->startGame();
    
    sf::Texture tileTextures[UNIQUECARDS];       // array to hold tile textures
    sf::RectangleShape tiles[UNIQUECARDS];       // array of textured rectangles a.k.a. tiles
    sf::Font font;
    
    sf::RenderWindow window(sf::VideoMode(1000, 1200), "SFML window");    // create the main window
    
    window.setFramerateLimit(15);
    
    
    
    if (  !tileTextures[ 0].loadFromFile(resourcePath()  + "1.png")
        
        || !tileTextures[ 1].loadFromFile(resourcePath()  + "1.png")      // load tile textures
        
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
        
        || !tileTextures[25].loadFromFile(resourcePath()  + "25.png")
        
        || !tileTextures[26].loadFromFile(resourcePath()  + "26.png")
        
        || !tileTextures[27].loadFromFile(resourcePath()  + "27.png")
        
        )
        
    {
        
        exit(1);
        
    }
    
    const double size = (800 - (ROWS + 1)*5 ) / ROWS;
    double offset = (size/2)*0.707;
    
    for (int i = 0; i < UNIQUECARDS; i++) {      // used when drawing tiles on the board
        sf::RectangleShape tile(sf::Vector2f(size, size));
        tile.setTexture( &tileTextures[ i ] );
        tiles[i] = tile;
    }
    
    int * rots = new int[UNIQUECARDS];
    int dRot = 0;
    for(int i = 0; i < UNIQUECARDS; i++){
        rots[i] = 0;
    }
    
    // Create a graphical text to display
    if (!font.loadFromFile(resourcePath() + "sansation.ttf")) {
        return EXIT_FAILURE;
    }
    
    
    sf::Text text("", font, 27);
    text.setStyle(sf::Text::Bold);
    text.setFillColor(sf::Color::Yellow);
    text.move(475,1100);
    
    sf::Text text2("", font, 27);
    text2.setStyle(sf::Text::Bold);
    text2.setFillColor(sf::Color::Yellow);
    text2.move(25,1000);
    text2.setString( "\ncurrent------->\ncard----------->" );
    
    sf::Text text3("", font, 27);
    text3.setStyle(sf::Text::Bold);
    text3.setFillColor(sf::Color::Yellow);
    text3.move(150,1127);
    text3.setString( "click card to rotate" );
    
    
    sf::Text text4("", font, 27);
    text4.setStyle(sf::Text::Bold);
    text4.setFillColor(sf::Color::Yellow);
    text4.move(695,910);
    
    sf::Text text5("", font, 27);
    text5.setStyle(sf::Text::Bold);
    text5.setFillColor(sf::Color::Yellow);
    text5.move(695,940);
    
    sf::Text text4b("", font, 27);
    text4b.setStyle(sf::Text::Bold);
    text4b.setFillColor(sf::Color::Yellow);
    text4b.move(370,910);
    
    sf::Text text5b("", font, 27);
    text5b.setStyle(sf::Text::Bold);
    text5b.setFillColor(sf::Color::Yellow);
    text5b.move(370,940);
    
    sf::Text text6("", font, 27);
    text6.setStyle(sf::Text::Bold);
    text6.setFillColor(sf::Color::Yellow);
    text6.move(25,940);
    
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
    
    int r = 0;
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
            if(abs(row) >= 0 && abs(col) >= 0 && abs(row) < ROWS && abs(col) < COLS) {  // for GUI, if user clicks on the board
                game->giveTurn(abs(row), abs(col));
            }
            if(abs(row) >= 13 && abs(row) <= 15 && abs(col) >= 2 && abs(col) <= 4 ) {
                cout << "ROTATE!!" << endl;
                game->rotateCard();                                                 // rotate current card
            }
        }
        
        //Input in;
        //Output  * out = new Output();
        game->giveCard();   // draw a card if the player needs
        
        // Clear screen
        window.clear();
        
        // Draw the string
        string score = int2Str( game->getDeck()->getSize() ) + " cards left in the deck,\nnot including current card";
        text.setString( score );
        window.draw(text2);
        window.draw(text);
        window.draw(text3);
        
        
        string player1score = "player 1's score: " + int2Str(game->getScore( true ));
        text4.setString(player1score);
        window.draw(text4); //p1 sc
        
        
        string player2score = "player 2's score: " + int2Str(game->getScore( false ));
        text5.setString(player2score);
        window.draw(text5); //p2 sc
        
        string player1meeps = "player 1's meeples: " + int2Str(game->getMeeples( true ));
        text4b.setString(player1meeps);
        window.draw(text4b); //p1 sc
        
        
        string player2meeps = "player 2's meeples: " + int2Str(game->getMeeples( false ));
        text5b.setString(player2meeps);
        window.draw(text5b); //p2 sc
        
        
        string turn_string;
        if ( game->getCurrTurn() ) {
            turn_string = "player 1's turn";
        }
        else {
            turn_string = "player 2's turn";
        }
        text6.setString( turn_string );
        window.draw(text6); //turn
        
        // should only call this once for efficiency
        // bool * b = game->getBoard()->getPossibleMoves();
        for(int i = 0; i < ROWS; i++) {
            for(int j = 0; j<COLS; j++) {
                if( game->getBoard()->getCard(i, j).getId() > -1 ) {
                    tiles[ game->getBoard()->getCard(i, j).getId() ] .setPosition(j * (size + 1) + 10 + offset, i * (size + 1) + 10 + offset);
                    tiles[ game->getBoard()->getCard(i, j).getId()  ] .setOrigin((size/2), (size/2));
                    tiles[ game->getBoard()->getCard(i, j).getId()  ] .rotate( 360 - rots[game->getBoard()->getCard(i, j).getId()] );
                    rots[game->getBoard()->getCard(i, j).getId() ] = game->getBoard()->getCard(i, j).getOrient();   // set rot
                    tiles[ game->getBoard()->getCard(i, j).getId()  ] .rotate( game->getBoard()->getCard(i, j).getOrient() );
                    window.draw( tiles[ game->getBoard()->getCard(i, j).getId() ] );
                }
                if( game->getBoard()->checkPossibleMove(i, j)  ) {
                    circle.setPosition(j * (size + 1) + 35, i * (size + 1) + 35);
                    circle.setOrigin(radius/2, radius/2);
                    tiles[ game->getBoard()->getCard(i, j).getId() ] .setOrigin((size/2), (size/2));
                    window.draw(circle);
                }
            }
        }
        deckTopTile.setTexture( &tileTextures[ game->getCurrCardID() ] );
        deckTopTile.rotate( 360 - dRot );
        dRot = game->getCurrCard()->getOrient();   // set rot
        deckTopTile.rotate( game->getCurrCard()->getOrient() );
        window.draw( deckTopTile );        // Update the window
        window.display();
    }
    return 0;
}
