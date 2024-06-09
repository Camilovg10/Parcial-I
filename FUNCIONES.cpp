#include <iostream>
#include "FUNCIONES.h"

using namespace std;

int* obtenerValidacion() {
    int* regla;
    int* temporal;
    unsigned int dimension = 2;

    // Ingresar valores iniciales para la posición de fila y columna
    while (true) {
        regla = new int[2];
        for (unsigned short int i = 0; i < 2; i++) {
            if (i == 0) {
                cout << "Ingrese un valor para K, el cual será la posición fila: " << endl;
                cin >> regla[i];
            } else {
                cout << "Ingrese un valor para K, el cual será la posición columna: " << endl;
                cin >> regla[i];
            }
            if (cin.fail()) {
                cin.clear();
                cin.ignore(10000, '\n');
                break;
            }
        }
        if (regla[0] >= 1 && regla[1] >= 1) {
            break;
        } else {
            cout << "Has ingresado datos inválidos. Debes ingresar algún número mayor o igual a 1." << endl;
            delete[] regla;
        }
    }

    // Ingresar valores adicionales para la regla K
    while (true) {
        cout << "Ingrese un valor para K (-1, 0, 1), cuando quiera parar, ingrese '-2': " << endl;
        short int valor;
        cin >> valor;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "El valor ingresado no es válido. Intente nuevamente." << endl;
            continue;
        }

        if (valor == -1 || valor == 0 || valor == 1) {
            dimension += 1;
            temporal = new int[dimension];
            for (unsigned int i = 0; i < dimension - 1; i++) {
                temporal[i] = regla[i];
            }
            temporal[dimension - 1] = valor;
            delete[] regla;
            regla = new int[dimension];
            for (unsigned int i = 0; i < dimension; i++) {
                regla[i] = temporal[i];
            }
            delete[] temporal;
        } else if (valor == -2) {
            break;
        } else {
            cout << "El valor ingresado no es válido. Intente nuevamente." << endl;
        }
    }

    // Crear un arreglo que incluye la dimensión y la regla
    temporal = new int[dimension + 1];
    temporal[0] = dimension;
    for (unsigned int i = 1; i <= dimension; i++) {
        temporal[i] = regla[i - 1];
    }
    delete[] regla;
    return temporal;
}

void liberarMatriz(int** matriz, unsigned int dimension) {
    for (unsigned int i = 0; i < dimension; ++i) {
        delete[] matriz[i];
    }
    delete[] matriz;
}

bool compararMatrices(int** matriz1, int** matriz2, unsigned int fila1, unsigned int columna1, unsigned int fila2, unsigned int columna2, int condicion) {
    if (condicion == -1) {
        return matriz1[fila1][columna1] < matriz2[fila2][columna2];
    } else if (condicion == 0) {
        return matriz1[fila1][columna1] == matriz2[fila2][columna2];
    } else if (condicion == 1) {
        return matriz1[fila1][columna1] > matriz2[fila2][columna2];
    }
    return false;
}

int** crearMatriz(unsigned int tamano) {
    int** matriz = new int*[tamano];
    for (unsigned int i = 0; i < tamano; ++i) {
        matriz[i] = new int[tamano];
    }

    unsigned int valor = 1;
    unsigned int centro = tamano / 2;

    for (unsigned int i = 0; i < tamano; ++i) {
        for (unsigned int j = 0; j < tamano; ++j) {
            if (i == centro && j == centro) {
                matriz[i][j] = 0;
            } else {
                matriz[i][j] = valor++;
            }
        }
    }
    return matriz;
}

void copiarMatriz(int**& destino, int** origen, unsigned int dimension) {
    destino = new int*[dimension];
    for (unsigned int i = 0; i < dimension; i++) {
        destino[i] = new int[dimension];
    }
    for (unsigned int i = 0; i < dimension; i++) {
        for (unsigned int j = 0; j < dimension; j++) {
            destino[i][j] = origen[i][j];
        }
    }
}

void rotarMatriz(int **matriz, unsigned int orden) {
    int **copia;
    copia = new int*[orden];
    for (unsigned int i = 0; i < orden; i++) {
        copia[i] = new int[orden];
    }
    for (unsigned int i = 0; i < orden; i++) {
        for (unsigned int j = 0; j < orden; j++) {
            copia[i][j] = matriz[i][j];
        }
    }
    for (unsigned int i = 0; i < orden; i++) {
        for (unsigned int j = 0; j < orden; j++) {
            matriz[j][orden - 1 - i] = copia[i][j];
        }
    }
    for (unsigned int i = 0; i < orden; i++) {
        delete[] copia[i];
    }
    delete[] copia;
}

