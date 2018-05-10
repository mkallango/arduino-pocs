#include "LiquidCrystal.h"

LiquidCrystal lcd(12,11,5,4,3,2);
int incomingByte, x, y;

void setup(){
  lcd.begin(16,2);
  Serial.begin(9600);
}

void loop(){
  if(Serial.available() > 0){
    incomingByte = Serial.read();
    lcd.print(char(incomingByte));
    x = x + 1;
    y = y + 1;
    if(x > 15){
      lcd.setCursor(0,1);
      x=0;
    }
    if(y > 31){
      lcd.setCursor(0,0);
      y=0;
      x=0;
    }
  }
}

