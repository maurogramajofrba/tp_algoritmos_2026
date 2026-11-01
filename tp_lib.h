#ifndef TP_LIB_H
#define TP_LIB_H

#include <limits>
#include "tp_types.h"
#include "funciones_comunes.h"
#include <string>

void CargarAtaqueEnMemoria(tMapaAtaque *&pMapa, tChecksAtaque *&checksAtaque, std::string &rutaCompleta);
void MostrarAtaque(tMapaAtaque *pMapa);
void CrearNuevoAtaque();
void CorregirRegistroDeMemoria(tMapaAtaque *pMapa, tChecksAtaque *checksAtaque);
void GuardarAtaque(tMapaAtaque *pMapa);
void CorregirRegistroDeArchivo();
void VisualizarAtaqueHTML(tMapaAtaque *pMapa, tChecksAtaque *checksAtaque, std::string rutaArchivoEnMemoria);

//Agregar aquí interfaces

#endif