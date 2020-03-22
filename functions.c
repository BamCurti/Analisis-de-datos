#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "functions.h"


matrix leerArchivo(int* nFilas, int* nColumnas){
	printf("Ingrese direccion de documento:\n");
	string direccion = leerString();
	FILE *archivo = fopen((string)direccion, "r");
	free(direccion);

    fseek(archivo, 0, SEEK_END);	/* file pointer at the end of file */
	long nbytes = ftell(archivo);	// Numero de caracters hasta el final
	rewind(archivo); //Volver al inicio de la función
	string texto =  (string)malloc(nbytes * sizeof(char));
	int i;
	char c;

	for(i = 0; (c = fgetc(archivo)) != EOF; i++){
		texto[i] = c;

		if(c == '\n')
			(*nFilas)++;

		if(*nFilas == 1)
			if(c == ',')
				(*nColumnas)++;
	}
	texto[i] = '\0';
	fclose(archivo);

	matrix contenido = crearMatrix(*nFilas);

	//Se crea el esqueleto de la matriz
	//Solo contiene las filas del documento
	contenido[0] = crearColumna(*nColumnas);
	contenido[0][0] = crearString();

	int indexTexto = 0, indexFilas = 0, indexString = 1, indexColumnas = 0;

	for(indexTexto = 0; indexTexto <= strlen(texto); indexTexto++)
	{
		if(texto[indexTexto] == ',' || texto[indexTexto] == '\n'){
			contenido[indexFilas][indexColumnas][indexString -1] = '\0';
			indexString = 1;

			if(texto[indexTexto] == ','){
				indexColumnas++;
				contenido[indexFilas][indexColumnas] = crearString();
//				printf("\t");
			}

			if(texto[indexTexto] == '\n'){
//				printf("\n");
				indexColumnas = 0;
				indexFilas++;
				contenido[indexFilas] = crearColumna(*nColumnas);
				contenido[indexFilas][indexColumnas] = crearString();
			}

		}

		else{
			contenido[indexFilas][indexColumnas][indexString - 1] = texto[indexTexto];
//			printf("%c", contenido[indexFilas][indexColumnas][indexString - 1]);
			reallocString(&contenido[indexFilas][indexColumnas], &indexString);
		}


	}

	return contenido;
}

void reallocString(string* lst, int *largo){
    (*largo) += 1;
    string temp = NULL;
    while(temp == NULL){
    	temp = (string) realloc(*lst, (*largo) * sizeof (char));
    }
    *lst = temp;
//    free(temp);
}
void readLine(string* lst, int *largo){
    int c;
    int pos = 0;
    fflush(stdin);

    c = getchar();
    while (c != '\n' && c != EOF) {
		reallocString(lst, largo);
        (*lst)[pos] =(char) c;
        pos++;
        c = getchar();
    }
    (*lst)[pos] = '\0';
}
string leerString(){
	char *texto = NULL;
	int largo = 0;

	reallocString(&texto, &largo);
	readLine(&texto, &largo);

	return texto;
}
int cantidadDeCaracteres(string str){
	int i;
	for(i = 0; str[i] != '\0'; i++);
	return i;
}
string crearString(){
	string new = NULL;
	while(new == NULL)
		new = (string)calloc(1, sizeof(char)); //string de un caracter
	return new;
}
columna crearColumna(int n){
	columna new = NULL;
	while(new == NULL){
		new = calloc(n, sizeof(string));
	}
	return new;
}
matrix crearMatrix(int n){
	matrix temp = NULL;
	while(temp == NULL)
		temp = (matrix)malloc(n * sizeof(columna));

	return temp;
}
void printMatrix(matrix info, int f, int c){

	for(int i = 0; i < f; i++){
		for(int j = 0; j < c; j++)
			printf("%s\t", info[i][j]);

		printf("\n");
	}

}

