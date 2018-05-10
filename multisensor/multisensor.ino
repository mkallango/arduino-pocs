const int LDR = A0;
const int LM35 = A1;
const int Buzzer = 2;
const int led[]={
  5,6,7,8,9,10,11
};
int ValorLDR = 0;
int ADClido = 0;
float temperatura = 0;

void setup(){
  for(int x=0; x<7; x++){
    pinMode(led[x],OUTPUT);
  }
}

void loop(){
  analogRead(LDR);
  delay(5);
  ValorLDR = analogRead(LDR);
  analogRead(LM35);
  delay(5);
  ADClido = analogRead(LM35);
  temperatura = ADClido * 0.4887585532;

  if(temperatura > 27){
    digitalWrite(led[0],HIGH);
  }
  else{
    digitalWrite(led[0],LOW);
  }
  if(temperatura > 28){
    digitalWrite(led[1], HIGH);
  }
  else{
    digitalWrite(led[1],LOW);
  }
  if(temperatura > 29){
    digitalWrite(led[2], HIGH);
  }
  else{
    digitalWrite(led[2],LOW);
  }

  if(ValorLDR > 400){
    digitalWrite(led[5], HIGH);
  }
  else{
    digitalWrite(led[5], LOW);
  }
  if(ValorLDR > 250){
    digitalWrite(led[4], HIGH);
  }
  else{
    digitalWrite(led[4], LOW);
  }
  if(ValorLDR > 100){
    digitalWrite(led[3], HIGH);
    digitalWrite(led[6], LOW);
  }
  else{
    digitalWrite(led[3], LOW);
    digitalWrite(led[6], HIGH);
  }
}

