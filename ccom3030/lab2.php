<?php
/*
Raul Negron Otero 801-13-4680
Programa: lab2.php

Este programa pide un numero al usuario, luego lo convierte en numero binario por medio de una funcion y
le demuestra al usuario el resultado.

Variables: 
$userNum = lo mismo que $numeroUsuario, pero es una variable local de la funcion naturalAbin
$listaBinaria = almacena el numero binario pero en orden alrevez
$cociente = siempre almacena el resultado mas reciente de una division entre 2
$numeroUsuario = el numero que el usuario provee
$contador = mantiene el largo de la lista en desorden
*/

function naturalAbin($userNum) //esta funcion tiene como argumento un numero
{
	//comenzamos a crear valores en la lista
	$listaBinaria[] = (int)($userNum % 2); //los valores de la lista son residuos de el numero escojido entre 2
	$cociente = floor($userNum / 2); //$cociente siempre contiene el resultado de la division mas reciente
	
	while ($cociente != 1) //mientras $cociente no sea 1, todavia se puede achicar mas con division
		{ 
		$listaBinaria[] = (int)($cociente % 2); //continuar llenando la lista binaria
		$cociente = floor($cociente / 2); //continuar dividiendo aun mas
		} 
		
	$listaBinaria[] = $cociente % 2; //luego de que $cociente sea 1, solo necesitamos un residuo mas
	return $listaBinaria; //devolver el array con todos sus valores
} //la funcion termina

echo "\nPor favor entre un numero: "; //pedimos el numero que desea convertir a binario
$numeroUsuario = trim(fgets(STDIN));
if ($numeroUsuario == 0){echo "\n0 en binario es: 0";} //para el programa no falle si el usuario entra el numero 0
else 
{
	$resultado = naturalAbin($numeroUsuario); //guardar el resultado(un array) de la llamada a la funcion en $resultado
	$contador = count($resultado) - 1; //$contador es el largo de la lista menos 1, count() no considera el 0 como el primero
	echo "\n".$numeroUsuario." en binario es: ";
	while ($contador > -1) //mientras no estemos en el indice 0...
	{ 
		echo $resultado[$contador]; //echo el digito en la posicion $contador
		$contador--; //vamos en orden decendiente
	} 	
}
echo "\n"; //para que se vea mejor el output, una linea nueva
