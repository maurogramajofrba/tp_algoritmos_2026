#include <iostream>
#include "tp-types.h"

using namespace std;

void CrearNuevoAtaque()
{

  string ruta;
  string nombreArchivo;

  int opcion;

  cout << endl
       << "-----------------------------------" << endl;
  cout << "Cargar en memoria archivo de ataque" << endl;
  cout << "Decime la ruta del archivo de ataque:" << endl;
  cin >> ruta;
  cout << "Decime el nombre del archivo de ataque:" << endl;
  cin >> nombreArchivo;

  string rutaCompleta = ruta + "\\" + nombreArchivo;

  tOrden *(*pMapa)[ANCHO_MAPA];

  pMapa = new tOrden *[ALTO_MAPA][ANCHO_MAPA]();

  // arrancar todos en null

  do
  {
    cout << "Nuevo ataque:" << endl;
    cout << "1. Agregar orden." << endl;
    cout << "2. Modificar orden." << endl;
    cout << "3. Mostrar nuevo ataque." << endl;
    cout << "4. Crear." << endl;
    cout << "0. Cancelar." << endl;

    cin >> opcion;

    if (opcion > 0 && opcion < 7)

    switch (opcion)
    {
    case 1:
      AgregarOrden(pMapa);
      break;
    case 2:
      ModificarOrden();
      break;
    case 3:
      MostrarAtaque();
      break;
    case 4:
      ConfirmarCreacion(rutaCompleta, pMapa);
      break;
    case 0:
      CancelarCreacion();
      break;

    default:
      cout << "Opción inválida intente nuevamente!" << endl
           << endl;
      break;
    }
  } while (opcion);

  delete[] pMapa;
}

void AgregarOrden(tOrden *(*pMapa)[ANCHO_MAPA])
{
  int x, y;
  int codigoOrden;

  cout << "Ingrese cordeenadas del ataque x y:" << endl;
  cin >> x >> y;

  if (x < 0 || y < 0 || x > ANCHO_MAPA - 1 || y > ALTO_MAPA - 1)
  {
    cout << "Coordenadas inválidas!!!" << endl;
    return;
  }

  if (pMapa[y][x] != nullptr)
  {
    cout << "Coordenadas ya tienen ordenes!!!" << endl;
    return;
  }

  do
  {
    cout << "Ingrese las ordenes a ejecutar:" << endl;
    cout << "1. Despegue." << endl;
    cout << "2. Aterrizaje." << endl;
    cout << "3. Soltar granada 1" << endl;
    cout << "4. Soltar granada 2" << endl;
    cout << "5. Ataque Kamikaze" << endl;
    cout << "6. Esperar." << endl;
    cout << "7. Mover." << endl;
    cout << "0. Terminar ordenes." << endl;

    cin >> codigoOrden;

    if (codigoOrden > 0 && codigoOrden < 8)
    {
      if (pMapa[y][x] == nullptr)
        pMapa[y][x] = new tOrden();
    }

    switch (codigoOrden)
    {
    case 1:
      pMapa[y][x]->despegue = true;
      break;
    case 2:
      pMapa[y][x]->aterrizaje = true;
      break;
    case 3:
      pMapa[y][x]->soltarGranada1 = true;
      break;
    case 4:
      pMapa[y][x]->soltarGranada2 = true;
      break;
    case 5:
      pMapa[y][x]->ataqueKamikaze = true;
      break;
    case 6:
      cout << "Indique los segundos de espera:" << endl;
      cin >> pMapa[y][x]->espera;
      break;
    case 7:
      cout << "Ingrese las coordenadas moverse x y:" << endl;
      cin >> pMapa[y][x]->siguienteX >> pMapa[y][x]->siguienteY;
      break;
    case 0:
      break;

    default:
      cout << "Opción inválida intente nuevamente!" << endl
           << endl;
      break;
    }
  } while (codigoOrden);
}

void ConfirmarCreacion(string rutaCompleta, tOrden *(*pMapa)[ANCHO_MAPA])
{
  FILE *nuevoAtaque;

  nuevoAtaque = fopen(rutaCompleta.c_str(), "wb");

  if (nuevoAtaque == NULL)
  {
    cout << "ERROR al crear el archivo!!!" << endl;
    return;
  }

  fclose(nuevoAtaque);

  cout << "Ataque creado con éxito!!!" << endl;
}