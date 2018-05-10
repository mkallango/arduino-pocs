const int ledPinAmarelo = 11;
const int ledPinVerde = 12;
const int ledPinVermelho = 13;
const int Buzzer = 8;
const int BotaoVerde = 4;
const int BotaoAmarelo = 2;
const int BotaoVermelho = 6;
int EstadoBotaoVerde = 0;
int EstadoBotaoAmarelo = 0;
int EstadoBotaoVermelho = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(Buzzer, OUTPUT);
  pinMode(ledPinVerde, OUTPUT);
  pinMode(BotaoVerde, INPUT);
  pinMode(ledPinAmarelo, OUTPUT);
  pinMode(BotaoAmarelo, INPUT);
  pinMode(ledPinVermelho, OUTPUT);
  pinMode(BotaoVermelho, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  EstadoBotaoVerde = digitalRead(BotaoVerde);
  EstadoBotaoAmarelo = digitalRead(BotaoAmarelo);
  EstadoBotaoVermelho = digitalRead(BotaoVermelho);
  
  if(EstadoBotaoVerde == HIGH){
    digitalWrite(ledPinVerde, HIGH);
    tone(Buzzer, 600);
  }
  
  if(EstadoBotaoVermelho == HIGH){
    digitalWrite(ledPinVermelho, HIGH);
    tone(Buzzer, 732);
  }
  
  if(EstadoBotaoAmarelo == HIGH){
    digitalWrite(ledPinAmarelo, HIGH);
    tone(Buzzer, 1500);
  }

  if(!EstadoBotaoVerde && !EstadoBotaoAmarelo && !EstadoBotaoVermelho){
    digitalWrite(ledPinVerde, LOW);
    digitalWrite(ledPinAmarelo,LOW);
    digitalWrite(ledPinVermelho,LOW);
    noTone(Buzzer);
  }
}
