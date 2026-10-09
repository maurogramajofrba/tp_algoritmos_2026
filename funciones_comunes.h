#ifndef FUNCIONES_COMUNES_H
#define FUNCIONES_COMUNES_H

#include "tp_types.h"

#define SEPARADOR_LEN 40
#define SEPARADOR_CARACTER '*'
#define SEPARADOR_SALTO_SUPERIOR 1
#define SEPARADOR_SALTO_INFERIOR 2

/*
* Acá podemos poner todas las interfaces de funciones en común del tp.
* Ejemplos: BurbujaSort, ValidarDespegue
*/
void ImprimirSeparador(
  int len = SEPARADOR_LEN,
  char caracter = SEPARADOR_CARACTER,
  int saltosSuperior = SEPARADOR_SALTO_SUPERIOR,
  int saltosInferior = SEPARADOR_SALTO_INFERIOR
);

void EnterParaContinuar();

#endif