#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <WiFi.h>
#include <time.h>
#include "Adafruit_I2CDevice.h"
#include "ESPAsyncWebServer.h"


//Puerto 80
WiFiServer server(80);

// Wifi
const char* ssid     = "Telefedu";
const char* password = "3e6eb1e28071";

//Variables
int contconexion = 0;

String header; // HTTP Request

//HTML
String paginaInicio = "<!DOCTYPE html>"
"<html>"
"<head>"
"<meta charset='utf-8' />"
"<META HTTP-EQUIV='Refresh' CONTENT='1'>"
"<title> Informacion Actual </title>"
"</head>"
"<body>"
"<center>"
"<h1> <u> Informacion Actual </u> </h1>"
"<br>"
"</center>";


String Temperatura = 
"<h2> <ul> <li> Temperature: </li> </ul> </h2>"
"<h2><h2>";

String Humedad = 
"<h2> <ul> <li> Humidity: </li> </ul> </h2>"
"<h2><h2><br>";

String Presion = 
"<h2> <ul> <li> Pressure: </li> </ul> </h2>"
"<h2><h2><br>";

String paginaFin = 
"</body>"
"</html>";

// NTP Server
const char* ntpServer = "pool.ntp.org";
const long  gmtOffset_sec = 0;
const int   daylightOffset_sec = 7200;

//Display
#define SCREEN_WIDTH 128  // OLED display width, in pixels
#define SCREEN_HEIGHT 64  // OLED display height, in pixels

#define I2Cdisplay_SDA 21
#define I2Cdisplay_SCL 22
TwoWire I2Cdisplay = TwoWire(1);

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &I2Cdisplay, -1);

// BME280
#define I2C_SDA 21
#define I2C_SCL 22
TwoWire I2CBME = TwoWire(0);
Adafruit_BME280 bme;

//Pantallas
int displayScreenNum = 0;
int displayScreenNumMax = 3;

unsigned long lastTimer = 0;
unsigned long timerDelay = 7500; 


//Circulitos
void displayIndicator(int displayNumber) {
  int xCoordinates[5] = {49, 59, 69, 79};
  for (int i =0; i<4; i++) {
    if (i == displayNumber) {
      display.fillCircle(xCoordinates[i], 60, 2, WHITE);
    }
    else {
      display.drawCircle(xCoordinates[i], 60, 2, WHITE);
    }
  }
}

//Fecha y Hora
void displayLocalTime(){
  struct tm timeinfo;
  if(!getLocalTime(&timeinfo)){
    Serial.println("Failed to obtain time");
  }
  Serial.println(&timeinfo, "%A, %B %d %Y %H:%M:%S");

  //GET DATE
  //Get full weekday name
  char weekDay[10];
  strftime(weekDay, sizeof(weekDay), "%a", &timeinfo);
  //Get day of month
  char dayMonth[4];
  strftime(dayMonth, sizeof(dayMonth), "%d", &timeinfo);
  //Get abbreviated month name
  char monthName[5];
  strftime(monthName, sizeof(monthName), "%b", &timeinfo);
  //Get year
  char year[6];
  strftime(year, sizeof(year), "%Y", &timeinfo);

  //GET TIME
  //Get hour (12 hour format)
  /*char hour[4];
  strftime(hour, sizeof(hour), "%I", &timeinfo);*/
  
  //Get hour (24 hour format)
  char hour[4];
  strftime(hour, sizeof(hour), "%H", &timeinfo);
  //Get minute
  char minute[4];
  strftime(minute, sizeof(minute), "%M", &timeinfo);

  //Display Date and Time on OLED display
  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setTextSize(3);
  display.setCursor(19,5);
  display.print(hour);
  display.print(":");
  display.print(minute);
  display.setTextSize(1);
  display.setCursor(16,40);
  display.print(weekDay);
  display.print(", ");
  display.print(dayMonth);
  display.print(" ");
  display.print(monthName);
  display.print(" ");
  display.print(year);
  displayIndicator(displayScreenNum);
  display.display();
}

