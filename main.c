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
	int menuColumna;
	setbuf(stdout, NULL);
	int menu = 1;
	matrix info = NULL;

	printf("<<MINI STAT>>\n\n");
	while(menu)
	{
		int menu2 = 0;
		printf("1)Cargar datos\n");
		printf("2)Visualizar\n");
		printf("3)Imprimir diccionario\n");
		printf("4)Analisis de datos \n");
		printf("0)Salir:");
		scanf("%d", &menu);

		switch(menu)
		{
		case 1:
			nFilas = 1;
			nColumnas = 1;
			info = leerArchivo(&nFilas, &nColumnas);
			break;

		case 2:
			if(info != NULL)
				printMatrix(info, nFilas, nColumnas);
			else
				printf("Primero carga el archivo\n");
			break;

		case 3:
			if(info != NULL)
				printDicionario(info, nFilas, nColumnas);
			else
				printf("Primero carga el archivo\n");
			break;

		case 4:
			if(info != NULL)
			{
				printf("1)Conteo\n2)Sumatoria\n3)Media\n4)Desv Estandar\n5)Varianza:\n");
				scanf("%d", &menu2);
				printf("Cual columna?:");
				scanf("%d", &menuColumna);
				switch(menu2)
				{
				case 1:
					printf("Conteo: %d\n", conteo(info, menuColumna, nFilas, nColumnas));
					break;

				case 2:
					printf("Sumatoria: %f\n", sumatoria(info, menuColumna, nFilas, nColumnas));
					break;

				case 3:
					printf("media: %f", media(info, menuColumna, nFilas, nColumnas));
					break;

				case 4:
					printf("desviacion: %f", desvEstandar(info, menuColumna, nFilas, nColumnas));
					break;

				case 5:
					printf("varianza: %f", varianza(info, menuColumna, nFilas, nColumnas));
					break;
				}
			}
			else
				printf("Primero carga el archivo\n");
			break;
		}
	}
	printf("Gracias por usar el código:)");

	return 0;
}
