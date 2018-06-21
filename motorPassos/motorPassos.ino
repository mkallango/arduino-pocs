const int pot = A0;
int i;
int pins[] = {7,8,9,10};
int side = 0;
int velocidade = 0;

void setup() {
  Serial.begin(9600);
  Serial.print("Digite 0 ou 1");
  for( i=0 ; i < 4 ; i++ ){
    pinMode(pins[i],OUTPUT); // Configura os pinos como saída
  }
}

void loop() {
  
  if(Serial.available() > 0){  
    side = Serial.read();
  }
  
  velocidade = analogRead(pot); // Faz a leitura do potenciometro
  velocidade = map(velocidade,0,1023,1,100); // Mapeia para ficar entre 1 e 100
      
  if(side == 0){ // Aciona o motor no sentido Horário
    Serial.println("Horario");
    Serial.println(velocidade);
    for( i=0 ; i < 4 ; i++ ){  // Intercala o as bobinas acionadas
       digitalWrite(pins[i],HIGH); // Envia um pulso de um passo
       delay(velocidade); 
       digitalWrite(pins[i],LOW);
    }
  }
  if(side == 1){ // Aciona o motor no sentido Anti-Horário
    Serial.println("Anti-Horario");
    Serial.println(velocidade);
    for( i=4 ; i > -1 ; i-- ){ // Intercala o as bobinas acionadas
       digitalWrite(pins[i],HIGH); // Envia um pulso de um passo
       delay(velocidade);
       digitalWrite(pins[i],LOW); 
    }
  }
}
