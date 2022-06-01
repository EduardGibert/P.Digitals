# Pràctica 1 Parte 2

## Codigo:

```
#include <Arduino.h>

#define LED 16
unsigned long myTime;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(LED,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  
  Serial.println(myTime); // prints time since program started
  myTime = millis();
  while(millis()<myTime+1000);
  
  //delay(1000);         
  digitalWrite(LED,HIGH);
  Serial.println("ON");
  myTime = millis();
  while(millis()<myTime+500);
  
  //delay(500);
  digitalWrite(LED,HIGH);
  Serial.println("OFF");
  digitalWrite(LED,LOW);
  myTime = millis();
  while(millis()<myTime+500);
  
  //delay(500);

}
```
## Funcionamiento:

Como siempre, primero tenemos que declarar las librerias necessarias, una vez hecho esto, vemos como el codigo en si es bastante sencillo. <br>
Primeramente declaramos el pin que vamos a usar.

```
#include <Arduino.h>

#define LED 16
unsigned long myTime;
```

Justo despues hacemos el setup donde vamos a inicializar un serial begin y el pinMode, en este caso un output de un LED .
```
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(LED,OUTPUT);
}
```
Seguido hacemos el loop que se va a encargar de alternar el ON and OFF cada uno con un delay distinto.
```
void loop() {
  // put your main code here, to run repeatedly:
  
  Serial.println(myTime); // prints time since program started
  myTime = millis();
  while(millis()<myTime+1000);
  
  //delay(1000);         
  digitalWrite(LED,HIGH);
  Serial.println("ON");
  myTime = millis();
  while(millis()<myTime+500);
  
  //delay(500);
  digitalWrite(LED,HIGH);
  Serial.println("OFF");
  digitalWrite(LED,LOW);
  myTime = millis();
  while(millis()<myTime+500);
  
  //delay(500);
```
