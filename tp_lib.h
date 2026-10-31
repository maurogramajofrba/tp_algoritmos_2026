#ifndef TP_LIB_H
#define TP_LIB_H

#include <limits>
#include "tp_types.h"
#include "funciones_comunes.h"
#include <string>

void CargarAtaqueEnMemoria(tMapaAtaque *&pMapa, std::string &rutaArchivoEnMemoria);
void MostrarAtaque(tMapaAtaque *pMapa);
void CrearNuevoAtaque();
void CorregirRegistroDeMemoria(tMapaAtaque *pMapa);
void GuardarAtaque(tMapaAtaque *pMapa);
void CorregirRegistroDeArchivo();
void VisualizarAtaqueHTML(tMapaAtaque *pMapa, std::string rutaArchivoEnMemoria);

//Agregar aquí interfaces

#endif