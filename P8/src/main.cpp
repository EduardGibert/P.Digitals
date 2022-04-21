#include <Arduino.h>

void setup() {
  Serial.begin(115200);
  Serial2.begin(115200);
}

void loop() {
  if(Serial.available()){
    Serial2.write(Serial.read());
    delay(2);
    if(Serial2.available()){
      Serial.write(Serial2.read());
    } 
  }
}