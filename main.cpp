#include "tp_lib.h"
#include <iostream>

using namespace std;

void menu();
void FinalizarPrograma();

tMapaAtaque *pMapa = nullptr;
tChecksAtaque *checksAtaque = nullptr;
string rutaArchivoEnMemoria;

int main() {
  menu();
  delete pMapa;
  delete checksAtaque;
  return 0;
}

void menu() {
  int opcion;

  do {
    if (pMapa != nullptr && checksAtaque != nullptr) {
      cout << "Archivo : " << rutaArchivoEnMemoria << endl;
      cout << "Cargado en memoria" << endl;

      cout << "Resumen:" << endl;
      cout << "El dron se mueve en " << checksAtaque->cantCoordenadas << " coordenadas distintas" << endl;
      if (checksAtaque->soltoGranada1)
        cout << "El dron usa la granada 1" << endl;
      if (checksAtaque->soltoGranada2)
        cout << "El dron usa la granada 2" << endl;
      if (checksAtaque->hayAterrizaje)
        cout << "El dron finaliza el viaje aterrizando" << endl;
      if (checksAtaque->hayAtaqueKamikaze)
        cout << "El dron finaliza con ataque kamikaze" << endl;
    }

    ImprimirSeparador(15, '*', 1, 0);
    cout << " MENÚ PRINCIPAL ";
    ImprimirSeparador(15, '*', 0, 2);
    cout << "1. Cargar archivo de ataque en memoria." << endl;
    cout << "2. Mostrar ataque cargado." << endl;
    cout << "3. Crear un archivo de ataque nuevo." << endl;
    cout << "4. Corregir un registro del archivo." << endl;
    cout << "5. Corregir un registro en memoria." << endl;
    cout << "6. Guardar memoria en un archivo nuevo." << endl;
    cout << "7. Visualizar un archivo de ataque en html." << endl;
    cout << "0. Finalizar programa." << endl << endl;

    cout << "> ";
    cin >> opcion;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    switch (opcion) {
    case 1:
      CargarAtaqueEnMemoria(pMapa, checksAtaque, rutaArchivoEnMemoria);
      EnterParaContinuar();
      break;
    case 2:
      MostrarAtaque(pMapa, checksAtaque);
      EnterParaContinuar();
      break;
    case 3:
      CrearNuevoAtaque();
      EnterParaContinuar();
      break;
    case 4:
      CorregirRegistroDeArchivo();
      EnterParaContinuar();
      break;
    case 5:
      CorregirRegistroDeMemoria();
      EnterParaContinuar();
      break;
    case 6:
      GuardarAtaque();
      EnterParaContinuar();
      break;
    case 7:
      VisualizarAtaqueHTML();
      EnterParaContinuar();
      break;
    case 0:
      FinalizarPrograma();
      EnterParaContinuar();
      break;

    default:
      cout << "Opción inválida intente nuevamente!" << endl << endl;
      EnterParaContinuar();
      break;
    }
  } while (opcion);
}

void FinalizarPrograma() { cout << "Soy la acción FinalizarPrograma." << endl; }