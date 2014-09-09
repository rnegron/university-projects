/*
	Raúl Negrón
	#801-13-4680

	frac.cpp

	This is the implementation of the Fraction class
	as specified in the frac.h file.

*/

#include <iostream>
using namespace std;
#include "frac.h"
#include <cassert>

// Default constructor
Fraction::Fraction() { 

	num = 1;
	denom = 1;
}

// Overloaded constructor
//	Arguments: Two ints to set as denom and num
Fraction::Fraction(int n, int d) {

	num = n;
	denom = d;

	assert(denom != 0);
}

// Function setNum
// 	Arguments: int n
// 	Sets num equal to n
void Fraction::setNum(int n) {

	num = n;
}

// Function setDenom
// 	Arguments: int n
//	Sets denom equal to n
void Fraction::setDenom(int n) {

	denom = n;

	assert(denom != 0);
}

// Function getNum
//	Returns num
int Fraction::getNum() const {
	return num;
}

// Function getDenom
// 	Returns denom
int Fraction::getDenom() const {
	return denom;
}

// Function print
//	Prints the num over the denom to the console
void Fraction::print() {
	cout << getNum() <<  "/" << getDenom() << endl ;
}

// Function add
//	Without modifying the calling Fraction object, 
//	adds two Fractions and returns the resulting
// 	Fraction object.
Fraction Fraction::add(const Fraction& F) const {

	Fraction localFrac;
	localFrac.setDenom(getDenom() * F.getDenom());
	localFrac.setNum( (getNum() * F.getDenom()) + (F.getNum() * getDenom()) );

	return localFrac;

}

// Function sub
// 	Withou modifying the calling Fraction object,
//	subtracts two Fractions and returns the resulting
//	Fraction object. The subtraction is done by negative
//	addition.
Fraction Fraction::sub(const Fraction& F) const {

	Fraction negFrac = F;
	negFrac.setNum(negFrac.getNum() * -1);

	Fraction localFrac = add(negFrac);

	return localFrac;
}

// Function mul
//	Without modifying the calling Fraction object, 
// 	multiplies two Fractions and returns the resulting
// 	Fraction object.
Fraction Fraction::mul(const Fraction& F) const {

	Fraction localFrac;

	localFrac.setNum(getNum() * F.getNum());
	localFrac.setDenom(getDenom() * F.getDenom());

	return localFrac;
}

// Function div
//	Without modifying the calling Fraction object, 
//	divides two Fractions and returns the resulting
//	Fraction object. Division is done by inverse
// 	multiplication.
Fraction Fraction::div(const Fraction& F) const {

	Fraction localFrac;
	Fraction recipFrac;

	recipFrac.setNum(F.getDenom());
	recipFrac.setDenom(F.getNum());

	localFrac = mul(recipFrac);

	return localFrac;

}

//	Function gt
//	Returns true if the calling Fraction is larger 
// 	than the pass-by-reference Fraction, false otherwise.
bool Fraction::gt(const Fraction& F) {

	double F1 = getNum() / getDenom();
	double F2 = F.getNum() / F.getDenom();

	if (F1 > F2) return true;
	else return false;

}

//	Function reduce
//	Reduces the calling Fraction object to its lowest
//	possible form. This is done by checking if the denominator
// 	is a common divisor of both the current denominator
//	and the numerator. If not, we subtract 1 from the denominator
//	and check again, until the denominator is 2. 
Fraction Fraction::reduce() {

	Fraction localFrac;

	localFrac.setNum(getNum());
	localFrac.setDenom(getDenom());


	for (int denomC = localFrac.getDenom(); denomC > 1; --denomC) {
		if (localFrac.getNum() % denomC == 0 && localFrac.getDenom() % denomC == 0) {
			localFrac.setNum(localFrac.getNum() / denomC);
			localFrac.setDenom(localFrac.getDenom() / denomC);
		}
	}

	return localFrac;

}
