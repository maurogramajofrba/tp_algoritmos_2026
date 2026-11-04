#include <iostream>
#include "tp_lib.h"

using namespace std;

void CorregirRegistroDeArchivo() {
  string rutaCompleta;
  FILE *ataque;

  ImprimirSeparador(15, '-', 1, 0);
  cout << " CORREGIR REGISTRO DEL ARCHIVO ";
  ImprimirSeparador(15, '-', 0, 2);

  cout << "Decime la ruta completa del archivo de ataque:" << endl;
  cout << "> ";
  getline(cin, rutaCompleta);

  ataque = fopen(rutaCompleta.c_str(), "rb+");

  if (ataque == NULL) {
    cout << "No se pudo abrir el archivo: " << rutaCompleta << endl;
    return;
  }

  int x, y;
  cout << "Ingrese la posicion X a corregir: ";
  cin >> x;
  cout << "Ingrese la posicion Y a corregir: ";
  cin >> y;

  tOrdenArchivo registro;
  bool encontrado = false;
  while (!encontrado && fread(&registro, sizeof(tOrdenArchivo), 1, ataque) == 1) {
    if (registro.x == x && registro.y == y) {
      encontrado = true;
    }
  }

  if (!encontrado) {
    cout << "No hay ningun registro en el archivo con esa coordenada." << endl;
    fclose(ataque);
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return;
  }

  cout << endl << "Registro actual:" << endl;
  ImprimirOrden(registro);

  tOrdenArchivo nuevaOrden = {};
  nuevaOrden.x = registro.x;
  nuevaOrden.y = registro.y;

  IngresarOrden(nuevaOrden);

  fseek(ataque, -(long)sizeof(tOrdenArchivo), SEEK_CUR);
  fwrite(&nuevaOrden, sizeof(tOrdenArchivo), 1, ataque);
  fclose(ataque);

  cin.ignore(numeric_limits<streamsize>::max(), '\n');
  cout << endl << "Registro corregido correctamente." << endl;
}
