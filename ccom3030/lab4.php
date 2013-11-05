<?php

/*	
Todo list:

Make it work with numbers higher than 511 and lower than -511
Make -0 work damn it
Busca ADDBITS para encontrar las lineas que necesitan cambio

*/

// global variables
$numUsuario = 0; // el numero que el usuario entra
$bitsUsuario = 0;
$ieeeSigno = 0; // el bit asignado para la representacion del signo (+,-)
$ieeeExponente = 0; // los bits asignados para la representacion del exponente
$ieeeEntero = 0; // variable creada para facilitar conversiones y algoritmos
$ieeeMantisa = 0; // los bits asignados para la representacion de la mantisa
$tmpNum = 0; // variable que contiene el valor absoluto de $numUsuario


// funcion para convertir un numero entero positivo a un numero binario (base 10 a base 2)

function convertir($convertirNum) // los argumentos: el numero que deseamos convertir a binario
{
	$listaBinaria[] = (int)($convertirNum % 2); // los valores de la lista son residuos de el numero escojido entre 2
	$cociente = floor($convertirNum / 2); // $cociente siempre contiene el resultado de la division mas reciente
	
	while ($cociente != 1) // mientras $cociente no sea 1, todavia se puede achicar mas con division
		{ 
		$listaBinaria[] = (int)($cociente % 2); // continuar llenando la lista binaria
		$cociente = floor($cociente / 2); // continuar dividiendo aun mas
		} 
		
	$listaBinaria[] = $cociente % 2; // luego de que $cociente sea 1, solo necesitamos un residuo mas

	$listaBinariaReversed = array_reverse($listaBinaria); // invertir la lista original (ir de atras hacia alfrente)

	// mientras no hayan digitos suficentes (determinados por los bits que se estan trabajando) en la lista binaria, crear mas 0s
	while (count($listaBinariaReversed) < 5) // ADDBITS
	{
		array_unshift($listaBinariaReversed, 0); // este codigo crea un numero "0" en la lista, siempre en el indice [0]
	}

	return $listaBinariaReversed; // devolvemos el numero en el orden correcto y con suficientes bits
}

function mult_mantisa($parteDecimalFunc, $veces) // los argumentos: la parte decimal del numero que el usuario entro, cuantas veces necesita ser multiplicado
{
	$i = 0; // contador
	if ($veces != 0) // si se necesita multiplicar por lo menos 1 vez...
	{
		while ($i < $veces) // mientras el contador sea menor que las veces...
		{	
			$parteDecimalFunc = $parteDecimalFunc * 2; // multiplicar por dos
			$tmpLista[] = floor($parteDecimalFunc); // añadir el primer digito a la lista
			if (floor($parteDecimalFunc) == 1) // si el primer digito es "1"
			{
				$parteDecimalFunc = $parteDecimalFunc - 1; // eliminar el "1" para continuar con la parte decimal
			}

			$i++; // incrementar el contador
		}
	}
	
	return $tmpLista; // devolvemos la lista que contiene la ultima parte de $ieeeMantisa
}

// esta funcion es utilizada cuando no hay un digito en la parte entera del numero que el usuario entra
// intenta encontrar la primera vez que una multiplicacion por 2 lleva a una parte entera
// todo mientras guarda cuenta de cuantas multiplicaciones fueron necesarias para llegar a ese primer "1"

function find_first_one($numeroDecimal)
{
	$counter = 0;

	while (floor($numeroDecimal) != 1)
	{
		$numeroDecimal = $numeroDecimal * 2;
		$counter++;
	}

	return $counter;
}

// esta funcion es llamada cuando ya tenemos los valores de $ieeeSigno, $ieeeExponente y $ieeeMantisa
// es la funcion final; la que despliega el resultado de las funciones previas

function done_computing()
{
	global $numUsuario, $ieeeExponente, $ieeeSigno, $ieeeMantisa;

	// resultados! (de un numero negativo y con numero entero!)
	echo "\n--------------------\n"; // por cuestiones de estetica

	echo $numUsuario." en IEEE 754 binary$bitsUsuario es: ".$ieeeSigno."|";
	foreach($ieeeExponente as $bits){
		echo $bits;
	}
	echo "|";

	foreach($ieeeMantisa as $bits){
		echo $bits;
	}

	// lo mismo que el bloque de codigo anterior, pero ahora sin los "|" entre las variables
	// esto es util para "copy-paste" el numero y probarlo en mi segundo programa, el convertidor de IEEE754 a base 10
	echo "\nForma alterna para utilizar en el re-convertidor: ";
	echo $ieeeSigno;
	foreach($ieeeExponente as $bits){
		echo $bits;
	}
	foreach($ieeeMantisa as $bits){
		echo $bits;
	}

	echo "\n--------------------\n"; // por cuestiones de estetica

}

