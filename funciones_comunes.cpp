#include "funciones_comunes.h"
#include "iostream"

using namespace std;

/*
 * Acá podemos poner todas las funciones en común del tp.
 * Ejemplos: BurbujaSort, ValidarDespegue
 */
void ImprimirSeparador(int len, char caracter, int saltosSuperior, int saltosInferior) {
  for (int i = 0; i < saltosSuperior; i++) {
    cout << endl;
  }
  for (int i = 0; i < len; i++) {
    cout << caracter;
  }
  for (int i = 0; i < saltosInferior; i++) {
    cout << endl;
  }
}

void EnterParaContinuar() {
  cout << endl << "Presione ENTER para continuar..." << flush;
  cin.get();
  cout << endl << endl;
}

bool EsMovimientoValido(int x, int y, int prevX, int prevY) {

  if (x == prevX && y == prevY)
    return false;

  if ((x < 0 || x >= ANCHO_MAPA) || (y < 0 || y >= ALTO_MAPA))
    return false;

  if (prevX > -1 && std::abs(x - prevX) > 1)
    return false;

  if (prevY > -1 && std::abs(y - prevY) > 1)
    return false;

  return true;
}
