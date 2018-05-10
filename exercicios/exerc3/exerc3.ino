const int LM35 = 0;
float temperatura = 0;
int ADClido = 0;


void setup(){
  Serial.begin(9600);
  analogReference(INTERNAL); //No Mega, use INTERNAL1V1, no Leonardo remova essa linha
}


void loop(){
  ADClido = analogRead(LM35);
  delay(500);
  ADClido = analogRead(LM35);
  
  temperatura = ADClido * 0.1075268817204301; //no Leonardo use 0.4887585532
  Serial.print("Temperatura = ");
  Serial.print((temperatura * (9/5))+32);
  Serial.println(" *F"); 
  Serial.print("Temperatura = ");
  Serial.print(temperatura);
  Serial.println(" *C"); 
  delay(1000); 
}
