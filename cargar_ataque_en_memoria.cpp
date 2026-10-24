#include <iostream>
#include "tp_lib.h"

using namespace std;

void CargarAtaqueEnMemoria(OrdenArchivo pMapa[200][200])
{
  string rutaCompleta;
  FILE *ataque;

  ImprimirSeparador(15, '-', 1, 0);
  cout << " CARGAR ATAQUE EN MEMORIA ";
  ImprimirSeparador(15, '-', 0, 2);
  cout << "Decime la ruta completa del archivo de ataque:" << endl;
  cout << "> ";
  getline(cin, rutaCompleta);

  ataque = fopen(rutaCompleta.c_str(), "rb");

  if (ataque == NULL)
  {
    cout << "No se pudo abrir el archivo: " << rutaCompleta << endl;
    return;
  }

  cout << "Archivo abierto correctamente." << endl;

  OrdenArchivo ataque_leido;
  int contador_despegues = 0;
  bool cancelado = false;
  bool visitados[200][200] = {false};
  int finales = 0;


  // Chequear las validaciones fundamentales
  while(fread(&ataque_leido, sizeof(OrdenArchivo),1, ataque)){
    // Medida por si los valores son incorrectos
    if (ataque_leido.x < 0 || ataque_leido.x >= 200 || ataque_leido.y < 0 || ataque_leido.y >= 200) {
      cancelado = true;
    }
    // Revisar si ya paso por esa ubicacion
    if (visitados[ataque_leido.x][ataque_leido.y]) {
      cancelado = true;
    } else {
      visitados[ataque_leido.x][ataque_leido.y] = true;
    }
    // Sólo debe haber 1 despegue
    if (ataque_leido.despegue){
      contador_despegues++;
      // El despegue no puede estar acompañado de ningún ataque
      if(ataque_leido.ataqueKamikaze || ataque_leido.soltarGranada1 || ataque_leido.soltarGranada2){
        cancelado = true;
      }
    }
    // Debe existir una sóla instrucción de final
    if (ataque_leido.ataqueKamikaze){
      finales++;
    }
    if (ataque_leido.aterrizaje){
      finales++;
    }
  }
  if(finales !=1 || contador_despegues>1){
    cancelado = true;
  }

  // Abortar si no cumple las condiciones
  if(cancelado){
    ImprimirSeparador(15, '-', 1, 0);
    cout << "El archivo no cumple con los requisitos, intente con otro" << endl;
    ImprimirSeparador(15, '-', 1, 0);
    fclose(ataque);
    CargarAtaqueEnMemoria();
  }

  // Devolver el cursor del archivo al principio
  rewind(ataque);

  // Cargar los ataques en la memoria
  while(fread(&ataque_leido, sizeof(OrdenArchivo),1, ataque)){
    if (ataque_leido.despegue){
      pMapa[ataque_leido.x][ataque_leido.y].despegue = true;
    }
    if (ataque_leido.aterrizaje){
      pMapa[ataque_leido.x][ataque_leido.y].aterrizaje = true;
    }
    if (ataque_leido.soltarGranada1){
      pMapa[ataque_leido.x][ataque_leido.y].soltarGranada1 = true;
    }
    if (ataque_leido.soltarGranada2){
      pMapa[ataque_leido.x][ataque_leido.y].soltarGranada2 = true;
    }
    if (ataque_leido.ataqueKamikaze){
      pMapa[ataque_leido.x][ataque_leido.y].ataqueKamikaze = true;
    }
    if (ataque_leido.espera){
      pMapa[ataque_leido.x][ataque_leido.y].espera = ataque_leido.espera;
    } // A CHECKEAR
    if (ataque_leido.siguienteX && ataque_leido.siguienteY){
      pMapa[ataque_leido.x][ataque_leido.y].siguienteX = ataque_leido.siguienteX;
      pMapa[ataque_leido.x][ataque_leido.y].siguienteY = ataque_leido.siguienteY;
    }
  }
  fclose(ataque);
}