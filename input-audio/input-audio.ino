int LED[] = {2,3,4,5,6};
int input = 0;
float sound = 0;

void setup(){
  analogReference(INTERNAL);
  Serial.begin(9600);
  for(int x = 0; x < 5; x++){
    pinMode(LED[x], OUTPUT);
  }  
  
}

void loop(){
  sound = analogRead(input);
  Serial.println(sound);
  delay(600);
}


