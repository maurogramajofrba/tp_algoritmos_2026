#include "tp_lib.h"
#include <iostream>

using namespace std;

bool LeerOpcion(string mensaje);
void AgregarOrdenArchivo(FILE *ataque, tChecksAtaque *checksAtaque);

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

  tChecksAtaque checksAtaque = {};

  int opcion;

  do {
    if (checksAtaque.cantCoordenadas > 0) {
      cout << endl << "Resumen ataque nuevo:" << endl;
      if (checksAtaque.hayDespegue)
        cout << "El dron se movio " << checksAtaque.cantCoordenadas << " veces por el mapa."
             << endl;
      if (checksAtaque.hayDespegue)
        cout << "Despega con exito." << endl;
      if (checksAtaque.soltoGranada1)
        cout << "Soltó la granada 1." << endl;
      if (checksAtaque.soltoGranada2)
        cout << "Soltó la granada 2." << endl;
      if (checksAtaque.hayAterrizaje)
        cout << "Aterrizo." << endl;
      if (checksAtaque.hayAtaqueKamikaze)
        cout << "Hizo ataque kamikaze." << endl;

      if (checksAtaque.hayAterrizaje || checksAtaque.hayAtaqueKamikaze) {
        cout << "Ataque finalizado y guardado con exito!!! volviendo al menu..." << endl;
        fclose(ataque);
        return;
      }

      cout << endl << "1. Agregar orden." << endl;
      cout << "0. Cancelar creación neuvo ataque." << endl;

      opcion = LeerOpcion("Opcion > ");
    } else {
      opcion = 1;
    }

    switch (opcion) {
    case 1:
      AgregarOrdenArchivo(ataque, &checksAtaque);
      break;
    case 0:
      fclose(ataque);
      remove(rutaCompleta.c_str());
      break;
    default:
      cout << "Opción inválida intente nuevamente!" << endl << endl;

      break;
    }
  } while (opcion);
}

bool LeerOpcion(string mensaje) {
  int opcion;
  bool valida;

  do {
    cout << mensaje;
    valida = bool(cin >> opcion);

    if (!valida)
      cin.clear();

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    valida = valida && (opcion == 0 || opcion == 1);

    if (!valida)
      cout << "Valor invalido. Ingrese 0 o 1." << endl;

  } while (!valida);

  return opcion == 1;
}

void AgregarOrdenArchivo(FILE *ataque, tChecksAtaque *checksAtaque) {
  tOrdenArchivo nuevaOrden = {};

  if (!checksAtaque->hayDespegue) {
    nuevaOrden.despegue = true;
    cout << "Indique donde despegara el dron:" << endl;
    bool valida;

    do {
      cout << "x y > ";
      valida = bool(cin >> nuevaOrden.x >> nuevaOrden.y);

      if (!valida)
        cin.clear();

      cin.ignore(numeric_limits<streamsize>::max(), '\n');

      valida = valida && EsMovimientoValido(nuevaOrden.x, nuevaOrden.y);

      if (!valida)
        cout << "Coordenadas invalidas ingreselas correctamente:" << endl;

    } while (!valida);
  } else {
    nuevaOrden.x = checksAtaque->moverseX;
    nuevaOrden.y = checksAtaque->moverseY;
    cout << "x y > " << nuevaOrden.x << " " << nuevaOrden.y << endl;
  }

  int segundos;
  bool valida;

  cout << "Espera? (Ingrese tiempo en segundos):" << endl;
  do {
    valida = bool(cin >> segundos);

    if (!valida)
      cin.clear();

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    valida = valida && segundos >= 0;

    if (!valida)
      cout << "Tiempo de espera invalido, ingreselo correctamente:" << endl;

  } while (!valida);

  nuevaOrden.espera = segundos;

  if (!nuevaOrden.despegue && !nuevaOrden.aterrizaje && !nuevaOrden.ataqueKamikaze) {
    nuevaOrden.aterrizaje = LeerOpcion("Aterriza? (0 = NO, 1 = SI):");
  }

  if (!nuevaOrden.despegue && !nuevaOrden.soltarGranada1 && !checksAtaque->soltoGranada1) {
    nuevaOrden.soltarGranada1 = LeerOpcion("Suelta granada 1? (0 = NO, 1 = SI):");
  }

  if (!nuevaOrden.despegue && !nuevaOrden.soltarGranada2 && !checksAtaque->soltoGranada2) {
    nuevaOrden.soltarGranada2 = LeerOpcion("Suelta granada 2? (0 = NO, 1 = SI):");
  }

  if (!nuevaOrden.despegue && !nuevaOrden.ataqueKamikaze && !nuevaOrden.aterrizaje) {
    nuevaOrden.ataqueKamikaze = LeerOpcion("Ataque kamikaze? (0 = NO, 1 = SI): ");
  }

  if (!nuevaOrden.siguienteX && !nuevaOrden.siguienteY && !nuevaOrden.ataqueKamikaze &&
      !nuevaOrden.aterrizaje) {
    bool valida;

    cout << "Ingresa siguiente coordenada del dron:" << endl;
    do {
      cout << "x y > ";
      valida = bool(cin >> nuevaOrden.siguienteX >> nuevaOrden.siguienteY);

      if (!valida)
        cin.clear();

      cin.ignore(numeric_limits<streamsize>::max(), '\n');

      valida = valida &&
               EsMovimientoValido(nuevaOrden.siguienteX, nuevaOrden.siguienteY, nuevaOrden.x,
                                  nuevaOrden.y) &&
               !checksAtaque->coordenadasUsadas[nuevaOrden.siguienteX][nuevaOrden.siguienteY];

      if (!valida)
        cout << "Siguiente coordenada invalida, ingresela correctamente:" << endl;

    } while (!valida);
  }

  if (fwrite(&nuevaOrden, sizeof(tOrdenArchivo), 1, ataque)) {
    if (nuevaOrden.despegue) {
      checksAtaque->hayDespegue = true;
      checksAtaque->coordenadaDespegueX = nuevaOrden.x;
      checksAtaque->coordenadaDespegueY = nuevaOrden.y;
    }

    if (nuevaOrden.aterrizaje)
      checksAtaque->hayAterrizaje = true;

    if (nuevaOrden.soltarGranada1)
      checksAtaque->soltoGranada1 = true;

    if (nuevaOrden.soltarGranada2)
      checksAtaque->soltoGranada2 = true;

    if (nuevaOrden.ataqueKamikaze)
      checksAtaque->hayAtaqueKamikaze = true;

    checksAtaque->coordenadasUsadas[nuevaOrden.x][nuevaOrden.y] = true;
    checksAtaque->cantCoordenadas += 1;
    checksAtaque->moverseX = nuevaOrden.siguienteX;
    checksAtaque->moverseY = nuevaOrden.siguienteY;
    cout << "Se guardó la orden con éxito!!" << endl;
  } else {
    cout << "Fallo guardar la orden en el archivo!!! reintentar..." << endl;
  }
}