/// FIX ///
function done_computing_zero()
{	
	global $numUsuario, $bitsUsuario;

	$drainZeros = 0;

	if ($bitsUsuario == 16)
		{
			$exponente = 5;
			$mantisa = 10;
		}

	if (abs($numUsuario == 0){$signo = 0;}
	elseif (floor($numUsuario + 0.1) == -1)){$signo = 1;}

	echo "$numUsuario en IEEE 754 binary$bitsUsuario es: $signo|";
	
}

/// ///

// Preliminary user interface ----------------------------------------- PROGRAM STARTS HERE
echo "Dame un numero: ";
$numUsuario = trim(fgets(STDIN));

if (is_numeric($numUsuario) == False)
{
	echo "Por favor entra un valor numerico.\n";
}

// Aqui verificamos si el numero es muy grande o muy pequeño
elseif ($numUsuario > 65504 or $numUsuario < -65504)
{
	echo "Su numero esta fuera del rango acceptable.\n";
}

// Aqui hacemos trampa y sacamos el 0 positivo y el 0 negativo fuera de las ecuaciones
elseif (abs($num == 0))
{
	done_computing_zero();
}

}
// 

// ----------------------------------- SI hay una parte entera en el numero del usuario -----------------------------------
elseif (abs(round($numUsuario, 0, PHP_ROUND_HALF_DOWN)) != 0)
{

	// Aqui verificamos si el numero es negativo o positivo
	if ($numUsuario < 0){$ieeeSigno = 1;}
	elseif ($numUsuario > 0){$ieeeSigno = 0;}
	else {echo "\nError: El numero no es ni positivo ni negativo...\n";}
	//

	// ya sabemos si es negativo o positivo por $ieeeSigno, volvemos el numero a positivo para trabajarlo
	$tmpNum = abs($numUsuario);

	// convertir la parte entera del numero a binario
	$ieeeEntero = convertir(floor($tmpNum));

	// encontrar donde esta el primero uno en la lista (el punto corre hacia el)
	$primerUno = array_search(1, $ieeeEntero);

	// con esto, "corremos" el 1 (en realidad eliminamos el uno y creamos una lista nueva sin el)
	$ieeeEnteroSlice = array_slice($ieeeEntero, $primerUno + 1);

	// 
	$movidasDelPunto = count($ieeeEnteroSlice);

	//
	$ieeeExponente = (15 + $movidasDelPunto);

	//
	$ieeeExponente = convertir($ieeeExponente);

	// si el largo de la lista de bits es menor que 10...

	if (count($ieeeEntero) < 10)
	{
		// necesitamos llenar la mantisa a 10 espacios
		$ieeeMantisa = mult_mantisa(($tmpNum - floor($tmpNum)), 10 - $movidasDelPunto);			
	}


	$ieeeMantisa = array_merge($ieeeEnteroSlice, $ieeeMantisa);

	// llamar a la funcion done_computing para imprimir nuestro resultado!
	done_computing();	
}

// ----------------------------------- NO hay una parte entera en el numero del usuario -----------------------------------
elseif (abs(round($numUsuario, 0, PHP_ROUND_HALF_DOWN)) == 0)

{	
	// Aqui verificamos si el numero es negativo o positivo
	if ($numUsuario < 0){$ieeeSigno = 1;}	
	elseif ($numUsuario > 0){$ieeeSigno = 0;}
	else {echo "\nError: El numero no es ni positivo ni negativo...\n";
}
	// ya sabemos si es negativo o positivo por $ieeeSigno, volvemos el numero a positivo para trabajarlo
	$tmpNum = abs($numUsuario);

	// encontrar donde esta el primero uno en la lista (el punto corre hacia el)
	$primerUno = find_first_one($tmpNum);

	// llenamos la mantisa con $veces = 10 + cuantas veces fueron necesarias para llegar al primer uno (ya que este sera elimindado...)
	$ieeeMantisa = mult_mantisa($tmpNum, 10 + $primerUno);

	// con esto, "corremos" el 1 (en realidad eliminamos el uno y creamos una lista nueva sin el)
	$ieeeMantisa = array_slice($ieeeMantisa, $primerUno);

	// aplicamos el bias de binary16:(15 - (veces que fue movido el punto hacia el primer uno))
	$ieeeExponente = convertir(15 - $primerUno);	

	// llamar a la funcion done_computing para imprimir nuestro resultado!
	done_computing();
}

else // aqui trabajamos los errores...
{
	echo "\nError! No es ni mayor que 0 ni menor que 0 ni 0...?";
}

// para que el programa se vea mejor al terminar
echo "\n-Programa llego al final del codigo-\n"; 

?>