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

  tOrden nuevaCelda = {};

  IngresarOrdenMemoria(nuevaCelda);

  
  if (nuevaCelda.despegue) {
    // 1. Borrar la ruta vieja partiendo desde el despegue anterior
    int borrarX = checksAtaque->coordenadaDespegueX;
    int borrarY = checksAtaque->coordenadaDespegueY;
    
    bool terminarBorrado = false;
    while (!terminarBorrado) {
      tOrden aux = pMapa->ordenes[borrarX][borrarY];
      
      // Limpiamos la celda en el mapa
      pMapa->ordenes[borrarX][borrarY] = {};
      
      // Liberamos la coordenada en los checks para que se pueda volver a usar
      checksAtaque->coordenadasUsadas[borrarX][borrarY] = false;
      checksAtaque->cantCoordenadas--;

      // Si esta celda era el fin de la ruta (aterrizaje o kamikaze) o era el último paso, salimos
      if (aux.aterrizaje || aux.ataqueKamikaze || (aux.siguienteX == 0 && aux.siguienteY == 0 && !aux.despegue)) {
        terminarBorrado = true;
      } else {
        borrarX = aux.siguienteX;
        borrarY = aux.siguienteY;
      }
    }

    // 2. Actualizar los checks con el nuevo despegue en la posición (x, y) actual
    checksAtaque->coordenadaDespegueX = x;
    checksAtaque->coordenadaDespegueY = y;
    checksAtaque->hayDespegue = true;
  }

  if(checksAtaque->soltoGranada1 && nuevaCelda.soltarGranada1){
    int xActual = checksAtaque->coordenadaDespegueX;
    int yActual = checksAtaque->coordenadaDespegueY;
    bool finRuta = false;
    while (!finRuta) {
      tOrden celda = pMapa->ordenes[xActual][yActual];

      if (celda.soltarGranada1) {
        celda.soltarGranada1=false;
        finRuta = true;
      } else {
        xActual = celda.siguienteX;
        yActual = celda.siguienteY;
      }
    }
  }

  if(checksAtaque->soltoGranada2 && nuevaCelda.soltarGranada2){
    int xActual = checksAtaque->coordenadaDespegueX;
    int yActual = checksAtaque->coordenadaDespegueY;
    bool finRuta = false;
    while (!finRuta) {
      tOrden celda = pMapa->ordenes[xActual][yActual];

      if (celda.soltarGranada2) {
        celda.soltarGranada2=false;
        finRuta = true;
      } else {
        xActual = celda.siguienteX;
        yActual = celda.siguienteY;
      }
    }
  }

  
  
  if (nuevaCelda.aterrizaje || nuevaCelda.ataqueKamikaze) {
    int borrarX = celda.siguienteX;
    int borrarY = celda.siguienteY;
    
    // Si la celda anterior no tenía a dónde ir, no hay nada que borrar hacia adelante
    bool terminarBorrado = (borrarX == 0 && borrarY == 0); 

    while (!terminarBorrado) {
      tOrden aux = pMapa->ordenes[borrarX][borrarY];
      
      // 1. Limpiamos la celda en el mapa
      pMapa->ordenes[borrarX][borrarY] = {};
      
      // 2. ¡CRUCIAL! Liberamos la coordenada en los checks
      checksAtaque->coordenadasUsadas[borrarX][borrarY] = false;
      checksAtaque->cantCoordenadas--;

      // 3. Si llegamos al final de esa sub-ruta vieja, cortamos
      if (aux.aterrizaje || aux.ataqueKamikaze || (aux.siguienteX == 0 && aux.siguienteY == 0)) {
        terminarBorrado = true;
      } else {
        borrarX = aux.siguienteX;
        borrarY = aux.siguienteY;
      }
    }
  }

  pMapa->ordenes[x][y] = nuevaCelda;

  cin.ignore(numeric_limits<streamsize>::max(), '\n');
  cout << endl << "Registro corregido correctamente." << endl;
}