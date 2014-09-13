<?php
/*
Raul Negron Otero 801-13-4680
Programa: lab1.php

Este programa pide un numero al usuario, luego lo convierte en numero binario y
le demuestra al usuario el resultado.

Variables: 
$numeroUsuario = el numero que el usuario provee
$listaBinaria = almacena el numero binario pero en orden alrevez
$cociente = siempre almacena el resultado mas reciente de una division entre 2
$contador = mantiene el largo de la lista en desorden
*/

echo "\nPor favor entre un numero: "; //pedimos el numero que desea convertir a binario
$numeroUsuario = trim(fgets(STDIN));
if ($numeroUsuario == 0){echo "\n0 en binario es: 0";} //para el programa no falle si el usuario entra el numero 0
else
{
//comenzamos a crear valores en la lista
$listaBinaria[] = $numeroUsuario % 2; //los valores de la lista son residuos de el numero escojido entre 2
$cociente = floor($numeroUsuario / 2); //$cociente siempre contiene el resultado de la division mas reciente

while ($cociente != 1){ //mientras $cociente no sea 1, todavia se puede achicar mas con division
	$listaBinaria[] = $cociente % 2; //continuar llenando la lista binaria
	$cociente = floor($cociente / 2);} //continuar dividiendo aun mas
	
$listaBinaria[] = $cociente % 2; //luego de que $cociente sea 1, solo necesitamos un residuo mas
echo "\n".$numeroUsuario." en binario es: ";
$contador = count($listaBinaria) - 1; //$contador es el largo de la lista menos 1, ya que la funcion count no considera el 0 como el primero
while ($contador > -1){ //mientras no estemos en el indice 0...
	echo $listaBinaria[$contador]; //demuestra el digito en la posicion $contador
	$contador--;} //vamos en orden decendiente
}
	
echo "\n"; //para que se vea mejor el output, una linea nueva
