#include "LiquidCrystal.h"
LiquidCrystal lcd(12,11,5,4,3,2);
int segundo = 0;
int minuto = 0;
const int LED13 = 13;
const int LED7 = 7;
const int Buzzer = A2;
const int Botao1 = A5;
const int Botao2 = A4;
const int Botao3 = A3;
int EstadoBotao1 = 0;
int EstadoBotao2 = 0;
int EstadoBotao3 = 0;

void setup(){
  pinMode(Botao1, INPUT);
  pinMode(Botao2, INPUT);
  pinMode(Botao3, INPUT);
  pinMode(LED13, OUTPUT);
  pinMode(LED7, OUTPUT);
  pinMode(Buzzer, OUTPUT);
  lcd.begin(16,2);
  inicializacao();
}

void loop(){
  EstadoBotao1 = digitalRead(Botao1);
  if(EstadoBotao1 == HIGH){
    delay(150);
    if(EstadoBotao1 == HIGH){
      segundo++;
      if(segundo>=60){
        segundo = 0;
        lcd.setCursor(11,0);
        lcd.print(" ");
      }
      lcd.setCursor(0,0);
      lcd.print("Segundos: ");
      lcd.print(segundo);
    }
  }
  EstadoBotao2 = digitalRead(Botao2);
  if(EstadoBotao2 == HIGH){
    delay(150);
    if(EstadoBotao2 == HIGH){
      minuto++;
      if(minuto>=60){
        minuto = 0;
        lcd.setCursor(10,1);
        lcd.print(" ");
      }
      lcd.setCursor(0,1);
      lcd.print("Minutos: ");
      lcd.print(minuto);
    }
  }
  EstadoBotao3 = digitalRead(Botao3);
  if(EstadoBotao3 == HIGH){
    if((minuto==0) && (segundo==0)){
      //nao faz nada
    }
    else{
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("START");
      delay(1000);
      if(segundo==0){
        minuto--;
        segundo=59;        
      }
      for(int y=0; y < segundo; y--){
        if(minuto < 10){
          lcd.setCursor(5,1);
          lcd.print("0");
          lcd.print(minuto);
          lcd.print(":");
        }
        else{
          lcd.setCursor(5,1);
          lcd.print(minuto);
          lcd.print(":");
        }
        if(segundo < 10){
          lcd.setCursor(5,1);
          lcd.print("0");
          lcd.println(segundo);
        }
        else{
          lcd.print(segundo);
        }
        segundo--;
        if(segundo < 0){
          minuto--;
          segundo=59;
        }
        delay(1000);

        if((segundo<=0) && (minuto<=0)){
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("ACABOU O TEMPO!");
          tone(Buzzer, 1500);
          digitalWrite(LED7, HIGH);
          delay(250);
          noTone(Buzzer);
          digitalWrite(LED7, LOW);
          delay(100);
          tone(Buzzer, 1500);
          digitalWrite(LED7, HIGH);
          delay(250);
          noTone(Buzzer);
          digitalWrite(LED7, LOW);
          delay(100);
          tone(Buzzer, 1500);
          digitalWrite(LED7, HIGH);
          delay(250);
          noTone(Buzzer);
          digitalWrite(LED7, LOW);
          delay(100);
          tone(Buzzer, 1500);
          digitalWrite(LED7, HIGH);
          delay(250);
          noTone(Buzzer);
          digitalWrite(LED7, LOW);
          delay(100);
          tone(Buzzer, 1500);
          digitalWrite(LED7, HIGH);
          delay(250);
          noTone(Buzzer);
          digitalWrite(LED7, LOW);
          delay(100);
          break;
        }
      }
      inicializacao();
    }
  }
}


void inicializacao(){
    lcd.begin(16,2);
    lcd.print("Selecione o ");
    lcd.setCursor(0,1);
    lcd.print("tempo do timer...");
    delay(1500);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Segundos: ");
    lcd.print(segundo);
    lcd.setCursor(0,1);
    lcd.print("Minutos: ");
    lcd.print(minuto);
}

