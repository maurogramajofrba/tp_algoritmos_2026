#ifndef TP_TYPES_H
#define TP_TYPES_H

#define ANCHO_MAPA 200
#define ALTO_MAPA 200

typedef struct Orden {
  unsigned int espera;
  bool soltarGranada1;
  bool soltarGranada2;
  bool ataqueKamikaze;
  bool aterrizaje;
  bool despegue;
  int siguienteX;
  int siguienteY;
} tOrden;

typedef struct OrdenArchivo {
  int x;
  int y;
  unsigned int espera;
  bool soltarGranada1;
  bool soltarGranada2;
  bool ataqueKamikaze;
  bool aterrizaje;
  bool despegue;
  int siguienteX;
  int siguienteY;
} tOrdenArchivo;

typedef struct ChecksAtaque {
  bool hayDespegue;
  bool soltoGranada1;
  bool soltoGranada2;
  bool hayAterrizaje;
  bool hayAtaqueKamikaze;
  int cantPosiciones;
  int posicionesUsadas[ANCHO_MAPA * ALTO_MAPA - 1];
  int moverseX;
  int moverseY;
} tChecksAtaque;

typedef struct MapaAtaque {
  tOrden ordenes[ANCHO_MAPA][ALTO_MAPA];
} tMapaAtaque;

#endif