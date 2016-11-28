CC = g++
CFLAGS = -Wall -std=c++11
OBJECTS = board.o card.o deck.o game.o player.o edge.o main.o trail.o lake.o jungle.o

all: $(OBJECTS)
	$(CC) $(CFLAGS) -o tiger $(OBJECTS)

board.o: board.cpp
card.o: card.cpp
deck.o: deck.cpp
game.o: game.cpp
player.o: player.cpp
trail.o: trail.cpp
jungle.o: jungle.cpp
lake.o: lake.cpp
edge.o: edge.cpp
output.o: output.cpp
input.o: input.cpp

main.o: main.cpp

clean:
	rm tiger $(OBJECTS) 
