/*
 * File:   Deck.cpp
 * Author: R. Arce-Nazario
 *
 * Created on March 5, 2012, 10:50 PM
 *
 * Implementation for the functions of the Deck class.
 */

#include "Deck.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>

// random generator function (for random_shuffle)
int rng (int i) { return rand() % i; }

Deck::Deck() {
    // initially just fill the deck with 0 through 25
    for (int i = 0; i < 51; ++i) push_back(i);
}

void Deck::shuffle() {

    // luckily the algorithm library includes a simple way of
    // randomly permuting the contents of the vector
    random_shuffle(begin(), end(), rng);
}

string Deck::asCard(int pos) {
    if (pos < 0 || pos > 51 ) cerr << "BAD";

    stringstream ss;

    // determine the number of the card
    switch ((*this)[pos] % 13) {
        case 0: ss << "A";
            break;
        case 10: ss << "J";
            break;
        case 11: ss << "Q";
            break;
        case 12: ss << "K";
            break;
        default: ss << (*this)[pos] % 13;
    }

    string st = ss.str();

    // determine the card's suit
    switch ((*this)[pos] / 13) {
        case 0:
            st += club;
            break;
        case 1:
            st += diamond;
            break;
        case 2:
            st += heart;
            break;
        case 3:
            st += spade;
            break;
    }
    return st;
}
