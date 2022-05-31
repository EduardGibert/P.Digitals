#include <Arduino.h>


/* delete a task when finish,
this will never happen because this is infinity loop */


void funcion1(void * parameter)
{
#define led 16
pinMode(led, OUTPUT);

for(;;)
{
digitalWrite(led, HIGH);
Serial.println("ON");
delay(1000);
digitalWrite(led, LOW);
Serial.println("OFF");
delay(1000);

}

}

void setup()
{
Serial.begin(112500);

xTaskCreate(
funcion1, /* Task function. */
"FUNCION 1", /* name of task. */
10000, /* Stack size of task */
NULL, /* parameter of the task */
1, /* priority of the task */
NULL); /* Task handle to keep track of created task */
}


void loop()
{}