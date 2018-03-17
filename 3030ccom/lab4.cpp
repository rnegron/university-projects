/*
	Raul Negron Otero 801-13-xxxx
	Programa: lab4.cpp
	Este programa le pide al usuario un numero 1 o 2. Luego le pide un valor en grados.
	Dependiendo de la seleccion entre 1 y 2, convierte el valor en grados a celsius o farenheit.
	Utiliza dos funciones separadas para cada conversion.
	
	Variables:
	* celsius = tipo int, contiene el valor de la conversion desde farenheit
	* farenheit = tipo float, contiene el valor de la conversion desde celsius
	* choice = tipo int, contiene la seleccion del usuario entre 2 tipos de conversion
	* user = tipo float, contiene el valor en grados que el usuario quiere convertir
*/
#include <iostream>
using namespace std;

int f_to_c(float farenheit) // esta funcion recibe un float como input, devuelve un int
{
	int celsius = (farenheit - 32) * 5/9; // celsius es el valor de farenheit - 32 multiplicado por 1.8
	return celsius;
}

float c_to_f(int celsius) // esta funcion recibe un int como input devuelve un float
{
	float farenheit = (celsius * 9/5) + 32; // farenheit es el valor de celsius multiplicado por 1.8 + 32
	return farenheit;
}

int main()
{
	int choice; // la variable choice contiene el valor numerico de la opcion que el usuario quiere
	float user; // la variable user contiene el valor numerico de los grados que el usuario entre
	cout << "Hacia que estandar desea convertir? Presione 1 para convertir a Celsius, 2 para convertir a Farenheit: ";
	cin >> choice; // se le asigna el valor del input a la variable choice
	cout << "Entre su valor: ";
	cin >> user; // se le asigna el valor del input a la variable user
	if (choice == 1){ // si el usuario escojio convertir desde farenheit a celsius...
		// llamamos a la funcion f_to_c quien se encarga de convertir el valor y desplegamos el resultado
		cout << user << " grados Farenheit es " << f_to_c(user) << " grados Celsius.";
		cout << endl;
	} else { // si el usuario escojio convertir desde celsius a farenheit...
		// llamamos a la funcion c_to_f quien se encarga de convertir el valor y desplegamos el resultado
		cout << user << " grados Celsius es " << c_to_f(user) << " grados Farenheit.";
		cout << endl;
	}
	return 0; // el programa acabo de correr, devolvemos 0
}
