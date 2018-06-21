#include "IRremote.h"

const int RECV_PIN = 11;
const int LED_GRN = 3;
const int LED_YLW = 2;
bool ylw_state = false;
bool grn_state = false;
IRrecv irrecv(RECV_PIN);
decode_results results;

void setup()
{
  pinMode(LED_GRN, OUTPUT);
  pinMode(LED_YLW, OUTPUT);
  Serial.begin(9600);
  irrecv.enableIRIn(); //começa a receber
}

void loop() {
  if (irrecv.decode(&results)) {
    Serial.println(results.value, HEX);
   
    if (results.value == 0xFF30CF){
      grn_state = !grn_state;
      Serial.println("Botao A Pressionado");
      digitalWrite(LED_GRN, grn_state);
      
    }
    
    if (results.value == 0xFF18E7){
      ylw_state = !ylw_state;
      Serial.println("Botao B Pressionado"); 
      digitalWrite(LED_YLW, ylw_state);
    }
   
    irrecv.resume(); // Recebe o próximo valor
  }
}
