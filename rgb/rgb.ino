const int R = 8;
const int G = 9;
const int B = 10;


void setup(){
  pinMode(R, OUTPUT);
  pinMode(G, OUTPUT);
  pinMode(B, OUTPUT);
}

void loop(){
      digitalWrite(R, HIGH);
      digitalWrite(G, LOW);
      digitalWrite(B, HIGH);
      delay(500);
      digitalWrite(R, HIGH);
      digitalWrite(G, HIGH);
      digitalWrite(B, HIGH);
      delay(500);
      digitalWrite(R, LOW);
      digitalWrite(G, LOW);
      digitalWrite(B, HIGH);
      delay(500);
}

