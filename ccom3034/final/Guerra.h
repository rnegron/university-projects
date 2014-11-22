/*
  Ricardo López
  Raúl Negrón
*/

#ifndef GUERRA_H
#define GUERRA_H

#include <iostream>
#include "Player.h"
#include "Deck.h"
using namespace std;

class Guerra {

public:
  void start(Player&, Player&);
  void stop(); // Should maybe reset game state (re-shuffle)
};

#endif
