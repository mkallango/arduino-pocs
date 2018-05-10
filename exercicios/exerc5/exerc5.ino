long randNum;
const int a = 4;
const int b = 5;
const int c = 6;
const int d = 7;
const int Botao= 2;
int EstadoBotao = 0;

void setup(){
  pinMode(a, OUTPUT);
  pinMode(b, OUTPUT);
  pinMode(c, OUTPUT);
  pinMode(d, OUTPUT);
  pinMode(Botao, INPUT);
  randomSeed(digitalRead(Botao));  
}

void loop(){
  EstadoBotao = digitalRead(Botao);
  if(EstadoBotao == HIGH){
    printRandom();
    delay(500);
  }
}

void printRandom(){
      randNum = random(0,6) + 1;
    switch(randNum){
      case 1:
        printUm();
        break;
      case 2:
        printDois();
        break;
      case 3:
        printTres();
        break;
      case 4:
        printQuatro();
        break;
      case 5:
        printCinco();
        break;
      case 6:
        printSeis();
        break;
      default:
        break;
    }
}

void printZero(){
  //0
  digitalWrite(a,LOW);
  digitalWrite(b,LOW);
  digitalWrite(c,LOW);
  digitalWrite(d,LOW);
}

void printUm(){
  //1
  digitalWrite(a,HIGH);
  digitalWrite(b,LOW);
  digitalWrite(c,LOW);
  digitalWrite(d,LOW);
}

void printDois(){
  //2
  digitalWrite(a,LOW);
  digitalWrite(b,HIGH);
  digitalWrite(c,LOW);
  digitalWrite(d,LOW);
}

void printTres(){
  //3
  digitalWrite(a,HIGH);
  digitalWrite(b,HIGH);
  digitalWrite(c,LOW);
  digitalWrite(d,LOW);
}

void printQuatro(){
  //4
  digitalWrite(a,LOW);
  digitalWrite(b,LOW);
  digitalWrite(c,HIGH);
  digitalWrite(d,LOW);
}

void printCinco(){
  //5
  digitalWrite(a,HIGH);
  digitalWrite(b,LOW);
  digitalWrite(c,HIGH);
  digitalWrite(d,LOW);
}

void printSeis(){
  //6
  digitalWrite(a,LOW);
  digitalWrite(b,HIGH);
  digitalWrite(c,HIGH);
  digitalWrite(d,LOW);
}

void scrumble(){
  
}

