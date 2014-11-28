/*
  Raúl Negrón Otero
  801-13-4680
  CCOM3034-f14

  War.cpp

  This file contains the implementation of the
  War class as specified in War.h

  Also, it contains the main function.

*/

// Preprocessor directives
#include <iostream>
#include <deque>
#include <cstdlib>
#include <ctime>
#include <string>

#include "War.h"
#include "Deck.h"


// Constructor
War::War() {
  turns = 1;
}


// assignVal:
//  input: string in
//  output:: a string with the corresponding
//  numeric representation of in
string War::assignVal(string in) {

  if (in == "A") return "0";
  else if (in == "J") return "11";
  else if (in == "Q") return "12";
  else if (in == "K") return "13";
  return in;

}

void War::cardCount() {
  cout << "Total carta " << J1Deck.size()
  << " / " << J2Deck.size() << "." << endl;

}

// applyTieback:
//  input a string s
//  output: function is void
void War::applyTieback(string s) {

  // J1 won the tiebreaker
  if (s == "J1") {

    // while the tieback vector has elements
    while (!tieback.empty()) {

      // Assign the elements to J1
      J1Deck.push_front(J1Deck.back());
      J1Deck.push_front(J2Deck.back());
      J1Deck.pop_back();
      J2Deck.pop_back();

      tieback.pop_back();
    }

  // J2 won the tiebreaker
  } else {

    // while the tieback vector has elements
    while (!tieback.empty()) {

      // Assign the elements to J2
      J2Deck.push_front(J2Deck.back());
      J2Deck.push_front(J1Deck.back());
      J1Deck.pop_back();
      J2Deck.pop_back();

      tieback.pop_back();
    }
  }
}

// duel:
//  input: none
//  output: function is void
void War::duel() {

  // J1val and J2val correspond to the value of a card
  // stoi() is called on the result of assignVal on the first 2 characters
  // of the card corresponding to the back of each player's deck

  J1val = stoi( assignVal(mainDeck.asCard(J1Deck.back()).substr(0, 1)) );
  J2val = stoi( assignVal(mainDeck.asCard(J2Deck.back()).substr(0, 1)) );

  // Output turn counter
  cout << turns << ".\t" << "J1: " << mainDeck.asCard(J1Deck.back())
       << "\t J2: " << mainDeck.asCard(J2Deck.back());

  // J1 has a better hand
  if (J1val > J2val) {

    // J1 wins the card played and J2's card
    J1Deck.push_front(J2Deck.back());
    J1Deck.push_front(J1Deck.back());
    J1Deck.pop_back();
    J2Deck.pop_back();

    cout << "\t\tGana J1. Total cartas: " << J1Deck.size()
    << " / " << J2Deck.size() << endl;

  // J2 has a better hand
  } else if (J1val < J2val) {

    // J2 wins the card played and J1's card
    J2Deck.push_front(J1Deck.back());
    J2Deck.push_front(J2Deck.back());
    J1Deck.pop_back();
    J2Deck.pop_back();

    cout << "\t\tGana J2. Total cartas: " << J1Deck.size()
    << " / " << J2Deck.size() << endl;


  // J1 and J2 drew the same value
  } else {

    // The value was 'A' == 0
    if (J1val == 0) {
      cout << "\t\tEmpate! Pero no se lanzarán barajas." << endl;
      J1Deck.pop_back();
      J2Deck.pop_back();
    }

    // The value was 1
    else if (J1val == 1) {
      cout << "\t\tEmpate! Se lanzará 1 baraja." << endl;
      J1Deck.pop_back();
      J2Deck.pop_back();
      duel();

    // The value was greater than 1
    } else {
      cout << "\t\tEmpate! Se lanzarán " << J1val << " barajas." << endl;

      // J1 cannot draw sufficient cards
      if (J1Deck.size() - J1val <= 0 || J1Deck.size() - J1val > 52) {
        stop("J2");
      }

      // J2 cannot draw sufficient cards
      else if (J2Deck.size() - J1val <= 0 || J2Deck.size() - J1val > 52) {
        stop("J1");
      }

      // Go to a tiebreaker
      else { tie(); }
    }
  }

  return;
}

