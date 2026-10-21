#include <iostream>
#include "tp_lib.h"

using namespace std;

void AgregarOrdenArchivo(FILE *ataque, tAccionesUnicas *checkAccionesUnicas);
void menuOrden(FILE *ataque, tOrdenArchivo *currOrden, tAccionesUnicas *checkAccionesUnicas);
void FinalizarSinGuardar(FILE *ataque, string rutaCompleta);

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

  tAccionesUnicas checkAccionesUnicas = {};
  checkAccionesUnicas.moverseX = -1;
  checkAccionesUnicas.moverseY = -1;

  int opcion;

  do
  {
    if (checkAccionesUnicas.hayDespegue)
      cout << "El dron despega con exito." << endl;
    if (checkAccionesUnicas.soltoGranada1)
      cout << "El dron soltó la granada 1." << endl;
    if (checkAccionesUnicas.soltoGranada2)
      cout << "El dron soltó la granada 2." << endl;
    if (checkAccionesUnicas.hayFinViaje)
      cout << "Ya finalizó el viaje." << endl;

    if (!checkAccionesUnicas.hayFinViaje)
      cout << "1. Agregar orden." << endl;
    else
      cout << "1. Ataque finalizado! volver al menú principal." << endl;
    if (!checkAccionesUnicas.hayFinViaje)
      cout << "0. Cancelar creación neuvo ataque." << endl;

    cin >> opcion;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    switch (opcion)
    {
    case 1:
      if (!checkAccionesUnicas.hayFinViaje)
      {
        AgregarOrdenArchivo(ataque, &checkAccionesUnicas);
        break;
      }
      else
      {
        fclose(ataque);
        return;
      }
    case 0:
      if (!checkAccionesUnicas.hayFinViaje)
      {
        FinalizarSinGuardar(ataque, rutaCompleta);
        break;
      }
      else
      {
      }

    default:
      cout << "Opción inválida intente nuevamente!" << endl
           << endl;
      EnterParaContinuar();
      break;
    }
  } while (opcion);
}

void AgregarOrdenArchivo(FILE *ataque, tAccionesUnicas *checkAccionesUnicas)
{
  tOrdenArchivo nuevaOrden = {};
  nuevaOrden.x = checkAccionesUnicas->moverseX;
  nuevaOrden.y = checkAccionesUnicas->moverseY;

  if (!checkAccionesUnicas->hayDespegue)
  {
    nuevaOrden.despegue = true;
    do
    {
      cout << "No hay despegue aún, ingrese posición de despegue válida:" << endl;
      cout << "x y > ";
      cin >> nuevaOrden.x >> nuevaOrden.y;
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
    } while (!EsMovimientoValido(nuevaOrden.x, nuevaOrden.y));
    checkAccionesUnicas->hayDespegue = true;
  }

  menuOrden(ataque, &nuevaOrden, checkAccionesUnicas);
}

