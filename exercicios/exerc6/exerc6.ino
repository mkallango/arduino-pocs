const int LED[] = {2,3,4,5,6,7,8,9,10,11};
const int LedBrilho = 12;
const int PinoPot = A0;
int ValorPot = 0;
int pwm = 0;
int pwm2 = 0;

void setup(){
  Serial.begin(9600);
  pinMode(LedBrilho, OUTPUT);
  for(int x = 0; x < 10; x++){
    pinMode(LED[x], OUTPUT);
  }  
}

void loop(){
  ValorPot = analogRead(PinoPot);
  pwm = map(ValorPot, 0, 1023, 0, 255);
  analogWrite(LedBrilho, pwm);
  
  printaPotencia(ValorPot);
  Serial.print(pwm2);
}

void printaPotencia(int intensidade){
  int consumo = 0;
  consumo = map(intensidade, 0, 1023, 0, 10);

  int desligados = 10-consumo;
  for(int x = 0; x < consumo; x++){
    digitalWrite(LED[x], HIGH);  
  }

  for(int x = 0; x < desligados; x++){
    digitalWrite(LED[9-x], LOW);
  }  
}

