#ifndef ARRAYOFFRACS_H
#define ARRAYOFFRACS_H

#include "frac.h"

class ArrayOfFractions {

	private:
		Fraction *array;
		double value;

	public:
		ArrayOfFractions();
		~ArrayOfFractions();
		void print() const;
		void setNums();
};

#endif