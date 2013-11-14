<?php

/*	

This program follows the PEAR coding standards for PHP (pear.php.net/manual/en/standards.php)

TODO restrict the range

*/

// LISTA DE VARIABLES GLOBALES
$numUsuario              = 0;
$bitsUsuario             = 0;
$ieeeSigno               = 0;
$ieeeExponente           = 0;
$ieeeMantisa             = 0;
$largoExponenteUsuario   = 0;
$largoMantisaUsuario     = 0;
$biasUsuario             = 0;

// Esta funcion convierte un numero en base 10 a un numero en base 2
function convertir($convertirNum) // los argumentos: el numero que deseamos convertir a binario
{

	$listaBinaria[] = (int)($convertirNum % 2); // los valores de la lista son residuos de el numero escojido entre 2
	$cociente = floor($convertirNum / 2); // $cociente siempre contiene el resultado de la division mas reciente
	
	while ($cociente != 1) { // mientras $cociente no sea 1, todavia se puede achicar mas con division
		$listaBinaria[]   = (int)($cociente % 2); // continuar llenando la lista binaria
		$cociente         = floor($cociente / 2); // continuar dividiendo aun mas 

	} $listaBinaria[]     = $cociente % 2; // luego de que $cociente sea 1, solo necesitamos un residuo mas

	$listaBinariaReversed = array_reverse($listaBinaria); // invertir la lista original (ir de atras hacia alfrente)

	return $listaBinariaReversed; // devolvemos el numero en el orden correcto y con suficientes bits
}

// Esta funcion fue creada para multiplicar por 2 y guardar el resultado en una lista una cierta cantidad de veces
function multMantisa($parteDecimalFunc, $veces) // los argumentos: la parte decimal del numero que el usuario entro, cuantas veces necesita ser multiplicado
{
	$i = 0; // contador
	if ($veces != 0) { // si se necesita multiplicar por lo menos 1 vez...
	
		while ($i < $veces) { // mientras el contador sea menor que las veces...
			
			$parteDecimalFunc = $parteDecimalFunc * 2; // multiplicar por dos
			$tmpLista[] = floor($parteDecimalFunc); // añadir el primer digito a la lista

			if (floor($parteDecimalFunc) == 1) { // si el primer digito es "1"
			
				$parteDecimalFunc = $parteDecimalFunc - 1; // eliminar el "1" para continuar con la parte decimal
			}
			$i++; // incrementar el contador
		}
	 } 
	 return $tmpLista; // devolvemos la lista que contiene la ultima parte de $ieeeMantisa
}


// esta funcion fue creada para encontrar la primera occurencia del numero "1"
function findFirstOne($numeroDecimal)
{
	$counter = 0; // inicializar el contador

	while (floor($numeroDecimal) != 1) { // mientras no haya un numero entero....
		$numeroDecimal = $numeroDecimal * 2; // multiplicar el numero decimal por 2
		$counter++; // incrementar el contador cada vez

	} return $counter; // devolver cuantas veces fue necesario multiplicar para llegar a un numero entero
}

// esta funcion recibe un numero tipo int, basado en el valor de este modifica otras variables que afectan la precision de la conversion
function bitWork($bitsUsuario)
{
	global $largoExponenteUsuario, $largoMantisaUsuario, $biasUsuario;

	$bitsUsuario = (int)$bitsUsuario; // asegurarnos que estamos trabajando con una variable tipo int

	if ($bitsUsuario       == 16) { // modificar variables para binary16
		
			$largoExponenteUsuario = 5;
			$largoMantisaUsuario   = 10;
			$biasUsuario           = 15;

	} elseif ($bitsUsuario == 32) { // modificar variables para binary32
	
		$largoExponenteUsuario     = 8;
		$largoMantisaUsuario       = 23;
		$biasUsuario               = 127;
	
	} elseif ($bitsUsuario == 64) { // modificar variables para binary64
	
		$largoExponenteUsuario     = 11;
		$largoMantisaUsuario       = 52;
		$biasUsuario               = 1023;
	}
}

// essta funcion es la que despliega el resultado de las previas funciones y algoritmos utilizando el valor de las variables globales que fueron modificadas
function doneComputing()
{
	global $numUsuario, $bitsUsuario, $ieeeSigno, $ieeeExponente, $ieeeMantisa;

	echo "\n--------------------\n"; // por cuestiones de estetica

	// desplegar el resultado final
	echo $numUsuario." en IEEE 754 binary$bitsUsuario es: ".$ieeeSigno."|";
	foreach($ieeeExponente as $bits){
		echo $bits;
	} echo "|";

	foreach($ieeeMantisa as $bits){
		echo $bits;

	// lo mismo que el bloque de codigo anterior, pero ahora sin los "|" entre las variables
	// esto es util para poder "copy-paste" el numero y probarlo en mi segundo programa, el convertidor de IEEE754 a base 10
	} echo "\nForma alterna para utilizar en el re-convertidor: ";
	echo $ieeeSigno;

	foreach($ieeeExponente as $bits){
		echo $bits;
	
	} foreach($ieeeMantisa as $bits){
		echo $bits;

	} echo "\n--------------------\n"; // por cuestiones de estetica
}

// esta funcion corre cuando el usuario intenta convertir el numero 0 a binario, es un tipo de handler para esta excepccion
function doneComputingZero()
{
	global $bitsUsuario; // depende de cuanta precision el usuario quiera, desplegamos mas 0s mientras mayor precision (para mantener el estilo)
	$i = 0; // inicializar el contador

	echo "0 en IEEE 754 binary$bitsUsuario es: ";
	while ($i < $bitsUsuario) {
	    echo "0"; $i++; // mientras todavia exista diferencia entre el contador y la precision, acercar el contador a $bitsUsuario
	
	} echo "\n"; 
}