// tie:
//  input: none
//  output: function is void
void War::tie() {

  // For loop which executes (tiebreaker - 1) times
  for (int i = 1; i < J1val; i++) {

    // Output all except tiebreaker card
    cout << "\t" << "J1: "
    << mainDeck.asCard(J1Deck[J1Deck.size() - 1 - tieback.size()])
    << "\t J2: "
    << mainDeck.asCard(J2Deck[J2Deck.size() - 1 - tieback.size()]) << endl;

    // push into tieback vector
    tieback.push_back(0);
  }

  // Output tiebreaker card
  cout << "\t" << "J1: "
  << mainDeck.asCard(J1Deck[J1Deck.size() - 1 - tieback.size()])
  << "\t J2: "
  << mainDeck.asCard(J2Deck[J2Deck.size() - 1 - tieback.size()]);

  // J1val and J2val correspond to the value of a card
  // stoi() is called on the result of assignVal on the first 2 characters
  // of the card corresponding to the back of each player's deck

  J1val = stoi( assignVal(mainDeck.asCard(J1Deck[J1Deck.size()  - 1 - tieback.size()]).substr(0, 1)) );
  J2val = stoi( assignVal(mainDeck.asCard(J2Deck[J2Deck.size()  - 1 - tieback.size()]).substr(0, 1)) );

  // Consier the tiebreaker card
  tieback.push_back(0);

  // J1 has a better hand
  if (J1val > J2val) {

    // Run the tieback function
    applyTieback("J1");

    // Output result
    cout << "\t\tGana J1. Total cartas: " << J1Deck.size()
    << " / " << J2Deck.size() << endl;

    return;

  // J2 has a better hand
  } else if (J1val < J2val) {

    // Run the tieback function
    applyTieback("J2");

    // Output result
    cout << "\t\tGana J2. Total cartas: " << J1Deck.size()
    << " / " << J2Deck.size() << endl;

    return;

  // J1 and J2 drew the same value
  } else {

    // The value was 'A' == 0
    if (J1val == 0) {
      cout << "\t\tEmpate! Pero no se lanzarán barajas." << endl;
      J1Deck.pop_back();
      J2Deck.pop_back();

    // The value was 1
    } else if (J1val == 1) {
        cout << "\t\tEmpate! Se lanzará 1 baraja." << endl;
        J1Deck.pop_back();
        J2Deck.pop_back();
        duel();

    // The value was greater than 1
    } else {
      cout << "\t\tEmpate! Se lanzarán " << J1val << " barajas." << endl;

      // J1 cannot draw sufficient cards
      if (J1Deck.size() - J1val <= 0 || J1Deck.size() - J1val > 52) {
        stop("J2");
      }

      // J2 cannot draw sufficient cards
      else if (J2Deck.size() - J1val <= 0 || J1Deck.size() - J1val > 52) {
        stop("J1");
      }

      // Go to a recursive tiebreaker
      else { tie(); }
    }
  }

  return;
}


// start:
//  input: none
//  output: function is void
void War::start() {

  cout << "Comienza juego. ";

  cout << "Barajando. ";

  // Shuffle the main deck
  mainDeck.shuffle();

  // Assign half the deck to each player
  for (int i = 0; i < 26; ++i) {
    J1Deck.push_back(mainDeck[i]);
    J2Deck.push_back(mainDeck[i + 26]);
  }

  // Just in case
  tieback.clear();

  // Output turns
  cardCount();

  // Game state
  // While neither deck is empty
  while (J1Deck.size() > 0 && J2Deck.size() > 0) {

    // Compare cards and increase turn count
    duel();
    turns++;
  }

  // If J1Deck is empty, J2 won
  if (J1Deck.size() == 0) {
    cout << "Ganó J2 en " << turns - 1 << " turnos." << endl;
  }

  // Else, J2Deck is empty so J1 won
  else {
    cout << "Ganó J1 en " << turns - 1 << " turnos." << endl;
  }

  return;

}

// stop:
//  input: string
//  output: function is void

// This function is called when winning
// parameters are detected and outputs
// results before exiting the program
void War::stop(string s) {

  if (s == "J2") {
    cout << "Ganó J2 en " << turns << " turnos." << endl;
  }

  else {
    cout << "Ganó J1 en " << turns << " turnos." << endl;
  }

  std::exit(0);

}


int main() {

  // Seed the random number generator
  srand(time(0));

  // Create a War instance
  War game;

  // Start the War card game
  game.start();

  return 0;
}
