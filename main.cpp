#include <iostream>
#include "tp_lib.h"

using namespace std;

void menu();
void VisualizarAtaqueHTML();
void FinalizarPrograma();

tMapaAtaque* pMapa = nullptr;

int main() {
  menu();
  delete pMapa;
  return 0;
}

void menu() {
  int opcion;

  do {
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

    switch (opcion)
    {
      case 1:
        CargarAtaqueEnMemoria(pMapa);
        EnterParaContinuar();
        break;
      case 2:
        MostrarAtaque(pMapa);
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

void VisualizarAtaqueHTML() {
  cout << "Soy la acción VisualizarAtaqueHTML." << endl;
}

void FinalizarPrograma() {
  cout << "Soy la acción FinalizarPrograma." << endl;
}