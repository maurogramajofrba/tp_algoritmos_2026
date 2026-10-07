#include <iostream>
#include "tp_lib.h"

using namespace std;

void CargarAtaqueEnMemoria() {
  string ruta;
  string nombreArchivo;
  cout << "--------------------------------" << endl << endl;
  cout << "Cargar en memoria archivo de ataque" << endl;
  cout << "Decime la ruta del archivo de ataque:" << endl;
  cin >> ruta;
  cout << "Decime el nombre del archivo de ataque:" << endl;
  cin >> nombreArchivo;

  cout << "Ruta ingresada: " << ruta << "/" << nombreArchivo << endl;
  cout << endl << "--------------------------------" << endl << endl;
}