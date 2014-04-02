//********************************************************************
//                                                                   *
//   Programador : Raul Negron          CCOM 3033 Seccion 001        *
//   Num. Est.   : 801-13-4680          Segundo Semestre 2013-14     *
//   Prelab 6                           Prof. Rafael Arce            *
//   Archivo     : expo.cpp       		Fecha : Marzo 3, 2014        *
//                                                                   *
//********************************************************************
//                                                                   *
//    Proposito :	Este programa lleva a cabo una serie de sumas    *
//		            con el numerador 1 y el denominador variando     *
//		            desde la el producto factorial de 1 hasta la     *
//                  el producto factorial de 20. A el resultado      *
//                  se le asigna una variable y este se compara      *
//                  con el resultado de una funcion pre-hecha.       *
//													                 *
//********************************************************************

#include <iostream>
using namespace std ;
#include <cmath>    // Necesario para pow(), sin() y exp()
#include <iomanip>  // Necesario para setprecision() y setw()

int main() {

	// Definicion de variables
	double facto = 1 ;
	double expo = 1.0 ;

	// Este loop va desde 1 a 20, utilizando la variable n
	for (int n = 1; n <= 20; n++) {
		// DEBUG
		// cout << "In n = " << n << "..." << endl ;

		// Este loop va desde 1 hasta el valor de n
		for (int i = 1; i <= n; i++) {
			// n factorial es igual a la multiplicacion de todos los numeros
			// desde 1 hasta n
			facto *= i ;
		}

	
	// El valor de expo es la sumatoria de ( 1 sobre el producto factorial
	// de los numeros naturales hasta 20 )
	expo += ( 1.0 / static_cast<double>(facto) ) ;

	// Regresamos el valor del producto factorial a 1 antes de volver el loop
	facto = 1 ;

	}

	// Modificamos la salida de los datos para desplegar 25 espacios
	// decimales
	cout << setprecision(25) << fixed ;

	// Desplegamos resultados
	cout << "Valor de e obtenido mediante sumatoria: "
	     << setw(25) << expo   << endl ;
	cout << "Valor de e obtenido mediante exp(1): "
	     << setw(30) << exp(1) << endl ;

    return 0;
    }
