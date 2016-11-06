#include "main.h"
#include "gui.h"

//Put all SFML functions here. Let's keep main clean and not dependent on gui.

/*Main as it stood:

    for (int i = 1; i < 25; i++) {      // used when drawing tiles on the board
        sf::RectangleShape tile(sf::Vector2f(size, size));
        tile.setTexture( &tileTextures[ i ] );
        tiles[i] = tile;
    }


    sf::RenderWindow window(sf::VideoMode(1000, 1200), "SFML window");    // create the main window
    window.setFramerateLimit(10);

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

    for (int i = 1; i < 25; i++) {      // used when drawing tiles on the board
        sf::RectangleShape tile(sf::Vector2f(size, size));
        tile.setTexture( &tileTextures[ i ] );
        tiles[i] = tile;
    }
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