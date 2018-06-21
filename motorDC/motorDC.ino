#include "LiquidCrystal.h"

const int pwm = 6;
const int pot = A0;
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
int ValorLidoPot_Real = 0;
int ValorLidoPot_Mapeado = 0;

void setup() {
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  pinMode(pwm, OUTPUT);
}

void loop() {
  ValorLidoPot_Real = analogRead(pot);
  ValorLidoPot_Mapeado = map(ValorLidoPot_Real, 0, 1023, 0, 255);
  analogWrite(pwm, ValorLidoPot_Mapeado);
  lcd.setCursor(0, 0);
  if(ValorLidoPot_Mapeado<10){
    lcd.print("00"+String(ValorLidoPot_Mapeado));  
  } 
  else if(ValorLidoPot_Mapeado<100){
    lcd.print("0"+String(ValorLidoPot_Mapeado));  
  } 
  else{
    lcd.print(ValorLidoPot_Mapeado);      
  }
}
