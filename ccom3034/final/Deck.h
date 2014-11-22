/*
 * File:   Deck.h
 * Author: R. Arce-Nazario
 *
 * Created on March 5, 2012, 10:50 PM
 *
 * Declaration of class Deck.
 */

#ifndef DECK_H
#define	DECK_H
#include <vector>
using namespace std;

// Deck is a child class of vector<int>, so it
// will inherit all its cool functions.
class Deck : public vector<int> {
public:
    // Constructor
    Deck();

    // Shuffles the cards
    void shuffle();

    // Returns the card at position as a number,suit.
    string asCard(int pos);
};


// Some string definitions for the suits
const char heart[]   = "\u2665";
const char spade[]   = "\u2660";
const char diamond[] = "\u2666";
const char club[]    = "\u2663";


#endif	/* DECK_H */
