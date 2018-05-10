const int LDR = A0;
const int Led = 6;
int ValorLido = 0;
int pwm = 0;

void setup(){
  Serial.begin(9600);
  pinMode(Led, OUTPUT);
}

void loop(){
  ValorLido = analogRead(LDR);
  Serial.print("Valor lido pelo LDR = ");
  Serial.println(ValorLido);
  delay(500);

  if(ValorLido < 300){
    analogWrite(Led, pwm);
    pwm+=20;
    delay(100);
  }
  else{
    analogWrite(Led, pwm);
    pwm-=20;
  }
  if(pwm > 255){
    pwm = 255;
  }
  if(pwm < 0){
    pwm = 0;
  }
}

