#include "DHT.h"
#include "LiquidCrystal.h"

#define DHTTYPE DHT11
#define DHTPIN A0

const int LM35 = A1;
float temp = 0;
int ADClido = 0;
const int alert = 9;
const int green = 10;
const int warning = 8;
DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup()
{
  analogReference(INTERNAL);
  pinMode(alert, OUTPUT);
  pinMode(warning, OUTPUT);
  pinMode(green, OUTPUT);
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("Temperatura");
  lcd.setCursor(0, 1);
  lcd.print("DHT x LM35");
  dht.begin();
  delay(3000);
}

void loop()
{
  ADClido = analogRead(LM35);
  temp = ADClido * 0.1075268817204301; //no Leonardo use 0.4887585532
  delay(500);
  // A leitura da temperatura e umidade pode levar 250ms!
  // O atraso do sensor pode chegar a 2 segundos.
  float h = dht.readHumidity();
  // testa se retorno é valido, caso contrário algo está errado.
  if (isnan(h))
  {
    lcd.println("Failed to read from DHT");
  }
  else
  {
    lcd.setCursor(0, 0);
    lcd.print("Umidade: ");
    lcd.print(h);
    lcd.print(" %");
    lcd.setCursor(0, 1);
    lcd.print("Temp2: ");
    lcd.print(temp);
    lcd.print(" *C");
    lcd.setCursor(0, 1);
    if(temp < 14){
      digitalWrite(alert,HIGH);
    }
    else if((temp >= 14) && (temp < 16)){
      digitalWrite(warning, HIGH);
    }
    else if((temp >= 16) && (temp < 21)){
      digitalWrite(green, HIGH);
    }
    else{
      digitalWrite(green, LOW);
      digitalWrite(warning, LOW);
      digitalWrite(alert, LOW);
    }
  }
}

