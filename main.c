/*
 * main.c
 *
 *  Created on: 8 mar. 2020
 *      Author: Edgar Vallejo Curti
 */
#include <stdio.h>
#include <stdlib.h>
#include "functions.h"

int main(){
	setbuf(stdout, NULL);
	char *informacion = leerArchivo();
	printf("Caracteres de informacion: %d\n", cantidadDeCaracteres(informacion));

	for(int i = 0; informacion[i] != '\0' ; i++)
		printf("%c", informacion[i]);

//	printf("%s", informacion);

	return 0;
}
