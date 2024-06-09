#ifndef FUNCIONES_H
#define FUNCIONES_H

void liberarMatriz(int** matriz, unsigned int dimension);
int* obtenerValidacion();
bool compararMatrices(int** matriz1, int** matriz2, unsigned int fila1, unsigned int columna1, unsigned int fila2, unsigned int columna2, int condicion);
int** crearMatriz(unsigned int tamano);
void rotarMatriz(int **matriz, unsigned int orden);
void copiarMatriz(int**& destino, int** origen, unsigned int dimension);

#endif // FUNCIONES_H