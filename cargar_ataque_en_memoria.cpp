#include <iostream>
#include "tp_lib.h"

using namespace std;

void CargarAtaqueEnMemoria()
{
  string rutaCompleta;
  FILE *ataque;

  ImprimirSeparador(15, '-', 1, 0);
  cout << " CARGAR ATAQUE EN MEMORIA ";
  ImprimirSeparador(15, '-', 0, 2);
  cout << "Decime la ruta completa del archivo de ataque:" << endl;
  cout << "> ";
  getline(cin, rutaCompleta);

  ataque = fopen(rutaCompleta.c_str(), "rb");

  if (ataque == NULL)
  {
    cout << "No se pudo abrir el archivo: " << rutaCompleta << endl;
    return;
  }

  cout << "Archivo abierto correctamente." << endl;

  fclose(ataque);
}