//Temperatura
void displayTemperature(){
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0, 5);
  display.print("Temperature ");
  display.setTextSize(3);
  display.setCursor(15, 25);
  delay(200);
  float temperature = bme.readTemperature();
  temperature = bme.readTemperature();
  display.print(temperature);
  display.cp437(true);
  display.setTextSize(1);
  display.print(" ");
  display.write(167);
  display.print("C");
  display.setCursor(0, 34);
  display.setTextSize(1);
  displayIndicator(displayScreenNum);
  display.display();
}

//Humedad
void displayHumidity(){
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0, 5);
  display.print("Humidity ");
  display.setTextColor(WHITE);
  display.setTextSize(3);
  display.setCursor(15, 25);
  float humidity = bme.readHumidity();
  display.print(humidity);
  display.setTextSize(1);
  display.print(" %");
  display.setCursor(0, 34);
  display.setTextSize(1);
  displayIndicator(displayScreenNum);
  display.display();
}

//Presion
void displayPressure(){
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0, 5);
  display.print("Pressure ");
  display.setTextSize(2);
  display.setCursor(15, 25);
  display.print(bme.readPressure()/100.0F);
  display.setTextSize(1);
  display.print(" hpa");
  display.setCursor(0, 34);
  display.setTextSize(1);
  displayIndicator(displayScreenNum);
  display.display();
}

//Subprograma encargado de mostar la pantalla correcta
void updateScreen() {
  if (displayScreenNum == 0){
    displayLocalTime();
  }
  else if (displayScreenNum == 1) {
    displayTemperature();
  }
  else if (displayScreenNum ==2){
    displayHumidity();
  }
  else {
    displayPressure();
  }
}

// Setup
void setup() {
  Serial.begin(115200);
  
  I2CBME.begin(I2C_SDA, I2C_SCL, 100000);
  I2Cdisplay.begin(I2Cdisplay_SDA, I2Cdisplay_SCL, 100000); 

  //Inicializar Display
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  display.clearDisplay();
  display.setTextColor(WHITE);
  
  //Inicializar BME280
  bool status = bme.begin(0x76, &I2CBME);  
  if (!status) {
    Serial.println("Could not find a valid BME280 sensor, check wiring!");
    while (1);
  }

  //Wi-Fi
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  //Cuenta hasta 50 si no se puede conectar lo cancela
  while (WiFi.status() != WL_CONNECTED and contconexion <50) {
    ++contconexion;
    delay(500);
    Serial.print(".");
  }
  
  if (contconexion <50) {
      Serial.println("");
      Serial.println("WiFi conectado");
      Serial.println(WiFi.localIP());
      server.begin(); // iniciamos el servidor
  }
  else { 
      Serial.println("");
      Serial.println("Error de conexion");
  }
  
  // Init and get the time
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
}

void loop() {

  // Change screen every 7.5 seconds (timerDelay variable)
  if ((millis() - lastTimer) > timerDelay) {
    updateScreen();
    Serial.println(displayScreenNum);
    if(displayScreenNum < displayScreenNumMax) {
      displayScreenNum++;
    }
    else {
      displayScreenNum = 0;
    }
    lastTimer = millis();
  }

  //Pagina Web
  WiFiClient client = server.available();   // clientes entrantes
 
  if (client) {                             // Si se conecta
    Serial.println("New Client.");          // 
    String currentLine = "";                //
    while (client.connected()) {            // loop mientras el cliente est谩 conectado
      if (client.available()) {             // si hay bytes para leer desde el cliente
        char c = client.read();             // lee un byte
        Serial.write(c);                    // 
        header += c;
        if (c == '\n') {                    // si el byte es un caracter de salto de linea
          // HTTP request del cliente, entonces respondemos:
          if (currentLine.length() == 0) {
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();
          
            // Mostrar pagina web
            float temperature = bme.readTemperature();
            float humidity = bme.readHumidity();
            float pressure = bme.readPressure()/100.0F;
            client.println(paginaInicio + Temperatura + String(temperature) + Humedad + String(humidity) + Presion + String(pressure) + paginaFin);
            
            // la respuesta HTTP temina
            client.println();
            break;
          } else { // si tenemos una nueva linea limpiamos
            currentLine = "";
          }
        } else if (c != '\r') {  // si C es distinto al caracter de retorno
          currentLine += c;      // lo agrega al final de currentLine
        }
      }
    }
    // Limpiamos
    header = "";
    // Cerrar Conexion
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
  }
}
