const int Potenciometro = A0;
const int Led = 13;
int ValorPot = 0;
int pwm = 0;

void setup(){
  pinMode(Led, OUTPUT);
}

void loop(){
  ValorPot = analogRead(Potenciometro);
  pwm = map(ValorPot, 0, 1023, 0 ,255);
  analogWrite(Led, pwm);
}

