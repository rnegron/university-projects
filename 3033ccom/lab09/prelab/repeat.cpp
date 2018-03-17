//                                                                   *
//   Programador : Raúl Negrón          CCOM 3033 Sección 001        *
//   Num. Est.   : 801-13-4680          Segundo Semestre 2013-14     *
//   Prelab 9                           Prof. Rafael J. Arce         *
//   Archivo     : repeat.cpp           Fecha : Marzo 26, 2014       *
//                                                                   *
//********************************************************************
//                                                                               
//    Pseudocodigo :  	START 
//						string repeatStr
//                      char letter
//						int chain = 1
//                      INPUT string s
//                      FOR i = 0 until i = length of s - 1:
//							IF word[i] = word[i+1]:
//								letter = word[i]
//								WHILE word[i] = word[i+1] AND i < s.length():
//									chain = chain + 1
//									i = i + 1
//								repeatStr = repeatStr + letter + chain
//								chain = 1
//							ELSE:
//								repeatStr = repeatStr + letter + "1"
//						OUTPUT repeatStr
//						END
//**********************************************************************************************

// Instrucciones al pre-procesador
#include <iostream>
#include <string>
#include <sstream> // necesario para stringstream

using namespace std ;

string repeat(string) ; // prototipo de la funcion

int main() {

    // Declaramos la variable string que el usuario utilizara
    string input ;

    // Guardamos el input del usuario
    cout << "Enter the string -> " ;
    cin >> input ;

    // Enviamos el input hacia la funcion para ser trabajado,
    // desplegamos el resultado de la funcion
    cout << "\nThe result is: " << repeat(input) << endl ;

    return 0 ;
}

// Esta funcion recibe el input del usuario (tipo string)
// y devuelve un string que cuenta la cardinalidad
// de la secuencia de un mismo caracter
string repeat(string word) {

    // Declaracion de variables
    string repeatWord ;
    stringstream ss ;
    char theLetter ;
    int chain = 1 ; // siempre hay por lo menos un caracter en la secuencia de el mismo

    // Esta funcion va desde el primer caracter hasta el ultimo en el string
    for (int i = 0 ; i < word.length(); i++) {

        // Si el presente caracter es igual al proximo...
        if (word[i] == word[i + 1]) {
            theLetter = word[i] ; // Guardamos ese caracter...
            // Mientras el caracter presente sea igual al proximo y no nos pasemos del largo del string...
            while (word[i] == word[i+1] && i < word.length() - 1) {
                // Sumamos uno a la secuencia
                chain++ ;
                // Nos movemos al proximo caracter
                i++ ;
            }

            // Utilizamos el stringstream para concatenar un int a un string
            ss << chain ;

            // Ir creando el string que devuelve la funcion
            repeatWord += theLetter ;
            repeatWord += ss.str() ;

            // Regresamos el acumulador
            chain = 1 ;
            // Limpiamos el streamstring
            ss.str("") ;
        }

        // Si el presente caracter y el proximo no son iguales,
        // pues la secuencia es de un caracter
        else {
            repeatWord += word[i] ;
            repeatWord += "1" ;
        }
    }

    // Devolvemos el string que contiene la informacion de repeticion en secuenciaaa
    return repeatWord ;
}
