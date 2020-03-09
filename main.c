/*
 * main.c
 *
 *  Created on: 8 mar. 2020
 *      Author: Edgar Vallejo Curti
 */
#include <stdio.h>
#include <stdlib.h>

char *leerArchivo();
void reallocString(char **, int*);
void readLine(char **, int*);
char* leerString();

int main(){
	setbuf(stdout, NULL);
	char *informacion = leerArchivo();

//	printf("caracteres después: %d\n", sizeof((char *)informacion / (char));

	printf("%s", informacion);

	return 0;
}

char * leerArchivo(){
	printf("Ingrese direccion de documento:\n");
	char *direccion = leerString();

	FILE *archivo = fopen((char*)direccion, "r");

    fseek(archivo, 0, SEEK_END);    /* file pointer at the end of file */
	long nbytes = ftell(archivo);
	printf("caracteres de archivo: %ld\n", nbytes);
	rewind(archivo);
	char *contenido = (char *)malloc(nbytes*sizeof(char));
	int  i = 0;

	while(i < nbytes){
		contenido[i] = fgetc(archivo);
		i++;
	}

	fclose(archivo);
	return contenido;
}
void reallocString(char **lst, int *largo){
    (*largo) += 1;
    char *temp = (char*) realloc(*lst, (*largo) * sizeof (char));
    *lst = temp;
}
void readLine(char **lst, int *largo){
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
//    reallocString(lst, largo);
    (*lst)[pos] = '\0';
}
char* leerString(){
	char *texto = NULL;
	int largo = 0;

	reallocString(&texto, &largo);
	readLine(&texto, &largo);

	return texto;
}
