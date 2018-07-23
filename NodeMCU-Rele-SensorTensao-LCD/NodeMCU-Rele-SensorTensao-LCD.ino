#include "Wire.h"
#include "LiquidCrystal_I2C.h"
#include "ESP8266WiFi.h"

const char* rede = "dbs-note-153"; 
const char* redeX = "NET_2G40A775";
const char* senhaX = "F840A775";
const char* senha = "c4nn4b1s";

const int rele = 16;
LiquidCrystal_I2C lcd(0x3F,16,2);
WiFiServer server(80);

void setup(){
  pinMode(rele, OUTPUT);
  digitalWrite(rele, LOW);
  
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0,0);
  delay(10);
  
  lcd.print(redeX);
  lcd.setCursor(0,1);

  WiFi.begin(redeX, senhaX);

  while (WiFi.status() != WL_CONNECTED){
    delay(500);
    lcd.setCursor(0,1);
    lcd.print("_");
    lcd.setCursor(0,1);
    lcd.print("|");
  }

  server.begin();
  
  delay(1000);
  lcd.setCursor(0,1);  
  lcd.print(WiFi.localIP());
}

void loop() {
  delay(10);
  WiFiClient client = server.available();
  if(!client){
    return;
  }

  //Serial.println("new client");
  while(!client.available()){
    delay(1);
  }

  String request = client.readStringUntil('\r');
  //Serial.println(request);
  client.flush();

  int value = LOW;
  if(request.indexOf("/rele=ON") != -1){
    digitalWrite(rele, HIGH);
    value = HIGH;
  }
  if(request.indexOf("/rele=OFF") != -1){
    digitalWrite(rele, LOW);
    value = LOW;
  }

  // Set relePin according to the request
  //digitalWrite(relePin, value);
  // Return the response
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println(""); //  do not forget this one
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
 
  client.print("Lampada : ");
 
  if(value == HIGH) {
    client.print("LIGADA");
  } else {
    client.print("DESLIGADA");
  }
  client.println("<br><br>");
  client.println("<a href=\"/rele=ON\"\"><button>Ligar</button></a>");
  client.println("<a href=\"/rele=OFF\"\"><button>Desligar</button></a><br />");  
  client.println("</html>");
 
  delay(1);
  //Serial.println("Client disonnected");
  //Serial.println("");
  
}
 