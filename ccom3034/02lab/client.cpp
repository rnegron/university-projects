#include <iostream>
#include "sweetArray.h"

using namespace std;

const int SIZE = 9;

int main() {
	SweetArray A(SIZE), B(SIZE), C(SIZE);

	for (int i=0; i<SIZE; i++) {
		A[i] = i * 30;
		B[i] = i * 60;

	}

	cout << "\nContents of A are: "  << A << endl;
	cout << "Contents of B are: "  << B << endl << endl;



	cout << "The sum of A and B is: " << (A + B) << endl << endl;
	cout << "The intersection of A and B is: " << (A & B) << endl << endl;
	cout << "The union of A and B is: " << (A | B) << endl << endl;


	return 0;
}
