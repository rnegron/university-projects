//                                                                   *
//   Programador : Raúl Negrón          CCOM 3033 Sección 001        *
//   Num. Est.   : 801-13-4680          Segundo Semestre 2013-14     *
//   Asignación 7                       Prof. Rafael J. Colorado     *
//   Archivo     : notapromedio.cpp     Fecha : Marzo 18, 2014       *
//                                                                   *
//********************************************************************
//                                                                   *
//    Proposito :	Este programa lee un archivo que contiene 4      *
//					valores por cada linea: un número de estudiante  *
//					y tres puntuaciones que representan 3 exámenes.  *
//					Luego de leer esta información, graba en un      *
//					archivo nuevo la misma información pero le       *
//					añade el promedio y la nota obtenida basada      *
//					en el promedio a cada linea.                     *
//********************************************************************
#include <iostream>
#include <fstream> // necesario para ifstream y ostream
#include <iomanip> // necesario para setprecision() y setw()
#include <windows.h> // necesario para system("pause")

using namespace std ;

int main() {

	// Declaracion de variables
    ifstream inputFile("examenes.txt") ;    // se inicializa el archivo que contiene la informacion
    ofstream outputFile("resultados.txt") ; // se inicializa el archivo al cual escribiremos
    string numDeEstudiante ;
    char notaFinal ;
    int sumatoria = 0 ;
	int exam ;
    double promedio = 0 ;


    // Crear el encabezamiento
    cout << "#_ESTUDIANTE"
         << setw(12) << "EXAMEN1"
         << setw(12) << "EXAMEN2"
         << setw(10) << "EXAMEN3"
         << setw(12) << "PROMEDIO"
         << setw(10) << "NOTA" << endl << endl ;

      outputFile << "#_ESTUDIANTE"
         << setw(12) << "EXAMEN1"
         << setw(12) << "EXAMEN2"
         << setw(10) << "EXAMEN3"
         << setw(12) << "PROMEDIO"
         << setw(10) << "NOTA" << endl << endl ;

	// Este loop termina cuando se llegue al final del archivo
    while(inputFile >> numDeEstudiante) {

		// Se despliega el primer valor obtenido en la linea (el # de estudiante)
		// y tambien se graba al archivo
        cout       << numDeEstudiante << " " ;
        outputFile << numDeEstudiante << " " ;

		// Los proximos 3 datos son las notas
        for (int i = 1 ; i <= 3 ; i++) {
			// Accedemos la nota, la desplegamos y grabamos
            inputFile >> exam ;

            cout       << setw(10) << exam << " " ;
            outputFile << setw(10) << exam << " " ;

			// Siempre llevamos cuenta de la suma de las notas para calcular el promedio
			// el tercer valor es el examen final, que vale por dos examenes parciales
            if (i == 3) sumatoria += exam * 2 ;
            else sumatoria += exam ;
        }

		// Se calcula el promedio basado en la sumatoria de las notas entre 4
        promedio = sumatoria / 4.0 ;

		// Se despliega y se graba el promedio
        cout       << setw(10) << promedio << " " ;
        outputFile << setw(10) << promedio << " " ;

		// Volvemos el valor de la sumatoria a 0 para la proxima iteracion
        sumatoria = 0 ;

		// Se calcula la nota basada en el promedio
        switch (static_cast<int>(promedio) / 10) {
            case 10: case 9: notaFinal = 'A' ;
                    break ;
            case 8: notaFinal = 'B' ;
                    break ;
            case 7: notaFinal = 'C' ;
                    break ;
            case 6: notaFinal = 'D' ;
                    break ;
            default: notaFinal = 'F' ;

        }

		// Se despliega la nota y podemos continuar a la proxima linea (si hay)
        cout       << setw(10) << notaFinal << endl ;
        outputFile << setw(10) << notaFinal << endl ;
    }
	
	// Detener la pantalla
    system("pause") ;

    return EXIT_SUCCESS ;
}
