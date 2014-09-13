/*
	Raúl Negrón 
	#801-13-4680

	fracClient.cpp

*/

#include <iostream>
#include "frac.h"

using namespace std;

int main() {
	
	Fraction myFrac(1, 2);
	Fraction testFrac(1, 3);

	myFrac.print();


	// Add
	Fraction addedFrac = myFrac.add(testFrac);
	addedFrac.print();

	// Sub
	Fraction subtractedFrac = myFrac.sub(testFrac);
	subtractedFrac.print();


	// Mul
	Fraction mulFrac = myFrac.mul(testFrac);
	mulFrac.print();

	// Div
	Fraction divFrac = myFrac.div(testFrac);
	divFrac.print();

	// GT
	cout << endl << myFrac.gt(testFrac) << endl;

	 // Reduce
	 Fraction reducedFrac = myFrac.reduce();
	 reducedFrac.print();

	cout << endl ;
	return 0;
}