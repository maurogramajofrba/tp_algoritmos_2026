#include <iostream>
#include "tp_lib.h"

using namespace std;

void MenuNuevoAtaque(FILE *ataque, tOrdenArchivo ordenAnterior, tAccionesUnicas checkAccionesUnicas);
void AgregarOrdenArchivo(FILE *ataque, tOrdenArchivo ordenAnterior, tAccionesUnicas checkAccionesUnicas);
void menuOrden(FILE *ataque, tOrdenArchivo currOrden, tAccionesUnicas checkAccionesUnicas);
void FinalizarAtaqueNuevo(FILE *ataque);

bool EsMovimientoValido(int x, int y, int prevX = -1, int prevY = -1);

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

  if (!checkAccionesUnicas.hayDespegue)
  {
    nuevaOrden.despegue = true;
    do
    {
      cout << "No hay despegue aún, ingrese posición de despegue válida:" << endl;
      cout << "x y > ";
      cin >> nuevaOrden.x >> nuevaOrden.y;
    } while (!EsMovimientoValido(nuevaOrden.x, nuevaOrden.y));
    checkAccionesUnicas.hayDespegue = true;
  }

  menuOrden(ataque, nuevaOrden, checkAccionesUnicas);
}

void menuOrden(FILE *ataque, tOrdenArchivo currOrden, tAccionesUnicas checkAccionesUnicas)
{
  int opcion;

  do
  {
    if (!currOrden.espera)
      cout << "1. Esperar" << endl;
    if (!currOrden.siguienteX || !currOrden.siguienteY)
      cout << "2. Moverse" << endl;
    if (!currOrden.soltarGranada1 && !checkAccionesUnicas.soltoGranada1)
      cout << "3. Soltar granada 1" << endl;
    if (!currOrden.soltarGranada2 && !checkAccionesUnicas.soltoGranada2)
      cout << "4. Soltar granada 2" << endl;
    if (!currOrden.aterrizaje && !checkAccionesUnicas.hayFinViaje)
      cout << "5. Aterrizar" << endl;
    if (!currOrden.ataqueKamikaze && !checkAccionesUnicas.hayFinViaje)
      cout << "6. Ataque kamikaze" << endl;
    cout << "0. Finalizar orden" << endl;

    cin >> opcion;
    bool opcionValida = false;

    switch (opcion)
    {
    case 1:
      if (!currOrden.espera)
      {
        opcionValida = true;
        do
        {
          cout << "Ingrese segundos a esperar válidos:" << endl;
          cin >> currOrden.espera;
        } while (currOrden.espera < 1);

        EnterParaContinuar();
      }
      break;
    case 2:
      if (!currOrden.siguienteX || !currOrden.siguienteY)
      {
        opcionValida = true;
        do
        {
          cout << "Ingresa la posición válida a moverse:" << endl;
          cout << "x y > ";
          cin >> currOrden.siguienteX >> currOrden.siguienteY;
        } while (!EsMovimientoValido(currOrden.siguienteX, currOrden.siguienteY, currOrden.x, currOrden.y));
        EnterParaContinuar();
      }
      break;
    case 3:
      if (!currOrden.soltarGranada1 && !checkAccionesUnicas.soltoGranada1)
      {
        opcionValida = true;
        currOrden.soltarGranada1 = true;
        checkAccionesUnicas.soltoGranada1 = true;
        cout << "Se soltará la granada 1 en esta orden" << endl;
        EnterParaContinuar();
      }
      break;
    case 4:
      if (!currOrden.soltarGranada2 && !checkAccionesUnicas.soltoGranada2)
      {
        opcionValida = true;
        currOrden.soltarGranada2 = true;
        checkAccionesUnicas.soltoGranada2 = true;
        cout << "Se soltará la granada 2 en esta orden" << endl;
        EnterParaContinuar();
      }
      break;
    case 5:
      if (!currOrden.aterrizaje && !checkAccionesUnicas.hayFinViaje)
      {
        opcionValida = true;
        currOrden.aterrizaje = true;
        checkAccionesUnicas.hayFinViaje = true;
        cout << "Se aterrizará en esta posición" << endl;
        EnterParaContinuar();
      }
      break;
    case 6:
      if (!currOrden.ataqueKamikaze && !checkAccionesUnicas.hayFinViaje)
      {
        opcionValida = true;
        currOrden.ataqueKamikaze = true;
        checkAccionesUnicas.hayFinViaje = true;
        cout << "Se hará el ataque kamikaze en esta posición" << endl;
        EnterParaContinuar();
      }
      break;
    case 0:
      if (currOrden.siguienteX || currOrden.siguienteY)

      default:
        break;
    }

    if (!opcionValida)
    {
      cout << "Opción inválida intente nuevamente!" << endl
           << endl;
      EnterParaContinuar();
    }
  } while (opcion);
}

void FinalizarAtaqueNuevo(FILE *ataque)
{
  fclose(ataque);
}

bool EsMovimientoValido(int x, int y, int prevX, int prevY)
{
  bool movimientoValido = true;

  if (x == prevX && y == prevY)
    movimientoValido = false;
  if (x >= ANCHO_MAPA || y >= ALTO_MAPA)
    movimientoValido = false;

  if (prevX < 0)
  {
    if (x < 0 || x >= ANCHO_MAPA)
      movimientoValido = false;
  }
  else
  {
    if (std::abs(x - prevX) > 1)
      movimientoValido = false;
  }

  if (prevY < 0)
  {
    if (y < 0 || y >= ALTO_MAPA)
      movimientoValido = false;
  }
  else
  {
    if (std::abs(y - prevY) > 1)
      movimientoValido = false;
  }

  return movimientoValido;
}