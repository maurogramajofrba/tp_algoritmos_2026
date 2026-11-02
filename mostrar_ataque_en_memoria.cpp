#include "tp_lib.h"
#include <iostream>

using namespace std;

void MostrarAtaque(tMapaAtaque *pMapa, tChecksAtaque *checksAtaque) {
  if (pMapa == nullptr || checksAtaque == nullptr) {
    cout << "No hay ataque cargado en memoria!!!" << endl;
    return;
  }

  int xActual = checksAtaque->coordenadaDespegueX;
  int yActual = checksAtaque->coordenadaDespegueY;
  int registrosImpresos = 0;
  bool finRuta = false;
  while (!finRuta) {
    tOrden celda = pMapa->ordenes[xActual][yActual];
    ImprimirOrden(celda, xActual, yActual);

    if (celda.aterrizaje || celda.ataqueKamikaze) {
      finRuta = true;
    } else {
      xActual = celda.siguienteX;
      yActual = celda.siguienteY;
    }

    registrosImpresos++;
    if (registrosImpresos % 15 == 0 && !finRuta) {
      EnterParaContinuar();
      cout << endl;
    }
  }
}
