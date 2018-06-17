#include "LiquidCrystal.h"
LiquidCrystal lcd(12, 11, 7, 6, 5, 4);
const int Botao1 = 9;
const int Botao2 = 8;
int EstadoBotao1 = 0;
int EstadoBotao2 = 0;
int velocidade = 1000; //velocidade inicial
int sentido = 0; //se for 0 a bola vai estar indo
//se for 1 a bola vai estar vindo
int i, x, k = 0;

void setup() {
  Serial.begin(9600);
  pinMode(Botao1, INPUT);
  pinMode(Botao2, INPUT);
  attachInterrupt(0, rebateuDireita, RISING); //interrupcao no pino 2
  attachInterrupt(1, rebateuEsquerda, RISING); //interrupcao no pino 3
  lcd.begin(16, 2);
  lcd.print(" Ping Pong 1.0 ");
  delay(2000);
  lcd.clear();
}

void loop() {
  jogo();
}

void jogo(){
  while(1){
    if(sentido == 0){ //da direita pra esqueda
      for(i=15; i>=0; i--){
        switch(k){
        case 0:
        lcd.setCursor(i,0);
        lcd.print("o");
        delay(velocidade);
        lcd.clear();
        k=1;
        break;
        case 1:
        lcd.setCursor(i,1);
        lcd.print("o");
        delay(velocidade);
        lcd.clear();
        k=0;
        break;
        }
      }
    }
    if(sentido == 1){ //da esquerda pra direita
      for(i=0; i < 16; i++){
        switch(k){
        case 0:
        lcd.setCursor(i,0);
        lcd.print("o");
        delay(velocidade);
        lcd.clear();
        k=1;
        break;
        case 1:
        lcd.setCursor(i,1);
        lcd.print("o");
        delay(velocidade);
        lcd.clear();
        k=0;
        break;
        }
      }
    }
  }
}

void rebateuEsquerda(){
  if(i == 0){ //bola no canto esquerdo
    sentido = 1; //muda o sentido
    velocidade=velocidade-50; //aumenta a velocidade
    if(velocidade <= 50){ //garante a velocidade minima de 50
      velocidade = 50;
    }
  }
  else{
    fimDeJogo(0); //vai pra função fim de jogo levando 0
    //isso mostra que ESQUERDA perdeu
  }
}

void rebateuDireita(){
  if(i == 15){ //bola no canto direito
    sentido = 0; //muda o sentido
    velocidade=velocidade-50; //aumenta a velocidade
    if(velocidade <= 50){ //garante a velocidade minima de 50
      velocidade = 50;
    }
  }
  else{
    fimDeJogo(1);//vai pra função fim de jogo levando 1
    //isso mostra que DIREITA perdeu
  }
}

int fimDeJogo(int x){
  if(x == 0){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Esquerda Perdeu!");
    lcd.setCursor(0,1);
    lcd.print("RESETE o Arduino");
    while(1);
  }
  if(x == 1){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Direita Perdeu!");
    lcd.setCursor(0,1);
    lcd.print("RESETE o Arduino");
    while(1);
  }
}
