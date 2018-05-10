int LED[] = {3,4,5,6,7,8,9,10,11,12};

void setup(){
  for(int x = 0; x < 10; x++){
    pinMode(LED[x], OUTPUT);
  }
}

void loop(){
  leds(true);  
  leds(false);
}

void leds(bool acende){
  if(acende){
    for(int x=0; x < 10; x++){
      digitalWrite(LED[x],HIGH);
      delay(50);
    }
  }  
  else{
    delay(200);
    for(int x=9; x >= 0; x--){
      digitalWrite(LED[x],LOW);      
      delay(50);
    }
  }

}

