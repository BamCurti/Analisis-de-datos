/*
 * functions.h
 *
 *  Created on: 10 mar. 2020
 *      Author: Edgar Vallejo Curti
 */
#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_

typedef char*** matrix;
typedef char** columna;
typedef char* string;

typedef enum {INTEGER, FLOAT, STR} type;

matrix leerArchivo(int*, int*);
void reallocString(string*, int*);
void readLine(string*, int*);
string leerString();
int cantidadDeCaracteres(string);
string crearString();
columna crearColumna(int);
void freeString(string);
int identificarTipoString(string);
matrix crearMatrix(int);
void printMatrix(matrix , int , int );
int identificarTipoColumna(matrix, int, int);
int cantidadDeNumeros(matrix,int,  int);
float media(matrix, int, int, int);
float desvEstandar(matrix, int, int, int);
float varianza(matrix , int , int , int );
float sumatoria(matrix , int, int, int);
int conteo(matrix);

//FUNCIONES A CODIFICAR
void freeMatrix(matrix);
void freeColumn(columna);
void printDicionario(matrix, int);

//FUNCIONES A MEJORAR


#endif /* FUNCTIONS_H_ */
