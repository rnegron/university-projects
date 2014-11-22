/*
  Ricardo López
  Raúl Negrón
*/

#ifndef PLAYER_H
#define PLAYER_H

#include "Deck.h"

using namespace std;

class Player {

public:

  // Member variables
  int cardAmount;
  Deck* playerDeck;

  // Constructor
  Player(Deck*);

  // Outputs cards in the player's deck
  void getCards();

  // Returns the amount of cards in the player's deck
  int checkAmount();


};


#endif
