#include <Arduino.h>

// TODO don't redefine
#define WEBSOCKET_PORT  81

const String html_start = (
  "<!DOCTYPE html>"
  "<html>"
    "<head>"
      "<meta name=viewport content=\"width=device-width, initial-scale=1\">"
      "<title>Wireless Battery</title>"
      "<link rel=\"stylesheet\" href=\"/style.css\" />"
      "<script type=\"text/javascript\" src=\"https://www.gstatic.com/charts/loader.js\"></script>"
    "</head>"
    "<body>"
      "<header><div class=\"wrap\">Wireless Battery</div></header>"
      "<content>"
        "<div class=\"wrap\">"
);

const String html_end = (
        "</div>"
      "</content>"
      "<footer>"
        "<div class=\"wrap\">"
          "<a href=\"/\">Info</a>"
          "<a href=\"/graph\">Graph</a>"
          "<a href=\"/config\">Config</a>"
          #ifdef ENABLE_WEBSOCKET_LOG
            "<a href=\"/log\">Log</a>"
          #endif
        "</div>"
      "</footer>"
    "</body>"
  "</html>"
);

const String html_log_content = (
  "<h1>Log</h1>"
  "<span id=\"indicator\">disconnected</span>"
  "<div id=\"log\" data-port=\"" + String(WEBSOCKET_PORT) + "\">"
    "<div id=\"empty\">nothing received yet</div>"
  "</div>"
  "<form class=\"line\">"
    "<input id=\"in\" type=\"text\" placeholder=\"Send NMEA sentence\" />"
    "<button id=\"send\" type=\"submit\" disabled>Send</button>"
  "</form>"
  "<script src=\"/log_script.js\"></script>"
);

const String html_graph_content_start = (
    "<script type=\"text/javascript\">"
      "google.charts.load('current', {'packages':['corechart']});"
      "google.charts.setOnLoadCallback(drawChart);"

      "function drawChart() {"
);

const String html_graph_content_end = (
     "var classicOptions = {"
        "curveType: 'function',"
        "legend: { position: 'in' },"
        "width: 900,"
        "height: 500,"
        "series: {"
          "0: {targetAxisIndex: 0},"
          "1: {targetAxisIndex: 1}"
        "}"
      "};"
      "var chart_min_VA = new google.visualization.LineChart(document.getElementById('chart_min_VA'));"
      "chart_min_VA.draw(data_min_VA, classicOptions);"
      "var chart_min_PC = new google.visualization.LineChart(document.getElementById('chart_min_PC'));"
      "chart_min_PC.draw(data_min_PC, classicOptions);"
      "var chart_hour_VA = new google.visualization.LineChart(document.getElementById('chart_hour_VA'));"
      "chart_hour_VA.draw(data_hour_VA, classicOptions);"
      "var chart_hour_PC = new google.visualization.LineChart(document.getElementById('chart_hour_PC'));"
      "chart_hour_PC.draw(data_hour_PC, classicOptions);"
      "var chart_day_VA = new google.visualization.LineChart(document.getElementById('chart_day_VA'));"
      "chart_day_VA.draw(data_day_VA, classicOptions);"
      "var chart_day_PC = new google.visualization.LineChart(document.getElementById('chart_day_PC'));"
      "chart_day_PC.draw(data_day_PC, classicOptions);"
    "}"
    "</script>"
    "<h2>Last minute</h2>"
    "<div id=\"chart_min_VA\" style=\"width: 100%; height: 500px;\"></div>"
    "<div id=\"chart_min_PC\" style=\"width: 100%; height: 500px;\"></div>"
    "<h2>Last hour</h2>"
    "<div id=\"chart_hour_VA\" style=\"width: 100%; height: 500px;\"></div>"
    "<div id=\"chart_hour_PC\" style=\"width: 100%; height: 500px;\"></div>"
    "<h2>Last week</h2>"
    "<div id=\"chart_day_VA\" style=\"width: 100%; height: 500px;\"></div>"
    "<div id=\"chart_day_PC\" style=\"width: 100%; height: 500px;\"></div>"
);
