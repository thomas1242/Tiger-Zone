#include "game.h"
#include "player.h"

#include <iostream>
#include <sstream>
#include <unistd.h>
#include <SFML/Graphics.hpp>
#include "ResourcePath.hpp"
#include <stdio.h>
#include <math.h>
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
    sf::Font font2;
    sf::RenderWindow window(sf::VideoMode(1000, 1200), "Tiger Zone");    // create the main window
    
    window.setFramerateLimit(10);
    
    
    
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
    
    sf::RectangleShape bg(sf::Vector2f(1000, 900));
    sf::Texture stripe;
    stripe.loadFromFile(resourcePath()  + "wood2.jpg");
    bg.setTexture( &stripe );
    bg.setPosition(0, 0);

    sf::RectangleShape bg1(sf::Vector2f(1000, 900));
    sf::Texture stripe1;
    stripe1.loadFromFile(resourcePath()  + "tface2.png");
    bg1.setTexture( &stripe1 );
    bg1.setFillColor( sf::Color(255, 255, 255, 65) );
    bg1.setPosition(0, 0);
    
    
    
    sf::RectangleShape wood(sf::Vector2f(1050, 330));
    sf::Texture woods;
    woods.loadFromFile(resourcePath()  + "wood.jpg");
    wood.setTexture( &woods );
    wood.setPosition(0, 900);
    
    const double size = (800 - (ROWS + 1)*5 ) / ROWS;       //800
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
    if (!font.loadFromFile(resourcePath() + "sansation.ttf")
        || !font2.loadFromFile(resourcePath() + "sansation.ttf")) {
        return EXIT_FAILURE;
    }
    
    
    sf::Text text("", font2, 27);
    text.setStyle(sf::Text::Bold);
    text.setFillColor(sf::Color::White);
    text.move(475,1127);
    
    sf::Text text2("", font, 27);
    text2.setStyle(sf::Text::Bold);
    text2.setFillColor(sf::Color::White);
    text2.move(25,1000);
    //text2.setString( "\ncurrent------->\ncard----------->" );
    
    sf::Text text3("", font, 27);
    text3.setStyle(sf::Text::Bold);
    text3.setFillColor(sf::Color::White);
    text3.move(50,1127);
    text3.setString( "click card to rotate" );
    
    
    sf::Text text4("", font, 30);
    text4.setStyle(sf::Text::Bold);
    text4.setFillColor(sf::Color::White);
    //text4.setFillColor(sf::Color(255, 0, 0, 225));

    text4.move(380,1045);
    
    sf::Text text5("", font, 30);
    text5.setStyle(sf::Text::Bold);
    text5.setFillColor(sf::Color::White);
    //text5.setFillColor(sf::Color(0, 0, 255, 225));
    text5.move(695,1045);
    
    sf::Text text4b("", font, 27);
    text4b.setStyle(sf::Text::Bold);
    text4b.setFillColor(sf::Color::White);
    //text4b.setFillColor(sf::Color(255, 0, 0, 225));

    text4b.move(380,980);
    
    sf::Text text5b("", font, 27);
    text5b.setStyle(sf::Text::Bold);
    text5b.setFillColor(sf::Color::White);
    //text5b.setFillColor(sf::Color(0, 0, 255, 225));
    text5b.move(695,980);
    
    sf::Text text6("", font2, 37);
    text6.setStyle(sf::Text::Bold);
    text6.setFillColor(sf::Color::White);
    text6.move(50,930);
    
    sf::Text p1name("", font2, 37);
    p1name.setStyle(sf::Text::Bold);
    p1name.move(380,930);
    p1name.setString( "player 1" );
    p1name.setFillColor(sf::Color::White);

    
    sf::Text p2name("", font2, 37);
    p2name.setStyle(sf::Text::Bold);
    p2name.move(695,930);
    p2name.setString( "player 2" );
    p2name.setFillColor(sf::Color::White);


    sf::RectangleShape deckTopTile(sf::Vector2f(size * 1.85, size * 1.85));
    deckTopTile.setPosition(155, 1052);
    deckTopTile.setOrigin((size * 1.85/2), (size * 1.85/2));
    deckTopTile.setTexture( &tileTextures[1] );
    
    sf::Texture pieceImg, pieceImg1, pieceImg2, pieceImg3, pieceImg4;
    if (    !pieceImg.loadFromFile(resourcePath()  + "p1.png")
        || !pieceImg1.loadFromFile(resourcePath()  + "blackpeice.jpg")
        || !pieceImg2.loadFromFile(resourcePath()  + "red.png")
        || !pieceImg3.loadFromFile(resourcePath()  + "blue.png")
        || !pieceImg4.loadFromFile(resourcePath()  + "croc.png"
        ))
    {
        exit(1);
    }
    
    
    pieceImg.setSmooth(true);
    double radius = (size - 10) / 6;
    sf::CircleShape circle(radius);
    circle.setTexture(&pieceImg1);
    //circle.setOutlineThickness(1);
    //circle.setOutlineColor( sf::Color(0, 0, 0, 255)  );
    
    
    pieceImg1.setSmooth(true);
    double radius1 = (size - 10) / 10;
    sf::CircleShape circle1(radius1);
    circle1.setTexture(&pieceImg1);
    //circle1.setFillColor(sf::Color(255, 255, 255, 2));
    //circle1.setFillColor( sf::Color::Transparent );

    pieceImg2.setSmooth(true);
    double radius2 = (size - 10) / 4;
    sf::CircleShape circle2(radius2);
    circle2.setTexture(&pieceImg2);
    
    pieceImg3.setSmooth(true);
    double radius3 = (size - 10) / 4;
    sf::CircleShape circle3(radius3);
    circle3.setTexture(&pieceImg3);
    circle2.setFillColor(sf::Color(255, 255, 255, 210));
    circle3.setFillColor(sf::Color(255, 255, 255, 210));

    double rr = (size - 10) / 2.5;
    sf::CircleShape circlep1(rr);
    circlep1.setTexture(&pieceImg2);
    
    sf::CircleShape circlep2(rr);
    circlep2.setTexture(&pieceImg3);
    circlep1.setFillColor(sf::Color(255, 255, 255, 210));
    circlep2.setFillColor(sf::Color(255, 255, 255, 210));

    
    pieceImg4.setSmooth(true);
    double radius4 = (size - 10) / 2.5;
    sf::CircleShape circle4(radius4);
    circle4.setTexture(&pieceImg4);
    circle4.setFillColor(sf::Color(255, 255, 255, 210));

    
    bool placingCard = true;
    bool placingMeeple = false;
    
    int r = 0;
    double resizeWidth = -1;
    double resizeHeight = -1;
    int cc = 0;
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
                return 0;
            }
            else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                window.close();
                return 0;
            }
            else if (event.type == sf::Event::Resized) {
                resizeWidth = event.size.width / 1000.0;
                resizeHeight = event.size.height / 800.0;
            }
        }
        
        sf::Vector2i localPosition = sf::Mouse::getPosition(window);
        
        int row = ((localPosition.y+offset) / resizeHeight) / int(size + 5);
        int col = ((localPosition.x+offset) / resizeWidth) / int(size + 5);
        
        double xx = fmod((((localPosition.x+offset) / resizeWidth) / int(size + 5)),1);
        double yy = fmod((((localPosition.y+offset) / resizeHeight) / int(size + 5)),1);

        if(xx < 0) {
            xx *= -1;
        }
        if(yy < 0) {
            yy *= -1;
        }
        
        
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && window.hasFocus()) {
            int zone = 0;
            if( (xx) < 0.33 && (yy) < 0.33) {
               // cout << "click in zone 1" << endl;
                zone = 1;
            }
            else if ( (xx) < 0.66 && (yy) < 0.33 ) {
              //  cout << "click in zone 2" << endl;
                zone = 2;
            }
            else if ( (xx) < 1.0 && (yy) < 0.33 ) {
              //  cout << "click in zone 3" << endl;
                zone = 3;
            }
            else if ( (xx) < 0.33 && (yy) < 0.66 ) {
              //  cout << "click in zone 4" << endl;
                zone = 4;
            }
            else if ( (xx) < 0.66 && (yy) < 0.66 ) {
              //  cout << "click in zone 5" << endl;
                zone = 5;
            }
            else if ( (xx) < 1.0 && (yy) < 0.66 ) {
              //  cout << "click in zone 6" << endl;
                zone = 6;
            }
            else if ( (xx) < 0.33 && (yy) < 1.0 ) {
             //   cout << "click in zone 7" << endl;
                zone = 7;
            }
            else if ( (xx) < 0.66 && (yy) < 1.0 ) {
              //  cout << "click in zone 8" << endl;
                zone = 8;
            }
            else if ( (xx) < 1.0 && (yy) < 1.0 ) {
              //  cout << "click in zone 9" << endl;
                zone = 9;
            }
            
              //cout << "click at x = " << abs(col)-5 << " y = " << -(abs(row)-5) << endl;
            if(abs(row) >= 0 && abs(col) >= 0 && abs(row) < ROWS && abs(col) < COLS && cc % 2 == 0) {  // for GUI, if user clicks on the board
                game->giveTurn(abs(row), abs(col));
                cc++;
               // cout << cc << endl;
            }
            else if(abs(row) >= 0 && abs(col) >= 0 && abs(row) < ROWS && abs(col) < COLS && cc % 2 == 1) {  // for GUI, if user clicks on the board
                game->giveTurn( zone );
                cc++;
               // cout << cc << endl;

            }
            else if(abs(row) >= 13 && abs(row) <= 15 && abs(col) >= 2 && abs(col) <= 4 ) {
               // cout << "ROTATE!!" << endl;
                game->rotateCard();                                                 // rotate current card
            }
        }
        
        //Input in;
        //Output  * out = new Output();
        game->giveCard( false );   // draw a card if the player needs
        
        // Clear screen
        window.clear( sf::Color(30, 30, 30) );
        window.draw(bg);
        window.draw(bg1);
        window.draw(wood);

        // Draw the string
        string score = int2Str( game->getDeck()->getSize() ) + " cards remaining";
        text.setString( score );
        window.draw(text2);
        window.draw(text);
        window.draw(text3);
        
        
        //string player1score = "player 1's score: " + int2Str(game->getScore( true ));
        string player1score = "score:  " + int2Str( game->getBoard()->getScore( true ) );

        text4.setString(player1score);
        window.draw(text4); //p1 sc
        
        
        //string player2score = "player 2's score: " + int2Str(game->getScore( false ));
        string player2score = "score: " + int2Str( game->getBoard()->getScore( false ) );
        text5.setString(player2score);
        window.draw(text5); //p2 sc
        
