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
  cout << "[X: " << registro.x << ", Y: " << registro.y << "] -> Acciones: ";
  bool hizoAlgo = false;
  if (registro.despegue) {
    cout << "Despegue ";
    hizoAlgo = true;
  }
  if (registro.aterrizaje) {
    cout << "Aterrizaje ";
    hizoAlgo = true;
  }
  if (registro.soltarGranada1) {
    cout << "Soltar Granada 1 ";
    hizoAlgo = true;
  }
  if (registro.soltarGranada2) {
    cout << "Soltar Granada 2 ";
    hizoAlgo = true;
  }
  if (registro.ataqueKamikaze) {
    cout << "Ataque Kamikaze ";
    hizoAlgo = true;
  }
  if (registro.espera > 0) {
    cout << "Esperar " << registro.espera << "s ";
    hizoAlgo = true;
  }
  if (!hizoAlgo) {
    cout << "Mover ";
  }
  if (registro.aterrizaje || registro.ataqueKamikaze) {
    cout << "| FIN DE LA RUTA" << endl << endl;
  } else {
    cout << "| Siguiente: [" << registro.siguienteX << ", " << registro.siguienteY << "]" << endl
         << endl;
  }

  tOrdenArchivo nuevaOrden = {};
  nuevaOrden.x = registro.x;
  nuevaOrden.y = registro.y;

  cout << "Ingrese los nuevos datos (1 = Si, 0 = No):" << endl;
  cout << "Despegue (actual: " << registro.despegue << ") (1/0): ";
  cin >> nuevaOrden.despegue;

  if (!nuevaOrden.despegue) {
    cout << "Aterrizaje (actual: " << registro.aterrizaje << ") (1/0): ";
    cin >> nuevaOrden.aterrizaje;

    if (!nuevaOrden.aterrizaje) {
      cout << "Ataque Kamikaze (actual: " << registro.ataqueKamikaze << ") (1/0): ";
      cin >> nuevaOrden.ataqueKamikaze;
    }

    cout << "Soltar Granada 1 (actual: " << registro.soltarGranada1 << ") (1/0): ";
    cin >> nuevaOrden.soltarGranada1;

    cout << "Soltar Granada 2 (actual: " << registro.soltarGranada2 << ") (1/0): ";
    cin >> nuevaOrden.soltarGranada2;
  }

  cout << "Tiempo de espera en segundos (actual: " << registro.espera << "): ";
  cin >> nuevaOrden.espera;

  if (!nuevaOrden.aterrizaje && !nuevaOrden.ataqueKamikaze) {
    cout << "Siguiente X (actual: " << registro.siguienteX << "): ";
    cin >> nuevaOrden.siguienteX;
    cout << "Siguiente Y (actual: " << registro.siguienteY << "): ";
    cin >> nuevaOrden.siguienteY;
  }

  fseek(ataque, -(long)sizeof(tOrdenArchivo), SEEK_CUR);
  fwrite(&nuevaOrden, sizeof(tOrdenArchivo), 1, ataque);
  fclose(ataque);

  cin.ignore(numeric_limits<streamsize>::max(), '\n');
  cout << endl << "Registro corregido correctamente." << endl;
}
