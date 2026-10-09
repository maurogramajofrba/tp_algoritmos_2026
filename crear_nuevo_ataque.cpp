#include <iostream>
#include "tp_lib.h"

using namespace std;

void MenuNuevoAtaque(FILE *ataque);
void AgregarOrdenArchivo(FILE *ataque);
void FinalizarAtaqueNuevo(FILE *ataque);

void CrearNuevoAtaque()
{
  string rutaCompleta;
  FILE *ataque;

  ImprimirSeparador(15, '-', 1, 0);
  cout << " CREAR ATAQUE NUEVO ";
  ImprimirSeparador(15, '-', 0, 2);

  cout << "Decime la ruta completa del archivo del nuevo ataque:" << endl;
  cout << "> ";
  getline(cin, rutaCompleta);

  ataque = fopen(rutaCompleta.c_str(), "wb");

  if (ataque == NULL)
  {
    cout << "No se pudo abrir el archivo: " << rutaCompleta << endl;
    return;
  }

  cout << "Archivo abierto correctamente." << endl;

  tAccionesUnicas checkAccionesUnicas;
  tOrdenArchivo ordenAnterior;


  MenuNuevoAtaque(ataque, ordenAnterior, checkAccionesUnicas);
}

void MenuNuevoAtaque(FILE *ataque, tOrdenArchivo ordenAnterior, tAccionesUnicas checkAccionesUnicas)
{
  int opcion;

  do
  {
    cout << "1. Agregar orden." << endl;
    cout << "0. Finalizar." << endl;

    cin >> opcion;

    if (opcion > 0 && opcion < 7)

      switch (opcion)
      {
      case 1:
        AgregarOrdenArchivo(ataque, ordenAnterior, checkAccionesUnicas);
        EnterParaContinuar();
        break;
      case 0:
        FinalizarAtaqueNuevo(ataque);
        EnterParaContinuar();
        break;

      default:
        cout << "Opción inválida intente nuevamente!" << endl
             << endl;
        EnterParaContinuar();
        break;
      }
  } while (opcion);
}

void AgregarOrdenArchivo(FILE *ataque, tOrdenArchivo ordenAnterior, tAccionesUnicas checkAccionesUnicas)
{
  tOrdenArchivo nuevaOrden;

  if (!checkAccionesUnicas.hayDespegue) {
    nuevaOrden.despegue = true;
    cout << "No hay despegue aún, ingrese posición de despegue:" << endl;
    cout << "x y > ";
    cin >> nuevaOrden.x >> nuevaOrden.y;

    menuOrden(ataque, nuevaOrden, checkAccionesUnicas);
  }
}

void menuOrden(FILE *ataque, tOrdenArchivo currOrden, tAccionesUnicas checkAccionesUnicas) {
  int opcion;

  do
  {
    if (!currOrden.espera) cout << "1. Esperar" << endl;
    if (!currOrden.siguienteX || !currOrden.siguienteY) cout << "2. Moverse" << endl;
    if (!currOrden.soltarGranada1 && !checkAccionesUnicas.soltoGranada1) cout << "3. Soltar granada 1" << endl;
    if (!currOrden.soltarGranada2 && !checkAccionesUnicas.soltoGranada2) cout << "4. Soltar granada 2" << endl;
    if (!currOrden.aterrizaje && !checkAccionesUnicas.hayFinViaje) cout << "5. Aterrizar" << endl;
    if (!currOrden.ataqueKamikaze && !checkAccionesUnicas.hayFinViaje) cout << "6. Ataque kamikaze" << endl;
    cout << "0. Finalizar" << endl;

    cin >> opcion;

    if (opcion > 0 && opcion < 7)

      switch (opcion)
      {
      case 1:
        AgregarOrdenArchivo(ataque, currOrden, checkAccionesUnicas);
        EnterParaContinuar();
        break;
      case 0:
        FinalizarAtaqueNuevo(ataque);
        EnterParaContinuar();
        break;

      default:
        cout << "Opción inválida intente nuevamente!" << endl
             << endl;
        EnterParaContinuar();
        break;
      }
  } while (opcion);
}

void FinalizarAtaqueNuevo(FILE *ataque)
{
  fclose(ataque);
}