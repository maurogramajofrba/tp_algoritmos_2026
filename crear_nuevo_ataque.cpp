#include "tp_lib.h"
#include <iostream>

using namespace std;

void AgregarOrdenArchivo(FILE *ataque, tChecksAtaque *checksAtaque, tOrdenArchivo *ordenAnterior);
void menuOrden(FILE *ataque, tOrdenArchivo *currOrden, tChecksAtaque *checksAtaque,
               tOrdenArchivo *ordenAnterior);
void FinalizarSinGuardar(FILE *ataque, string rutaCompleta);

void CrearNuevoAtaque() {
  string rutaCompleta;
  FILE *ataque;

  ImprimirSeparador(15, '-', 1, 0);
  cout << " CREAR ATAQUE NUEVO ";
  ImprimirSeparador(15, '-', 0, 2);

  cout << "Decime la ruta completa del archivo del nuevo ataque:" << endl;
  cout << "> ";
  getline(cin, rutaCompleta);

  ataque = fopen(rutaCompleta.c_str(), "wb");

  if (ataque == NULL) {
    cout << "No se pudo abrir el archivo: " << rutaCompleta << endl;
    return;
  }

  cout << "Archivo abierto correctamente." << endl;

  tChecksAtaque checksAtaque = {};
  tOrdenArchivo *ordenAnterior = nullptr;

  int opcion;

  do {
    if (checksAtaque.hayDespegue)
      cout << "El dron despega con exito." << endl;
    if (checksAtaque.soltoGranada1)
      cout << "El dron soltó la granada 1." << endl;
    if (checksAtaque.soltoGranada2)
      cout << "El dron soltó la granada 2." << endl;
    if (checksAtaque.hayAterrizaje)
      cout << "El dron aterrizo." << endl;
    if (checksAtaque.hayAtaqueKamikaze)
      cout << "El dron hizo ataque kamikaze." << endl;

    if (!(checksAtaque.hayAterrizaje || checksAtaque.hayAtaqueKamikaze))
      cout << "1. Agregar orden." << endl;
    else
      cout << "1. Ataque finalizado! volver al menú principal." << endl;

    cout << "0. Cancelar creación neuvo ataque." << endl;

    cin >> opcion;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    switch (opcion) {
    case 1:
      if (!(checksAtaque.hayAterrizaje || checksAtaque.hayAtaqueKamikaze)) {
        AgregarOrdenArchivo(ataque, &checksAtaque, ordenAnterior);
        break;
      } else {
        fclose(ataque);
        return;
      }
    case 0:
      FinalizarSinGuardar(ataque, rutaCompleta);
      break;
    default:
      cout << "Opción inválida intente nuevamente!" << endl << endl;

      break;
    }
  } while (opcion);
}

void AgregarOrdenArchivo(FILE *ataque, tChecksAtaque *checksAtaque, tOrdenArchivo *ordenAnterior) {
  tOrdenArchivo nuevaOrden = {};
  if (ordenAnterior != nullptr) {
    nuevaOrden.x = ordenAnterior->siguienteX;
    nuevaOrden.y = ordenAnterior->siguienteY;
  }

  if (!checksAtaque->hayDespegue) {
    nuevaOrden.despegue = true;
    do {
      cout << "Indique donde despegara el dron:" << endl;
      cout << "x y > ";
      cin >> nuevaOrden.x >> nuevaOrden.y;
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
    } while (!EsMovimientoValido(nuevaOrden.x, nuevaOrden.y));
  }

  menuOrden(ataque, &nuevaOrden, checksAtaque, ordenAnterior);
}

