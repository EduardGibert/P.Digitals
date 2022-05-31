# Práctica 3 Parte 1

## Código:
```
/*
ESP32 Web Server - STA Mode
modified on 25 MAy 2019
by Mohammadreza Akbari @ Electropeak
hvoid handle_root()ttps://electropeak.com/learn
*/

#include <WiFi.h>
#include <WebServer.h>
void handle_root();

// SSID & Password
const char* ssid = "Xiaomi_11T_Pro"; // Enter your SSID here
const char* password = "f5cbd8a82232"; //Enter your Password here
WebServer server(80);

// Object of WebServer(HTTP port, 80 is defult)
void setup() {
Serial.begin(115200);
Serial.println("Try Connecting to ");
Serial.println(ssid);

// Connect to your wi-fi modem
WiFi.begin(ssid, password);

// Check wi-fi is connected to wi-fi network
while (WiFi.status() != WL_CONNECTED) {
delay(1000);
Serial.print(".");
}
Serial.println("");
Serial.println("WiFi connected successfully");
Serial.print("Got IP: ");
Serial.println(WiFi.localIP()); //Show ESP32 IP on serial
server.on("/", handle_root);
server.begin();
Serial.println("HTTP server started");
delay(100);
}
void loop() {
server.handleClient();
}

// HTML & CSS contents which display on web server
String HTML = "<!DOCTYPE html>\
<html>\
<body>\
<h1>Socl'Edu i aixo es : My Primera Pagina con ESP32 - Station Mode &#128522;</h1>\
</body>\
</html>";

// Handle root url (/)
void handle_root() {
server.send(200, "text/html", HTML);
}
```

## Funcionamiento:
Es un programa para crear una página web. Para esto necesitamos connectar nuestra ESP32 a una red Wi-Fi:

```
#include <WiFi.h>
#include <WebServer.h>
void handle_root();

// SSID & Password
const char* ssid = "Xiaomi_11T_Pro"; // Enter your SSID here
const char* password = "f5cbd8a82232"; //Enter your Password here
WebServer server(80);

// Object of WebServer(HTTP port, 80 is defult)
void setup() {
Serial.begin(115200);
Serial.println("Try Connecting to ");
Serial.println(ssid);

// Connect to your wi-fi modem
WiFi.begin(ssid, password);

// Check wi-fi is connected to wi-fi network
while (WiFi.status() != WL_CONNECTED) {
delay(1000);
Serial.print(".");
}
Serial.println("");
Serial.println("WiFi connected successfully");
Serial.print("Got IP: ");
Serial.println(WiFi.localIP()); //Show ESP32 IP on serial
server.on("/", handle_root);
server.begin();
Serial.println("HTTP server started");
delay(100);
}
```
Una vez la red Wi-Fi este conectada la placa dara una respuesta por pantalla la qual dira "WiFi connected successfully".

Ahora necesitamos crear el contenido que tendra la página. Para ello utilizaremos HTML:
```
void loop() {
server.handleClient();
}

// HTML & CSS contents which display on web server
String HTML = "<!DOCTYPE html>\
<html>\
<body>\
<h1>Socl'Edu i aixo es : My Primera Pagina con ESP32 - Station Mode &#128522;</h1>\
</body>\
</html>";

// Handle root url (/)
void handle_root() {
server.send(200, "text/html", HTML);
}
```

Una vez lo tenemos todo hay que subir el código a la placa, y nos dara la IP de nuestro ordenador:

Esta IP al ponerla en el buscador de un dispositivo conectado a la misma red Wi-Fi y  nos llevara a la página web que hemos creado.
