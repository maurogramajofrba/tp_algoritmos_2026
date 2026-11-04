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
    return;
  }

  int xActual = checksAtaque->coordenadaDespegueX;
  int yActual = checksAtaque->coordenadaDespegueY;

  fprintf(reporteHTML, "<!DOCTYPE html>\n");
  fprintf(reporteHTML, "<html>\n");
  fprintf(reporteHTML, "<head>\n");
  fprintf(reporteHTML, "<title>\n");
  fprintf(reporteHTML, "Ataque %s\n", ruta.stem().string().c_str());
  fprintf(reporteHTML, "</title>\n");
  fprintf(reporteHTML, "<style>\n");

  fprintf(reporteHTML, "body {\n");
  fprintf(reporteHTML, "  font-family: Arial, sans-serif;\n");
  fprintf(reporteHTML, "  background-color: #f4f6f8;\n");
  fprintf(reporteHTML, "  color: #263238;\n");
  fprintf(reporteHTML, "  display: flex;\n");
  fprintf(reporteHTML, "  flex-direction: column;\n");
  fprintf(reporteHTML, "  gap: 24px;\n");
  fprintf(reporteHTML, "  align-items: center;\n");
  fprintf(reporteHTML, "}\n");

  fprintf(reporteHTML, "h1 {\n");
  fprintf(reporteHTML, "  color: #254b70;\n");
  fprintf(reporteHTML, "}\n");

  fprintf(reporteHTML, "table {\n");
  fprintf(reporteHTML, "  width: 100%%;\n");
  fprintf(reporteHTML, "  max-width: 1000px;\n");
  fprintf(reporteHTML, "  margin: 30px;\n");
  fprintf(reporteHTML, "  border-collapse: collapse;\n");
  fprintf(reporteHTML, "  background-color: white;\n");
  fprintf(reporteHTML, "}\n");

  fprintf(reporteHTML, "th, td {\n");
  fprintf(reporteHTML, "  text-align: center;\n");
  fprintf(reporteHTML, "  padding: 10px;\n");
  fprintf(reporteHTML, "  border: 1px solid #d5dce3;\n");
  fprintf(reporteHTML, "}\n");

  fprintf(reporteHTML, "thead th {\n");
  fprintf(reporteHTML, "  background-color: #254b70;\n");
  fprintf(reporteHTML, "  color: white;\n");
  fprintf(reporteHTML, "  vertical-align: top;\n");
  fprintf(reporteHTML, "}\n");

  fprintf(reporteHTML, "tbody tr:nth-child(even) {\n");
  fprintf(reporteHTML, "  background-color: #edf2f7;\n");
  fprintf(reporteHTML, "}\n");

  fprintf(reporteHTML, "tbody tr:hover {\n");
  fprintf(reporteHTML, "  background-color: #dceaf7;\n");
  fprintf(reporteHTML, "}\n");

  fprintf(reporteHTML, "</style>\n");
  fprintf(reporteHTML, "</head>\n");
  fprintf(reporteHTML, "<body>\n");
  fprintf(reporteHTML, "<h1>\n");
  fprintf(reporteHTML, "Reporte ataque %s\n", ruta.stem().string().c_str());
  fprintf(reporteHTML, "</h1>\n");
  fprintf(reporteHTML, "<table>\n");
  fprintf(reporteHTML, "<thead>\n");
  fprintf(reporteHTML, "<tr>\n");
  fprintf(reporteHTML, "<th rowspan=\"2\">N°</th>\n");
  fprintf(reporteHTML, "<th colspan=\"2\">Coordenada</th>\n");
  fprintf(reporteHTML, "<th rowspan=\"2\">Despega</th>\n");
  fprintf(reporteHTML, "<th rowspan=\"2\">Aterriza</th>\n");
  fprintf(reporteHTML, "<th rowspan=\"2\">Suelta granada 1</th>\n");
  fprintf(reporteHTML, "<th rowspan=\"2\">Suelta granada 2</th>\n");
  fprintf(reporteHTML, "<th rowspan=\"2\">Ataque kamikaze</th>\n");
  fprintf(reporteHTML, "<th rowspan=\"2\">Espera</th>\n");
  fprintf(reporteHTML, "<th colspan=\"2\">Se mueve a</th>\n");
  fprintf(reporteHTML, "</tr>\n");

  fprintf(reporteHTML, "<tr>\n");
  fprintf(reporteHTML, "<th>X</th>\n");
  fprintf(reporteHTML, "<th>Y</th>\n");
  fprintf(reporteHTML, "<th>X</th>\n");
  fprintf(reporteHTML, "<th>Y</th>\n");
  fprintf(reporteHTML, "</tr>\n");
  fprintf(reporteHTML, "</thead>\n");
  fprintf(reporteHTML, "<tbody>\n");

  int contador = 1;
  bool finRuta = false;
  while (!finRuta) {
    fprintf(reporteHTML, "<tr><th scope=\"row\">%d</th>", contador);
    ImprimirFilaHTML(reporteHTML, pMapa->ordenes[xActual][yActual], xActual, yActual);
    contador++;

    if (pMapa->ordenes[xActual][yActual].aterrizaje ||
        pMapa->ordenes[xActual][yActual].ataqueKamikaze) {
      finRuta = true;
    } else {
      int aux = xActual;
      xActual = pMapa->ordenes[xActual][yActual].siguienteX;
      yActual = pMapa->ordenes[aux][yActual].siguienteY;
    }
  }

  fprintf(reporteHTML, "</tbody>\n");
  fprintf(reporteHTML, "</table>\n");

  fprintf(reporteHTML, "</body>\n");
  fprintf(reporteHTML, "</html>\n");

  fclose(reporteHTML);
  cout << "Se creo el reporte HTML en la misma ruta del archivo: "
       << ruta.string() << endl;
  return;
}

void ImprimirFilaHTML(FILE *htmlFile, tOrden orden, int x, int y) {
  fprintf(htmlFile, "<td>%d</td>\n", x);
  fprintf(htmlFile, "<td>%d</td>\n", y);

  if (orden.despegue)
    fprintf(htmlFile, "<td>SI</td>");
  else
    fprintf(htmlFile, "<td>-</td>");

  if (orden.aterrizaje)
    fprintf(htmlFile, "<td>SI</td>");
  else
    fprintf(htmlFile, "<td>-</td>");

  if (orden.soltarGranada1)
    fprintf(htmlFile, "<td>SI</td>");
  else
    fprintf(htmlFile, "<td>-</td>");

  if (orden.soltarGranada2)
    fprintf(htmlFile, "<td>SI</td>");
  else
    fprintf(htmlFile, "<td>-</td>");

  if (orden.ataqueKamikaze)
    fprintf(htmlFile, "<td>SI</td>");
  else
    fprintf(htmlFile, "<td>-</td>");

  if (orden.espera) {
    fprintf(htmlFile, "<td>%d s.</td>", orden.espera);
  } else {
    fprintf(htmlFile, "<td>-</td>");
  }

  if (!orden.ataqueKamikaze && !orden.aterrizaje) {
    fprintf(htmlFile, "<td>%d</td>\n", orden.siguienteX);
    fprintf(htmlFile, "<td>%d</td>\n", orden.siguienteY);
  } else {
    fprintf(htmlFile, "<td>-</td>\n");
    fprintf(htmlFile, "<td>-</td>\n");
  }

  fprintf(htmlFile, "</tr>\n");
}
