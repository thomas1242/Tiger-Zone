CC = g++
CFLAGS = -Wall
OBJECTS = board.o card.o deck.o game.o player.o main.o moves.o coords.o

all: $(OBJECTS)
	$(CC) $(CFLAGS) -o tiger $(OBJECTS)

board.o: board.cpp
card.o: card.cpp
deck.o: deck.cpp
gamo.o: game.cpp
player.o: player.cpp
main.o: main.cpp
moves.o: moves.cpp
coords.o: coords.cpp

clean:
	rm tiger $(OBJECTS) 
