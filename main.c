/*
 * main.c
 *
 *  Created on: 8 mar. 2020
 *      Author: Edgar Vallejo Curti
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"

int main(){
	int nFilas = 1, nColumnas = 1;
	setbuf(stdout, NULL);

	matrix informacion = leerArchivo(&nFilas, &nColumnas);
	printf("%d",cantidadDeNumeros(informacion,nFilas,5));

	return 0;
}
