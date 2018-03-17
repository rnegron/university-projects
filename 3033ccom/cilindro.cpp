//********************************************************************
//                                                                   *
//   Programador : Raúl Negrón          CCOM 3033 Sección 001        * 
//   Num. Est.   : 801-13-4680          Segundo Semestre 2013-14     * 
//   Asignacion 3                       Prof. Rafael J. Colorado     *     
//   Archivo     : cilindro.cpp         Fecha : Febrero 6, 2014      *
//                                                                   *
//********************************************************************
//                                                                   * 
//    Proposito :  Este programa pide al usuario el radio y la       *
//                 altura de un clindro. Luego, calcula el area      *
//                 y el volumen del cilindro utilizando los          *
//                 valores dados. Finalmente, despliega el radio,    *
//				   la altura, el volumen y el area del cilindro.     *                                                      
//																	 *
//********************************************************************

// Instrucciones al pre-procesador

#include <cmath> 
#include <iomanip>
#include <iostream>

using namespace std;

const double PI = 3.14159 ; // Declaramos la constante PI como global

int main()
{
	// Definición de variables

	double radio ;		// Radio de las bases
	double altura ;		// Altura del cilindro
	double area ;		// Area de la superficie
	double volumen ;	// Volumen del cilindro

	// Desplegar el proposito del programa al usuario
	cout << "\nEste programa, dado el radio y la altura\n"
		 << "de un cilindro, calcula y despliega el area\n"
		 << "y el volumen del cilindro.\n\n" ;
		 
	// INPUT radio de las bases
	cout << "Entre el radio de las bases -- > ";
	cin >> radio ;
	
	// INPUT altura del cilindro
	cout << "Entre la altura del cilindro - > ";
	cin >> altura ;
	
	cout << endl << endl ;

	// Calcular el area y el volumen
	area = 2.0 * PI * radio * (radio + altura) ;
	volumen = PI * pow(radio, 2.0) * altura ;
	
	
	cout << fixed << setprecision(3) ;
	
	// Desplegar radio, altura, area y volumen
	cout << "\t ~~~~~ RESULTADOS ~~~~~\n" 
		 << "\tEl radio de las bases es    " << setw(10) << radio 
		 << "\n\tLa altura del cilindro es   " << setw(10) << altura
		 << "\n\tEl area de la superficie es " << setw(10) << area
		 << "\n\tEl volumen del cilindro es  " << setw(10) << volumen
		 << endl ;

	return 0 ;
}