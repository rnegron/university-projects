<?php
/*
Raul Negron Otero 801-13-4680
Programa: lab3.php

Este programa le pide al usuario un numero (en base 10). Verifica que lo entrado sea un valor numerico. 
Tambien pide la cantidad de bits y verifica si el valor es numerico y menor de 32. Entonces computa si 
los valores pueden ser trabajados entre si. Lo ultimo que necesita saber es si el valor del numero es 
negativo o positivo. Luego llama a la funcion organizar(), la cual utiliza el resultado de la funcion 
convertir(), que convierte el numero original a un numero binario (el mismo numero en base 2 en vez
de base 10), y se encarga de cambiar el numero binario a la version presentable. Si el numero original
es negativo, 


Variables (en el orden que aparecen): 
$listaDesorganizada = argumento incial de la funcion organizar(), es una lista de 0s y 1s
$contador = mantiene el largo de la lista en desorden
$stringOrganizado = contine los valores de la lista binaria, pero de final a principio
$numero, $userNum = el numero que el usuario provee
$listaBinaria = almacena el numero binario
$cociente = siempre almacena el resultado mas reciente de una division entre 2
$bitCheck = contiene la diferencia entre los bits que el usuario desee y el largo de la lista binaria
$listaDeUno = lista que contiene el valor binario de 1 mas los zeros correspondientes
$sobrantePositivo = contiene la suma del 2 al poder de los bits - 1 y el numero negativo
$convertido = 
$loop = booleano para ayudarme a manejar el input del usuario
$usuarioBits = la cantidad de bits que el usuario desee trabajar (no se pasa de 32)

Bugs conocidos:
Con complemento de dos, 7, -8 y -9 no funcionan en 4 bits. Desconozco porque...
*/

function organizar($listaDesorganizada) //argumentos: una lista de 0s y 1s, los organiza de final a principio
{
	$contador = count($listaDesorganizada) - 1; // las listas tienen indices desde 0 (un valor), pero count() comienza desde 1
	$stringOrganizado = ""; // inicializar un string
	while ($contador >= 0){ //mientras la lista tenga valores:
		$stringOrganizado .= $listaDesorganizada[$contador]; //el valor de la lista en indice $contador es añadido al string
		$contador--;} // vamos de mayor a menor con los indices
	return $stringOrganizado; // devolver el resultado, organizado al fin
}
function convertir($userNum, $userBits) //los argumentos: el numero que deseamos convertir y la cantidad de bits en los cual se representara
{
	$numero = abs($userNum); //asegurarnos de que estamos trabajando con positivos
	$listaBinaria[] = (int)($numero % 2); //el primer valor dado a la lista es el residuo del numero entre 2
	$cociente = floor($numero / 2); //designar una nueva variable que siempre representa la division mas reciente del numero entre 2

	while ($cociente != 1){ //si el cociente es 1, la proxima division sera la ultima que necesitamos
		$listaBinaria[] = (int)($cociente % 2); //continuar añadiendo a la lista binaria el residuo
		$cociente = floor($cociente / 2); //continuar disminuyendo el cociente, aplicando el redondeo hacia abajo
		}
	$listaBinaria[] = (int)($cociente % 2); //un ultimo digito binario es necesario

	$bitCheck = abs($userBits - count($listaBinaria)); //verificar la diferencia entre los bits y el largo de la lista binaria
	while ($bitCheck > 0) //mientras exista una diferencia,
	{
		$listaBinaria[] = 0; //llenar la lista de 0s
		$bitCheck--; //disminuir la diferencia
	}
	return $listaBinaria;
}

function convertirUno($userBits) //argumentos: cuantos bits necesitamos rellenar con 0s
{
	$listaDeUno[] = 1; //al final de la lista (en el ultimo indice) va el digito 1
	while ($userBits > 1) //mientras no llegemos al penultimo indice,
	{
		$listaDeUno[] = 0; //llenar la lista de 0s
		$userBits--; //disminuir el indice
	}
	return organizar($listaDeUno);
}

function complementoDos($userNum, $userBits) //argumentos: el numero que el usario entro y los bits que entro tambien
{
	//ya sabemos que el numero es negativo, necesitamos uno positvo, lo encontramos restando 2^$userbits - (-$userNum)
	$sobrantePositivo = pow(2, $userBits - 1) + $userNum; 
	$convertido = organizar(convertir($sobrantePositivo, $userBits)); //ese sobrante positivo es pasado por el proceso que conversion
	$convertido[0] = "1"; //el digito que corresponde al inidice 0 (el primero) siempre sera 1 cuando trabajamos en complemento de dos
	return $convertido;
}

$loop = True; //con esto mantenemos el control de las opciones dadas al usuario
while ($loop == True){
	echo "\nPor favor entra un numero entero: ";
	$usuarioNum = trim(fgets(STDIN)); //el numero que el usario desea cambiar es recibido y almacenado
	
	//el usuario tiene la libertad de entrar cualquier cosa... pero solo trabajamos numeros
	if (is_numeric($usuarioNum) != True){echo "\nERROR: Solo numeros son permitidos.";} 
	//si entra el digito 0, es sencillo: 0 en cualquier base es 0.
	elseif($usuarioNum == 0){echo "\nEl numero 0 en base 2 es 0!\n";}
	else //ya el numero paso las pruebas preliminares
	{
		echo "\nPor favor entra la cantidad de bits: "; 
		$usuarioBits = trim(fgets(STDIN)); //ahora pedimos los bits para trabajarlos, aqui es almacenada la seleccion
		
		//igual que $usuarioNum, los bits tienen que representar numeros
		if (is_numeric($usuarioBits) != True){echo "\nERROR: Solo numeros son permitidos.";} 
		else
		{
			if ($usuarioBits > 32) //limite de bits escojido por practicalidad
			{echo "\nERROR: No mas de 32 bits.\n";}
			
			elseif ($usuarioBits < 4) //arbitrario, pero es tambien para facilitar la conversion de numeros pequeños
			{echo "\nERROR: No menos de 4 bits.\n";}
			
			elseif (abs($usuarioNum) >= pow(2, $usuarioBits)) //si el numero no se puede representar dentro de los bits, esta fuera de rango
			{echo "\nERROR: Su numero esta fuera de rango.\n";}
			
			//si el numero es 1, solo necesitamos rellenar de 0s, para eso creamos una funcion exclusiva
			elseif($usuarioNum == 1)
			{echo "\n1 en base 2 y ".$usuarioBits." bits es: ".convertirUno($usuarioBits)."\n"; $loop = False;}
			
			//si el numero es menos que 0, llamamos a la funcion para comenzar a convertirlo en complemento de dos
			elseif($usuarioNum < 0)
			
			{echo "\n".$usuarioNum." en complemento de 2 y ".$usuarioBits." bits es: ".complementoDos($usuarioNum, $usuarioBits)."\n\n"; $loop = False;}
			
			
			else //la otra opcion es que el numero sea positivo, entonces llamamos a la funcion estandar para convertirlo a binario
			{echo "\n".$usuarioNum." en base 2 y ".$usuarioBits." bits es: ".organizar(convertir($usuarioNum, $usuarioBits))."\n\n"; $loop = False;}
		}
	if ($loop == False){echo "Programa ejecuto correctamente.\n";} //es una conveniente llamada para saber si todo ejecuto en orden
	}
}
?>
