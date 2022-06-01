# Practica 7 Part 2 

## Codigo:
```
#include "Arduino.h"
#include "FS.h"
#include "HTTPClient.h"
#include "SPIFFS.h"
#include "SD.h"
#include "SPI.h"
#include "AudioGeneratorAAC.h"
#include "AudioOutputI2S.h"
#include "AudioFileSourcePROGMEM.h"
#include "sampleaac.h"

AudioFileSourcePROGMEM *in;
AudioGeneratorAAC *aac;
AudioOutputI2S *out;

void setup(){
  Serial.begin(115200);
  in = new AudioFileSourcePROGMEM(sampleaac, sizeof(sampleaac));
  aac = new AudioGeneratorAAC();
  out = new AudioOutputI2S();
  out -> SetGain(0.125);
  out -> SetPinout(26,25,22);
  aac->begin(in, out);
}

void loop(){
  if (aac->isRunning()) {
    aac->loop();
    } else {

      aac -> stop();
      Serial.printf("Sound Generator\n");
      delay(1000);
  }
}
```

## Salida:
Como siempre compilamos y ejecutamos el programa.<br>
Una vez hecho estro podemos ver que muestra por pantalla la frase "Sound generator" repetidamente, 
conectando un altavoz se escucha a un hombre decir una frase como podemos esuchar en el siguiente video:



https://user-images.githubusercontent.com/100867309/171394773-318b24c6-1667-4cf8-9e18-efa50f7443d4.mp4



## Funcionamiento:
Como simepre para empezar declaramos las librerias, variables y todo lo que sea necessario :
```
#include "Arduino.h"
#include "FS.h"
#include "HTTPClient.h"
#include "SPIFFS.h"
#include "SD.h"
#include "SPI.h"
#include "AudioGeneratorAAC.h"
#include "AudioOutputI2S.h"
#include "AudioFileSourcePROGMEM.h"
#include "sampleaac.h"

AudioFileSourcePROGMEM *in;
AudioGeneratorAAC *aac;
AudioOutputI2S *out;
```

Seguidamente en el setup, iniciamos el serial y asignamos una variable "in". Esta variable sera la que importara el archivo de audio. "Acc" sera la variable variable para poder descodificar el audio. 
La variable "Out" es la encargada de la ganancia del audio. Seguidamente asignamos los pines de salida y la última linea es para la entrada y la salida.
```
void setup(){

  Serial.begin(115200);
  in = new AudioFileSourcePROGMEM(sampleaac, sizeof(sampleaac));
  aac = new AudioGeneratorAAC();
  out = new AudioOutputI2S();
  out -> SetGain(0.125);
  out -> SetPinout(26,25,22);
  aac->begin(in, out);
}
```

Dentro de el void loop se inicia un loop que descodifica el "acc". Si todo sale bien, saldra por pantalla el mensaje "Sound Generator" en caso contrario el mensaje no saldria.
```
void loop(){
  if (aac->isRunning()) {
    aac->loop();
    } else {

      aac -> stop();
      Serial.printf("Sound Generator\n");
      delay(1000);
  }
}
```
