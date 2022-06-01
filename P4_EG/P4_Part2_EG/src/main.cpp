#include <Arduino.h>
#define LED 16
unsigned long myTime;
#define interruptPin 0

void Task1(void * parameter);
void anotherTask(void * parameter);

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

void loop(){
  Serial.println("this is ESP32 Task");
  delay(1000);
}

void anotherTask( void * parameter ){
  for(;;){
    Serial.println("this is another Task");
    delay(1000);
  }
  /* delete a task when finish,
  this will never happen because this is infinity loop */
  vTaskDelete( NULL );
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
}
