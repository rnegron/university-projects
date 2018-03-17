<?php

/*
Raul Negron Otero 801-13-xxxx
Programa: ieee754_reverse.php

Este programa convierte un numero en representacion IEEE754 a un numero en representacion decimal (de IEEE754 binario a base 10). El programa
le pide al usuario los bits del numero que desea convertir, y luego el numero en si. Luego de recibir estos dos inputs, verifica que los
parametros esten de acuerdo (ej. que el largo del numero sea igual que el valor de los bits). Entonces convierte el numero en representacion
IEEE754 a uno en base 10. 

Ej. Input: bits = 32
		   numero = 11000010100000101010100111111011
	Output: -65.331993103027 

Variables:

$bitsUsuario = contiene el valor que el usario entra, especifica el largo del numero que desea convertir
$ieeeSigno =  contiene 1 si el numero dado por el usuario es positivo, -1 si es negativo
$ieeeExponente = contiene el valor final del algoritmo utilizado para encontrar el valor del exponente (incluyendo el bias)
$ieeeMantisa = contiene el valor final del algoritmo utilizado para encontrar cierta precision en el numero (mientras mas bits, mas precision)
$startLoopBits = esta variable sirve como "flag" para continuar repitiendo un loop hasta que su valor cambie
$startLoopNum = esta variable sirve como "flag" para continuar repitiendo un loop hasta que su valor cambie
$stringNumero = contiene el valor del numero entrado por el usuario, en tipo string
$testArray = contiene el valor exacto de $stringNumero, pero esta vez en tipo array
$numeroBinario = contiene una lista cuyo elementos son 0s y 1s
$numeroEnBase10 = contiene el resultado de la conversion de $numeroBinario a base 10
$listaNumeroVerificado = es el array que contiene el numero en representacion IEEE754, luego de ser verificado como correcto
$signo = contiene -1 si el primer elemento en la lista del numero que el usuario entro es 1
$exponente = mientras ocurren los calculos, esta variable contiene informacion sobre el exponente del numero que el usuario entro
$mantisa = contiene el slice de la lista, su largo depende de los bits que el usuario entro
$sum = mientras ocurren los calculos, esta variable contiene informacion sobre la mantisa del numero que el usuario entro
$verificacion = contiene el string "Error" solo si el numero que el usuario entro consiste no solo de 0s y 1s
$numUsuario = esta variable contiene el valor que el usuario entra como input, desea convertir este numero

*/

// Inicializamos las variables globales
$bitsUsuario    = 0;
$ieeeSigno      = 1; // al inicializarlo como 1, no tenemos que cambiar nada si ocurre que el numero que el usuario entra es positivo
$ieeeExponente  = 0;
$ieeeMantisa    = 0;
$startLoopBits  = True;
$startLoopNum   = True;

// esta funcion recibe un string como input y devuelve el string "Error" si encuentra un error, o una lista verificada si no encuentra errores
function stringCheck($stringNumero)
{
	$testArray = str_split($stringNumero); // con esto, convertimos un string a un array directamente

	foreach($testArray as $char) { // por cada elemento del nuevo array..
		$char = (int)$char; // convertimos los elementos en tipos INT
		if ($char != 1 and $char != 0) { // y si no es ni 1 ni 0...
			return "Error"; // pues hay algo mal, ya que valores binarios son siempre 1s o 0s
		}
	}
	listWork($testArray); // si todos los elementos son 1s y 0s, podemos continuar en otra funcion
}

// esta funcion recive una lista llena de 1s y 0s y devuelve la representacion de ese mismo numero, pero en base 10 en vez de base 2
function baseDosABaseDiez($numeroBinario) 
{	
	$numeroBinario = array_reverse($numeroBinario); // comenzamos virando el arreglo
	$numeroEnBase10 = 0; // e inicializando nuestra variable
	$i = 1;	// y nuestro contador

	foreach($numeroBinario as $bit) { // por cada elemento en la lista
		if ($bit == "1") { // si el elemento es el digito 1
			$numeroEnBase10 += pow(2, $i); // pues la variable que tendra el resultado final se ve modificada, sumandole 2 elevado a la (posicion del elemento)
		}
		$i++; // incrementamos el contador
	}
	return $numeroEnBase10 / 2; // el resultado que devolvemos necesitara ser dividido entre 2
}

