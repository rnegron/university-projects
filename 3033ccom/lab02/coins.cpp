//********************************************************************
//                                                                   *
//   Programador 1: Raul Negrón         CCOM 3033 Seccion 001        * 
//   Num. Est.   : 801-13-4680          Segundo Semestre 2013-14     * 
//   Programador 2: Hector Quiñones									 *
//	 Num. Est.   : 801-09-5300										 *
//																	 *
//   Lab 02		                        Prof. Rafael Arce		     *     
//   Archivo     : coins.cpp            Fecha : Febrero 7, 2014      *
//                                                                   *
//********************************************************************
//                                                                   * 
//    Proposito : Este programa comienza generando un numero         *
//                aleatorio entre el 5 y el 99. Luego le pide al     *
//                usuario que piense en la manera en la cual se	     *
//                podria dividir este numero entre pecetas,          *
//                dimes, vellones y chavitos. Al presionar           *	
//                ENTER, se despliega el resultado de los            *
//                calculos hechos para encontrar la manera           *
//				  correcta de combinar el menudo para llegar a       *
//                el numero aleatorio.                               *
//															         *
//********************************************************************

// Instrucciones al pre-procesador
#include <iostream> 
using namespace std ;

#include <cstdlib>  // Necesario para las funciones rand() y srand()
#include <ctime>    // Necesario para la funcion time()

int main() {
		
	// Creamos la semilla del numero aleatorio
	srand(time(NULL)) ;
	
	// Inicializamos el valor del numero aleatorio dentro de [5,99]
	int random = rand() % (99 - 5 + 1) + 5 ; 
	
	// Inicializamos la variable que contiene la suma del menudo
	int total = 0 ;
	
	// Definición de variables
	int pesetas ; 	// Cantidades de 25
	int dimes ; 	// Cantidades de 10
	int vellones ;	// Cantidades de 5
	int chavitos ;	// Cantidades de 1
	

	// Despliegue las instrucciones del programa
	cout << "\n\nSistema de entrenamiento de devolución de monedas\n\n" ; 
	cout << "Determine la combinación de monedas para un cambio de " 
		 << random << " centavos.\n" ;
	cout << "Luego de que piense en la solución, oprima ENTER para "
		 << "ver la solución correcta." << endl ; 

	// Calcular la combinación correcta
	pesetas = random / 25 ;
	dimes = (random % 25) / 10 ;
	vellones = ((random %  25) % 10) / 5;
	chavitos = (((random % 25) % 10) % 5) / 1 ;
	
	// Pausar el sistema mientras el usuario no oprima ENTER 
	cin.get() ;
	
	// Desplegar el resultado de los calculos
	// Mientras desplegamos, llevamos cuenta del total y desplegamos
	cout << "\n<<< Resultados >>>\n" ;
	cout << "Para llegar a " << random << ", necesitas:\n" ;
	cout << "---------------------" << endl;
	total += pesetas * 25 ;
	cout << pesetas  << " pesetas ("  << total << ")" << endl;
	
	total += dimes * 10 ;
	cout << dimes    << " dimes ("    << total << ")" << endl;
	
	total += vellones * 5 ;
	cout << vellones << " vellones (" << total << ")" << endl;
	
	total += chavitos * 1 ;
	cout << chavitos << " chavitos (" << total << ")" << endl;
	cout << "---------------------" << endl;

	return 0;
}