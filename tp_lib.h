#ifndef TP_LIB_H
#define TP_LIB_H

#include <limits>
#include "tp_types.h"
#include "funciones_comunes.h"

void CargarAtaqueEnMemoria(tMapaAtaque *&pMapa);
void MostrarAtaque(tMapaAtaque *pMapa);
void CrearNuevoAtaque();
void CorregirRegistroDeMemoria(tMapaAtaque *pMapa);
void GuardarAtaque(tMapaAtaque *pMapa);
void CorregirRegistroDeArchivo();

//Agregar aquí interfaces

#endif