function listWork($listaNumeroVerificado)
{	
	global $ieeeSigno, $ieeeExponente, $ieeeMantisa, $bitsUsuario;
	
	$signo = $listaNumeroVerificado[0]; // el valor de $ieeeSigno depende del primer elemento en la lista
	if ($signo == 1) { // si este elemento es igual al digito 1...
		$ieeeSigno = -1; // entonces modificamos esta variable para que cambie el signo de nuestro resultado final

	// en este bloque de codigo, tomamos partes de la lista, dependiendo de los bits que el usuario desee. 
	// Por ejemplo, el largo de la variable $exponente cambia dependiendo del valor de $bitsUsuario.
	// Luego de obtener el largo correspondiente, convertimos el exponente a un numero decimal.
	// El bias aplicado es tambien differente segun los bits.
	// Luego, el largo de $mantisa tambien se ve afectado por el valor de $bitsUsuario.
	} if ($bitsUsuario == 16) {
		$exponente = array_slice($listaNumeroVerificado, 1, 5);
		$exponente = baseDosABaseDiez($exponente); 
		$ieeeExponente = $exponente - 15;
		$mantisa = array_slice($listaNumeroVerificado, 6, 17);

	} elseif ($bitsUsuario == 32) {
		$exponente = array_slice($listaNumeroVerificado, 1, 8);
		$exponente = baseDosABaseDiez($exponente);
		$ieeeExponente = $exponente - 127;
		$mantisa = array_slice($listaNumeroVerificado, 9, 33);

	} elseif ($bitsUsuario == 64) {
		$exponente = array_slice($listaNumeroVerificado, 1, 11);
		$exponente = baseDosABaseDiez($exponente);
		$ieeeExponente = $exponente - 1023;
		$mantisa = array_slice($listaNumeroVerificado, 12, 53);
	}

	// inicializamos dos variablos, un contador y el resultado final
	$i = 1;
	$sum = 0;
		
	foreach($mantisa as $bit) { // por cada elemento en la mantisa
		if ($bit == 1) { // si el elemento es 1
			$sum += pow(2, -$i); // pues la variable que tendra el resultado final se ve modificada, sumandole 2 elevado a la negativa (posicion del elemento)
		}
		$i++; // con esta variables llevamos cuenta de la posicion en el arreglo $mantisa
	}
	
	$sum += 1; // nos recordamos del 1 implicito
	$sum *= pow(2, $ieeeExponente); // y del exponente, que siempre estuvo presente
	$ieeeMantisa = $sum; // ahora le pasamos el valor final a una variable global
	doneComputing();
}

// esta funcion es la que despliega el resultado de las previas funciones y algoritmos utilizando el valor de las variables globales que fueron modificadas
function doneComputing()
{
	global $ieeeSigno, $ieeeMantisa;
	echo "\n--------------------------\n"; // por cuestiones de estetica
	echo "El resultado: ";
	echo $ieeeMantisa * $ieeeSigno; // aqui desplegamos nuestro resultado final, multiplicando el numero de la conversion por su signo correspondiente
	echo "\n\n";
	return 0;
}

// en esta funcion trabajamos el aspecto interactivo del programa, recibimos nuestras variables iniciales y verificamos que todo esta correcto con ellas
function goStart()
{
	global $startLoopNum, $startLoopBits, $bitsUsuario;

	while ($startLoopBits) { // mientras $startLoopBits sea cierto...
		echo "Cuantos bits?: "; 
		$bitsUsuario = trim(fgets(STDIN)); // $bitsUsuario = a los bits que el usuario necesite

		if (is_numeric($bitsUsuario) == False) { // si $bitsUsuario no es tan siquiera un numero..
			echo "\nPor favor entre un valor numerico.\n\n"; // desplegamos el error al usuario
			 goStart(); // comenzamos la funcion de nuevo
			}

		$bitsUsuario = (int)$bitsUsuario; // nos aseguramos que estamos trabajando con una variable tipo INT

		if ($bitsUsuario == 16 or $bitsUsuario == 32 or $bitsUsuario == 64) { // siempre y cuando $bitsUsuario sea 16, 32 o 64...
			$startLoopBits = False; // terminamos este loop
		} else { // si no es 16, 32 o 64...
			echo "\nPor favor escoja entre 16, 32 o 64 bits.\n"; // desplegamos el error al usuario
			goStart(); // comenzamos la funcion de nuevo
		}
	}

	while ($startLoopNum) { // mientras $startLoopNum sea cierto...
		echo "Entra el numero (en formato IEEE754): ";
		$numUsuario = trim(fgets(STDIN)); // $numUsuario = al valor que el usuario quiero convertir

		if (is_numeric($numUsuario) == False) { // si $numUsuario no es tan siquiera un numero...
			echo "\nPor favor entre un valor numerico.\n";  // desplegamos el error al usuario
			$startLoopBits = True; // activamos de nuevo el loop de los bits
			goStart(); // comenzamos la funcion de nuevo

			// en este bloque de codigo, verificamos que el largo del valor entrado por el usuario corresponda a los bits escojidos
		} if ($bitsUsuario     == 16 and strlen($numUsuario) == 16) {
			$startLoopNum = False;
		} elseif ($bitsUsuario == 32 and strlen($numUsuario) == 32) { 
			$startLoopNum = False;
		} elseif ($bitsUsuario == 64 and strlen($numUsuario) == 64) {
			$startLoopNum = False;

		} else { // si no corresponden...
			echo "Error, por favor verifique el largo de su numero comparado a los bits escojidos.\n\n"; // desplegamos el error al usuario
			$startLoopBits = True; // activamos de nuevo el loop de los bits
			goStart(); // comenzamos la funcion de nuevo
		}

		$verificacion = stringCheck($numUsuario); // llamamos a la funcion stringCheck, la cual devuelve "Error" si el valor no pasa la prueba	
												  // la prueba verifica si el valor que el usuario entro consiste en 1s y 0s solamente

		if ($verificacion == "Error") { // si ocurre un error en la prueba...
			echo "\nPor favor entre la lista del numero en formato binario (0s y 1s).\n"; // desplegamos el error al usuario
			$startLoopBits = True; // activamos de nuevo el loop de los bits
			$startLoopNum  = True; // activamos de nuevo el loop del numero
			goStart(); // comenzamos la funcion de nuevo
		}
	}
}
goStart(); // comenzamos la funcion por primera vez
echo "\n-Programa llego al final del codigo-\n"; 
?>