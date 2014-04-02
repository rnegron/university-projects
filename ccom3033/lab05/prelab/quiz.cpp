
//********************************************************************
//                                                                   *
//   Programador : Raúl Negrón          CCOM 3033 Sección 001        * 
//   Num. Est.   : 801-13-4680          Segundo Semestre 2013-14     * 
//   Prelab 05                      	Prof. R. Arce				 *     
//   Archivo     : quiz.cpp       		Fecha : Febrero 25, 2014     *
//                                                                   *
//********************************************************************
//                                                                   * 
//    Proposito :	Este programa le pide al usuario un numero entre *
//					0 y 6, inclusivo. Este numero representa el      *
//					maximo numero de digitos que tendra una suma     *
//					que se genera de manera aleatoria. El usuario    *
//					debe luego intentar de resolver la suma          *
//					creada basada en su input previo.                *             
//													                 *
//********************************************************************

// Instrucciones al pre-procesador

#include <iostream>
using namespace std;
#include <cstdlib> // necesario para las funciones rand y srand
#include <ctime>   // necesario para la funcion time
#include <cmath>   // necesario para la funcion pow

int main()
{
    srand(time(NULL)) ; // la semilla para generar numeros aleatoreos

	// Definicion de variables
	
    int x ;  		  // contiene un lado de la suma
    int y ;  	 	  // contiene el otro lado de la suma
    int userRange ;   // contiene un valor entre 0 y 6, inclusivo, dado por el usuario
    int userResult ;  // contiene el resultado de la suma hecha por el usuario
    int randomLimit ; // contiene el valor de 10 elevado por userRange

	// pedir input mientras no cumpla con ser [0, 6]
    do { 
        cout << "Please enter a number in the range [0, 6]: " ;
        cin >> userRange ;
    } while (userRange < 0 || userRange > 6) ;

	// crear los limites de los numeros aleatorios
    randomLimit = pow(10.0, static_cast<double>(userRange)) ;
	
	// crear los dos numeros que seran sumados por el usuario
    x = rand() % randomLimit ;
    y = rand() % randomLimit ;
	
	// pedir input sobre el resultado de la suma aleatoria
    cout << "What is the result of " << x << " + " << y << " : " ;
    cin >> userResult ;
	
	// verificar el resultado de la suma hecha por el usuario
	// y desplegar si fue correcto o si fue incorrecto
    if (userResult == x + y) cout << "Correct!\n" ;
    else cout << "Incorrect!\n" ;

    return 0;
}
