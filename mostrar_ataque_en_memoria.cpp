#include <iostream>
#include "tp_lib.h"
using namespace std;
extern tOrden (*pMapa)[ANCHO_MAPA];
void MostrarAtaque() {
  ImprimirSeparador(15, '-', 1, 0);
  cout << " MOSTRAR ATAQUE CARGADO ";
  ImprimirSeparador(15, '-', 0, 2);
  int xActual = -1;
  int yActual = -1;
  bool encontrado = false;
  for (int x = 0; x < ANCHO_MAPA && !encontrado; x++) {
    for (int y = 0; y < ALTO_MAPA && !encontrado; y++) {
      if (pMapa[x][y].despegue) {
        xActual = x;
        yActual = y;
        encontrado = true;
      }
    }
  }
  if (!encontrado) {
    cout << "No hay ningun ataque cargado en memoria." << endl;
    return;
  }
  int registrosImpresos = 0;
  bool finRuta = false;
  while (!finRuta) {
    tOrden celda = pMapa[xActual][yActual];
    cout << "[X: " << xActual << ", Y: " << yActual << "] -> Acciones: ";
    bool hizoAlgo = false;
    if (celda.despegue) {
      cout << "Despegue ";
      hizoAlgo = true;
    }
    if (celda.aterrizaje) {
      cout << "Aterrizaje ";
      hizoAlgo = true;
    }
    if (celda.soltarGranada1) {
      cout << "Soltar Granada 1 ";
      hizoAlgo = true;
    }
    if (celda.soltarGranada2) {
      cout << "Soltar Granada 2 ";
      hizoAlgo = true;
    }
    if (celda.ataqueKamikaze) {
      cout << "Ataque Kamikaze ";
      hizoAlgo = true;
    }
    if (celda.espera > 0) {
      cout << "Esperar " << celda.espera << "s ";
      hizoAlgo = true;
    }

    if (!hizoAlgo) {
      cout << "Mover ";
    }
    if (celda.aterrizaje || celda.ataqueKamikaze) {
      cout << "| FIN DE LA RUTA" << endl;
      finRuta = true;
    } else {
      cout << "| Siguiente: [" << celda.siguienteX << ", " << celda.siguienteY << "]" << endl;
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