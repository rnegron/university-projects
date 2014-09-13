//********************************************************************
//                                                                   *
//   Programador : Raúl Negrón          CCOM 3033 Sección 001        * 
//   Num. Est.   : 801-13-4680          Segundo Semestre 2013-14     * 
//   Prelab 04                          Prof. R. Arce                *     
//   Archivo     : colorcode.cpp       	Fecha : Febrero ??, 2014     *
//                                                                   *
//********************************************************************
//                                                                   * 
//    Proposito :	Este programa le pide al usuario un numero       *
//                  entre el 0 y el 9. Si el numero esta entre       *
//                  [0, 9], despliega el nombre color dependiendo    *
//                  del numero escojido. Si el numero no esta        *
//                  entre 0 y 9, despliega un error.                 *
//													                 *
//********************************************************************

// Instrucciones al pre-processador
#include <iostream>
using namespace std ;

int main()
{
	// Definición de variables
    int numero ;     // Contiene el INPUT del usuario
    string color ;   // contiene un string dependiendo del valor de la variable "numero"

    // Desplegar el propósito del programa
	cout << "\t\t <<< colorcode.cpp >>> " 
	     << "\n\t Luego de entrar un numero"
		 << "\n\t entre 0 y 9, se despliega"
		 << "\n\t el color que corresponde"
		 << "\n\t a el numero escojido." << endl << endl ;
		 
	// Recibir el INPUT del usuario
    cout << "Entre un numero entre 0 y 9: " ;
    cin >> numero ;

    // Si el INPUT es un numero entre 0 y 9
	// procedemos a asignar el valor de la
	// variable "color"
    if (numero <= 9) {
		// El valor de la variable "color"
		// depende del valor de la variable
		// "numero", utilizamos un switch
		// para correr los posibles valores
        switch (numero) {
            case 0: color = "negro" ;      break ;
            case 1: color = "marrón" ;     break ;
            case 2: color = "rojo" ;       break ;
            case 3: color = "anaranjado" ; break ;
            case 4: color = "amarillo" ;   break ;
            case 5: color = "verde" ;      break ;
            case 6: color = "azul" ;       break ;
            case 7: color = "violeta" ;    break ;
            case 8: color = "gris" ;       break ;
            case 9: color = "blanco" ;     break ;
        }
		// Desplegamos el calor correspondiente
        cout << "Ese color es " << color << "." << endl ;
    }
	// Si el INPUT del usuario no es un numero
	// entre 0 y 9, desplegar error
    else cout << "Ese color no existe. Error!!" << endl ;

    return 0; // Devolvemos 0 para simbolizar el final del programa.
}
