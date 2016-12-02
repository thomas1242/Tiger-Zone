CC = g++
CFLAGS = -std=c++11
OBJECTS = board.o card.o deck.o game.o player.o jungle.o edge.o input.o output.o trail.o lake.o main.o

all: $(OBJECTS)
	$(CC) $(CFLAGS) -o client $(OBJECTS)

board.o: board.cpp
card.o: card.cpp
deck.o: deck.cpp
game.o: game.cpp
player.o: player.cpp
edge.o: edge.cpp
input.o: input.cpp
trail.o: trail.cpp
jungle.o: jungle.cpp
lake.o: lake.cpp
output.o: output.cpp
main.o: main.cpp

clean:
	rm client $(OBJECTS) 
