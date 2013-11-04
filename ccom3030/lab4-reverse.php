<?php

/*
Todo list:

Make it work with binary32 and binary64 (the framework is there I believe)


*/


$startLoopBits = True;
$startLoopNum = True;

$bitsUsuario = 0;

$ieeeSigno = 1;
$ieeeExponente = 0;
$ieeeMantisa = 0;

function base2_a_base10($numeroBinario)
{	
	$numeroBinario = (int)$numeroBinario;
	return base_convert($numeroBinario, 2, 10); // PLACEHOLDER LOL
}

function string_check($stringNumero)
{
	$testArray = str_split($stringNumero);

	foreach($testArray as $char)
	{
		$char = (int)$char;
		if ($char == 1 or $char == 0)
		{
			echo "\nPass!"; // debug
		}
		else
		{
			return "Error";
		}
	}

	list_work($testArray);
}

function list_work($listaNumeroVerificado)
{	
	global $ieeeSigno, $ieeeExponente, $ieeeMantisa, $bitsUsuario;
	
	$signo = $listaNumeroVerificado[0];
	if ($signo == 1){$ieeeSigno = -1;}

	if ($bitsUsuario == 16)
	{	
		$exponente = array_slice($listaNumeroVerificado, 1, 5);
		$exponenteString = "";
		foreach ($exponente as $bit)
		{
			$exponenteString = $exponenteString.$bit;
		}
		echo "\nel array slice del exponente dio: ".$exponenteString."\n"; // debug
		$exponente = base2_a_base10($exponenteString); 
		echo "\nLa conversion a base 10 fue: ".$exponente."\n"; // debug
		$ieeeExponente = $exponente - 15;
		echo "\nLuego de quitar el bias, el exponente dio: ".$ieeeExponente."\n"; // debug

		$mantisa = array_slice($listaNumeroVerificado, 6, 17);
		
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

		done_computing();
	}

	elseif ($bitsUsuario == 32)
	{
		$exponente = array_slice($listaNumeroVerificado, 1, 8);
		$exponenteString = "";
		foreach ($exponente as $bit)
		{
			$exponenteString = $exponenteString.$bit;
		}
		echo "\nel array slice del exponente dio: ".$exponenteString."\n"; // debug
		$exponente = base2_a_base10($exponenteString); 
		echo "\nLa conversion a base 10 fue: ".$exponente."\n"; // debug
		$ieeeExponente = $exponente - 127;
		echo "\nLuego de quitar el bias, el exponente dio: ".$ieeeExponente."\n"; // debug

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

		done_computing();
	}



	elseif ($bitsUsuario == 64)
	{
		$exponente = array_slice($listaNumeroVerificado, 1, 11);
		$exponenteString = "";
		foreach ($exponente as $bit)
		{
			$exponenteString = $exponenteString.$bit;
		}
		echo "\nel array slice del exponente dio: ".$exponenteString."\n"; // debug
		$exponente = base2_a_base10($exponenteString); 
		echo "\nLa conversion a base 10 fue: ".$exponente."\n"; // debug
		$ieeeExponente = $exponente - 1023;
		echo "\nLuego de quitar el bias, el exponente dio: ".$ieeeExponente."\n"; // debug
	}

}

function done_computing()
{
	global $ieeeSigno, $ieeeMantisa;
	echo "\n--------------------------\n";
	echo "El resultado: ";
	echo $ieeeMantisa * $ieeeSigno;
	echo "\n\n";
	return 0;
}

function go_start()
{
	global $startLoopNum, $startLoopBits, $bitsUsuario;

	while ($startLoopBits)
	{
		echo "Cuantos bits?: ";
		$bitsUsuario = trim(fgets(STDIN));

		if (is_numeric($bitsUsuario) == False) {echo "\nPor favor entre un valor numerico.\n\n"; go_start();}

		$bitsUsuario = (int)$bitsUsuario;

		if ($bitsUsuario == 16 or $bitsUsuario == 32 or $bitsUsuario == 64){$startLoopBits = False;}
		else{echo "\nPor favor escoja entre 16, 32 o 64 bits.\n";}
	}

	while ($startLoopNum)
	{
		echo "Entra el numero (en formato IEEE754): ";
		$numUsuario = trim(fgets(STDIN));

		if (is_numeric($numUsuario) == False) {echo "\nPor favor entre un valor numerico.\n"; $startLoopBits = True; go_start();}

		if ($bitsUsuario == 16 and strlen($numUsuario) == 16){$startLoopNum = False;}
		elseif ($bitsUsuario == 32 and strlen($numUsuario) == 32){$startLoopNum = False;}
		elseif ($bitsUsuario == 64 and strlen($numUsuario)== 64){$startLoopNum = False;}

		else {echo "Error, por favor verifique el largo de su numero comparado a los bits escojidos.\n\n"; $startLoopBits = True; go_start();}

		$verificacion = string_check($numUsuario);

		if ($verificacion == "Error")
		{
			echo "\nPor favor entre la lista del numero en formato binario (0s y 1s).\n"; $startLoopBits = True; $startLoopNum = True;
			go_start();
		}

	}

}

go_start();

?>