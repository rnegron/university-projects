/*
	Raúl Negrón
	#801-13-4680

	arrayOfFracs.h

	This is the specifications for the ArrayOfFractions class.

*/

#ifndef FRACARRAY_H
#define FRACARRAY_H

#include "frac.h"

class ArrayOfFractions {

	private:
		Fraction *array;

	public:
		ArrayOfFractions();
		~ArrayOfFractions();
		void print() const;
		void setNums();
		void sortAscending();
		Fraction min();
		Fraction max();
		Fraction sum();
	};

#endif