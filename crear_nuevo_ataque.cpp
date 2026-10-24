#include "tp_lib.h"
#include <iostream>

using namespace std;

void AgregarOrdenArchivo(FILE *ataque, tChecksAtaque *checksAtaque);
void menuOrden(FILE *ataque, tOrdenArchivo *currOrden, tChecksAtaque *checksAtaque);
void FinalizarSinGuardar(FILE *ataque, string rutaCompleta);

bool EsMovimientoValido(int x, int y, int prevX = -1, int prevY = -1);
void InsertarPosicionOrdenada(int posicionesUsadas[], int *cantPosiciones, int nuevaPosicion);
bool PosicionUsada(int posicionesUsadas[], int cantPosiciones, int nuevaPosicion);
int CodificarCoordenada(int x, int y);

void CrearNuevoAtaque() {
  string rutaCompleta;
  FILE *ataque;

  ImprimirSeparador(15, '-', 1, 0);
  cout << " CREAR ATAQUE NUEVO ";
  ImprimirSeparador(15, '-', 0, 2);

  cout << "Decime la ruta completa del archivo del nuevo ataque:" << endl;
  cout << "> ";
  getline(cin, rutaCompleta);

  ataque = fopen(rutaCompleta.c_str(), "wb");

  if (ataque == NULL) {
    cout << "No se pudo abrir el archivo: " << rutaCompleta << endl;
    return;
  }

  cout << "Archivo abierto correctamente." << endl;

  tChecksAtaque checksAtaque = {};
  checksAtaque.moverseX = -1;
  checksAtaque.moverseY = -1;

  int opcion;

  do {
    if (checksAtaque.hayDespegue)
      cout << "El dron despega con exito." << endl;
    if (checksAtaque.soltoGranada1)
      cout << "El dron soltó la granada 1." << endl;
    if (checksAtaque.soltoGranada2)
      cout << "El dron soltó la granada 2." << endl;
    if (checksAtaque.hayAterrizaje)
      cout << "El dron aterrizo." << endl;
    if (checksAtaque.hayAtaqueKamikaze)
      cout << "El dron hizo ataque kamikaze." << endl;

    if (!(checksAtaque.hayAterrizaje || checksAtaque.hayAtaqueKamikaze))
      cout << "1. Agregar orden." << endl;
    else
      cout << "1. Ataque finalizado! volver al menú principal." << endl;

    cout << "0. Cancelar creación neuvo ataque." << endl;

    cin >> opcion;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    switch (opcion) {
    case 1:
      if (!(checksAtaque.hayAterrizaje || checksAtaque.hayAtaqueKamikaze)) {
        AgregarOrdenArchivo(ataque, &checksAtaque);
        break;
      } else {
        fclose(ataque);
        return;
      }
    case 0:
      FinalizarSinGuardar(ataque, rutaCompleta);
      break;
    default:
      cout << "Opción inválida intente nuevamente!" << endl << endl;

      break;
    }
  } while (opcion);
}

void AgregarOrdenArchivo(FILE *ataque, tChecksAtaque *checksAtaque) {
  tOrdenArchivo nuevaOrden = {};
  nuevaOrden.x = checksAtaque->moverseX;
  nuevaOrden.y = checksAtaque->moverseY;

  if (!checksAtaque->hayDespegue) {
    nuevaOrden.despegue = true;
    do {
      cout << "Indique donde despegara el dron:" << endl;
      cout << "x y > ";
      cin >> nuevaOrden.x >> nuevaOrden.y;
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
    } while (!EsMovimientoValido(nuevaOrden.x, nuevaOrden.y));
    checksAtaque->hayDespegue = true;
  }

  menuOrden(ataque, &nuevaOrden, checksAtaque);
}

