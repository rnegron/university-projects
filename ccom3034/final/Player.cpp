/*
  Ricardo López
  Raúl Negrón
*/

#include <iostream>
#include "Player.h"

using namespace std ;

Player::Player(Deck* D) {

  playerDeck = D;
  cardAmount = 26;
}



void Player::getCards() {

  for (int i = 1; i < (*playerDeck).size(); ++i)
    cout << (*playerDeck).asCard(i) << " ";
    cout << endl;

}

int Player::checkAmount() {
  return cardAmount;
}
