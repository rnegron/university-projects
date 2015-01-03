#include <iostream>
#include <cstdlib>
#include <time.h>

#include "fracArray.h"
using namespace std;

const int size = 10;

ArrayOfFractions::ArrayOfFractions() {
		array = new Fraction[size];
		setNums();
	}

ArrayOfFractions::~ArrayOfFractions() { delete [] array; }

void ArrayOfFractions::print() const {
	cout << endl;
	for (int i = 0; i < size; i++) {
		cout << "Fraction " << i + 1 << ": ";
		array[i].print();
		cout << endl;
	}
}

void ArrayOfFractions::setNums() {
	// Seeding pseudo-rand with time
	srand(time(NULL));

	for (int i = 0; i < size; i++) {
		array[i].setNum((rand() % 9) + 1);
		array[i].setDenom((rand() % 9) + 1);
	}
}

void ArrayOfFractions::sortAscending() {

	Fraction tempFrac;

	// Selection sort
	for (int startIndex = 0; startIndex < size; startIndex++) {

		int smallestIndex = startIndex;

		for (int currentIndex = startIndex + 1; currentIndex < size; currentIndex++) {

			if (array[currentIndex].gt(array[smallestIndex]) == false)
				smallestIndex = currentIndex;
		}

		// Swap
		tempFrac.setNum(array[startIndex].getNum());
		tempFrac.setDenom(array[startIndex].getDenom());

		array[startIndex].setNum(array[smallestIndex].getNum());
		array[startIndex].setDenom(array[smallestIndex].getDenom());

		array[smallestIndex].setNum(tempFrac.getNum());
		array[smallestIndex].setDenom(tempFrac.getDenom());

	}
}

Fraction ArrayOfFractions::min() {

	sortAscending();
	return array[0];
}

Fraction ArrayOfFractions::max() {
	sortAscending();
	return array[size - 1];
}

Fraction ArrayOfFractions::sum() {
	Fraction tempFrac;

	for (int i = 0; i < size; i++) {
		tempFrac = tempFrac.add(array[i]);
	}

	return tempFrac;

}
