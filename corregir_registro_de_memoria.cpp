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

  tOrden celdaVieja = pMapa->ordenes[x][y];

  cout << endl << "Registro actual:" << endl;
  ImprimirOrden(celdaVieja, x, y);

  tOrden nuevaCelda = {};
  IngresarOrdenMemoria(nuevaCelda);

  // 1. HERENCIA DE PUNTEROS: Si no es fin de ruta, heredamos el movimiento que ya tenía
  if (!nuevaCelda.aterrizaje && !nuevaCelda.ataqueKamikaze) {
    nuevaCelda.siguienteX = celdaVieja.siguienteX;
    nuevaCelda.siguienteY = celdaVieja.siguienteY;
  } else {
    // Si ahora es el final, no tiene a dónde moverse
    nuevaCelda.siguienteX = 0;
    nuevaCelda.siguienteY = 0;
  }

  // 2. Lógica de Despegue
  if (nuevaCelda.despegue) {
    int borrarX = checksAtaque->coordenadaDespegueX;
    int borrarY = checksAtaque->coordenadaDespegueY;
    
    bool terminarBorrado = false;
    while (!terminarBorrado) {
      tOrden aux = pMapa->ordenes[borrarX][borrarY];
      
      if (borrarX == x && borrarY == y) {
        break;
      }
      pMapa->ordenes[borrarX][borrarY] = {};
      checksAtaque->coordenadasUsadas[borrarX][borrarY] = false;
      checksAtaque->cantCoordenadas--;

      if (aux.aterrizaje || aux.ataqueKamikaze || (aux.siguienteX == 0 && aux.siguienteY == 0 && !aux.despegue)) {
        terminarBorrado = true;
      } else {
        borrarX = aux.siguienteX;
        borrarY = aux.siguienteY;
      }
    }

    checksAtaque->coordenadaDespegueX = x;
    checksAtaque->coordenadaDespegueY = y;
    checksAtaque->hayDespegue = true;
  }

  // 3. Limpieza de Granada 1 (corrigiendo asignación directa al mapa)
  if (checksAtaque->soltoGranada1 && nuevaCelda.soltarGranada1) {
    int xActual = checksAtaque->coordenadaDespegueX;
    int yActual = checksAtaque->coordenadaDespegueY;
    bool finRuta = false;
    while (!finRuta) {
      tOrden &celdaRef = pMapa->ordenes[xActual][yActual]; // Referencia real al mapa
      if (celdaRef.soltarGranada1) {
        celdaRef.soltarGranada1 = false;
        finRuta = true;
      } else {
        xActual = celdaRef.siguienteX;
        yActual = celdaRef.siguienteY;
      }
    }
  }

  // 4. Limpieza de Granada 2
  if (checksAtaque->soltoGranada2 && nuevaCelda.soltarGranada2) {
    int xActual = checksAtaque->coordenadaDespegueX;
    int yActual = checksAtaque->coordenadaDespegueY;
    bool finRuta = false;
    while (!finRuta) {
      tOrden &celdaRef = pMapa->ordenes[xActual][yActual];
      if (celdaRef.soltarGranada2) {
        celdaRef.soltarGranada2 = false;
        finRuta = true;
      } else {
        xActual = celdaRef.siguienteX;
        yActual = celdaRef.siguienteY;
      }
    }
  }

  // 5. Lógica de Recorte del Final (Aterrizaje o Kamikaze)
  if (nuevaCelda.aterrizaje || nuevaCelda.ataqueKamikaze) {
    int borrarX = celdaVieja.siguienteX;
    int borrarY = celdaVieja.siguienteY;
    
    bool terminarBorrado = (borrarX == 0 && borrarY == 0); 

    while (!terminarBorrado) {
      tOrden aux = pMapa->ordenes[borrarX][borrarY];
      
      pMapa->ordenes[borrarX][borrarY] = {};
      checksAtaque->coordenadasUsadas[borrarX][borrarY] = false;
      checksAtaque->cantCoordenadas--;

      if (aux.aterrizaje || aux.ataqueKamikaze || (aux.siguienteX == 0 && aux.siguienteY == 0)) {
        terminarBorrado = true;
      } else {
        borrarX = aux.siguienteX;
        borrarY = aux.siguienteY;
      }
    }

    // Actualizamos los checks globales de fin de ruta
    if (nuevaCelda.aterrizaje) {
      checksAtaque->hayAterrizaje = true;
      checksAtaque->hayAtaqueKamikaze = false;
    } else {
      checksAtaque->hayAtaqueKamikaze = true;
      checksAtaque->hayAterrizaje = false;
    }
  }

  // Guardamos definitivamente la celda corregida en el mapa
  pMapa->ordenes[x][y] = nuevaCelda;

  cin.ignore(numeric_limits<streamsize>::max(), '\n');
  cout << endl << "Registro corregido correctamente." << endl;
}