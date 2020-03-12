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

matrix leerArchivo(int*, int*);
void reallocString(string*, int*);
void readLine(string*, int*);
string leerString();
int cantidadDeCaracteres(string);

#endif /* FUNCTIONS_H_ */
