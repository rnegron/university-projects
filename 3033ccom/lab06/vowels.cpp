//********************************************************************
//                                                                   *
//   Programador 1: Raúl Negrón         CCOM 3033 Sección 001        *
//   Num. Est.   : 801-13-4680          Segundo Semestre 2013-14     *
//   Programador 2: Ricarco López									 *
//   Num. Est.   : 801-13-3608              						 *
//   Lab06                              Prof. Rafael Arce            *
//   Archivo     : vowels.cpp           Fecha : Marzo, 8 2014        *
//                                                                   *
//********************************************************************
//                                                                   *
//    Proposito :	Este programa le pide al usuario que entre un    *
//                  string. Luego verifica letra por letra si el     *
//					string contiene una vocal y va contando          *
//					cuantas vocales encuentra. Al final, se          * 
//					despliega al usuario cuantas vocales fueron      *
//					encontradas.                                     *  
//													                 *
//********************************************************************

#include <iostream>

using namespace std;

int main()
{
	// Definición de variables
    string input ;
    string vowels = "aeiou" ; // Este string contiene todas las letras vocales
    int counter = 0 ;
	
	// Pedir al usuario un string y guardarlo en input
    cout << "Enter a string --> " ;
    cin >> input ;
	
	// Este loop va desde el primer character en el string
	// hasta el ultimo character 
    for (unsigned i = 0 ; i < input.length(); i++) {
		
		// y este otro va buscando todas las vocales
		// que estan guardadas en el string "vowels"
        for (unsigned z = 0 ; z < vowels.length(); z++) {
			
			// Cada character del string "input" es probada con
			// todas las vocales. Si son iguales, entonces el
			// character en "input" es una vocal y se incrementa
			// el contador
           if (input[i] == vowels[z]) counter++ ;
        }
    }
	
	// Desplegar cuantas vocales fueron encontradas
    cout << endl << input << " has " << counter << " vowels." << endl ;
	
    return 0;
}
