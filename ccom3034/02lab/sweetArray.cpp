/*
	Raúl Negrón
	#801-13-4680

	sweetArray.cpp

	This file contains the implementation of
	the SweetArray class as specified in
	sweetArray.h
*/

#include <iostream>
#include "sweetArray.h"

using namespace std;

// Default Constructor
SweetArray::SweetArray() {
	// Initialize a new array of 10 ints
	array = new int[10];
	size = 10;
}

// Overloaded Constructor
// Can specifiy array size
SweetArray::SweetArray(int n) {
	array = new int[n];

	// Initialize each element to -1
	for (int i = 0; i < n; i++) {array[i] = -1;}

	size = n;
}

// Function countVal
// 	INPUT: int first, last, values
//	 	specify the beginning of the array
//		(usually 0), the end of the array and the
//		value which we must find in the array
//	OUTPUT: int ret
//		contains the amount of times value was found
//		in the calling array
int SweetArray::countVal(int first, int last, int value) {
	int ret = 0;

	while (first!=last) {
		if (array[first] == value) {++ret;}
		++first;
	}

	return ret;

}

// overloaded [] operator
int& SweetArray::operator[](int i) {
	return array[i];
}

// overloaded << operator
ostream& operator<<(ostream& out, SweetArray S) {
	if (S.size == 0) return out;

	out << S.array[0];

	for (int i=1; i<S.size; i++)
		out << ", " << S.array[i];

	return out;
}

// overloaded + operator
SweetArray SweetArray::operator+(SweetArray& S) {
	SweetArray temp(size);

	for (int i = 0; i < temp.size; i++) {
		temp[i] = array[i] + S[i];
	}

	return temp;

}

// overloaded & operator
// INPUT: SweetArray S (reference)
// OUTPUT: SweetArray temp
//	temp contains the logical intersection
//	of the calling SweetArray and the parameter
//	SweetArray
SweetArray SweetArray::operator&(SweetArray& S) {
	// Initialize variables
	int amount = 0;
	int index = 0;

	// Priming nested For loop
	// Will yield the amount of elements
	// in the returning SweetArray
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < S.size; j++) {
			if (array[i] == S[j]) {amount++;}
		}
	} // End of priming nested For loop

	// Declare return object and
	// initialize with amount variable
	SweetArray temp(amount);

	// nested For loop to populate
	// the SweetArray with the intersected
	// elements
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < S.size; j++) {
			// If the elements are the same and we have not already
			// added the element to the returning SweetArray...
			if (array[i] == S[j] && temp.countVal(0, amount, array[i]) == 0) {
				temp[index] = array[i];
				index++;
			}
		}
	}
	return temp;
}

// overloaded | operator
// INPUT: SweetArray S (reference)
// OUTPUT: SweetArray temp
//	temp contains the logical union
//	of the calling SweetArray and the parameter
// 	SweetArray
SweetArray SweetArray::operator|(SweetArray& S) {
	// Initialize intersection to the intersection
	// of the calling object and S
	SweetArray intersection = (*this & S);

	// Initialize variables
	int amount1 = 0;
	int amount2 = 0;
	int index;

	// 	For loop which counts the amount of times
	//	the calling SweetArray has an element
	// 	which is not in the intersection SweetArray
	for (int i = 0; i < size; i++) {
		if (intersection.countVal(0, intersection.size, array[i]) == 0
				&& countVal(0, size, array[i]) == 1) {amount1++;}
	}

	// 	For loop which counts the amount of times
	//	the parameter SweetArray has an element
	//	which is not the intersection SweetArray
	for (int i = 0; i < S.size; i++) {
		if (intersection.countVal(0, intersection.size, S[i]) == 0
			 	&& S.countVal(0, S.size, S[i]) == 1) {amount2++;}
	}

	//	Initialize temp to be as large as each
	//	individual element which is not in
	// 	the intersection SweetArray + the size
	//	of the intersection SweetArray
	SweetArray temp(amount1 + amount2 + intersection.size);

	// 	For loop to populate the temp SweetArray with
	//	the elements of the intersection SweetArray
	for (index = 0; index < intersection.size; index++) {
		temp[index] = intersection[index];
	}

	// 	The following two For loops will populate the
	// 	temp SweetArray with elements which belong to
	//	either the calling SweetArray or the parameter
	//	sweetArray, but not both.

	for (int i = 0; i < size; i++) {
		if (temp.countVal(0, temp.size, array[i]) == 0) {
			temp[index] = array[i];
			index++;
			}
	}

	for (int i = 0; i < S.size; i++) {
		if (temp.countVal(0, temp.size, S[i]) == 0) {
			temp[index] = S[i];
			index++;
			}
	}

	return temp;
}
