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
	printf("caracteres de archivo: %ld\n", nbytes);
	rewind(archivo); //Volver al inicio de la función
	string texto =  (string)malloc(nbytes * sizeof(char));

	char c;
	for(int i = 0; (c = fgetc(archivo)) != EOF; i++){
		texto[i] = c;

		if(c == '\n')
			(*nFilas)++;

		if(*nFilas == 1)
			if(c == ',')
				(*nColumnas)++;
	}
	printf("%s", texto);

	fclose(archivo);

	matrix contenido = (matrix)malloc((*nFilas) * sizeof(char));

/*	for(int indexFilas = 0; indexFilas < nFilas; indexFilas++)
		for(int indexColumnas= 0; indexColumnas < nColumnas; indexColumnas++){
			int indexString = 0;
		}*/





	fclose(archivo);
	return contenido;
}

void reallocString(string* lst, int *largo){
    (*largo) += 1;
    char *temp = (char*) realloc(*lst, (*largo) * sizeof (char));
    *lst = temp;
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
