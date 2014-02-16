//********************************************************************
//                                                                   *
//   Programador : Raúl Negrón          CCOM 3033 Sección 001        * 
//   Num. Est.   : 801-13-4680          Segundo Semestre 2013-14     * 
//   Asignación 5                       Prof. Rafael J. Colorado     *     
//   Archivo     : heron.cpp       		Fecha : Febrero 18, 2014     *
//                                                                   *
//********************************************************************
//                                                                   * 
//    Proposito :	Este programa le pide al usuario 3 valores,      *
//                  los cuales representan los 3 lados de un         *
//                  triangulo. Luego, siguiendo la formula de 	     *
//					Herón, encontramos el semi-perimetro. Con        *
//					este calculamos el area del triangulo y lo       *			
//				    desplegamos al usuario.                          *
//													                 *
//********************************************************************

// Instrucciones al pre-processador
#include <iostream>
using namespace std ;

#include <iomanip> // Necesario para la funcion setprecision() y setw()
#include <cmath>   // Necesario para la funcion sqrt()

int main() {

	// Definición de variables

	double a ; // Primer lado del triangulo
	double b ; // Segundo lado del triangulo
	double c ; // Tercer lado del triangulo
	double semi ; // Almacena el resultado de la ecuacion (a + b + c) / 2
	double area ; // Calculada usando la formula de Herón
	
	// Desplegar el propósito del programa
	cout << "\t\t <<<  Area del Triangulo >>>" << endl ;
	cout << "\t\t <<< La formula de Heron >>>" << endl ;
	cout << "\t Dados los tres lados de un triangulo,\n "
		 << "\t calculamos la area del mismo utilizando\n"
		 << "\t la formula de Heron.\n\n" ;

	
	// Recibir los INPUTS del usuario
	cout << "Favor de entrar el lado #1 --> " ;
	cin >> a ;
	cout << "Favor de entrar el lado #2 --> " ; 
	cin >> b ;
	cout << "Favor de entrar el lado #3 --> " ;
	cin >> c ;
	
	// Calcular el semiperímetro basado en las variables a, b y c
	semi = (a + b + c) / 2.0 ;
	
	// Calcular el area del triangulo con la formula de Herón
	area = sqrt( semi * (semi - a) * (semi - b) * (semi - c) ) ; 
	
	// Modificar los datos de salida
	cout << fixed << setprecision(3) ;
	
	// Desplegar los resultados
	cout << "\n\nDado un triangulo con lados " 
		 << a << ", " << b << " y " << c << ", \n" 
		 << "tenemos semiperímetro " << semi 
		 << " y area " << area << endl ;

	return 0 ; // Devolvemos 0 para simbolizar el final del programa.a
}