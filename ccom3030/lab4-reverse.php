<?php

/*
Todo list:

From line 61 onwards, the calculations can be in a separete function (call it finalCalc)
Apply styling guide
Comment the code
*/

// VARIABLES GLOBALES
$bitsUsuario    = 0;
$ieeeSigno      = 1; // al inicializarlo como 1, no tenemos que cambiar nada si ocurre que el numero que el usuario entra es positivo
$ieeeExponente  = 0;
$ieeeMantisa    = 0;
$startLoopBits  = True;
$startLoopNum   = True;

// esta funcion recibe un string como input y 
function stringCheck($stringNumero)
{
	$testArray = str_split($stringNumero);

	foreach($testArray as $char) {
		$char = (int)$char;
		if ($char != 1 and $char != 0) {
			return "Error";
		}
	}

	listWork($testArray);
}

function baseDosABaseDiez($numeroBinario)
{	
	$numeroBinario = array_reverse($numeroBinario);
	$numeroEnBase10 = 0;
	$i = 1;	

	foreach($numeroBinario as $bit) {
		if ($bit == "1") {

			$numeroEnBase10 += pow(2, $i);
		}
		$i++;
	}

	return $numeroEnBase10 / 2;
}

function listWork($listaNumeroVerificado)
{	
	global $ieeeSigno, $ieeeExponente, $ieeeMantisa, $bitsUsuario;
	
	$signo = $listaNumeroVerificado[0];
	if ($signo == 1) {
		$ieeeSigno = -1;

	} if ($bitsUsuario == 16) {
		$exponente = array_slice($listaNumeroVerificado, 1, 5);
		// echo "\nel array slice del exponente dio: ".$exponenteString."\n"; // debug
		$exponente = baseDosABaseDiez($exponente); 
		// echo "\nLa conversion a base 10 fue: ".$exponente."\n"; // debug
		$ieeeExponente = $exponente - 15;
		// echo "\nLuego de quitar el bias, el exponente dio: ".$ieeeExponente."\n"; // debug

		// this can be in a function! the whole next parts
		$mantisa = array_slice($listaNumeroVerificado, 6, 17);
		
		$i = 1;
		$sum = 0;
			
		foreach($mantisa as $bit) {
			if ($bit == 1) {
				$sum += pow(2, -$i);
			}
			$i++;
		}

		// implicit
		$sum += 1;

		$sum *= pow(2, $ieeeExponente);

		$ieeeMantisa = $sum;

		doneComputing();
	}

	elseif ($bitsUsuario == 32)
	{
		$exponente = array_slice($listaNumeroVerificado, 1, 8);
		$exponente = baseDosABaseDiez($exponente);
		// echo "\nLa conversion a base 10 fue: ".$exponente."\n"; // debug
		$ieeeExponente = $exponente - 127;
		// echo "\nLuego de quitar el bias, el exponente dio: ".$ieeeExponente."\n"; // debug

		// this can be in a function!
		$mantisa = array_slice($listaNumeroVerificado, 9, 33);

		$i = 1;
		$sum = 0;
			
		foreach($mantisa as $bit)
		{
			if ($bit == 1)
			{
				$sum += pow(2, -$i);
			}
			$i++;
		}

		// implicit
		$sum += 1;

		$sum *= pow(2, $ieeeExponente);
		$ieeeMantisa = $sum;

		doneComputing();
	}



	elseif ($bitsUsuario == 64)
	{
		$exponente = array_slice($listaNumeroVerificado, 1, 11);
		$exponente = baseDosABaseDiez($exponente);
		// echo "\nel array slice del exponente dio: ".$exponenteString."\n"; // debug 
		// echo "\nLa conversion a base 10 fue: ".$exponente."\n"; // debug
		$ieeeExponente = $exponente - 1023;
		// echo "\nLuego de quitar el bias, el exponente dio: ".$ieeeExponente."\n"; // debug

		// this can be in a function!
		$mantisa = array_slice($listaNumeroVerificado, 12, 53);

		$i = 1;
		$sum = 0;
			
		foreach($mantisa as $bit)
		{
			if ($bit == 1)
			{
				$sum += pow(2, -$i);
			}
			$i++;
		}

		// implicit
		$sum += 1;

		$sum *= pow(2, $ieeeExponente);
		$ieeeMantisa = $sum;

		doneComputing();
	}

}

function doneComputing()
{
	global $ieeeSigno, $ieeeMantisa;
	echo "\n--------------------------\n";
	echo "El resultado: ";
	echo $ieeeMantisa * $ieeeSigno;
	echo "\n\n";
	return 0;
}

function goStart()
{
	global $startLoopNum, $startLoopBits, $bitsUsuario;

	while ($startLoopBits)
	{
		echo "Cuantos bits?: ";
		$bitsUsuario = trim(fgets(STDIN));

		if (is_numeric($bitsUsuario) == False) {echo "\nPor favor entre un valor numerico.\n\n"; goStart();}

		$bitsUsuario = (int)$bitsUsuario;

		if ($bitsUsuario == 16 or $bitsUsuario == 32 or $bitsUsuario == 64){$startLoopBits = False;}
		else{echo "\nPor favor escoja entre 16, 32 o 64 bits.\n";}
	}

	while ($startLoopNum)
	{
		echo "Entra el numero (en formato IEEE754): ";
		$numUsuario = trim(fgets(STDIN));

		if (is_numeric($numUsuario) == False) {echo "\nPor favor entre un valor numerico.\n"; $startLoopBits = True; goStart();}

		if ($bitsUsuario == 16 and strlen($numUsuario) == 16){$startLoopNum = False;}
		elseif ($bitsUsuario == 32 and strlen($numUsuario) == 32){$startLoopNum = False;}
		elseif ($bitsUsuario == 64 and strlen($numUsuario)== 64){$startLoopNum = False;}

		else {echo "Error, por favor verifique el largo de su numero comparado a los bits escojidos.\n\n"; $startLoopBits = True; goStart();}

		$verificacion = stringCheck($numUsuario);

		if ($verificacion == "Error")
		{
			echo "\nPor favor entre la lista del numero en formato binario (0s y 1s).\n"; $startLoopBits = True; $startLoopNum = True;
			goStart();
		}

	}

}

goStart();
echo "\n-Programa llego al final del codigo-\n"; 

?>