int valvula = 8; // sinal do rele para válvula
const int botao = 7
int EstadoBotao = 0;

void setup() {
  pinMode(valvula, OUTPUT); // declara válvula como saída
  pinMode(botao, INPUT);
}
 
void loop() {
 EstadoBotao = digitalRead(botao);
 
 if (EstadoBotao == HIGH){
   // se sim, libera água por 1s
   digitalWrite(valvula,LOW);
   delay(1000);
   digitalWrite(valvula,HIGH); // desliga válvula
 }else{
 // se não, interrompe a passagem de água
   digitalWrite(valvula,HIGH);
   delay(1000);
 }
}

