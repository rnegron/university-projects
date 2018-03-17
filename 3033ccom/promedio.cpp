//********************************************************************
//                                                                   *
//   Programador : Raúl Negrón          CCOM 3033 Sección 001        *
//   Num. Est.   : 801-13-4680          Segundo Semestre 2013-14     *
//   Asignacion 6                       Prof. Rafael J. Colorado     *
//   Archivo     : promedio.cpp         Fecha : Marzo 4, 2014        *
//                                                                   *
//********************************************************************
//                                                                   *
//    Proposito :	Este programa le pide al usuario un valor        *
//                  inicial, el cual representa la cantidad de	     *
//                  datos que el programa va a permitir entrada.     *
//                  El usuario luego podra entrar estos datos,       *
//                  y mientras los entra se va llevando cuenta       *
//                  de la sumatoria de estos datos numericos.        *
//                  Luego, se calcula la media aritmetica de         *
//                  los valores entrados por el usuario usando       *
//                  la ecuaccion (s / n), donde n es la cantidad     *
//                  de valores y s es la sumatoria de los valores.   *
//                  Al final, se despliega esta media aritmetica     *
//													                 *
//********************************************************************


#include <iostream>
using namespace std ;

#include <iomanip> // necesario para setprecision y setw
int main()
{

    // Definición de variables
    double promedio    ; // contiene el valor dado por (sumatoria / cantidad)
    int cantidad       ; // contiene el valor que el usuario entra como la cantidad de valores que desea entrar
    int contador       ; // no es inicializado porque luego tomara el valor de la variable cantidad
    double nuevoNumero ; // contiene el mas reciente numero dado por el usuario
    double sumatoria = 0  ; // contiene el valor de la suma de todos los numeros dados por el usuario

    // Desplegamos el proposito del programa al usuario
    cout << "\t Este programa, dado la cantidad de datos,\n"
         << "\t pide al usuario valores numericos hasta que\n"
         << "\t hallan tantos valores como la cantidad dada.\n\n"
         << "\t Luego, calcula la sumatoria de los valores y \n"
         << "\t tambien el promedio (o media aritmetica)." << endl << endl ;

   // Solicitar al usuario la cantidad de datos
   cout << "Cuantos datos desea entrar? --> " ;
   cin >> cantidad ;

   if (cantidad <= 0)
    do {
        cout << "Error! Favor de entrar una cantidad positiva!" << endl ;
        cout << "Cuantos datos desea entrar? --> " ;
        cin >> cantidad ;
    } while (cantidad <= 0) ;

    // Creamos una variable para contar hacia abajo sin afectar la cantidad original
    contador = cantidad ;

   // Leer los datos y continuar con la sumatoria
   while (contador > 0)
   {
       cout << "Entre un dato numerico --> " ;
       cin >> nuevoNumero ;
       sumatoria += nuevoNumero ;
       contador-- ;
   }

   // Calcular la media aritmetica
   promedio = sumatoria / static_cast<double>(cantidad) ;

   // Modificar los datos de salida
   cout << setprecision(2) << fixed ;


   // Desplegar media aritmetica resultados
   cout << "\n\n\t <<< RESULTADO >>>" << endl ;
   cout << "El promedio de sus datos es = " << setw(6) << promedio << endl ;
    return 0;
}
