#ifndef TP_LIB_H
#define TP_LIB_H

#include <limits>
#include "tp_types.h"
#include "funciones_comunes.h"

void CargarAtaqueEnMemoria(tMapaAtaque *&pMapa, tChecksAtaque *&checksAtaque);
void MostrarAtaque(tMapaAtaque *pMapa);
void CrearNuevoAtaque();
void CorregirRegistroDeMemoria();
void GuardarAtaque();
void CorregirRegistroDeArchivo();
void VisualizarAtaqueHTML();

//Agregar aquí interfaces

#endif