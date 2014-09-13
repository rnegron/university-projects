#include <iostream>
#include "sweetArray.h"
#include <algorithm>

using namespace std;

SweetArray::SweetArray() {
	array = new int[10];
	size = 10;
}

SweetArray::SweetArray(int n) {
	array = new int[n];

	for (int i = 0; i < n; i++) {array[i] = -1;}

	size = n;
}

int SweetArray::countVal(int first, int last, int value) {

	int ret = 0;

	while (first!=last) {

		if (array[first] == value) {++ret;}
		++first;

	}

	return ret;

}

int& SweetArray::operator[](int i) {
	return array[i];
}

ostream& operator<<(ostream& out, SweetArray S) {
	if (S.size == 0) return out;
	out << S.array[0];
	for (int i=1; i<S.size; i++)
		out << ", " << S.array[i];
	return out;
}

SweetArray SweetArray::operator+(SweetArray& S) {

	SweetArray temp(size);

	for (int i = 0; i < temp.size; i++) {
		temp[i] = array[i] + S[i];
	}

	return temp;

}

SweetArray SweetArray::operator&(SweetArray& S) {

// Priming nested For loop
// Will yield the amount of elements
// in the returning SweetArray
	int amount = 0;

	for (int i = 0; i < size; i++) {

		for (int j = 0; j < S.size; j++) {

			if (array[i] == S[j]) {amount++;}
		}
	}

// End of priming nested For loop
	SweetArray temp(amount);

	for (int i = 0; i < size; i++) {
		for (int j = 0; j < S.size; j++) {
			// If the elements are the same and we have not already
			// added the element to the returning SweetArray...
			if (array[i] == S[j] && temp.countVal(0, amount, array[i]) == 0) {
				temp[i] = array[i];
			}
		}
	}

	return temp;
}

SweetArray SweetArray::operator|(SweetArray& S) {

	SweetArray intersection = (*this & S);

	int amount1 = 0;
	int amount2 = 0;

	int index;

	for (int i = 0; i < size; i++) {

		if (intersection.countVal(0, intersection.size, array[i]) == 0 && countVal(0, size, array[i]) == 1) {amount1++;}
	}

	for (int i = 0; i < S.size; i++) {

		if (intersection.countVal(0, intersection.size, S[i]) == 0 && S.countVal(0, S.size, S[i]) == 1) {amount2++;}

	}


	SweetArray temp(amount1 + amount2 + intersection.size);

	for (index = 0; index < intersection.size; index++) {
		temp[index] = intersection[index];
	}

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
