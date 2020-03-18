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

//	printf("%s", texto);

	fclose(archivo);

	matrix contenido = (matrix)malloc((*nFilas) * sizeof(char));

	//Se crea el esqueleto de la matriz
	//Solo contiene las filas del documento
	contenido[0] = crearColumna(*nColumnas);
	contenido[0][0] = crearString();

	int indexTexto = 0, indexFilas = 0, indexString = 0, indexColumnas = 0, primerCar = 0, ultimoCar = 0;

	for(indexTexto = 0; texto[indexTexto] != '\0'; indexTexto++)
	{
		c = texto[indexTexto];
		if(c == '\n'){ //Siguiente fila
/*			indexFilas++;
			indexColumnas = 0;
			indexString = 0;
			contenido[indexFilas] = crearColumna(*nColumnas);
			contenido[indexFilas][indexColumnas] = crearString();*/

			contenido[indexFilas][indexColumnas] = prototipoString(texto, primerCar, ultimoCar);
			ultimoCar = indexTexto +1;
			primerCar = indexTexto +1;

			indexFilas++;
			indexColumnas = 0;
			contenido[indexFilas] = crearColumna(*nColumnas);

			printf("\n");

		}

		else if(c == ','){ //Siguiente columna
//			printf("Nueva columna\n");
/*			indexColumnas++;
			contenido[indexFilas][indexColumnas] = crearString();
			indexString = 0;*/

			contenido[indexFilas][indexColumnas] = prototipoString(texto, primerCar, ultimoCar);
			ultimoCar = indexTexto +1;
			primerCar = indexTexto +1;

			indexColumnas++;

			printf("\t");
		}

		else{ //Solo agregas nuevo char
	//		printf("Nueva char\n");
/*			reallocString(&contenido[indexFilas][indexColumnas], &indexString);
			contenido[indexFilas][indexColumnas][indexString] = c;
			printf("%c", contenido[indexFilas][indexColumnas][indexString]);*/

			ultimoCar = indexTexto;
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
		new = (string)calloc(0, sizeof(char)); //string sin caracteres
	return new;
}
columna crearColumna(int n){
	columna new = NULL;
	while(new == NULL){
		new = calloc(n, sizeof(char));
	}
	return new;
}
void printMatrix(matrix info){
	int nFilas = cantidadDeFilas(info);
	int nColumnas = cantidadDeColumnas(info);

	for(int i = 0; i < nFilas; i++){
		for(int j = 0; j < nColumnas; j++)
		{
			for(int k = 0; info[i][j][k] != '\0'; k++)
				printf("%c", info[i][j][k]);

			printf("\t");
		}
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

//	printf("%s", value);

	return value;
}
