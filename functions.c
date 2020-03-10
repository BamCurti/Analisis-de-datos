#include <stdio.h>
#include <stdlib.h>
#include "functions.h"

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

	fgets(contenido, nbytes, archivo);

/*	while(i < nbytes){
		contenido[i] = fgetc(archivo);
		i++;
	}
	contenido[i] = '\0';*/

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
    (*lst)[pos] = '\0';
}
char* leerString(){
	char *texto = NULL;
	int largo = 0;

	reallocString(&texto, &largo);
	readLine(&texto, &largo);

	return texto;
}
int cantidadDeCaracteres(char *string){
	int i;
	for(i = 0; string[i] != '\0'; i++);
	return i;
}
