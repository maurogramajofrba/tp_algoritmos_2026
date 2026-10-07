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

#endif