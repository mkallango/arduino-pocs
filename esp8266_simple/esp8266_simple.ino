#include "SoftwareSerial.h"

SoftwareSerial ESP_Serial(2, 3); // RX, TX

void setup(){  
  delay(1000);
  Serial.begin(9600);
  ESP_Serial.begin(9600);
}

void loop(){
  if (ESP_Serial.available()){
    Serial.write(ESP_Serial.read());
  }
  if (Serial.available()){
    ESP_Serial.write(Serial.read());
  }  
}
