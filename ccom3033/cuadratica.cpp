//********************************************************************
//                                                                   *
//   Programador : Raúl Negrón          CCOM 3033 Sección 001        * 
//   Num. Est.   : 801-13-4680          Segundo Semestre 2013-14     * 
//   Asignacion 4                       Prof. Rafael J. Colorado     *     
//   Archivo     : cuadratica.cpp       Fecha : Febrero 11, 2014     *
//                                                                   *
//********************************************************************
//                                                                   * 
//    Proposito :	Este programa le pide al usuario 3 valores,      *
//                  los cuales son utilizados para evaluar la        *
//                  ecuación cuadratica. Primero se encuentra el     *
//                  discriminante y se determina el mejor curso      *
//				    que tomar a partir de su valor. Luego de esto,   *                                                      
//					se despliega el resultado del cálculo al         *
//					usuario.										 *
//													                 *
//********************************************************************

// Instrucciones al pre-procesador
#include <iostream>
using namespace std;

#include <cmath>		// Necesario para la función pow()
#include <iomanip>      // Necesario para los manipuladores de salida

int main() {
	
	// Definición de variables
	double a ; 
	double b ;
	double c ;
	double discriminante ; // contiene pow(b, 2) - 4 * a * c
	
	// Desplegamos el proposito del programa al usuario
	cout << "\t\t <<< Ecuación Cuadratica >>>\n" ;
	cout << "\t A continuación se le pedira que llene los\n "
	     << "\t valores de las variables a, b y c. Estos serán\n "
	     << "\t utilizados para evaluar la función cuadratica\n "
	     << "\t y el resultado sera desplegado en pantalla.\n\n" ;
	
	// Pedir INPUT del usuario para las variables
	cout << "Entre el valor de la variable 'a' --> " ;
	cin >> a ;

	cout << "Entre el valor de la variable 'b' --> " ;
	cin >> b ;
	
	cout << "Entre el valor de la variable 'c' --> " ;
	cin >> c ;
	
	// Calcular el discriminante
	discriminante = pow(b, 2) - 4 * a * c ;
	
	// Ajustar la precision deseada para la salida de los valores
	cout << setprecision(2) << fixed ;
	
	// Si el discriminante > 0, existen dos soluciones reales
	if (discriminante > 0) {
		
		cout << "\nEl discriminante ("             << discriminante
		     << ") es mayor que 0."			       << endl ;
		cout << "Existen dos soluciones reales.\n" << endl ; 
		
		// Desplegar las raices
		cout << "La 1ra raiz es: " << setw(6)
		     << (-b + sqrt(discriminante)) / (2 * a) << endl ;
		
		cout << "La 2nda raiz es: " << setw(6)
		     << (-b - sqrt(discriminante)) / (2 * a) << endl ;
	
	// Si el discriminant es < 0, existen soluciones complejas
	} else if (discriminante < 0) {
		
		cout << "\nEl discriminante (" << discriminante
		     << ") es menor que 0."    << endl ;
		     
		// Dejarle saber al usuario sobre los limites de este programa
		cout << "Existen soluciones complejas. No las puedo calcular." ;
		cout << endl ;
	
	// Si el discriminante es 0, la raiz es de multiplicidad 2
	} else {
		
		cout << "\nEl discriminante es 0. La raiz es de " ;
		
		// Desplegar la raiz
		cout << "multiplicidad 2. La raiz es: " << setw(6) 
		     << (-b) / (2 * a) << endl ;
	}
	
	return 0; // Devolver 0 para anunciar el fin del programa
}