void menuOrden(FILE *ataque, tOrdenArchivo *currOrden, tChecksAtaque *checksAtaque,
               tOrdenArchivo *ordenAnterior) {
  int opcion;

  do {
    cout << "El dron está en x: " << currOrden->x << " y: " << currOrden->y << endl
         << "Realiza las siguientes acciones:" << endl;
    if (currOrden->despegue)
      cout << "Despega." << endl;
    if (currOrden->aterrizaje)
      cout << "Aterriza." << endl;
    if (currOrden->soltarGranada1)
      cout << "Suelta granada 1." << endl;
    if (currOrden->soltarGranada2)
      cout << "Suelta granada 2." << endl;
    if (currOrden->ataqueKamikaze)
      cout << "Hace ataque kamikaze." << endl;
    if (currOrden->espera)
      cout << "Espera " << currOrden->espera << " segundos." << endl;
    if (currOrden->siguienteX && currOrden->siguienteY)
      cout << "Se mueve a x: " << currOrden->siguienteX << " y:" << currOrden->siguienteY << endl;

    if (!currOrden->espera)
      cout << "1. Esperar" << endl;
    if (!(currOrden->siguienteX || currOrden->siguienteY) && !currOrden->ataqueKamikaze &&
        !currOrden->aterrizaje && !checksAtaque->hayAterrizaje && !checksAtaque->hayAtaqueKamikaze)
      cout << "2. Moverse" << endl;
    if (!currOrden->despegue && !currOrden->soltarGranada1 && !checksAtaque->soltoGranada1)
      cout << "3. Soltar granada 1" << endl;
    if (!currOrden->despegue && !currOrden->soltarGranada2 && !checksAtaque->soltoGranada2)
      cout << "4. Soltar granada 2" << endl;
    if (!currOrden->despegue && !currOrden->aterrizaje && !checksAtaque->hayAterrizaje &&
        !checksAtaque->hayAtaqueKamikaze)
      cout << "5. Aterrizar" << endl;
    if (!currOrden->despegue && !currOrden->ataqueKamikaze && !checksAtaque->hayAterrizaje &&
        !checksAtaque->hayAtaqueKamikaze)
      cout << "6. Ataque kamikaze" << endl;
    cout << "7. Cancelar orden" << endl;

    cout << "0. Finalizar orden" << endl;

    cin >> opcion;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    bool opcionValida = false;

    switch (opcion) {
    case 1:
      if (!currOrden->espera) {
        opcionValida = true;
        do {
          cout << "Ingrese segundos a esperar válidos:" << endl;
          cin >> currOrden->espera;
          cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } while (currOrden->espera < 1);
      }
      break;
    case 2:
      if (!currOrden->siguienteX && !currOrden->siguienteY && !currOrden->ataqueKamikaze &&
          !currOrden->aterrizaje && !checksAtaque->hayAterrizaje &&
          !checksAtaque->hayAtaqueKamikaze) {
        opcionValida = true;
        do {
          cout << "Ingresa la posición válida a moverse:" << endl;
          cout << "x y > ";
          cin >> currOrden->siguienteX >> currOrden->siguienteY;
          cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } while (!EsMovimientoValido(currOrden->siguienteX, currOrden->siguienteY, currOrden->x,
                                     currOrden->y) ||
                 checksAtaque->coordenadasUsadas[currOrden->siguienteX][currOrden->siguienteY]);
      }
      break;
    case 3:
      if (!currOrden->soltarGranada1 && !checksAtaque->soltoGranada1 && !currOrden->despegue) {
        opcionValida = true;
        currOrden->soltarGranada1 = true;
        checksAtaque->soltoGranada1 = true;
        cout << "Se soltará la granada 1 en esta orden" << endl;
      }
      break;
    case 4:
      if (!currOrden->soltarGranada2 && !checksAtaque->soltoGranada2 && !currOrden->despegue) {
        opcionValida = true;
        currOrden->soltarGranada2 = true;
        checksAtaque->soltoGranada2 = true;
        cout << "Se soltará la granada 2 en esta orden" << endl;
      }
      break;
    case 5:
      if (!currOrden->despegue && !currOrden->aterrizaje && !checksAtaque->hayAterrizaje &&
          !checksAtaque->hayAtaqueKamikaze) {
        opcionValida = true;
        currOrden->aterrizaje = true;
        checksAtaque->hayAterrizaje = true;
        cout << "Se aterrizará en esta posición" << endl;
      }
      break;
    case 6:
      if (!currOrden->despegue && !currOrden->ataqueKamikaze && !checksAtaque->hayAterrizaje &&
          !checksAtaque->hayAtaqueKamikaze) {
        opcionValida = true;
        currOrden->ataqueKamikaze = true;
        checksAtaque->hayAtaqueKamikaze = true;
        cout << "Se hará el ataque kamikaze en esta posición" << endl;
      }
      break;

    case 7:
      cout << "Se cancela la orden al dron" << endl;
      opcionValida = true;

      if (currOrden->despegue) {
        checksAtaque->hayDespegue = false;
        checksAtaque->coordenadaDespegueX = -1;
        checksAtaque->coordenadaDespegueY = -1;
      }
      if (currOrden->soltarGranada1)
        checksAtaque->soltoGranada1 = false;
      if (currOrden->soltarGranada2)
        checksAtaque->soltoGranada2 = false;
      if (currOrden->ataqueKamikaze)
        checksAtaque->hayAtaqueKamikaze = false;
      if (currOrden->aterrizaje)
        checksAtaque->hayAterrizaje = false;

      return;
    case 0:
      if ((currOrden->siguienteX && currOrden->siguienteY) || currOrden->aterrizaje ||
          currOrden->ataqueKamikaze) {
        opcionValida = true;
        fwrite(currOrden, sizeof(tOrdenArchivo), 1, ataque);

        if (currOrden->despegue) {
          checksAtaque->hayDespegue = true;
          checksAtaque->coordenadaDespegueX = currOrden->x;
          checksAtaque->coordenadaDespegueY = currOrden->y;
        }
        checksAtaque->coordenadasUsadas[currOrden->x][currOrden->y] = true;
        checksAtaque->cantCoordenadas += 1;
        ordenAnterior = currOrden;
        cout << "Se guardó la orden con éxito!!" << endl;
      }
    default:
      break;
    }

    if (!opcionValida) {
      cout << "Opción inválida intente nuevamente!" << endl << endl;
    }
  } while (opcion);
}

void FinalizarSinGuardar(FILE *ataque, string rutaCompleta) {
  fclose(ataque);
  remove(rutaCompleta.c_str());
}