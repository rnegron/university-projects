//********************************************************************
//                                                                   *
//   Programador 1: Raúl Negrón         CCOM 3033 Sección 001        *
//   Num. Est.   : 801-13-4680          Segundo Semestre 2013-14     *
//   Programador 2: Ricarco López									 *
//   Num. Est.   : 801-13-3608              						 *
//   Lab06                              Prof. Rafael Arce            *
//   Archivo     : shuffle.cpp          Fecha : Marzo, 8 2014        *
//                                                                   *
//********************************************************************
//                                                                   *
//    Proposito :	Este programa le pide al usuario que entre dos   *
//                  strings. Luego verifica el largo del string      *
//					mas pequeño y basado en este valor, va creando   *
//					un nuevo string que contiene los characteres     *
//					de ambos strings, pero mezclados. En el caso     *
//					de que un string sea mayor que otro, se rellena  *
//					el string nuevo con los valores que sobran del   *
//					mas largo. Al final se despliega el nuevo string *                                    
//													                 *
//********************************************************************

#include <iostream>

using namespace std;

int main()
{
	// Definicón de variables
    string input1, input2, result ;
    int lenOfShortest, acumulator ;
	
	// Pedir al usuario el primer string
    cout << "Enter string 1 --> " ;
    cin >> input1 ;

	// Pedir al usuario el segundo string
    cout << "Enter string 2 --> " ;
    cin >> input2 ;

	// A la variable lenOfShortest se le asigna el valor numerico
	// del tamaño mas pequeño entre los dos strings
    lenOfShortest = (input1.length() <= input2.length()) ? input1.length() : input2.length() ;

	// Este loop va desde 0 hasta el largo del string mas corto
    for (acumulator = 0 ; acumulator < lenOfShortest ; acumulator++ ) {
		
		// El string mezclado se le asigna un character
		// de cada string entrando por el usuari en la 
		// misma posicion pero uno tras otro
		
        result += input1[acumulator] ;
        result += input2[acumulator] ;
    }
	
	// Si ocurre que el string 1 es mas grande
	// que el string 2...
    if (input1.length() > acumulator) {
		
		// Mientras no se pase del largo...
        while (input1.length() > acumulator) {
		    
			// Rellenamos el string mezclado
			// con los valores finales de este string
            result += input1[acumulator] ;
            acumulator++ ;
        }
    }
	
	// Si ocurre que el string 2 es mas grande
	// que el string 1...
    else if (input2.length() > acumulator) {
	    
		// Mientras no se pase del largo...
        while (input2.length() > acumulator) {
		
			// Rellenamos el string mezclado
			// con los valores finales de este string
            result += input2[acumulator] ;
            acumulator++ ;
        }
    }

	// Desplegamos el resultado al usuario
    cout << "The shuffled string is: " << result << endl ;
  
	return 0 ;
}
