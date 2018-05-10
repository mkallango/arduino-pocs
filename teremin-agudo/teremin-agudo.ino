int ValorSensor = 0;
int nota = 0;
const int Buzzer = 9;

void setup(){
}

void loop(){
  ValorSensor = analogRead(A0);
  nota = map(ValorSensor, 1023, 5, 432, 2300);
  tone(Buzzer, nota, 20);
  delay(10);
}

