<?php

/*	
Todo list:

Make it work with numbers higher than 511 and lower than -511
Make it work with negative numbers without a whole number(ex. -0.028)
*/

// global variables
$numUsuario = 0;
$ieeeSigno = 0;
$ieeeExponente = 0;
$ieeeEntero = 0;
$ieeeMantisa = 0;
$tmpNum = 0;
$tmpLista = 0;
$goNegativeZero = 0; // test this...

// funcion para convertir un numero entero positivo a un numero binario
function convertir($convertirNum) //los argumentos: el numero que deseamos convertir a binario
{
	$listaBinaria[] = (int)($convertirNum % 2); //los valores de la lista son residuos de el numero escojido entre 2
	$cociente = floor($convertirNum / 2); //$cociente siempre contiene el resultado de la division mas reciente
	
	while ($cociente != 1) //mientras $cociente no sea 1, todavia se puede achicar mas con division
		{ 
		$listaBinaria[] = (int)($cociente % 2); //continuar llenando la lista binaria
		$cociente = floor($cociente / 2); //continuar dividiendo aun mas
		} 
		
	$listaBinaria[] = $cociente % 2; //luego de que $cociente sea 1, solo necesitamos un residuo mas

	//mientras no hayan 4 digitos en la lista binaria, add 0s


	$listaBinariaReversed = array_reverse($listaBinaria);
	while (count($listaBinariaReversed) < 5)
	{
		array_unshift($listaBinariaReversed, 0);
	}
	return $listaBinariaReversed;
}

function mult_whole($parteDecimalFunc, $veces)
{
	$i = 0;
	if ($veces != 0)
	{
		while ($i < $veces)
		{	
			$parteDecimalFunc = $parteDecimalFunc * 2;
			$tmpLista[] = floor($parteDecimalFunc);
			if (floor($parteDecimalFunc) == 1)
			{
				$parteDecimalFunc = $parteDecimalFunc - 1;
			}
			$i++;
		}
	}
	
	return $tmpLista;
}

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

function done_computing()
{
	global $numUsuario, $ieeeExponente, $ieeeSigno, $ieeeMantisa;

	// resultados! (de un numero negativo y con numero entero!)
	echo "\n--------------------\n";
	echo $numUsuario." en IEEE 754 binary16 es: ".$ieeeSigno."|";
	foreach($ieeeExponente as $bits){
		echo $bits;
	}
	echo "|";

	foreach($ieeeMantisa as $bits){
		echo $bits;
	}

	echo "\n--------------------\n";

}

function done_computing_zero($signo)
{	
	if ($signo == 1)
	{
		echo "0 en IEEE 754 es: 1|00000|0000000000";
	}

	else 
	{
		echo "0 en IEEE 754 es: 0|00000|0000000000";
	}
	
}

// Preliminary user interface ----------------------------------------- PROGRAM STARTS HERE
echo "Dame un numero: ";
$numUsuario = trim(fgets(STDIN));

if (is_numeric($numUsuario) == False)
{
	echo "Por favor entra un valor numerico.\n";
}

// Aqui verificamos si el numero es muy grande o muy small
elseif ($numUsuario > 65504 or $numUsuario < -65504)
{
	echo "Su numero esta fuera del rango acceptable.\n";
}

// Aqui hacemos trampa y sacamos el 0 positivo y el 0 negativo fuera de las ecuaciones
elseif ($numUsuario == 0)
{
	done_computing_zero(0);
}

elseif ($numUsuario == -0)
{
	done_computing_zero(1);
}
// 

// ----------------------------------- SI hay una parte entera en el numero del usuario -----------------------------------
elseif (abs(floor($numUsuario)) != 0)
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
		$ieeeMantisa = mult_whole(($tmpNum - floor($tmpNum)), 10 - $movidasDelPunto);			
	}


	$ieeeMantisa = array_merge($ieeeEnteroSlice, $ieeeMantisa);

	// llamar a la funcion done_computing para imprimir nuestro resultado!
	done_computing();	
}

// ----------------------------------- NO hay una parte entera en el numero del usuario -----------------------------------
elseif (abs(floor($numUsuario)) == 0)
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
	$ieeeMantisa = mult_whole($tmpNum, 10 + $primerUno);

	echo "ieeeMantisa es: "; foreach($ieeeMantisa as $bits) echo $bits; echo "\n"; // debug

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