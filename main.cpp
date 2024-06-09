#include <iostream>
#include "FUNCIONES.h"

using namespace std;

int main() {
    bool comparar, condicionValida;
    int** matrizBase, **matrizTemporal, **matrizOriginal;
    unsigned int dimension;
    unsigned int dimensionCambiante;
    unsigned int numMatrices;
    unsigned int indiceCondicion = 3;
    unsigned int dimensionMayor;
    int* resultadoValidacion = obtenerValidacion();
    unsigned int tamanoK = resultadoValidacion[0];
    unsigned int condicionesRestantes = tamanoK - 2;
    unsigned int parCambiante1[2];
    unsigned int parCambiante2[2];

    // Determinar la mayor dimensión
    if (resultadoValidacion[1] > resultadoValidacion[2]) {
        dimensionMayor = resultadoValidacion[1];
    } else {
        dimensionMayor = resultadoValidacion[2];
    }
    if ((dimensionMayor % 2) == 0) {
        dimensionMayor++;
    } else if (dimensionMayor == 1) {
        dimensionMayor = 3;
    }
    if (resultadoValidacion[1] == 2 && resultadoValidacion[2] == 2) {
        dimensionMayor = 5;
    }
    parCambiante1[0] = resultadoValidacion[1];
    parCambiante1[1] = resultadoValidacion[2];
    parCambiante2[0] = parCambiante1[0];
    parCambiante2[1] = parCambiante1[1];
    dimensionCambiante = dimensionMayor;
    matrizBase = crearMatriz(dimensionMayor);
    matrizOriginal = crearMatriz(dimensionMayor);
    dimension = dimensionMayor;
    numMatrices = resultadoValidacion[0] - 1;
    int dimensiones[numMatrices];
    int rotaciones[numMatrices];
    int indiceMatrices = 1;
    matrizTemporal = crearMatriz(dimensionCambiante);
    dimensiones[0] = dimensionMayor;
    rotaciones[0] = 0;

    // Proceso de comparación y rotación
    while (condicionesRestantes >= 1) {
        comparar = false;
        while (comparar == false) {
            unsigned int rotacion = 0;

            while (rotacion <= 3) {
                comparar = compararMatrices(matrizBase, matrizTemporal, parCambiante1[0] - 1, parCambiante1[1] - 1, parCambiante2[0] - 1, parCambiante2[1] - 1, resultadoValidacion[indiceCondicion]);

                if (comparar == false) {
                    rotarMatriz(matrizTemporal, dimensionCambiante);
                    rotacion++;
                } else {
                    dimensiones[indiceMatrices] = dimensionCambiante;
                    rotaciones[indiceMatrices] = rotacion;
                    indiceMatrices++;
                    liberarMatriz(matrizBase, dimension);
                    copiarMatriz(matrizBase, matrizTemporal, dimensionCambiante);
                    dimension = dimensionCambiante;

                    liberarMatriz(matrizTemporal, dimensionCambiante);
                    dimensionCambiante = dimensionMayor;
                    matrizTemporal = crearMatriz(dimensionCambiante);
                    parCambiante1[0] = parCambiante2[0];
                    parCambiante1[1] = parCambiante2[1];
                    parCambiante2[0] = resultadoValidacion[1];
                    parCambiante2[1] = resultadoValidacion[2];

                    rotacion = 10;
                }

                if (rotacion == 4) {
                    liberarMatriz(matrizTemporal, dimensionCambiante);
                    dimensionCambiante += 2;
                    matrizTemporal = crearMatriz(dimensionCambiante);
                    parCambiante2[0]++;
                    parCambiante2[1]++;
                }
            }
        }

        condicionesRestantes--;
        indiceCondicion++;
    }

    // Mostrar resultado final
    cout << "Para una regla K: (";
    for (unsigned int i = 1; i < tamanoK; i++) {
        cout << resultadoValidacion[i] << ", ";
    }
    cout << resultadoValidacion[tamanoK] << ") una posible cerradura podría ser:" << endl << "Dimensiones (";
    for (unsigned int i = 0; i < numMatrices - 1; i++) {
        cout << dimensiones[i] << ", ";
    }
    cout << dimensiones[numMatrices - 1] << ")" << endl << "Esta cerradura tendría las siguientes rotaciones en su respectivo orden a Dimensiones:" << endl << "Rotaciones(";
    for (unsigned int i = 0; i < numMatrices - 1; i++) {
        cout << rotaciones[i] << ", ";
    }
    cout << rotaciones[numMatrices - 1] << ")" << endl;

    // Liberar memoria
    delete[] resultadoValidacion;
    liberarMatriz(matrizBase, dimension);
    liberarMatriz(matrizTemporal, dimensionCambiante);
    liberarMatriz(matrizOriginal, dimensionMayor);

    return 0;
}
