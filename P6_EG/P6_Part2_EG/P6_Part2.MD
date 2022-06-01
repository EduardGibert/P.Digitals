## Práctica 6 Parte 2:

### Código:
```
#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN 21
#define SS_PIN 5

MFRC522 mfrc522(SS_PIN, RST_PIN); //Creamos el objeto para el RC522
void setup() {
Serial.begin(115200); //Iniciamos la comunicación

SPI.begin();
//Iniciamos el Bus SPI

mfrc522.PCD_Init(); // Iniciamos el MFRC522

Serial.println("Lectura del UID");
}

void loop() {

// Revisamos si hay nuevas tarjetas presentes
if ( mfrc522.PICC_IsNewCardPresent())
{
//Seleccionamos una tarjeta

if ( mfrc522.PICC_ReadCardSerial())
{

// Enviamos serialemente su UID
Serial.print("Card UID:");
for (byte i = 0; i < mfrc522.uid.size; i++) {
Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
Serial.print(mfrc522.uid.uidByte[i], HEX);
}
Serial.println();

// Terminamos la lectura de la tarjeta actual
mfrc522.PICC_HaltA();
}
}
}
```

### Salida:
Para empezar, como siempre, subimos el programa a la placa. Este hace que al pasar una tarjeta/llavero por delante del sensor que estamos utilizando, se vea por la pantalla del ordenador el código de la tarjeta o llavero que estemos usando en ese momento, como podemos ver en el siguiente video:



https://user-images.githubusercontent.com/100867309/171390981-56ba2255-8d34-4587-80bb-32d9e11b46b4.mp4



### Funcionamiento:
Para poder usar el sensor primeramente hemos de instalar las librerias necessarias y declararlas, seguido de la definicion de los pines que vamos a necessitar y el reset:
```
#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN 21
#define SS_PIN 5

MFRC522 mfrc522(SS_PIN, RST_PIN); //Creamos el objeto para el RC522
```
Dentro del setup inicializamos la comunicación serial, una vez hecho estro inicializamos el SPI y el MFRC522. Si todo va bien saldra por pantalla un mensaje que nos dira que ya podemos pasar la tarjeta o e llavero por el sensor.
```
void setup() {
Serial.begin(115200); //Iniciamos la comunicación

SPI.begin();
//Iniciamos el Bus SPI

mfrc522.PCD_Init(); // Iniciamos el MFRC522

Serial.println("Lectura del UID");
}
```

Finalmente en el loop trabajamos con el sensor. Primeramente el sensor va ir mirando si algo pasa por delante suyo, a continuacion escoje la tarjeta/llavero que le hemos pasado por denalte y nos muestra por pantalla su UID y finaliza la lectura. 

```
void loop() {

// Revisamos si hay nuevas tarjetas presentes
if ( mfrc522.PICC_IsNewCardPresent())
{
//Seleccionamos una tarjeta

if ( mfrc522.PICC_ReadCardSerial())
{

// Enviamos serialemente su UID
Serial.print("Card UID:");
for (byte i = 0; i < mfrc522.uid.size; i++) {
Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
Serial.print(mfrc522.uid.uidByte[i], HEX);
}
Serial.println();

// Terminamos la lectura de la tarjeta actual
mfrc522.PICC_HaltA();
}
}
}
```
