all: guerra

guerra: main.o Deck.o Player.o Guerra.o
	g++ main.o Deck.o Player.o Guerra.o -o guerra

main.o: main.cpp
	g++ -c main.cpp

Deck.o:
	g++ -c Deck.cpp

Player.o:
	g++ -c Player.cpp

Guerra.o:
	g++ -c Guerra.cpp

clean:
	rm -rf *.o guerra
