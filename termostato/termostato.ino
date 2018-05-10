const int LM35 = 0;
float temperatura = 0;
int ADClido = 0;
const int Buzzer = 12;

void setup() {
  Serial.begin(9600);
  analogReference(INTERNAL);
  pinMode(Buzzer, OUTPUT);
}

void loop() {
  ADClido = analogRead(LM35);
  temperatura = ADClido * 0.1075268817;
  Serial.print("Temperatura = ");
  Serial.print(temperatura);
  Serial.println(" *C");
  delay(500);
  if(temperatura > 29){
    ADClido = analogRead(LM35);
    temperatura = ADClido * 0.1075268817;
    if(temperatura>29){
      tone(Buzzer,432);
    }
  }
  else{
    noTone(Buzzer);
  }
}
