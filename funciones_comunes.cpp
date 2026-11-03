#include "funciones_comunes.h"
#include "iostream"

using namespace std;

/*
 * Acá podemos poner todas las funciones en común del tp.
 * Ejemplos: BurbujaSort, ValidarDespegue
 */
void ImprimirSeparador(int len, char caracter, int saltosSuperior, int saltosInferior)
{
  for (int i = 0; i < saltosSuperior; i++)
  {
    cout << endl;
  }
  for (int i = 0; i < len; i++)
  {
    cout << caracter;
  }
  for (int i = 0; i < saltosInferior; i++)
  {
    cout << endl;
  }
}

void EnterParaContinuar() {
  cout << endl << "Presione ENTER para continuar..." << flush;
  cin.get();
  cout << endl << endl;
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

void ImprimirOrden(tOrden orden, int x, int y) {
  tOrdenArchivo ordenArchivo;

  ordenArchivo.x = x;
  ordenArchivo.y = y;
  ordenArchivo.espera = orden.espera;
  ordenArchivo.soltarGranada1 = orden.soltarGranada1;
  ordenArchivo.soltarGranada2 = orden.soltarGranada2;
  ordenArchivo.ataqueKamikaze = orden.ataqueKamikaze;
  ordenArchivo.aterrizaje = orden.aterrizaje;
  ordenArchivo.despegue = orden.despegue;
  ordenArchivo.siguienteX = orden.siguienteX;
  ordenArchivo.siguienteY = orden.siguienteY;

  ImprimirOrden(ordenArchivo);
}

void ImprimirOrden(tOrdenArchivo orden) {
  cout << "[" << orden.x << " " << orden.y << "]: Despega: ";
  if (orden.despegue)
    cout << "SI";
  else
    cout << "NO";
  cout << " | Aterriza: ";
  if (orden.aterrizaje)
    cout << "SI";
  else
    cout << "NO";
  cout << " | Suelta granada 1: ";
  if (orden.soltarGranada1)
    cout << "SI";
  else
    cout << "NO";
  cout << " | Suelta granada 2: ";
  if (orden.soltarGranada2)
    cout << "SI";
  else
    cout << "NO";
  cout << " | Ataque kamikaze: ";
  if (orden.ataqueKamikaze)
    cout << "SI";
  else
    cout << "NO ";

  cout << " | Espera: ";
  if (orden.espera) {
    cout << orden.espera << " s";
  } else {
    cout << "NO";
  }

  if (!orden.ataqueKamikaze && !orden.aterrizaje)
    cout << " | Se mueve a: [" << orden.siguienteX << " " << orden.siguienteY << "]";

  cout << endl;
}

void IngresarOrdenMemoria(tOrden &orden){
  cout << "Espera?: ";
  do {
    cin >> orden.espera;
    if (!(orden.espera>=0)) {
      cout << "Ingrese valor valido!!!" << endl;
      cout << "Espera?: ";
    }
  } while (!(orden.espera>=0));

  cout << "Despega? (0 = NO, 1 = SI): ";
  do {
    cin >> orden.despegue;
    if (!(orden.despegue == 0 || orden.despegue == 1)) {
      cout << "Ingrese valor valido!!!" << endl;
      cout << "Despega? (0 = NO, 1 = SI): ";
    }
  } while (!(orden.despegue == 0 || orden.despegue == 1));

  cout << "Aterriza? (0 = NO, 1 = SI): ";
  do {
    cin >> orden.aterrizaje;
    if (!(orden.aterrizaje == 0 || orden.aterrizaje == 1)) {
      cout << "Ingrese valor valido!!!" << endl;
      cout << "Aterriza? (0 = NO, 1 = SI): ";
    }
  } while (!(orden.aterrizaje == 0 || orden.aterrizaje == 1));

  cout << "Soltar granada 1? (0 = NO, 1 = SI): ";
  do {
    cin >> orden.soltarGranada1;
    if (!(orden.soltarGranada1 == 0 || orden.soltarGranada1 == 1)) {
      cout << "Ingrese valor valido!!!" << endl;
      cout << "Soltar granada 1? (0 = NO, 1 = SI): ";
    }
  } while (!(orden.soltarGranada1 == 0 || orden.soltarGranada1 == 1));

  cout << "Soltar granada 2? (0 = NO, 1 = SI): ";
  do {
    cin >> orden.soltarGranada2;
    if (!(orden.soltarGranada2 == 0 || orden.soltarGranada2 == 1)) {
      cout << "Ingrese valor valido!!!" << endl;
      cout << "Soltar granada 2? (0 = NO, 1 = SI): ";
    }
  } while (!(orden.soltarGranada2 == 0 || orden.soltarGranada2 == 1));

  cout << "Ataque Kamikaze? (0 = NO, 1 = SI): ";
  do {
    cin >> orden.ataqueKamikaze;
    if (!(orden.ataqueKamikaze == 0 || orden.ataqueKamikaze == 1)) {
      cout << "Ingrese valor valido!!!" << endl;
      cout << "Ataque Kamikaze? (0 = NO, 1 = SI): ";
    }
  } while (!(orden.ataqueKamikaze == 0 || orden.ataqueKamikaze == 1));
}

void IngresarOrden(tOrdenArchivo &orden) {
  cout << "Coordenadas X Y: ";
  cin >> orden.x >> orden.y;

  cout << "Tiempo de espera: ";
  cin >> orden.espera;

  cout << "Despega? (0 = NO, 1 = SI): ";
  cin >> orden.despegue;

  cout << "Aterriza? (0 = NO, 1 = SI): ";
  cin >> orden.aterrizaje;

  cout << "Suelta granada 1? (0 = NO, 1 = SI): ";
  cin >> orden.soltarGranada1;

  cout << "Suelta granada 2? (0 = NO, 1 = SI): ";
  cin >> orden.soltarGranada2;

  cout << "Ataque kamikaze? (0 = NO, 1 = SI): ";
  cin >> orden.ataqueKamikaze;

  if (!orden.aterrizaje && !orden.ataqueKamikaze) {
    cout << "Siguiente coordenada X Y: ";
    cin >> orden.siguienteX >> orden.siguienteY;
  }
}