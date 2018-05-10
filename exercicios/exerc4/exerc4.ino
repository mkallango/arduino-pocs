#include "LiquidCrystal.h"
const int LM35 = 0;
float temperatura = 0;
int ADClido = 0;
LiquidCrystal lcd(12,11,7,6,5,4);

void setup(){
  lcd.begin(16,2);
  analogReference(INTERNAL); //No Mega, use INTERNAL1V1, no Leonardo remova essa linha
}


void loop(){
  ADClido = analogRead(LM35);
  delay(500);
  ADClido = analogRead(LM35);
  
  temperatura = ADClido * 0.1075268817204301; //no Leonardo use 0.4887585532
  lcd.setCursor(0,0);
  lcd.print("Temp = ");
  lcd.print((temperatura * (9/5))+32);
  lcd.print(" *F"); 
  lcd.setCursor(0,1);
  lcd.print("Temp = ");
  lcd.print(temperatura);
  lcd.print(" *C"); 
  delay(1000); 
}
