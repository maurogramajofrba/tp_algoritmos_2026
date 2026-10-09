#include <iostream>
#include "tp_lib.h"

using namespace std;

void menu();
void MostrarAtaque();
void CorregirRegistroDeArchivo();
void CorregirRegistroDeMemoria();
void GuardarAtaque();
void VisualizarAtaqueHTML();
void FinalizarPrograma();

tOrden (*pMapa)[ANCHO_MAPA];

int main() {
  pMapa = new tOrden[ALTO_MAPA][ANCHO_MAPA]();
  menu();
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
        CargarAtaqueEnMemoria();
        EnterParaContinuar();
        break;
      case 2:
        MostrarAtaque();
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

void MostrarAtaque() {
  cout << "Soy la acción MostrarAtaque." << endl;
}

void CorregirRegistroDeArchivo() {
  cout << "Soy la acción CorregirRegistroDeArchivo." << endl;
}

void CorregirRegistroDeMemoria() {
  cout << "Soy la acción CorregirRegistroDeMemoria." << endl;
}

void GuardarAtaque() {
  cout << "Soy la acción GuardarAtaque." << endl;
}

void VisualizarAtaqueHTML() {
  cout << "Soy la acción VisualizarAtaqueHTML." << endl;
}

void FinalizarPrograma() {
  cout << "Soy la acción FinalizarPrograma." << endl;
}