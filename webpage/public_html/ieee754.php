<?php

$bitsUsuario             = 0;
$numUsuario              = 0;
$ieeeSigno               = 1; 
$ieeeExponente 	         = 0;
$ieeeMantisa             = 0;
$largoExponenteUsuario   = 0;
$largoMantisaUsuario     = 0;
$biasUsuario             = 0;
$check                   = False;

function convertir($convertirNum) 
{	
	if (abs($convertirNum) == 1) {
		$listaBinaria[] = 1;
		return $listaBinaria;
	} 
	$listaBinaria[] = (int)($convertirNum % 2);
	$cociente = floor($convertirNum / 2);
	
	while ($cociente != 1) {
		$listaBinaria[] = (int)($cociente % 2);
		$cociente = floor($cociente / 2);
	} 
	
	$listaBinaria[] = $cociente % 2;

	$listaBinariaReversed = array_reverse($listaBinaria);

	return $listaBinariaReversed;
}

function multMantisa($numeroDecimal, $veces) 
{
	$i = 0;
	if ($veces != 0) {
	
		while ($i < $veces) {
			
			$numeroDecimal = $numeroDecimal * 2;
			$tmpLista[] = floor($numeroDecimal);

			if (floor($numeroDecimal) == 1) {
			
				$numeroDecimal = $numeroDecimal - 1;
			}
			$i++;
		}
	 } 
	 return $tmpLista;
}


function findFirstOne($numeroDecimal)
{
	$counter = 0;

	while (floor($numeroDecimal) != 1) {
		$numeroDecimal = $numeroDecimal * 2;
		$counter++;

	} return $counter;
}

function bitWork($bitsUsuario)
{
	global $largoExponenteUsuario, $largoMantisaUsuario, $biasUsuario;

	$bitsUsuario = (int)$bitsUsuario;

	if ($bitsUsuario       == 16) {
		
			$largoExponenteUsuario = 5;
			$largoMantisaUsuario   = 10;
			$biasUsuario           = 15;

	} elseif ($bitsUsuario == 32) {
	
		$largoExponenteUsuario     = 8;
		$largoMantisaUsuario       = 23;
		$biasUsuario               = 127;
	
	} elseif ($bitsUsuario == 64) {
	
		$largoExponenteUsuario     = 11;
		$largoMantisaUsuario       = 52;
		$biasUsuario               = 1023;
	}
}

function doneComputingBinary()
{
	global $numUsuario, $bitsUsuario, $ieeeSigno, $ieeeExponente, $ieeeMantisa;

	echo $ieeeSigno;
	foreach($ieeeExponente as $bits){
		echo $bits;
	
	} foreach($ieeeMantisa as $bits){
		echo $bits;
	}
}


function doneComputingZero()
{
	global $bitsUsuario;
	$i = 0;

	while ($i < $bitsUsuario) {
	    echo "0"; $i++;
	}
}

function goStartBinary()
{
	global $bitsUsuario, $numUsuario, $ieeeSigno, $ieeeExponente, $ieeeMantisa, $biasUsuario, $largoExponenteUsuario, $largoMantisaUsuario, $check;

	$numUsuario = $_POST['num'];

	if (is_numeric($numUsuario) == False) {
		echo "Please enter numeric values only";
		$check = True;
	}

	$bitsUsuario = 32;

	if ($bitsUsuario != 16 and $bitsUsuario != 32 and $bitsUsuario != 64) {
		echo "Please enter a number in 32 bits.";
		$check = True;

	} if ($numUsuario < 0) {
		$ieeeSigno = 1;

	} else {
		$ieeeSigno = 0;
	}

	$tmpNum = abs($numUsuario);

	if (floor($tmpNum) != 0 and $check != True)
	{	
		bitWork($bitsUsuario);
		$enteroEnBin = convertir(floor($tmpNum));
		$ieeeExponente = count($enteroEnBin) - 1;
		$ieeeMantisa = array_slice($enteroEnBin, 
				count($enteroEnBin) - $ieeeExponente);
		$ieeeExponente = convertir($ieeeExponente + $biasUsuario);
	
		if (count($ieeeExponente) < $largoExponenteUsuario) {

			while (count($ieeeExponente) < $largoExponenteUsuario) {
				array_unshift($ieeeExponente, 0);
			}

		} if (count($ieeeMantisa) < $largoMantisaUsuario) {

		
			$extraMantisa = multMantisa($tmpNum - floor($tmpNum),
				     $largoMantisaUsuario - count($ieeeMantisa));
			$ieeeMantisa = array_merge($ieeeMantisa, $extraMantisa);

		} elseif (count($ieeeMantisa) > $largoMantisaUsuario) {

			$ieeeMantisa = array_slice($ieeeMantisa, 0, $largoMantisaUsuario);
		}

		doneComputingBinary();
		$numUsuario  = 0;
		$bitsUsuario = 0;
	}

	  elseif (floor($tmpNum) == 0 and $check != True) {
		bitWork($bitsUsuario);

		if (2 * $tmpNum == 0) {
			doneComputingZero();
			$check = True;
		} elseif ($check != True) {

		$primerUno = findFirstOne($tmpNum);
	
		$ieeeExponente = convertir($biasUsuario - $primerUno); 
		
		} while (count($ieeeExponente) < $largoExponenteUsuario){
			array_unshift($ieeeExponente, 0);
		}

		$ieeeMantisa = multMantisa($tmpNum, $largoMantisaUsuario + $primerUno);
		$ieeeMantisa = array_slice($ieeeMantisa, $primerUno);
		doneComputingBinary();
		$numUsuario = 0;
		$bitsUsuario = 0; 	
	}
}

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

	$i = 1;
	$sum = 0;
		
	foreach($mantisa as $bit) {
		if ($bit == 1) {
			$sum += pow(2, -$i);
		}
		$i++;
	}
	
	$sum += 1;
	$sum *= pow(2, $ieeeExponente);
	$ieeeMantisa = $sum;
	doneComputingReverse();
}

function doneComputingReverse()
{
	global $ieeeSigno, $ieeeMantisa;
	if (isset($_POST['checkround'])) {
		echo round($ieeeMantisa * $ieeeSigno, 2);
	} else {
		echo $ieeeMantisa * $ieeeSigno;
	}
	return 0;
}

function goStartReverse()
{	
	global $numUsuario, $bitsUsuario;
	$numUsuario = $_POST['num'];
	$bitsUsuario = strlen($numUsuario);
	if ($bitsUsuario != 32 and $bitsUsuario != 16 and $bitsUsuario != 64) {
		echo "Please enter a number in 32 bits.";
	}

	else {
		$verificacion = stringCheck($numUsuario); 
		if ($verificacion == "Error") {
			echo "\nPlease enter only binary numbers (0s and 1s).";
		}
	}
}

if (isset($_POST['binary'])) {
	goStartBinary();

} else if (isset($_POST['decimal'])) {
	goStartReverse();

} else {
	echo "Error!";
}

?>