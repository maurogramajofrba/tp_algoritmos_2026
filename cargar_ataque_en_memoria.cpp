#include "tp_lib.h"
#include <iostream>

using namespace std;

void CargarAtaqueEnMemoria(tMapaAtaque *&pMapa, tChecksAtaque *&checksAtaque) {
  string rutaCompleta;
  FILE *ataque;

  delete pMapa;
  delete checksAtaque;
  pMapa = nullptr;
  checksAtaque = nullptr;

  ImprimirSeparador(15, '-', 1, 0);
  cout << " CARGAR ATAQUE EN MEMORIA ";
  ImprimirSeparador(15, '-', 0, 2);
  cout << "Decime la ruta completa del archivo de ataque:" << endl;
  cout << "> ";
  getline(cin, rutaCompleta);

  ataque = fopen(rutaCompleta.c_str(), "rb");

  if (ataque == NULL) {
    cout << "No se pudo abrir el archivo: " << rutaCompleta << endl;
    return;
  }

  cout << "Archivo abierto correctamente." << endl;

  tMapaAtaque *nuevoAtaque = new tMapaAtaque{};
  OrdenArchivo ataque_leido;
  tChecksAtaque *nuevosChecks = new tChecksAtaque{};
  bool cancelado = false;

  // Chequear las validaciones fundamentales
  while (fread(&ataque_leido, sizeof(OrdenArchivo), 1, ataque)) {
    // Medida por si los valores son incorrectos
    if (!EsMovimientoValido(ataque_leido.x, ataque_leido.y)) {
      cancelado = true;
      break;
    }

    // Revisar si ya paso por esa ubicacion
    if (nuevosChecks->coordenadasUsadas[ataque_leido.x][ataque_leido.y]) {
      cancelado = true;
      break;
    } else {
      nuevosChecks->coordenadasUsadas[ataque_leido.x][ataque_leido.y] = true;
      nuevosChecks->cantCoordenadas += 1;
    }

    if (ataque_leido.despegue) {
      // Sólo debe haber 1 despegue
      if (nuevosChecks->hayDespegue) {
        cancelado = true;
        break;
      }

      // El despegue no puede estar acompañado de ningún ataque
      if (ataque_leido.ataqueKamikaze || ataque_leido.soltarGranada1 ||
          ataque_leido.soltarGranada2) {
        cancelado = true;
        break;
      }

      nuevosChecks->hayDespegue = true;
      nuevosChecks->coordenadaDespegueX = ataque_leido.x;
      nuevosChecks->coordenadaDespegueY = ataque_leido.y;
    }

    // Debe existir una sóla instrucción de final
    if (ataque_leido.ataqueKamikaze) {
      if (nuevosChecks->hayAtaqueKamikaze || nuevosChecks->hayAterrizaje) {
        cancelado = true;
        break;
      } else {
        nuevosChecks->hayAtaqueKamikaze = true;
      }
    }

    if (ataque_leido.aterrizaje) {
      if (nuevosChecks->hayAtaqueKamikaze || nuevosChecks->hayAterrizaje) {
        cancelado = true;
        break;
      } else {
        nuevosChecks->hayAterrizaje = true;
      }
    }

    if (!ataque_leido.aterrizaje && !ataque_leido.ataqueKamikaze) {
      if (!EsMovimientoValido(ataque_leido.siguienteX, ataque_leido.siguienteY, ataque_leido.x,
                              ataque_leido.y)) {
        cancelado = true;
        break;
      }
    }

    if (ataque_leido.soltarGranada1) {
      if (nuevosChecks->soltoGranada1) {
        cancelado = true;
        break;
      } else {
        nuevosChecks->soltoGranada1 = true;
      }
    }

    if (ataque_leido.soltarGranada2) {
      if (nuevosChecks->soltoGranada2) {
        cancelado = true;
        break;
      } else {
        nuevosChecks->soltoGranada2 = true;
      }
    }

    nuevoAtaque->ordenes[ataque_leido.x][ataque_leido.y].despegue = ataque_leido.despegue;
    nuevoAtaque->ordenes[ataque_leido.x][ataque_leido.y].aterrizaje = ataque_leido.aterrizaje;
    nuevoAtaque->ordenes[ataque_leido.x][ataque_leido.y].soltarGranada1 =
        ataque_leido.soltarGranada1;
    nuevoAtaque->ordenes[ataque_leido.x][ataque_leido.y].soltarGranada2 =
        ataque_leido.soltarGranada2;
    nuevoAtaque->ordenes[ataque_leido.x][ataque_leido.y].ataqueKamikaze =
        ataque_leido.ataqueKamikaze;
    nuevoAtaque->ordenes[ataque_leido.x][ataque_leido.y].espera = ataque_leido.espera;
    nuevoAtaque->ordenes[ataque_leido.x][ataque_leido.y].siguienteX = ataque_leido.siguienteX;
    nuevoAtaque->ordenes[ataque_leido.x][ataque_leido.y].siguienteY = ataque_leido.siguienteY;
  }

  if (!nuevosChecks->hayDespegue ||
      (!nuevosChecks->hayAterrizaje && !nuevosChecks->hayAtaqueKamikaze))
    cancelado = true;

  if (!cancelado) {
    int recorridas = 1; //arranca en el despegue
    int i = nuevosChecks->coordenadaDespegueX;
    int j = nuevosChecks->coordenadaDespegueY;
    // ultimo check recorrer todo el ataque si no se llega al final romper
    while (!nuevoAtaque->ordenes[i][j].aterrizaje && !nuevoAtaque->ordenes[i][j].ataqueKamikaze) {
      if (!nuevosChecks->coordenadasUsadas[i][j] || recorridas >= nuevosChecks->cantCoordenadas) {
        cancelado = true;
        break;
      }

      int aux = i;

      i = nuevoAtaque->ordenes[i][j].siguienteX;
      j = nuevoAtaque->ordenes[aux][j].siguienteY;
      recorridas++;
    }

    if (recorridas != nuevosChecks->cantCoordenadas)
      cancelado = true;
  }

  // Abortar si no cumple las condiciones
  if (cancelado) {
    ImprimirSeparador(15, '-', 1, 0);
    cout << "El archivo no cumple con los requisitos, intente con otro" << endl;
    ImprimirSeparador(15, '-', 1, 0);
    delete nuevoAtaque;
    delete nuevosChecks;
    fclose(ataque);
    return;
  }

  pMapa = nuevoAtaque;
  checksAtaque = nuevosChecks;
  cout << "Ataque cargado correctamente." << endl;
  fclose(ataque);
}