CC = g++

CFLAGS = -g -Wall -lsfml-graphics -lsfml-window -lsfml-system

SOURCES = src/*.cpp

all:
	@$(CC) $(CFLAGS) $(SOURCES) -o Quoridor -I include/

run: 
	@./Quoridor

clean:
	rm -rf *.o Quoridor