void menuOrden(FILE *ataque, tOrdenArchivo *currOrden, tChecksAtaque *checksAtaque) {
  int opcion;

  do {
    cout << "El dron está en x: " << currOrden->x << " y: " << currOrden->y << endl
         << "Realiza las siguientes acciones:" << endl;
    if (currOrden->despegue)
      cout << "Despega." << endl;
    if (currOrden->aterrizaje)
      cout << "Aterriza." << endl;
    if (currOrden->soltarGranada1)
      cout << "Suelta granada 1." << endl;
    if (currOrden->soltarGranada2)
      cout << "Suelta granada 2." << endl;
    if (currOrden->ataqueKamikaze)
      cout << "Hace ataque kamikaze." << endl;
    if (currOrden->espera)
      cout << "Espera " << currOrden->espera << " segundos." << endl;
    if (currOrden->siguienteX && currOrden->siguienteY)
      cout << "Se mueve a x: " << currOrden->siguienteX << " y:" << currOrden->siguienteY << endl;

    if (!currOrden->espera)
      cout << "1. Esperar" << endl;
    if (!(currOrden->siguienteX || currOrden->siguienteY) && !currOrden->ataqueKamikaze &&
        !currOrden->aterrizaje && !checksAtaque->hayAterrizaje && !checksAtaque->hayAtaqueKamikaze)
      cout << "2. Moverse" << endl;
    if (!currOrden->despegue && !currOrden->soltarGranada1 && !checksAtaque->soltoGranada1)
      cout << "3. Soltar granada 1" << endl;
    if (!currOrden->despegue && !currOrden->soltarGranada2 && !checksAtaque->soltoGranada2)
      cout << "4. Soltar granada 2" << endl;
    if (!currOrden->despegue && !currOrden->aterrizaje && !checksAtaque->hayAterrizaje &&
        !checksAtaque->hayAtaqueKamikaze)
      cout << "5. Aterrizar" << endl;
    if (!currOrden->despegue && !currOrden->ataqueKamikaze && !checksAtaque->hayAterrizaje &&
        !checksAtaque->hayAtaqueKamikaze)
      cout << "6. Ataque kamikaze" << endl;
    cout << "7. Cancelar orden" << endl;

    cout << "0. Finalizar orden" << endl;

    cin >> opcion;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    bool opcionValida = false;

    switch (opcion) {
    case 1:
      if (!currOrden->espera) {
        opcionValida = true;
        do {
          cout << "Ingrese segundos a esperar válidos:" << endl;
          cin >> currOrden->espera;
          cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } while (currOrden->espera < 1);
      }
      break;
    case 2:
      if (!currOrden->siguienteX && !currOrden->siguienteY && !currOrden->ataqueKamikaze &&
          !currOrden->aterrizaje && !checksAtaque->hayAterrizaje &&
          !checksAtaque->hayAtaqueKamikaze) {
        opcionValida = true;
        do {
          cout << "Ingresa la posición válida a moverse:" << endl;
          cout << "x y > ";
          cin >> currOrden->siguienteX >> currOrden->siguienteY;
          cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } while (!EsMovimientoValido(currOrden->siguienteX, currOrden->siguienteY, currOrden->x,
                                     currOrden->y) ||
                 PosicionUsada(checksAtaque->posicionesUsadas, checksAtaque->cantPosiciones,
                               CodificarCoordenada(currOrden->siguienteX, currOrden->siguienteY)));
      }
      break;
    case 3:
      if (!currOrden->soltarGranada1 && !checksAtaque->soltoGranada1 && !currOrden->despegue) {
        opcionValida = true;
        currOrden->soltarGranada1 = true;
        checksAtaque->soltoGranada1 = true;
        cout << "Se soltará la granada 1 en esta orden" << endl;
      }
      break;
    case 4:
      if (!currOrden->soltarGranada2 && !checksAtaque->soltoGranada2 && !currOrden->despegue) {
        opcionValida = true;
        currOrden->soltarGranada2 = true;
        checksAtaque->soltoGranada2 = true;
        cout << "Se soltará la granada 2 en esta orden" << endl;
      }
      break;
    case 5:
      if (!currOrden->despegue && !currOrden->aterrizaje && !checksAtaque->hayAterrizaje &&
          !checksAtaque->hayAtaqueKamikaze) {
        opcionValida = true;
        currOrden->aterrizaje = true;
        checksAtaque->hayAterrizaje = true;
        cout << "Se aterrizará en esta posición" << endl;
      }
      break;
    case 6:
      if (!currOrden->despegue && !currOrden->ataqueKamikaze && !checksAtaque->hayAterrizaje &&
          !checksAtaque->hayAtaqueKamikaze) {
        opcionValida = true;
        currOrden->ataqueKamikaze = true;
        checksAtaque->hayAtaqueKamikaze = true;
        cout << "Se hará el ataque kamikaze en esta posición" << endl;
      }
      break;

    case 7:
      cout << "Se cancela la orden al dron" << endl;
      opcionValida = true;

      if (currOrden->despegue)
        checksAtaque->hayDespegue = false;
      if (currOrden->soltarGranada1)
        checksAtaque->soltoGranada1 = false;
      if (currOrden->soltarGranada2)
        checksAtaque->soltoGranada2 = false;
      if (currOrden->ataqueKamikaze)
        checksAtaque->hayAtaqueKamikaze = false;
      if (currOrden->aterrizaje)
        checksAtaque->hayAterrizaje = false;

      return;
    case 0:
      if ((currOrden->siguienteX && currOrden->siguienteY) || currOrden->aterrizaje ||
          currOrden->ataqueKamikaze) {
        opcionValida = true;
        fwrite(currOrden, sizeof(tOrdenArchivo), 1, ataque);
        InsertarPosicionOrdenada(checksAtaque->posicionesUsadas, &checksAtaque->cantPosiciones,
                                 (CodificarCoordenada(currOrden->x, currOrden->y)));
        checksAtaque->moverseX = currOrden->siguienteX;
        checksAtaque->moverseY = currOrden->siguienteY;
        cout << "Se guardó la orden con éxito!!" << endl;
      }
    default:
      break;
    }

    if (!opcionValida) {
      cout << "Opción inválida intente nuevamente!" << endl << endl;
    }
  } while (opcion);
}

