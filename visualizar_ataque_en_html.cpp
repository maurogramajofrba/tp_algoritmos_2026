#include <iostream>
#include "tp_lib.h"

using namespace std;

void VisualizarAtaqueHTML()
{
  string html;

  html += R"(
<!DOCTYPE html>
<html>
  <head>
    <title>Hola Mundo</title>
  </head>
  <body>
    <h1>Visualización del ataque</h1>
  </body>
</html>
  )";

  FILE *archivoHTML;
  archivoHTML = fopen("test.html", "w");

  if (archivoHTML == NULL) {
    cout << "Error al crear archivo html!!" <<endl <<endl;
    return;
  }

  fprintf(archivoHTML, html.c_str());

  fclose(archivoHTML);
}