CC = g++
CFLAGS = -Wall
CLIENT_OBJECTS = client.o
SERVER_OBJECTS = server.o

client: $(CLIENT_OBJECTS)
	$(CC) $(CFLAGS) -o client $(CLIENT_OBJECTS)

server: $(SERVER_OBJECTS)
	$(CC) $(CFLAGS) -o server $(SERVER_OBJECTS)


client.o: client.cpp
server.o: server.cpp

clean:
	rm client server $(CLIENT_OBJECTS) $(SERVER_OBJECTS) 
