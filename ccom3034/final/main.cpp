/* 
 * File:   Main.cpp
 * Author: R. Arce-Nazario
 * 
 * Created on March 5, 2012, 10:50 PM
 * 
 * Client for testing the Deck class.
 */

#include <iostream>
#include "Deck.h"

int main() {

    vector <int> V;
    
    srand(time(0));

    Deck D;

    cout << "Here's your deck: ";
    for (int i=1; i<D.size(); ++i) 
        cout << D.asCard(i) << " ";
    cout << endl;

    D.shuffle();
    cout << "After shuffle: ";
    for (int i=1; i<D.size(); ++i) 
        cout << D.asCard(i) << " ";
    cout << endl;
    
    return 0;
}
