#include "tp_lib.h"
#include <iostream>

using namespace std;

void CorregirRegistroDeMemoria(tMapaAtaque *pMapa) {
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

  tOrden celda = pMapa->ordenes[x][y];

  if (!celda.despegue && !celda.aterrizaje && !celda.ataqueKamikaze &&
      !celda.soltarGranada1 && !celda.soltarGranada2 && celda.espera == 0 &&
      celda.siguienteX == 0 && celda.siguienteY == 0) {
    cout << "No hay ningun registro cargado en esa coordenada." << endl;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return;
  }

  cout << endl << "Registro actual:" << endl;
  cout << "[X: " << x << ", Y: " << y << "] -> Acciones: ";
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
    cout << "| FIN DE LA RUTA" << endl << endl;
  } else {
    cout << "| Siguiente: [" << celda.siguienteX << ", " << celda.siguienteY << "]" << endl << endl;
  }

  tOrden nuevaOrden = {};

  cout << "Ingrese los nuevos datos (1 = Si, 0 = No):" << endl;
  cout << "Despegue (actual: " << celda.despegue << ") (1/0): ";
  cin >> nuevaOrden.despegue;

  if (!nuevaOrden.despegue) {
    cout << "Aterrizaje (actual: " << celda.aterrizaje << ") (1/0): ";
    cin >> nuevaOrden.aterrizaje;

    if (!nuevaOrden.aterrizaje) {
      cout << "Ataque Kamikaze (actual: " << celda.ataqueKamikaze << ") (1/0): ";
      cin >> nuevaOrden.ataqueKamikaze;
    }

    cout << "Soltar Granada 1 (actual: " << celda.soltarGranada1 << ") (1/0): ";
    cin >> nuevaOrden.soltarGranada1;

    cout << "Soltar Granada 2 (actual: " << celda.soltarGranada2 << ") (1/0): ";
    cin >> nuevaOrden.soltarGranada2;
  }

  cout << "Tiempo de espera en segundos (actual: " << celda.espera << "): ";
  cin >> nuevaOrden.espera;

  if (!nuevaOrden.aterrizaje && !nuevaOrden.ataqueKamikaze) {
    cout << "Siguiente X (actual: " << celda.siguienteX << "): ";
    cin >> nuevaOrden.siguienteX;
    cout << "Siguiente Y (actual: " << celda.siguienteY << "): ";
    cin >> nuevaOrden.siguienteY;
  } else {
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