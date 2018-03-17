//********************************************************************
//                                                                   *
//   Programador : Raúl Negrón          CCOM 3033 Sección 001        *
//   Num. Est.   : 801-13-4680          Segundo Semestre 2013-14     *
//   Prelab07                           Prof. Rafael Arce   	     *
//   Archivo     : rima.cpp      	    Fecha : Marzo 10, 2014       *
//                                                                   *
//********************************************************************
//                                                                   *
//    Proposito :		Este programa abre un archivo que contiene   *
//						un diccionario de palabras en español.       *
//						Luego le pide al usuario una palabra y       *
//						verifica si esa palabra rima con alguna otra *
//						palabra en el diccionario. Despliega las     *
//						palabras con las cual rima y la cantidad     *
//						de ellas encontradas.                        *
//													                 *
//********************************************************************

// Instrucciones al pre-procesador
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main()
{

    // Definicion de variables
    string terminacion, palabra ;
    int contador = 0 ;
    int palabraLength = 0 ;
    int terminacionLength = 0 ;

    // Dejarle saber al usuario que intentamos acceder un archivo
    cout << "Abriendo el archivo diccionario... " << endl ;

	// Intentar de abrir el archivo soloPalabras.txt para ser leido
    ifstream inputFile("soloPalabras.txt") ;

	// Dejarle saber al usuario si la apertura del archivo fue o no exitosa
    if (inputFile) cout << "El archivo diccionario ha sido abierto!" << endl << endl ;
    else {
        cout << "Error! No se pudo abrir el archivo diccionario! Abortando... " << endl ;
		// Si el archivo no se pudo abrir, salimos del programa ya que no podemos hacer mucho sin el archivo...
        return 1 ;
    }

    cout << "Escriba canciones al estilo Calle 13!!" << endl << endl ;

    // Pedirle al usuario un STRING con el cual buscamos palabras en el archivo,
	// palabras que rimen con él
    cout << "Entre una terminacion de palabra --> " ;
    cin >> terminacion ;

	// Necesitamos saber el largo del STRING dado para luego determinar si la rima
	// corresponde al final de la palabra encontrada (no, por ejemplo, al principio)
    terminacionLength = terminacion.length() ;

    cout << endl << "Palabras que riman con \"" << terminacion << "\":" << endl ;

	// Mientras existan lineas en el archivo...
	while (inputFile >> palabra) {
		// Necesitamos saber el largo del STRING encontrado para luego determinar
		// si la rima corresponde al final de la palabra encontrada
		palabraLength = palabra.length() ;

		// Si dentro de la palabra encontrada se encuentra la secuencia de caracteres
		// dados por el usuario Y TAMBIEN estan al final de la palabra...
		if (palabra.find(terminacion, palabraLength - terminacionLength ) != -1) {

			// Entonces desplegamos la palabra y dejamos una linea en blanco para
			// la proxima (si hay)
			cout << palabra << endl ;

			// Incrementos el contador para llevar cuenta de cuantas palabras
			// que rimen hemos encontrado
			contador++ ;
		}
	}

	// Desplegar la cantidad de palabras encontradas
    cout << "=============================" << endl
         << "Un total de " << contador << " palabras." << endl ;

    // Cerramos el archivo
    inputFile.close() ;
    return 0 ;
}