//        string player1meeps = "tigers:  " + int2Str(game->getMeeples( true ));
//        text4b.setString(player1meeps);
//        window.draw(text4b); //p1 sc
//        
       
        
//        
//        string player2meeps = "tigers: " + int2Str( game->getMeeples( false) );
//        text5b.setString(player2meeps);
//        window.draw(text5b); //p2 sc
//        
//        
        string turn_string;
        if ( game->getCurrTurn() ) {
            turn_string = "player 1's turn";
        }
        else {
            turn_string = "player 2's turn";
        }
        text6.setString( turn_string );
        window.draw(text6); //turn
        
        window.draw(p1name);
        window.draw(p2name);


        
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
            
                
                if( (i == game->getBoard()->getX() && j == game->getBoard()->getY()) && !(i == ROWS/2 && j == ROWS/2) &&  cc % 2 == 1 ) {
                
                    
                    //
                    cout << "CROCLOCS = " << game->getBoard()->getCrocLocs() << endl;
                    if( ((game->getBoard()->getCrocLocs() >> 1) & 1 ) == 1 ) {
                        circle.setPosition(j * (size + 1) + 10, i * (size + 1) + 10);
                        circle.setOrigin(radius/2, radius/2);
                        tiles[ game->getBoard()->getCard(i, j).getId() ] .setOrigin((size/2), (size/2));
                        window.draw(circle);
                    }
                    if( ((game->getBoard()->getCrocLocs() >> 2) & 1 ) == 1 ) {
                        circle.setPosition(j * (size + 1) + 30, i * (size + 1) + 10);
                        circle.setOrigin(radius/2, radius/2);
                        tiles[ game->getBoard()->getCard(i, j).getId() ] .setOrigin((size/2), (size/2));
                        window.draw(circle);
                        
                    }
                    if( ((game->getBoard()->getCrocLocs() >> 3) & 1 ) == 1 ) {
                        circle.setPosition(j * (size + 1) + 50, i * (size + 1) + 10);
                        circle.setOrigin(radius/2, radius/2);
                        tiles[ game->getBoard()->getCard(i, j).getId() ] .setOrigin((size/2), (size/2));
                        window.draw(circle);
                        
                    }
                    if( ((game->getBoard()->getCrocLocs() >> 4) & 1 ) == 1 ) {
                        circle.setPosition(j * (size + 1) + 10, i * (size + 1) + 30);
                        circle.setOrigin(radius/2, radius/2);
                        tiles[ game->getBoard()->getCard(i, j).getId() ] .setOrigin((size/2), (size/2));
                        window.draw(circle);
                        
                    }
                    if( ((game->getBoard()->getCrocLocs() >> 5) & 1 ) == 1 ) {
                        circle.setPosition(j * (size + 1) + 30, i * (size + 1) + 30);
                        circle.setOrigin(radius/2, radius/2);
                        tiles[ game->getBoard()->getCard(i, j).getId() ] .setOrigin((size/2), (size/2));
                        window.draw(circle);
                    }
                    if( ((game->getBoard()->getCrocLocs() >> 6) & 1 ) == 1 ) {
                        circle.setPosition(j * (size + 1) + 50, i * (size + 1) + 30);
                        circle.setOrigin(radius/2, radius/2);
                        tiles[ game->getBoard()->getCard(i, j).getId() ] .setOrigin((size/2), (size/2));
                        window.draw(circle);
                    }
                    if( ((game->getBoard()->getCrocLocs() >> 7) & 1 ) == 1 ) {
                        circle.setPosition(j * (size + 1) + 10, i * (size + 1) + 50);
                        circle.setOrigin(radius/2, radius/2);
                        tiles[ game->getBoard()->getCard(i, j).getId() ] .setOrigin((size/2), (size/2));
                        window.draw(circle);
                    }
                    if( ((game->getBoard()->getCrocLocs() >> 8) & 1 ) == 1 ) {
                        circle.setPosition(j * (size + 1) + 30, i * (size + 1) + 50);
                        circle.setOrigin(radius/2, radius/2);
                        tiles[ game->getBoard()->getCard(i, j).getId() ] .setOrigin((size/2), (size/2));
                        window.draw(circle);
                    }
                    if( ((game->getBoard()->getCrocLocs() >> 9) & 1 ) == 1 ) {
                        circle.setPosition(j * (size + 1) + 50, i * (size + 1) + 50);
                        circle.setOrigin(radius/2, radius/2);
                        tiles[ game->getBoard()->getCard(i, j).getId() ] .setOrigin((size/2), (size/2));
                        window.draw(circle);
                    }
                    
                    //
                    
                    
                     if( ((game->getBoard()->getMeepleLocs() >> 1) & 1 ) == 1 ) {
                         circle1.setPosition(j * (size + 1) + 10, i * (size + 1) + 10);
                         circle1.setOrigin(radius/2, radius/2);
                         tiles[ game->getBoard()->getCard(i, j).getId() ] .setOrigin((size/2), (size/2));
                         window.draw(circle1);
                     }
                     if( ((game->getBoard()->getMeepleLocs() >> 2) & 1 ) == 1 ) {
                         circle1.setPosition(j * (size + 1) + 30, i * (size + 1) + 10);
                         circle1.setOrigin(radius/2, radius/2);
                         tiles[ game->getBoard()->getCard(i, j).getId() ] .setOrigin((size/2), (size/2));
                         window.draw(circle1);
                         
                     }
                    if( ((game->getBoard()->getMeepleLocs() >> 3) & 1 ) == 1 ) {
                        circle1.setPosition(j * (size + 1) + 50, i * (size + 1) + 10);
                        circle1.setOrigin(radius/2, radius/2);
                        tiles[ game->getBoard()->getCard(i, j).getId() ] .setOrigin((size/2), (size/2));
                        window.draw(circle1);
                        
                    }
                    if( ((game->getBoard()->getMeepleLocs() >> 4) & 1 ) == 1 ) {
                        circle1.setPosition(j * (size + 1) + 10, i * (size + 1) + 30);
                        circle1.setOrigin(radius/2, radius/2);
                        tiles[ game->getBoard()->getCard(i, j).getId() ] .setOrigin((size/2), (size/2));
                        window.draw(circle1);
                        
                    }
                    if( ((game->getBoard()->getMeepleLocs() >> 5) & 1 ) == 1 ) {
                        circle1.setPosition(j * (size + 1) + 30, i * (size + 1) + 30);
                        circle1.setOrigin(radius/2, radius/2);
                        tiles[ game->getBoard()->getCard(i, j).getId() ] .setOrigin((size/2), (size/2));
                        window.draw(circle1);
                    }
                    if( ((game->getBoard()->getMeepleLocs() >> 6) & 1 ) == 1 ) {
                        circle1.setPosition(j * (size + 1) + 50, i * (size + 1) + 30);
                        circle1.setOrigin(radius/2, radius/2);
                        tiles[ game->getBoard()->getCard(i, j).getId() ] .setOrigin((size/2), (size/2));
                        window.draw(circle1);
                    }
                    if( ((game->getBoard()->getMeepleLocs() >> 7) & 1 ) == 1 ) {
                        circle1.setPosition(j * (size + 1) + 10, i * (size + 1) + 50);
                        circle1.setOrigin(radius/2, radius/2);
                        tiles[ game->getBoard()->getCard(i, j).getId() ] .setOrigin((size/2), (size/2));
                        window.draw(circle1);
                    }
                    if( ((game->getBoard()->getMeepleLocs() >> 8) & 1 ) == 1 ) {
                        circle1.setPosition(j * (size + 1) + 30, i * (size + 1) + 50);
                        circle1.setOrigin(radius/2, radius/2);
                        tiles[ game->getBoard()->getCard(i, j).getId() ] .setOrigin((size/2), (size/2));
                        window.draw(circle1);
                    }
                    if( ((game->getBoard()->getMeepleLocs() >> 9) & 1 ) == 1 ) {
                        circle1.setPosition(j * (size + 1) + 50, i * (size + 1) + 50);
                        circle1.setOrigin(radius/2, radius/2);
                        tiles[ game->getBoard()->getCard(i, j).getId() ] .setOrigin((size/2), (size/2));
                        window.draw(circle1);
                    }
                    
                   
                    
                    
                }
                
                if( game->getBoard()->checkPossibleMove(i, j) &&  cc % 2 != 1 ) {                              // center row
                    circle.setPosition(j * (size + 1) + 30, i * (size + 1) + 30);
                    circle.setOrigin(radius/2, radius/2);
                    window.draw(circle);
                }
                
                if( game->getBoard()->getCard(i, j).getId() > -1 && game->getBoard()->getOwner(i, j) == 1 ) {
                    //cout << "tigerlocs = " << game->getBoard()->getTigerLocs(i, j) << endl;
                    if( ((game->getBoard()->getTigerLocs(i, j) >> 1) & 1 ) == 1 ) {
                        circle2.setPosition(j * (size + 1) + 0, i * (size + 1) + 0);
                        circle2.setOrigin(radius/2, radius/2);
                        window.draw(circle2);
                    }
                    if( ((game->getBoard()->getTigerLocs(i, j) >> 2) & 1 ) == 1 ) {
                        circle2.setPosition(j * (size + 1) + 20, i * (size + 1) + 0);
                        circle2.setOrigin(radius/2, radius/2);
                        window.draw(circle2);
                    }
                    if( ((game->getBoard()->getTigerLocs(i, j) >> 3) & 1 ) == 1 ) {
                        circle2.setPosition(j * (size + 1) + 40, i * (size + 1) + 0);
                        circle2.setOrigin(radius/2, radius/2);
                        window.draw(circle2);
                    }
                    if( ((game->getBoard()->getTigerLocs(i, j) >> 4) & 1 ) == 1 ) {
                        circle2.setPosition(j * (size + 1) + 0, i * (size + 1) + 20);
                        circle2.setOrigin(radius/2, radius/2);
                        window.draw(circle2);
                    }
                    if( ((game->getBoard()->getTigerLocs(i, j) >> 5) & 1 ) == 1 ) {
                        circle2.setPosition(j * (size + 1) + 20, i * (size + 1) + 20);
                        circle2.setOrigin(radius/2, radius/2);
                        window.draw(circle2);
                    }
                    if( ((game->getBoard()->getTigerLocs(i, j) >> 6) & 1 ) == 1 ) {
                        circle2.setPosition(j * (size + 1) + 40, i * (size + 1) + 20);
                        circle2.setOrigin(radius/2, radius/2);
                        window.draw(circle2);
                    }
                    if( ((game->getBoard()->getTigerLocs(i, j) >> 7) & 1 ) == 1 ) {
                        circle2.setPosition(j * (size + 1) + 0, i * (size + 1) + 40);
                        circle2.setOrigin(radius/2, radius/2);
                        window.draw(circle2);
                    }
                    if( ((game->getBoard()->getTigerLocs(i, j) >> 8) & 1 ) == 1 ) {
                        circle2.setPosition(j * (size + 1) + 20, i * (size + 1) + 40);
                        circle2.setOrigin(radius/2, radius/2);
                        window.draw(circle2);
                    }
                    if( ((game->getBoard()->getTigerLocs(i, j) >> 9) & 1 ) == 1 ) {
                        circle2.setPosition(j * (size + 1) + 40, i * (size + 1) + 40);
                        circle2.setOrigin(radius/2, radius/2);
                        window.draw(circle2);
                    }
                    
                }
                else if( game->getBoard()->getCard(i, j).getId() > -1 && game->getBoard()->getOwner(i, j) == 2 ) {
                    //cout << "tigerlocs = " << game->getBoard()->getTigerLocs(i, j) << endl;
                    if( ((game->getBoard()->getTigerLocs(i, j) >> 1) & 1 ) == 1 ) {
                        circle3.setPosition(j * (size + 1) + 5, i * (size + 1) + 5);
                        circle3.setOrigin(radius/2, radius/2);
                        window.draw(circle3);
                    }
                    if( ((game->getBoard()->getTigerLocs(i, j) >> 2) & 1 ) == 1 ) {
                        circle3.setPosition(j * (size + 1) + 25, i * (size + 1) + 5);
                        circle3.setOrigin(radius/2, radius/2);
                        window.draw(circle3);
                    }
                    if( ((game->getBoard()->getTigerLocs(i, j) >> 3) & 1 ) == 1 ) {
                        circle3.setPosition(j * (size + 1) + 45, i * (size + 1) + 5);
                        circle3.setOrigin(radius/2, radius/2);
                        window.draw(circle3);
                    }
                    if( ((game->getBoard()->getTigerLocs(i, j) >> 4) & 1 ) == 1 ) {
                        circle3.setPosition(j * (size + 1) + 5, i * (size + 1) + 25);
                        circle3.setOrigin(radius/2, radius/2);
                        window.draw(circle3);
                    }
                    if( ((game->getBoard()->getTigerLocs(i, j) >> 5) & 1 ) == 1 ) {
                        circle3.setPosition(j * (size + 1) + 25, i * (size + 1) + 25);
                        circle3.setOrigin(radius/2, radius/2);
                        window.draw(circle3);
                    }
                    if( ((game->getBoard()->getTigerLocs(i, j) >> 6) & 1 ) == 1 ) {
                        circle3.setPosition(j * (size + 1) + 45, i * (size + 1) + 25);
                        circle3.setOrigin(radius/2, radius/2);
                        window.draw(circle3);
                    }
                    if( ((game->getBoard()->getTigerLocs(i, j) >> 7) & 1 ) == 1 ) {
                        circle3.setPosition(j * (size + 1) + 5, i * (size + 1) + 45);
                        circle3.setOrigin(radius/2, radius/2);
                        window.draw(circle3);
                    }
                    if( ((game->getBoard()->getTigerLocs(i, j) >> 8) & 1 ) == 1 ) {
                        circle3.setPosition(j * (size + 1) + 25, i * (size + 1) + 45);
                        circle3.setOrigin(radius/2, radius/2);
                        window.draw(circle3);
                    }
                    if( ((game->getBoard()->getTigerLocs(i, j) >> 9) & 1 ) == 1 ) {
                        circle3.setPosition(j * (size + 1) + 45, i * (size + 1) + 45);
                        circle3.setOrigin(radius/2, radius/2);
                        window.draw(circle3);
                    }
                    
                }
                if( game->getBoard()->getCard(i, j).getId() > -1) {
                    //cout << "tigerlocs = " << game->getBoard()->getTigerLocs(i, j) << endl;
                    if( ((game->getBoard()->getCrocoLocs(i, j) >> 1) & 1 ) == 1 ) {
                        circle4.setPosition(j * (size + 1) + 5, i * (size + 1) + 5);
                        circle4.setOrigin(radius/2, radius/2);
                        window.draw(circle4);
                    }
                    if( ((game->getBoard()->getCrocoLocs(i, j) >> 2) & 1 ) == 1 ) {
                        circle4.setPosition(j * (size + 1) + 25, i * (size + 1) + 5);
                        circle4.setOrigin(radius/2, radius/2);
                        window.draw(circle4);
                    }
                    if( ((game->getBoard()->getCrocoLocs(i, j) >> 3) & 1 ) == 1 ) {
                        circle4.setPosition(j * (size + 1) + 45, i * (size + 1) + 5);
                        circle4.setOrigin(radius/2, radius/2);
                        window.draw(circle4);
                    }
                    if( ((game->getBoard()->getCrocoLocs(i, j) >> 4) & 1 ) == 1 ) {
                        circle4.setPosition(j * (size + 1) + 5, i * (size + 1) + 25);
                        circle4.setOrigin(radius/2, radius/2);
                        window.draw(circle4);
                    }
                    if( ((game->getBoard()->getCrocoLocs(i, j) >> 5) & 1 ) == 1 ) {
                        circle4.setPosition(j * (size + 1) + 25, i * (size + 1) + 25);
                        circle4.setOrigin(radius/2, radius/2);
                        window.draw(circle4);
                    }
                    if( ((game->getBoard()->getCrocoLocs(i, j) >> 6) & 1 ) == 1 ) {
                        circle4.setPosition(j * (size + 1) + 45, i * (size + 1) + 25);
                        circle4.setOrigin(radius/2, radius/2);
                        window.draw(circle4);
                    }
                    if( ((game->getBoard()->getCrocoLocs(i, j) >> 7) & 1 ) == 1 ) {
                        circle4.setPosition(j * (size + 1) + 5, i * (size + 1) + 45);
                        circle4.setOrigin(radius/2, radius/2);
                        window.draw(circle4);
                    }
                    if( ((game->getBoard()->getCrocoLocs(i, j) >> 8) & 1 ) == 1 ) {
                        circle4.setPosition(j * (size + 1) + 25, i * (size + 1) + 45);
                        circle4.setOrigin(radius/2, radius/2);
                        window.draw(circle4);
                    }
                    if( ((game->getBoard()->getCrocoLocs(i, j) >> 9) & 1 ) == 1 ) {
                        circle4.setPosition(j * (size + 1) + 45, i * (size + 1) + 45);
                        circle4.setOrigin(radius/2, radius/2);
                        window.draw(circle4);
                    }
                    
                }


            }
        }
        
        int t = game->getMeeples( true );
        int tt = game->getMeeples( false );
        for(int i = 0; i < t ; i++ ) {
            circlep1.setPosition(380 + i*30,990);
            circlep1.setOrigin(radius/2, radius/2);
             window.draw(circlep1);
        }
        for(int i = 0; i < tt ; i++ ) {
            circlep2.setPosition(695 + i*30,990);
            circlep2.setOrigin(radius/2, radius/2);
            window.draw(circlep2);
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
