# Pràctica 1 Parte 2

## Codigo:

```
#include <Arduino.h>

#define LED 16

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(LED,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(LED,HIGH);
  Serial.println("ON");
  delay(500);
  digitalWrite(LED,HIGH);
  Serial.println("OFF");
  digitalWrite(LED,LOW);
  delay(500);

}
```



## Diagrama de flujos:


```mermaid
graph LR;
    Programa-->Build;
    Build-->Upload;
    Upload-->Monitor;
    Monitor-->ON
    Monitor-->OFF
    ON-->|500 MS|OFF;
    OFF-->|500 MS|ON;    
      
```