void FinalizarSinGuardar(FILE *ataque, string rutaCompleta) {
  fclose(ataque);
  remove(rutaCompleta.c_str());
}

bool EsMovimientoValido(int x, int y, int prevX, int prevY) {
  bool movimientoValido = true;

  if (x == prevX && y == prevY)
    movimientoValido = false;
  if (x >= ANCHO_MAPA || y >= ALTO_MAPA)
    movimientoValido = false;

  if (prevX < 0) {
    if (x < 0 || x >= ANCHO_MAPA)
      movimientoValido = false;
  } else {
    if (std::abs(x - prevX) > 1)
      movimientoValido = false;
  }

  if (prevY < 0) {
    if (y < 0 || y >= ALTO_MAPA)
      movimientoValido = false;
  } else {
    if (std::abs(y - prevY) > 1)
      movimientoValido = false;
  }

  return movimientoValido;
}

void InsertarPosicionOrdenada(int posicionesUsadas[], int *cantPosiciones, int nuevaPosicion) {
  int aux = (*cantPosiciones) - 1;

  while (aux >= 0 && posicionesUsadas[aux] > nuevaPosicion) {
    posicionesUsadas[aux + 1] = posicionesUsadas[aux];
    aux--;
  }

  posicionesUsadas[aux + 1] = nuevaPosicion;
  (*cantPosiciones)++;
}

bool PosicionUsada(int posicionesUsadas[], int cantPosiciones, int nuevaPosicion) {
  int indiceInferior = 0;
  int indiceSuperior = cantPosiciones - 1;
  int indiceCentro;
  bool encontradaUbicacion = false;

  while (indiceInferior <= indiceSuperior && !encontradaUbicacion) {
    indiceCentro = (indiceSuperior + indiceInferior) / 2;

    if (posicionesUsadas[indiceCentro] == nuevaPosicion) {
      encontradaUbicacion = true;
    } else {
      if (nuevaPosicion < posicionesUsadas[indiceCentro]) {
        indiceSuperior = indiceCentro - 1;
      } else {
        indiceInferior = indiceCentro + 1;
      }
    }
  }

  return encontradaUbicacion;
}

int CodificarCoordenada(int x, int y) { return x * ALTO_MAPA + y; }