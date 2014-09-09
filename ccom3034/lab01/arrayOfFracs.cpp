#include <iostream>
#include <cstdlib>
#include <time.h>

#include "ArrayOfFracs.h"
using namespace std;

ArrayOfFractions::ArrayOfFractions() {
		array = new Fraction[10];
	}

ArrayOfFractions::~ArrayOfFractions() { delete [] array; }

void ArrayOfFractions::print() const {
	for (int i = 0; i < 10; i++) {
		cout << "Array " << i << ": ";
		array[i].print();
		cout << endl;
	}
}

void ArrayOfFractions::setNums() {
	srand (time(NULL));

	for (int i = 0; i < 10; i++) {
		array[i].setNum((rand() % 9) + 1);
		array[i].setDenom((rand() % 9) + 1);
	}
}