void freeString(string str){
	for(int i = 0; i < strlen(str); i++)
		free(&str[i]);
}
int identificarTipoString(string str){
	int flag = INTEGER;
	int contadorDePuntos = 0;
	for(int i = 0; i < strlen(str); i++){
		if(str[i] == '.'){
			contadorDePuntos++;
			flag = FLOAT;
		}

		if(!(str[i]>= '0' && str[i]<= '9'))
		{
			if(contadorDePuntos != 1)
				flag = STR;
		}
	}

	if(strcmp(str, "") == 0)
		flag = STR;


	return flag;
}
float media(matrix info, int wichColumn,int nFila, int nColumna){
	float promedio = 0;
	int type = identificarTipoColumna(info, nFila, wichColumn);

	if(type == STR){
		printf("No se puede realizar la función\n");
		return -1;
	}

	promedio = sumatoria(info, wichColumn, nFila, nColumna);
	promedio /= cantidadDeNumeros(info, nFila, wichColumn);

	return promedio;
}
float desvEstandar(matrix info, int wichColumn, int nFila, int nColumna){
	float result = 0;
	float promedio = media(info, wichColumn, nFila, nColumna);
	int i;
	int type = identificarTipoColumna(info, nFila, wichColumn);

	if(type == STR){
		printf("No se puede realizar la función\n");
		return -1;
	}

	else{
		for(i = 0; i < nFila; i++){
			if(identificarTipoString(info[i][wichColumn]) != STR)
				result += pow((atof(info[i][wichColumn]) - promedio), 2);
	}
		result /= cantidadDeNumeros(info, nFila, wichColumn);
		result = sqrt(result);

	}
	return result;
}
float varianza(matrix info, int wichColumn, int nFila, int nColumna){
	return pow(desvEstandar(info, wichColumn, nFila, nColumna), 2);
}
float sumatoria(matrix info,int wichColumn, int nFila, int nColumna){
	float result = 0;
	int type = identificarTipoColumna(info, nFila, wichColumn);
	int i;

	if(type == STR){
		printf("No se puede realizar la función\n");
		return -1;
	}

	else
		for(i = 0; i < nFila; i++)
			if(identificarTipoString(info[i][wichColumn]) != STR)
				result += atof(info[i][wichColumn]);


	return result;
}

int identificarTipoColumna(matrix info, int f, int c){
	int type = INTEGER;
	int nInt = 0, nFloat = 0, nString = 0;

	for(int i = 0; i < f; i++){
		type = identificarTipoString(info[i][c]);

		if(type == INTEGER) nInt++;
		if(type == FLOAT)	nFloat++;
		if(type == STR)		nString++;
	}

	if(nInt > nFloat && nInt > nString)	type = INTEGER;
	if(nFloat > nInt && nFloat > nString) type = FLOAT;
	if(nString > nInt && nString > nFloat) type = STR;

	return type;

}
int cantidadDeNumeros(matrix info, int fil, int col){
	int n = 0;

	for(int i = 0; i < fil; i++){
		if(identificarTipoString(info[i][col]) != STR)
			n++;
	}

	return n;
}
int conteo(matrix info, int wichColumn, int nFila, int nColumna){
	if(identificarTipoColumna(info, nFila, wichColumn) != STR)
		return cantidadDeNumeros(info, nFila, wichColumn);

	else
		return nFila - 1;
}
void freeColumn(columna info, int nCol){
	for(int i = 0; i < nCol; i++) //Numero de strings
		freeString(info[i]);
}
void freeMatrix(matrix info, int nCol, int nFil){
	for(int i = 0; i < nFil; i++)
		freeColumn(info[i], nCol);
}
void printDicionario(matrix info, int nFila, int nCol){
	printf("Numero de filas: %d\n", nFila);
	printf("Numero de columnas: %d\n", nCol);
	printf("Descripcion de campos:\n");

	for(int i = 0; i < nCol; i++){
		printf("%s\t", info[0][i]);
		if(identificarTipoColumna(info,nFila, i) == INTEGER) printf("ENTERO\t");
		if(identificarTipoColumna(info,nFila, i) == FLOAT) printf("FLOTANTE\t");
		if(identificarTipoColumna(info,nFila, i) == STR) printf("STRING\t");

		printf("%d\n", conteo(info, i, nFila, nCol));
	}

}

