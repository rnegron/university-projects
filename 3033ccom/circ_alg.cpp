#include <iostream>
#include <cmath>
using namespace std;

int main()
{
	float radius;
	const double PI = 3.141592;

	cout << "Enter the radius of the circle: ";
	cin >> radius;
	cout << endl;
	cout << "The radius is " << radius << endl;
	cout << "The diameter is " << radius * 2 << endl;
	cout << "The circumference is " << 2 * PI * radius << endl;
	cout << "The area is " << PI * pow(radius, 2) << endl << endl;
	return 0;
}