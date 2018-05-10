#include "LiquidCrystal.h"

int freq = 0;
int Botao1 = 8;
int Botao2 = 9;
int EstadoBotao1 = 0;
int EstadoBotao2 = 0;
int Buzzer = 6;
LiquidCrystal lcd(12,11,5,4,3,2);

void setup(){
  lcd.begin(16,2);
  lcd.setCursor(0,0);
  lcd.print("Frequencia = ");
  lcd.setCursor(6,1);
  lcd.print("Hz");
  pinMode(Botao1, INPUT);
  pinMode(Botao2, INPUT);
  pinMode(Buzzer, OUTPUT);
}

void loop(){
  EstadoBotao1 = digitalRead(Botao1);
  EstadoBotao2 = digitalRead(Botao2);

  lcd.print(freq);
  tone(Buzzer, freq);
  delay(100);
  
  if(EstadoBotao1 == HIGH){
    freq = freq + 100;
  }

  if(EstadoBotao2 == HIGH){
    freq = freq - 100;
  }

  if(freq <= 0){
    freq = 0;
    noTone(Buzzer);
  }

  if(freq >= 20000){
    freq = 20000;
  }
  if(freq <= 99){
    lcd.setCursor(0,1);
    lcd.print(" ");
    lcd.setCursor(1,1);
    lcd.print(" ");
    lcd.setCursor(2,1);
    lcd.print(" ");
    lcd.setCursor(3,1);
    lcd.print(" ");
  }
  if(freq >= 100){
    lcd.setCursor(0,1);
    lcd.print(" ");
    lcd.setCursor(1,1);
    lcd.print(" ");
    lcd.setCursor(2,1);
  }
   if(freq >= 1000){
    lcd.setCursor(0,1);
    lcd.print(" ");
    lcd.setCursor(1,1);
  }
   if(freq >= 10000){
    lcd.setCursor(0,1);
  }
}