// en esta funcion trabajamos el aspecto interactivo. Aqui recojemos los parametros necesarios para la conversion
function goStart()
{
	global $bitsUsuario, $numUsuario, $ieeeSigno, $ieeeExponente, $ieeeMantisa, $biasUsuario, $largoExponenteUsuario, $largoMantisaUsuario;

	echo "Dame un numero: ";
	$numUsuario = trim(fgets(STDIN)); // guardar el valor entrado en la varibale $numUsuario

	if (is_numeric($numUsuario) == False) { // si el valor entrado por el usuario no es un numero, dejarle saber y re-empezar la funcion

		echo "Por favor entra un valor numerico.\n\n";
		$numUsuario  = 0;
		goStart();
	}

	echo "\nAhora los bits: ";
	$bitsUsuario = trim(fgets(STDIN)); // guardar el valor entrado en la variable $bitsUsuario


	if (is_numeric($bitsUsuario) == False) // si el valor entrado por el usuario no es un numero, dejarle saber y re-empezar la funcion
	{
		echo "Por favor entra un valor numerico.\n\n";
		$bitsUsuario = 0;
		$numUsuario  = 0;
		goStart();
	}

	elseif ($bitsUsuario != 16 and $bitsUsuario != 32 and $bitsUsuario != 64) // si el usuario escojio bits que no son 16, 32 o 64, dejarle saber y re-empezar
	{
		echo "Por favor entre solo 16, 32 o 64.\n\n";
		$numUsuario  = 0;
		$bitsUsuario = 0;
		goStart();
	}

	// desde aqui comenzamos a trabajar el numero
	elseif ($numUsuario < 0) { // si el numero es menor que 0 (negativo), entonces el primer digito de la representacion IEEE754 sera [1]
		$ieeeSigno = 1;

	} else { // si el numero es mayor que 0 (positivo), entonces el primer digito de la representacion IEEE754 sera [0]
		$ieeeSigno = 0;
	}

	$tmpNum = abs($numUsuario); // ya que sabemos el signo del numero, lo convertimos a positivo utilizando el valor absoluto

	// ----------------------------------- SI hay una parte entera en el numero del usuario -----------------------------------
	if (floor($tmpNum) != 0)
	{
		bitWork($bitsUsuario); // llamamos a una funcion que va a organizar ciertas variables globales que dependen de la cantidad de bits que el usuario quiere

		$enteroEnBin = convertir(floor($tmpNum)); // con esto, convertimos la parte entera (usando floor()) del numero entrado a binario

		$ieeeExponente = count($enteroEnBin) - 1; // el exponente sera el largo de la lista creada - 1

		if (count($enteroEnBin) >= $largoMantisaUsuario) { // si el largo de la lista ya se pasa del largo de la mantisa (depende de los bits)...
			// pues la mantisa puede ser esa misma lista, pero desde el indice 0 hasta el esperado largo de la mantisa (depende de los bits)
			$ieeeMantisa = array_slice($enteroEnBin, 0, $largoMantisaUsuario);

		} else { // pero si la lista todavia no se pasa, pues la mantisa comienza desde el indice [largo de la lista previa - exponente]
		
			$ieeeMantisa = array_slice( $enteroEnBin,  // primer argumento: la lista del numero entero convertido a binario
				count($enteroEnBin) - $ieeeExponente); // segundo argumento: el largo de esa lista menos el valor del exponente
		}

		$ieeeExponente = convertir($ieeeExponente + $biasUsuario); // ya terminamos de utilizar el exponente como tipo int, ahora lo convertimos a binario

		if (count($ieeeExponente < $largoExponenteUsuario)) { // si el exponente (en binario) es muy corto (depende de los bits)...

			while (count($ieeeExponente) < $largoExponenteUsuario) {array_unshift($ieeeExponente, 0);} 
		
		} if (count($ieeeMantisa) < $largoMantisaUsuario) {

			$extraMantisa = multMantisa($tmpNum - floor($tmpNum), $largoMantisaUsuario - count($ieeeMantisa)); 
			$ieeeMantisa = array_merge($ieeeMantisa, $extraMantisa);
		}

		// llamamos a la funcion final para que despliegue los resultados y revertimos las variables que el usuario entro hacia 0
		doneComputing();
		$numUsuario  = 0;
		$bitsUsuario = 0;
	}

	//  ----------------------------------- NO hay una parte entera en el numero del usuario -----------------------------------
	elseif (floor($tmpNum) == 0)
	{
		bitWork($bitsUsuario); // llamamos a una funcion que va a organizar ciertas variables globales que dependen de la cantidad de bits que el usuario quiere

		if (2 * $tmpNum == 0) { 
			doneComputingZero(); 
	
		} else {

		$primerUno = findFirstOne($tmpNum);
		$ieeeExponente = convertir($biasUsuario - $primerUno);

		while (count($ieeeExponente) < $largoExponenteUsuario){
			array_unshift($ieeeExponente, 0);
		}

		$ieeeMantisa = multMantisa($tmpNum, $largoMantisaUsuario + $primerUno);

		$ieeeMantisa = array_slice($ieeeMantisa, $primerUno);

		// llamamos a la funcion final para que despliegue los resultados y revertimos las variables que el usuario entro hacia 0
		doneComputing();
		$numUsuario = 0;
		$bitsUsuario = 0; }	
	}
}

goStart(); // comenzamos el programa, rapidamente llamamos a la funcion que contiene el codigo central

// para que el programa se vea mejor al terminar
echo "\n-Programa llego al final del codigo-\n"; 


?>