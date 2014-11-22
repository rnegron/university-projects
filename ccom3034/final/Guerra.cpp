/*
  Ricardo López
  Raúl Negrón
*/

#include <vector>
#include "Guerra.h"
#include "Deck.h"
#include "Player.h"

void Guerra::start(Player &P1, Player &P2) {

  cout << endl;
  // while (P1.checkAmount() > 0 && P2.checkAmount() > 0) {
  for (int i = 1; i <= P1.cardAmount; ++i) {
    cout << P1.playerDeck->asCard(i) << " vs. " << P2.playerDeck->asCard(i);
    cout << endl;
  }

}