void menuOrden(FILE *ataque, tOrdenArchivo *currOrden, tAccionesUnicas *checkAccionesUnicas)
{
  int opcion;

  do
  {
    cout << "El dron está en x: " << currOrden->x << " y: " << currOrden->y << endl
         << "Realiza las siguientes acciones:" << endl
         << endl;
    if (currOrden->despegue)
      cout << "Despega." << endl;
    if (currOrden->espera)
      cout << "Espera " << currOrden->espera << " segundos." << endl;
    if (currOrden->siguienteX && currOrden->siguienteY)
      cout << "Se mueve a x: " << currOrden->siguienteX << " y:" << currOrden->siguienteY << endl;
    if (currOrden->soltarGranada1)
      cout << "Suelta granada 1." << endl;
    if (currOrden->soltarGranada2)
      cout << "Suelta granada 2." << endl;
    if (currOrden->aterrizaje)
      cout << "Aterriza." << endl;
    if (currOrden->ataqueKamikaze)
      cout << "Hace ataque kamikaze." << endl;

    if (!currOrden->espera)
      cout << "1. Esperar" << endl;
    if (!(currOrden->siguienteX || currOrden->siguienteY) && !currOrden->ataqueKamikaze && !currOrden->aterrizaje && !checkAccionesUnicas->hayFinViaje)
      cout << "2. Moverse" << endl;
    if (!currOrden->soltarGranada1 && !checkAccionesUnicas->soltoGranada1 && !currOrden->despegue)
      cout << "3. Soltar granada 1" << endl;
    if (!currOrden->soltarGranada2 && !checkAccionesUnicas->soltoGranada2 && !currOrden->despegue)
      cout << "4. Soltar granada 2" << endl;
    if (!currOrden->aterrizaje && !checkAccionesUnicas->hayFinViaje && !currOrden->despegue)
      cout << "5. Aterrizar" << endl;
    if (!currOrden->ataqueKamikaze && !checkAccionesUnicas->hayFinViaje && !currOrden->despegue)
      cout << "6. Ataque kamikaze" << endl;
    cout << "7. Cancelar orden" << endl;

    cout << "0. Finalizar orden" << endl;

    cin >> opcion;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    bool opcionValida = false;

    switch (opcion)
    {
    case 1:
      if (!currOrden->espera)
      {
        opcionValida = true;
        do
        {
          cout << "Ingrese segundos a esperar válidos:" << endl;
          cin >> currOrden->espera;
          cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } while (currOrden->espera < 1);

        EnterParaContinuar();
      }
      break;
    case 2:
      if (!(currOrden->siguienteX || currOrden->siguienteY) && !currOrden->ataqueKamikaze && !currOrden->aterrizaje && !checkAccionesUnicas->hayFinViaje)
      {
        opcionValida = true;
        do
        {
          cout << "Ingresa la posición válida a moverse:" << endl;
          cout << "x y > ";
          cin >> currOrden->siguienteX >> currOrden->siguienteY;
          cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } while (!EsMovimientoValido(currOrden->siguienteX, currOrden->siguienteY, currOrden->x, currOrden->y));
        EnterParaContinuar();
      }
      break;
    case 3:
      if (!currOrden->soltarGranada1 && !checkAccionesUnicas->soltoGranada1 && !currOrden->despegue)
      {
        opcionValida = true;
        currOrden->soltarGranada1 = true;
        checkAccionesUnicas->soltoGranada1 = true;
        cout << "Se soltará la granada 1 en esta orden" << endl;
        EnterParaContinuar();
      }
      break;
    case 4:
      if (!currOrden->soltarGranada2 && !checkAccionesUnicas->soltoGranada2 && !currOrden->despegue)
      {
        opcionValida = true;
        currOrden->soltarGranada2 = true;
        checkAccionesUnicas->soltoGranada2 = true;
        cout << "Se soltará la granada 2 en esta orden" << endl;
        EnterParaContinuar();
      }
      break;
    case 5:
      if (!currOrden->aterrizaje && !checkAccionesUnicas->hayFinViaje && !currOrden->despegue)
      {
        opcionValida = true;
        currOrden->aterrizaje = true;
        checkAccionesUnicas->hayFinViaje = true;
        cout << "Se aterrizará en esta posición" << endl;
        EnterParaContinuar();
      }
      break;
    case 6:
      if (!currOrden->ataqueKamikaze && !checkAccionesUnicas->hayFinViaje && !currOrden->despegue)
      {
        opcionValida = true;
        currOrden->ataqueKamikaze = true;
        checkAccionesUnicas->hayFinViaje = true;
        cout << "Se hará el ataque kamikaze en esta posición" << endl;
        EnterParaContinuar();
      }
      break;

    case 7:
      cout << "Se cancela la orden al dron" << endl;
      opcionValida = true;

      if (currOrden->despegue)
        checkAccionesUnicas->hayDespegue = false;
      if (currOrden->soltarGranada1)
        checkAccionesUnicas->soltoGranada1 = false;
      if (currOrden->soltarGranada2)
        checkAccionesUnicas->soltoGranada2 = false;
      if (currOrden->ataqueKamikaze)
        checkAccionesUnicas->hayFinViaje = false;
      if (currOrden->aterrizaje)
        checkAccionesUnicas->hayFinViaje = false;
      EnterParaContinuar();
      return;
    case 0:
      if ((currOrden->siguienteX && currOrden->siguienteY) || currOrden->aterrizaje || currOrden->ataqueKamikaze)
      {
        opcionValida = true;
        fwrite(currOrden, sizeof(tOrdenArchivo), 1, ataque);
        checkAccionesUnicas->moverseX = currOrden->siguienteX;
        checkAccionesUnicas->moverseY = currOrden->siguienteY;
        cout << "Se guardó la orden con éxito!!" << endl;
        EnterParaContinuar();
      }
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

void FinalizarSinGuardar(FILE *ataque, string rutaCompleta)
{
  fclose(ataque);
  remove(rutaCompleta.c_str());
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