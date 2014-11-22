/*
  Ricardo López
  Raúl Negrón
*/

#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "Deck.h"
#include "Player.h"
#include "Guerra.h"

int main() {

    srand(time(NULL));
    
    // Create Deck instances
    Deck* D1 = new Deck;
    D1->shuffle();
    Deck* D2 = new Deck;
    D2->shuffle();

    // Create Player instances
    Player P1(D1);
    Player P2(D2);

    // Start Debug
    cout << "\nP1 Deck: ";
    P1.getCards();

    cout << "\nP2 Deck: ";
    P2.getCards();
    // End Debug

    // Create game state and start game
    Guerra game;
    game.start(P1, P2);


    // Memory management
    delete D1;
    delete D2;

    return 0;
}
