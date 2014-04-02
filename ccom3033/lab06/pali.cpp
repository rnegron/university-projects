//********************************************************************
//                                                                   *
//   Programador 1: Raúl Negrón         CCOM 3033 Sección 001        *
//   Num. Est.   : 801-13-4680          Segundo Semestre 2013-14     *
//   Programador 2: Ricarco López                                    *
//   Num. Est.   : 801-13-3608                                       *
//   Lab06                              Prof. Rafael Arce            *
//   Archivo     : pali.cpp             Fecha : Marzo, 8 2014        *
//                                                                   *
//********************************************************************
//                                                                   *
//    Proposito :	Este programa le pide al usuario que entre un    *
//                  string. Luego creo otro string que es el         * 
//					original pero al revez y los compara. Si el      *
//					nuevo string es igual al original, entonces      *
//					la palabra o el string es un palidromo. De       *
//					cualquier modo, se despliega el resultado        *
//					al usuario.                                      * 
//													                 *
//********************************************************************

#include <iostream>

using namespace std ;

int main()
{
	// Definición de variables
    string input, converse ;

	// Pedimos al usuario un string y lo guardamos en input
    cout << "Enter a string --> " ;
    cin >> input ;
	
	// Este loop va desde el largo del string - 1 hasta el segundo 
	// character del string (el character antes del primero)
    for (unsigned i = input.length() - 1 ; i > 0 ; i--) {
		
		// Asignar al string converse los valores de input pero 
		// al revez
        converse += input[i] ;
    }
	
	// Añadir el último que falta... el primer character
    converse += input[0] ;
    
	// Si el string original es igual que el string al revez, es un palidromo
    if (input == converse) cout << "Yes, " << input << " is a palindrome." << endl ;
	
	// Si el string original no es igual al string al revez, no es un palidromo
    else cout << "No, " << input << " is not a palindrome." << endl ;

    return 0;
}
