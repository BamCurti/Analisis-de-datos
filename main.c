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
	string value =	(string)calloc(4, sizeof(char));
	value[0] = '1';
	value[1] = '.';
	value[2] = '3';
	value[3] = '\0';

	matrix informacion = leerArchivo(&nFilas, &nColumnas);

//	printMatrix(informacion, nFilas, nColumnas);

	return 0;
}
