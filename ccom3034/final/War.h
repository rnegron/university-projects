/*
  Raúl Negrón Otero
  801-13-4680
  CCOM3034-f14

  This file contains the specifications for the War class.

*/


// Preprocessor directives
#ifndef WAR_H
#define WAR_H

#include <deque>
#include <vector>
#include "Deck.h"


class War {

public:

  // Member functions
  War();
  string assignVal(string);
  void applyTieback(string);
  void duel();
  void tie();
  void cardCount();
  void start();
  void stop(string s);

  // Member variables
  vector<int> tieback;            // tieback will help with tiebreakers
  int turns, J1val, J2val;        // turns is a counter, J1val and J2val are
                                  // temporary ints which hold the card value
  std::deque<int> J1Deck, J2Deck; // J1Deck and J2Deck are each player decks
  Deck mainDeck;                  // mainDeck is where the randomization
                                  // occurs and is a Deck variable

};

#endif
