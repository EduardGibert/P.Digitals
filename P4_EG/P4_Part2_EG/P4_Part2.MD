# Práctica 4 Parte 2: 

## Código:

```
#include <Arduino.h>
#define LED 16
unsigned long myTime;
#define interruptPin 0

void Task1(void * parameter);
void anotherTask(void * parameter);

void setup(){
  Serial.begin(115200);
  
  xTaskCreate(
  anotherTask, /* Task function. */
  "another Task", /* name of task. */
  10000, /* Stack size of task */
  NULL, /* parameter of the task */
  1, /* priority of the task */
  NULL); /* Task handle to keep track of created task */
  
  xTaskCreate(
  Task1, /* Task function. */
  "Task 1", /* name of task. */
  10000, /* Stack size of task */
  NULL, /* parameter of the task */
  1, /* priority of the task */
  NULL);
}

void loop(){
  Serial.println("this is ESP32 Task");
  delay(1000);
}

void Task1(void * parameter){
  pinMode(LED,OUTPUT);
  for(;;){
    Serial.println(myTime); // prints time since program started
    delay(500);    
    digitalWrite(LED,HIGH);
    Serial.println("ON");
    delay(500);
    digitalWrite(LED,HIGH);
    Serial.println("OFF");
    digitalWrite(LED,LOW);
    delay(500);
  }
  
void anotherTask( void * parameter ){
  /* loop forever */
  for(;;){
    Serial.println("this is another Task");
    delay(1000);
  }
  vTaskDelete( NULL );
}

}
```
## Funcionamiento:
En el caso de esta práctica queremos que se nos encienda y apague un led usando las tascas que hemos visto ya en el apartado 1, 
para ello vemos como el setup de nuestro codigo va a ser el mismo pero pondremos una tasca mas como vemos aqui:

```
void setup(){
  Serial.begin(115200);
  
  /* we create a new task here */
  xTaskCreate(
  anotherTask, /* Task function. */
  "another Task", /* name of task. */
  10000, /* Stack size of task */
  NULL, /* parameter of the task */
  1, /* priority of the task */
  NULL); /* Task handle to keep track of created task */
  
  xTaskCreate(
  Task1, /* Task function. */
  "Task 1", /* name of task. */
  10000, /* Stack size of task */
  NULL, /* parameter of the task */
  1, /* priority of the task */
  NULL);
}
```
Con esto hecho nos faltara definir el loop y declarar la funcion y exactamente que queremos que esta haga, dicho esto vemos como el loop va a ser sencillo
ya que solo queremos que nos escriba por pantalla un mensaje.
```
void loop(){
  Serial.println("this is ESP32 Task");
  delay(1000);
}
```
Finalmente, declararemos las dos tascas que hemos creado anteriormente, primero la "Task1", la qual sera la encargada del LED:
```
void Task1(void * parameter){
  pinMode(LED,OUTPUT);
  for(;;){
    Serial.println(myTime); // prints time since program started
    delay(500);    
    digitalWrite(LED,HIGH);
    Serial.println("ON");
    delay(500);
    digitalWrite(LED,HIGH);
    Serial.println("OFF");
    digitalWrite(LED,LOW);
    delay(500);
  }

```
Y seguidamente la tasca "anothertask" la qual pondra por pantalla el siguiente mensaje:
```
void anotherTask( void * parameter ){
  /* loop forever */
  for(;;){
    Serial.println("this is another Task");
    delay(1000);
  }
  vTaskDelete( NULL );
}

```
