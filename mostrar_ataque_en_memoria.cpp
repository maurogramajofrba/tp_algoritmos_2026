#include "tp_lib.h"
#include <iostream>

using namespace std;

void ImprimirOrden(tOrden orden, int x, int y);

void MostrarAtaque(tMapaAtaque *pMapa, tChecksAtaque *checksAtaque) {
  if (pMapa == nullptr || checksAtaque == nullptr) {
    cout << "No hay ataque cargado en memoria!!!" << endl;
    return;
  }

  ImprimirSeparador(15, '-', 1, 0);
  cout << " MOSTRAR ATAQUE CARGADO ";
  ImprimirSeparador(15, '-', 0, 2);

  int i = checksAtaque->coordenadaDespegueX;
  int j = checksAtaque->coordenadaDespegueY;

  while (!pMapa->ordenes[i][j].aterrizaje && !pMapa->ordenes[i][j].ataqueKamikaze) {
    ImprimirOrden(pMapa->ordenes[i][j], i, j);

    int aux = i;
    i = pMapa->ordenes[i][j].siguienteX;
    j = pMapa->ordenes[aux][j].siguienteY;
  }
  ImprimirOrden(pMapa->ordenes[i][j], i, j);
}

void ImprimirOrden(tOrden orden, int x, int y) {
    cout << "[X: " << x << ", Y: " << y << "] -> Acciones: ";

    if (orden.despegue) {
      cout << "Despegue         ";
    }
    if (orden.aterrizaje) {
      cout << "Aterrizaje       ";
    }
    if (orden.soltarGranada1) {
      cout << "Soltar Granada 1 ";
    }
    if (orden.soltarGranada2) {
      cout << "Soltar Granada 2 ";
    }
    if (orden.ataqueKamikaze) {
      cout << "Ataque Kamikaze  ";
    }
    if (orden.espera > 0) {
      cout << "Esperar " << orden.espera << "s ";
    }

    if (orden.ataqueKamikaze || orden.aterrizaje) {
      cout << "| Fin de viaje " << endl;
    } else {
      cout << "| Siguiente: [" << orden.siguienteX << ", " << orden.siguienteY << "]" << endl;
    }
}