#include "tp_lib.h"
#include <iostream>

using namespace std;

string DibujarTabla(tMapaAtaque *pMapa, ChecksAtaque *checksAtaque);
// DOCUMENTACION DE TOOLTIPS
// https://developer.mozilla.org/en-US/docs/Web/Accessibility/ARIA/Reference/Roles/tooltip_role
string DibujarEmoji(string idTooltip, string emoji);
string DibujarTooltip(string id, string texto);

void VisualizarAtaqueHTML(tMapaAtaque *pMapa, tChecksAtaque *checksAtaque,
                          std::string rutaArchivoEnMemoria) {
  string html;

  html += R"(
<!DOCTYPE html>
<html>
  <head>
    <title>Hola Mundo</title>
    <meta charset="UTF-8">
    <link rel="stylesheet" href="estilos.css">
  </head>
  <body class="bodyStyle">
    <div class="encabezadoStyle">
      <h1>Visualización del ataque</h1>
      <div class="infoBlockStyle">
        <div class="descriptionBlockStyle">
          <p>Grafico del ataque</p>
        </div>
        <div class="summaryBlockStyle">
        </div>
      </div>
    </div>
    )" + DibujarTabla(pMapa, checksAtaque);
  html += R"(
    <script>
      // Mover el tooltip compartido junto al emoji que lo necesita.
      function mostrarTooltip(evento) {
        const emoji = evento.target.closest('.info > span');
        if (!emoji) return;
        const tooltip = document.getElementById(emoji.getAttribute('aria-describedby'));
        if (!tooltip) return;
        tooltip.style.removeProperty('visibility');
        emoji.parentElement.appendChild(tooltip);
      }
      document.addEventListener('mouseover', mostrarTooltip);
      document.addEventListener('keydown', function(evento) {
        if (evento.key === 'Escape') {
          document.querySelectorAll('[role="tooltip"]').forEach(function(tooltip) {
            tooltip.style.visibility = 'hidden';
          });
        }
      });
    </script>
  </body>
</html>
  )";

  FILE *archivoHTML;
  archivoHTML = fopen("test.html", "w");

  if (archivoHTML == NULL) {
    cout << "Error al crear archivo html!!" << endl << endl;
    return;
  }

  fprintf(archivoHTML, html.c_str());

  fclose(archivoHTML);
}

string DibujarTabla(tMapaAtaque *pMapa, ChecksAtaque *checksAtaque) {
  string tooltips = DibujarTooltip("despegue", "El dron despega");
  tooltips += DibujarTooltip("aterrizaje", "El dron aterriza");
  tooltips += DibujarTooltip("granada1", "El dron lanza granada 1");
  tooltips += DibujarTooltip("granada2", "El dron lanza granada 2");
  tooltips += DibujarTooltip("kamikaze", "El dron hace un ataque kamikaze");

  string tabla = "<table class=\"tablaStyle\">\n";

  tabla += "<thead><tr><th>Y / X</th>";

  for (int j = 0; j < 20; j++) {
    tabla += "<th scope='col'>" + to_string(j) + "</th>";
  }

  tabla += "</tr></thead><tbody>";

  for (int i = 0; i < 20; i++) {
    tabla += "<tr class=\"filaStyle\">\n";
    tabla += "<th scope='row'>" + to_string(i) + "</th>";
    for (int j = 0; j < 20; j++) {
      tabla += "<td class=\"columnaStyle\">\n";
      if (checksAtaque->coordenadasUsadas[i][j]) {
        tabla += "<div class=\"celdaStyle\">\n";
        if (pMapa->ordenes[i][j].despegue)
          tabla += DibujarEmoji("despegue", "🛫");
        if (pMapa->ordenes[i][j].aterrizaje)
          tabla += DibujarEmoji("aterrizaje", "🛬");
        if (pMapa->ordenes[i][j].soltarGranada1)
          tabla += DibujarEmoji("granada1", "💣");
        if (pMapa->ordenes[i][j].soltarGranada2)
          tabla += DibujarEmoji("granada2", "💣");
        if (pMapa->ordenes[i][j].ataqueKamikaze)
          tabla += DibujarEmoji("kamikaze", "💥");
        if (pMapa->ordenes[i][j].espera) {
          string idEspera = "espera-" + to_string(i) + "-" + to_string(j);
          tabla += DibujarEmoji(idEspera, "⌛");
          tooltips +=
              DibujarTooltip(idEspera, "El dron espera aqui " +
                                           to_string(pMapa->ordenes[i][j].espera) + " segundos");
        }
        if (pMapa->ordenes[i][j].siguienteX && pMapa->ordenes[i][j].siguienteY) {
          string idMovimiento = "movimiento-" + to_string(i) + "-" + to_string(j);
          tabla += DibujarEmoji(idMovimiento, "✈️");
          tooltips += DibujarTooltip(idMovimiento, "El dron se mueve a x: " + to_string(pMapa->ordenes[i][j].siguienteX) +
                                                       " y:" + to_string(pMapa->ordenes[i][j].siguienteY));
        }
        tabla += "</div>\n";
      }
      tabla += "</td>\n";
    }
    tabla += "</tr>\n";
  }
  tabla += "</tbody></table>";
  return tabla + "<div hidden>" + tooltips + "</div>";
}

string DibujarEmoji(string idTooltip, string emoji) {
  return "<div class='info'><span aria-describedby='" + idTooltip + "'>" + emoji +
         "</span></div>\n";
}

string DibujarTooltip(string id, string texto) {
  return "<div role='tooltip' id='" + id + "'><p>" + texto + "</p></div>\n";
}