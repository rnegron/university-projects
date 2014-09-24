#include <iostream>
#include "sweetArray.h"

using namespace std;

int main() {

	int sizeA, sizeB;
	cout << "Hello Mr. TA! Please enter a size for the first array (A) > ";
	cin >> sizeA;
	cout << endl << "And now for the second array (B) > ";
	cin >> sizeB;
	cout << endl;

	SweetArray A(sizeA);
	SweetArray B(sizeB);

	for (int i = 0; i < sizeA; i++) {
		cout << "Enter an integer value for A[" << i << "] > ";
		cin >> A[i];
		cout << endl;
	}

	cout << "\tOkay! Array A is full." << endl;

	for (int i = 0; i < sizeB; i++) {
		cout << "Enter an integer value for B[" << i << "] > ";
		cin >> B[i];
		cout << endl;
	}

	cout << "\tOkay! Array B is full." << endl;

	cout << "\nContents of A are: "  << A << endl;
	cout << "Contents of B are: "  << B << endl << endl;
	cout << "Press Enter to continue > ";
	cin.get();
	cin.ignore();


	cout << "The sum of A and B is: " << (A + B) << endl << endl;
	cout << "The intersection of A and B is: " << (A & B) << endl << endl;
	cout << "The union of A and B is: " << (A | B) << endl << endl;

	cout << "That's all! Have a good day." << endl;


	return 0;
}
