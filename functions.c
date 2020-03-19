#include <stdio.h>
#include <stdlib.h>
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

//	printf("%s\n", texto);

	fclose(archivo);

	matrix contenido = (matrix)malloc((*nFilas) * sizeof(columna));

	//Se crea el esqueleto de la matriz
	//Solo contiene las filas del documento
	contenido[0] = crearColumna(*nColumnas);
	contenido[0][0] = crearString();

	int indexTexto = 0, indexFilas = 0, indexString = 0, indexColumnas = 0;

	for(indexTexto = 0; indexTexto < cantidadDeCaracteres(texto); indexTexto++)
	{
		c = texto[indexTexto];

		if(c == '\n' || c == ','){
			reallocString(&contenido[indexFilas][indexColumnas], &indexString);
			contenido[indexFilas][indexColumnas][indexString] = '\0';
			indexString = 0;

			if(c == '\n'){ //Siguiente fila
				indexFilas++;
				indexColumnas = 0;
				contenido[indexFilas] = crearColumna(*nColumnas);
				printf("\n");
			}

			if(c == ','){ //Siguiente columna
				indexColumnas++;
				printf("\t");
			}
			contenido[indexFilas][indexColumnas] = crearString();

		}


		else{ //Solo agregas nuevo char

			contenido[indexFilas][indexColumnas][indexString] = c;
			printf("%c", contenido[indexFilas][indexColumnas][indexString]);
			reallocString(&contenido[indexFilas][indexColumnas], &indexString);

		}
	}

	fclose(archivo);
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
void printMatrix(matrix info, int c, int f){

	for(int i = 0; i < f; i++){
		for(int j = 0; j < c; j++)
			printf("%s\t", info[f][c]);

		printf("\n");
	}

}

int cantidadDeFilas(matrix info){
	int i;
	for(i = 0; info[i] != NULL; i++);
	return i;
}
int cantidadDeColumnas(matrix info){
	int i;
	for(i = 0; info[0][i] != NULL; i++);
	return i;
}
void freeString(string str){
	for(int i = 0; str[i] != '\0'; i++)
		free(&str[i]);
}
string prototipoString(string info, int indexMenor, int indexMayor){
	string value = NULL;
	int size = indexMayor - indexMenor;
	while(value == NULL)
		value = (string)malloc(size * sizeof(char));

	int j = 0;
	for(int i = indexMenor; i < indexMayor; i++){
		value[j] = info[i];
		j++;
	}

	return value;
}
