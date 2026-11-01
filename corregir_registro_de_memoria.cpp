#include "tp_lib.h"
#include <iostream>

using namespace std;

void CorregirRegistroDeMemoria(tMapaAtaque *pMapa, tChecksAtaque *checksAtaque) {
  if (pMapa == nullptr) {
    cout << "No hay ataque cargado en memoria!!!" << endl;
    return;
  }

  ImprimirSeparador(15, '-', 1, 0);
  cout << " CORREGIR REGISTRO EN MEMORIA ";
  ImprimirSeparador(15, '-', 0, 2);

  int x, y;
  cout << "Ingrese la posicion X a corregir: ";
  cin >> x;
  cout << "Ingrese la posicion Y a corregir: ";
  cin >> y;

  if (x < 0 || x >= ANCHO_MAPA || y < 0 || y >= ALTO_MAPA) {
    cout << "Coordenadas fuera de rango." << endl;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return;
  }

  if (!checksAtaque->coordenadasUsadas[x][y]) {
    cout << "No hay ningun registro cargado en esa coordenada." << endl;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return;
  }

  tOrden celda = pMapa->ordenes[x][y];

  cout << endl << "Registro actual:" << endl;
  ImprimirOrden(celda, x, y);

  tOrden nuevaOrden = {};

  cout << "Ingrese los nuevos datos (1 = Si, 0 = No):" << endl;
  IngresarOrdenMemoria(nuevaOrden);

  if (nuevaOrden.aterrizaje && nuevaOrden.ataqueKamikaze) {
    int borrarX = celda.siguienteX;
    int borrarY = celda.siguienteY;
    while (borrarX != 0 || borrarY != 0) {
      tOrden aux = pMapa->ordenes[borrarX][borrarY];
      pMapa->ordenes[borrarX][borrarY] = {};
      if (aux.aterrizaje || aux.ataqueKamikaze) {
        break;
      }
      borrarX = aux.siguienteX;
      borrarY = aux.siguienteY;
    }
  }

  pMapa->ordenes[x][y] = nuevaOrden;

  cin.ignore(numeric_limits<streamsize>::max(), '\n');
  cout << endl << "Registro corregido correctamente." << endl;
}