#include <iostream>
#include "tp_lib.h"

using namespace std;

void GuardarAtaque(tMapaAtaque *pMapa){
  string nombre;
  string rutaCarpeta;
  string rutaCompleta;

  if (pMapa==nullptr){
    cout << "No hay nada cargado en memoria" << endl;
    return;
  }

  // Ingresar nombre del archivo y ruta
  ImprimirSeparador(15, '-', 1, 0);
  cout << "ingrese el nombre del nuevo archivo: " << endl;
  getline(cin, nombre);
  ImprimirSeparador(15, '-', 1, 0);
  cout << "ingrese la ruta de la carpeta donde estará el archivo: " << endl;
  getline(cin, rutaCarpeta);
  ImprimirSeparador(15, '-', 1, 0);

  // Hacer que la ruta contenga el nombre deseado del archivo
  if (!rutaCarpeta.empty() && rutaCarpeta.back() != '/' && rutaCarpeta.back() != '\\') {
    rutaCompleta = rutaCarpeta + "/" + nombre;
  } else {
    rutaCompleta = rutaCarpeta + nombre;
  }

  // Crear archivo
  FILE * Nuevo_Archivo;
  Nuevo_Archivo = fopen(rutaCompleta.c_str(), "wb");

  // Comprobar si se creó el archivo
  if (Nuevo_Archivo == NULL) {
    cout << "No se pudo crear el archivo!!!" << endl;
    return;
  }

  int xActual = -1;
  int yActual = -1;
  bool encontrado = false;
  for (int x = 0; x < ANCHO_MAPA && !encontrado; x++) {
    for (int y = 0; y < ALTO_MAPA && !encontrado; y++) {
      if (pMapa->ordenes[x][y].despegue) {
        xActual = x;
        yActual = y;
        encontrado = true;
      }
    }
  }
  if (!encontrado) {
    cout << "No hay ningun ataque cargado en memoria." << endl;
    return;
  }

  bool finRuta = false;
  while (!finRuta) {
    tOrden celda = pMapa->ordenes[xActual][yActual];
    OrdenArchivo celda_a_guardar;
    celda_a_guardar.x=xActual;
    celda_a_guardar.y=yActual;
    celda_a_guardar.espera = pMapa->ordenes[xActual][yActual].espera;
    celda_a_guardar.soltarGranada1 = pMapa->ordenes[xActual][yActual].soltarGranada1;
    celda_a_guardar.soltarGranada2 = pMapa->ordenes[xActual][yActual].soltarGranada2;
    celda_a_guardar.ataqueKamikaze = pMapa->ordenes[xActual][yActual].ataqueKamikaze;
    celda_a_guardar.aterrizaje = pMapa->ordenes[xActual][yActual].aterrizaje;
    celda_a_guardar.despegue = pMapa->ordenes[xActual][yActual].despegue;
    celda_a_guardar.siguienteX = pMapa->ordenes[xActual][yActual].siguienteX;
    celda_a_guardar.siguienteY = pMapa->ordenes[xActual][yActual].siguienteY;
    fwrite(&celda_a_guardar, sizeof(OrdenArchivo), 1, Nuevo_Archivo);
    if (celda.aterrizaje || celda.ataqueKamikaze) {
      finRuta = true;
    } else {
      xActual = celda.siguienteX;
      yActual = celda.siguienteY;
    }
  }

  cout << "Archivo cargado con éxito" << endl;
  fclose(Nuevo_Archivo);
}