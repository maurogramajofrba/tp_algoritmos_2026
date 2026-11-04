#include <iostream>
#include "tp_lib.h"

using namespace std;

void CorregirRegistroDeArchivo() {
  string rutaCompleta;
  FILE *ataque;

  ImprimirSeparador(15, '-', 1, 0);
  cout << " CORREGIR REGISTRO DEL ARCHIVO ";
  ImprimirSeparador(15, '-', 0, 2);

  cout << "Decime la ruta completa del archivo de ataque:" << endl;
  cout << "> ";
  getline(cin, rutaCompleta);

  ataque = fopen(rutaCompleta.c_str(), "rb+");

  if (ataque == NULL) {
    cout << "No se pudo abrir el archivo: " << rutaCompleta << endl;
    return;
  }

  int x, y;
  cout << "Ingrese la posicion X a corregir: ";
  cin >> x;
  cout << "Ingrese la posicion Y a corregir: ";
  cin >> y;

  tOrdenArchivo registro;
  bool encontrado = false;
  long offsetRegistro = -1; // <--- 1. Variable para guardar la posición exacta del byte

  while (fread(&registro, sizeof(tOrdenArchivo), 1, ataque) == 1) {
    if (registro.x == x && registro.y == y) {
      encontrado = true;
      offsetRegistro = ftell(ataque) - sizeof(tOrdenArchivo); // <--- 2. Capturamos el inicio exacto del registro
      break;
    }
  }

  if (!encontrado) {
    cout << "No hay ningun registro en el archivo con esa coordenada." << endl;
    fclose(ataque);
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return;
  }

  cout << endl << "Registro actual:" << endl;
  ImprimirOrden(registro);

  tOrdenArchivo nuevaOrden = {};
  nuevaOrden.x = registro.x;
  nuevaOrden.y = registro.y;

  IngresarOrden(nuevaOrden);

  // Lógica para limpiar registros anteriores si cambia el despegue
  if (nuevaOrden.despegue) {
    rewind(ataque);
    tOrdenArchivo regActual;
    long posActual;

    while (fread(&regActual, sizeof(tOrdenArchivo), 1, ataque) == 1) {
      if (regActual.x == x && regActual.y == y) {
        break;
      }

      if (regActual.despegue) {
        regActual.despegue = false;
      }

      posActual = ftell(ataque);
      fseek(ataque, posActual - (long)sizeof(tOrdenArchivo), SEEK_SET);
      
      tOrdenArchivo registroVacio = {};
      fwrite(&registroVacio, sizeof(tOrdenArchivo), 1, ataque);
      
      fseek(ataque, posActual, SEEK_SET);
    }
  }

  // Lógica para limpiar registros posteriores si cambia el aterrizaje / kamikaze
  if (nuevaOrden.aterrizaje || nuevaOrden.ataqueKamikaze){
    rewind(ataque);
    tOrdenArchivo regActual;
    long posActual;
    bool empezarAEliminar = false;
    
    while (fread(&regActual, sizeof(tOrdenArchivo), 1, ataque) == 1) {
      if (regActual.x == x && regActual.y == y) {
        empezarAEliminar = true;
        continue;
      }
      if (empezarAEliminar) {
        bool eraFinViejo = regActual.aterrizaje || regActual.ataqueKamikaze;

        posActual = ftell(ataque);
        fseek(ataque, posActual - (long)sizeof(tOrdenArchivo), SEEK_SET);
        
        tOrdenArchivo registroVacio = {};
        fwrite(&registroVacio, sizeof(tOrdenArchivo), 1, ataque);
        
        fseek(ataque, posActual, SEEK_SET);

        if (eraFinViejo) {
          break;
        }
      }
   }
  }


  fseek(ataque, offsetRegistro, SEEK_SET);
  fwrite(&nuevaOrden, sizeof(tOrdenArchivo), 1, ataque);
  fclose(ataque);

  cin.ignore(numeric_limits<streamsize>::max(), '\n');
  cout << endl << "Registro corregido correctamente." << endl;
}