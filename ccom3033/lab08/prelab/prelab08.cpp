//                                                                   *
//   Programador : Raúl Negrón          CCOM 3033 Sección 001        *
//   Num. Est.   : 801-13-4680          Segundo Semestre 2013-14     *
//   Prelab 8                           Prof. Rafael J. Arce         *
//   Archivo     : prelab08.cpp         Fecha : Marzo 21, 2014       *
//                                                                   *
//********************************************************************
//                                                                   *
//    Proposito :	Este programa provee tres funciones diferentes.  *
//                  Cada funcion esta acompañada de una explicacion  *
//                  antes de su definicion. Las tres funciones son   *
//                  utilizadas en main() y demuestran su utilidad.   *
//********************************************************************

// Instrucciones al pre-procesador
#include <iostream>
#include <string>

using namespace std ;

/*
    Esta funcion recibe un valor numerico entero. Luego, inicializa
    dos variables a 0. Una de ellas sirve como contador y la otra como
    acumulador. Mientras el contador sea menor que el valor numerico
    dado, al valor del acumulador se le suma el valor del contador.
    Se le suma 1 al contador por cada iteracion.

    Devuelve el valor numerico (entero) del acumulador cuando el contador es igual 
	al valor numerico dado.
*/
int foo(int t) {

    // Inicializacion de variables
    int n = 0 ;
    int i = 0 ;

    // Mientras el contador i sea menor que el numero dado...
    while (i < t) {
        // A la variable n se le suma el contador i
        n += i ;
        // Y se incrementa i en 1
        i++ ;
    }

    // Al salir del loop, significa que el contador
    // sobrepaso el valor de la variable dada o es igual.

    // Devolvemos la suma de los contadores necesarios para
    // alcanzar el valor de la variable dada.
    return n ;
}

/*
    Esta funcion recibe un string. Luego lo encripta de la siguente forma:
        1) Toma el string letra por letra y cambia las letras a la letra que corresponde
            al proximo valor en el codigo ASCII
        2) Si la letra que corresponde al proximo valor en el codigo ASCII es una vocal,
            entonces la intercambia por la misma vocal pero mayuscula.

    Devuelve el string encriptado.
*/
string tkEncrypt(string s) {

    // Definicion de variables
    string encrypted ;           // contiene el string encriptado
    string vowels    = "aeiou" ;
    string vowelsCap = "AEIOU" ;
    int vowelLocation ;          // contiene la posicion en el string donde se encuentra una vocal

    // Este loop va letra por letra en el string dado
    for (int i = 0; i < s.length(); i++) {

        // Si encuentra que la letra que corresponde al proximo
        // numero ASCII es una vocal...
        if ( vowels.find(s[i] + 1) != -1 ) {

            // Guarda la posicion donde se encuentra esta vocal dentro
            // de nuestro string de vocales
            vowelLocation = vowels.find(s[i] + 1) ;

            // Y basado en esta localizacion, intercambia la vocal
            // en minuscula por la vocal en mayuscula
            encrypted += vowelsCap[vowelLocation] ;
        }

        // Si la letra es 'z', la proxima vuelve al principo del alfabeto
        else if (s[i] == 'z') encrypted += 'A' ;

        // Normalmente, se busca la letra que corresponde al codigo ASCII proximo
        else encrypted += s[i] + 1 ;
    }

    // Devolver el string encriptado
    return encrypted ;
}

/*
    Esta funcion recibe un string previamente encriptado.
    Lo decripta de la siguente forma:
        1) Toma el string letra por letra y cambia las letras a la letra que corresponde
            al valor previo en el codigo ASCII
        2) Si la letra que corresponde al valor previo en el codigo ASCII es una vocal
            mayuscula, entonces la intercambia por la misma vocal pero minuscula.

    Devuelve el string decriptado (el original).
*/
string tkDecrypt (string s) {

    // Definicion de variables
    string decrypted ;           // contiene el string decriptado
    string vowels    = "aeiou" ;
    string vowelsCap = "AEIOU" ;
    int vowelLocation ;          // contiene la posicion en el string donde se encuentra una vocal

    // Este loop va letra por letra en el string dado
    for (int i = 0; i < s.length(); i++) {

        // Si encuentra que la letra que corresponde al previo
        // numero ASCII es una vocal mayuscula...
        if ( vowelsCap.find(s[i] - 1) != -1 ) {

            // Guarda la posicion donde se encuentra esta vocal dentro
            // de nuestro string de vocales mayusculas
            vowelLocation = vowelsCap.find(s[i] - 1) ;

            // Y basado en esta localizacion, intercambia la vocal
            // en mayuscula por la vocal en minuscula
            decrypted += vowels[vowelLocation] ;
        }

        // Si la letra es 'A', la anterior vuelve al final del alfabeto
        else if (s[i] == 'A') decrypted += 'z' ;

        // Normalmente, se busca la letra que corresponde al codigo ASCII anterior
        else decrypted += s[i] - 1 ;
    }

    // Devolver el string decriptado
    return decrypted ;
}

int main() {

    // Comienzan las pruebas de las funciones

    // Prueba de foo()
    cout << "Resultado pasando argumento 4: " << foo(4) << endl;
    cout << "Resultado pasando argumento 9: " << foo(9) << endl;

    // Prueba de tkEncrypt()
    cout << "zorra encriptada es: " << tkEncrypt("zorra") << endl;
    cout << "candido encriptada es: " << tkEncrypt("candido") << endl;

    // Prueba de tkDecrypt()
    string st = "perro";
    if (st == tkDecrypt( tkEncrypt( st ) ) ) {
        cout << "Encripte y decripte correctamente!" << endl;
    }
    else {
        cout << "Luego de decriptar no logre recuperar el "
             << "mensaje original" << endl;
    }

    return 0 ; // Devolvemos 0 para indicar el fin del programa
}
