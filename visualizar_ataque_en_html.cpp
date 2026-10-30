#include "tp_lib.h"
#include <filesystem>
#include <iostream>

using namespace std;

void ImprimirFilaHTML(FILE *htmlFile, tOrden orden, int x, int y);

void VisualizarAtaqueHTML(tMapaAtaque *pMapa, tChecksAtaque *checksAtaque,
                          std::string rutaArchivoEnMemoria) {
  if (pMapa == nullptr) {
    cout << "No hay ataque cargado en memoria!!!" << endl;
    return;
  }

  filesystem::path ruta(rutaArchivoEnMemoria);
  ruta.replace_extension(".html");

  FILE *reporteHTML = fopen(ruta.string().c_str(), "w");

  if (!reporteHTML) {
    cout << "No se pudo crear reporte html!!!" << endl;
  }

  fprintf(reporteHTML, "<!DOCTYPE html>\n");
  fprintf(reporteHTML, "<html>\n");
  fprintf(reporteHTML, "<head>\n");
  fprintf(reporteHTML, "<title>\n");
  fprintf(reporteHTML, "Reporte archivo %s\n", ruta.filename().string().c_str());
  fprintf(reporteHTML, "</title>\n");
  fprintf(reporteHTML, "</head>\n");
  fprintf(reporteHTML, "<body>\n");
  fprintf(reporteHTML, "<h1>\n");
  fprintf(reporteHTML, "Reporte archivo %s\n", ruta.filename().string().c_str());
  fprintf(reporteHTML, "</h1>\n");
  fprintf(reporteHTML, "<table>\n");
  fprintf(reporteHTML,
          "<thead><tr><th></th><th>Coordenada</th><th>Despega</th><th>Aterriza</th><th>Suelta "
          "granada 1</th><th>Suelta granada 2</th><th>Ataque kamikaze</th><th>Espera</th><th>Se "
          "mueve a</th></tr></thead>\n");
  fprintf(reporteHTML, "<tbody>\n");

  int i = checksAtaque->coordenadaDespegueX;
  int j = checksAtaque->coordenadaDespegueY;
  int contador = 1;

  while (!pMapa->ordenes[i][j].aterrizaje && !pMapa->ordenes[i][j].ataqueKamikaze) {
    fprintf(reporteHTML, "<tr><th>%d</th>", contador);
    ImprimirFilaHTML(reporteHTML, pMapa->ordenes[i][j], i, j);

    contador++;
    int aux = i;
    i = pMapa->ordenes[i][j].siguienteX;
    j = pMapa->ordenes[aux][j].siguienteY;
  }
  fprintf(reporteHTML, "<tr><th>%d</th>", contador);
  ImprimirFilaHTML(reporteHTML, pMapa->ordenes[i][j], i, j);

  fprintf(reporteHTML, "</tbody>\n");
  fprintf(reporteHTML, "</table>\n");

  fprintf(reporteHTML, "</body>\n");
  fprintf(reporteHTML, "</html>\n");

  fclose(reporteHTML);
  return;
}

void ImprimirFilaHTML(FILE *htmlFile, tOrden orden, int x, int y) {
  fprintf(htmlFile, "<td>%d %d</td>", x, y);

  if (orden.despegue)
    fprintf(htmlFile, "<td>SI</td>");
  else
    fprintf(htmlFile, "<td>NO</td>");

  if (orden.aterrizaje)
    fprintf(htmlFile, "<td>SI</td>");
  else
    fprintf(htmlFile, "<td>NO</td>");

  if (orden.soltarGranada1)
    fprintf(htmlFile, "<td>SI</td>");
  else
    fprintf(htmlFile, "<td>NO</td>");

  if (orden.soltarGranada2)
    fprintf(htmlFile, "<td>SI</td>");
  else
    fprintf(htmlFile, "<td>NO</td>");

  if (orden.ataqueKamikaze)
    fprintf(htmlFile, "<td>SI</td>");
  else
    fprintf(htmlFile, "<td>NO</td>");

  if (orden.espera) {
    fprintf(htmlFile, "<td>%d s.</td>", orden.espera);
  } else {
    fprintf(htmlFile, "<td>-</td>");
  }

  if (!orden.ataqueKamikaze && !orden.aterrizaje)
    fprintf(htmlFile, "<td>%d %d</td>", orden.siguienteX, orden.siguienteY);
  else
    fprintf(htmlFile, "<td>-</td>");

  fprintf(htmlFile, "</tr>\n");
}