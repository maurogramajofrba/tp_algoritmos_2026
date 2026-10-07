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
    cout << "Elija una opción:" << endl;
    cout << "1. Cargar archivo de ataque en memoria." << endl;
    cout << "2. Mostrar ataque cargado." << endl;
    cout << "3. Crear un archivo de ataque nuevo." << endl;
    cout << "4. Corregir un registro del archivo." << endl;
    cout << "5. Corregir un registro en memoria." << endl;
    cout << "6. Guardar memoria en un archivo nuevo." << endl;
    cout << "7. Visualizar un archivo de ataque en html." << endl;
    cout << "0. Finalizar programa." << endl;

    cin >> opcion;

    switch (opcion)
    {
      case 1:
        CargarAtaqueEnMemoria();
        break;
      case 2:
        MostrarAtaque();
        break;
      case 3:
        CrearNuevoAtaque();
        break;
      case 4:
        CorregirRegistroDeArchivo();
        break;
      case 5:
        CorregirRegistroDeMemoria();
        break;
      case 6:
        GuardarAtaque();
        break;
      case 7:
        VisualizarAtaqueHTML();
        break;
      case 0:
        FinalizarPrograma();
        break;
      
      default:
        cout << "Opción inválida intente nuevamente!" << endl << endl;
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