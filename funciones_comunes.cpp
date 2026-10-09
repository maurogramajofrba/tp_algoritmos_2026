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
}