/*
	Raúl Negrón
	#801-13-4680

	sweetArray.h

	This file contains the specification of
	the SweetArray class
*/

#ifndef SWEET_H
#define SWEET_H

#include <iostream>
using namespace std;

class SweetArray {
	private:
		int *array;
		int size;
		int countVal(int first, int last, int value);

	public:
		SweetArray();
		SweetArray(int n);
		void setSize(int n);
		int& operator[](int i);
		SweetArray operator+(SweetArray& S);
		SweetArray operator&(SweetArray& S);
		SweetArray operator|(SweetArray& S);
		friend ostream& operator<<(ostream& out, SweetArray S);

};
#endif
