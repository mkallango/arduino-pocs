#include "SoftwareSerial.h"

SoftwareSerial ESP_Serial(2, 3); // RX, TX

String rede = "dbs-note-153";
String senha = "c4nn4b1s";
String resposta = "";

void setup() {
  Serial.begin(9600);
  ESP_Serial.begin(9600);

  Serial.println("Inicializando...");
  delay(1000);

  Serial.println("Chamando atencao do modulo com AT...");
  sendCommand("AT");
  readResponse(5000);

  Serial.println("Mudando o modo com CWMODE=1...");
  sendCommand("AT+CWMODE=1");
  readResponse(1000);

  Serial.println("Conectando a rede...");
  String CWJAP = "AT+CWJAP=\"";
  CWJAP += rede;
  CWJAP += "\",\"";
  CWJAP += senha;
  CWJAP += "\"";
  sendCommand(CWJAP);
  readResponse(10000);

  delay(2000); //espera de seguranca

  if (resposta.indexOf("OK") == -1) { //procura na resposta se houve OK
    Serial.println("Atencao: Nao foi possivel conectar a rede WiFi.");
    Serial.println("Verifique se o nome da rede e senha foram preenchidos corretamente no codigo e tente novamente.");
  } else {
    Serial.println("Sucesso! Conectado a rede WiFi.");
  }
}

void loop() {
  if (ESP_Serial.available()) {
    Serial.write(ESP_Serial.read());
  }
  if (Serial.available()) {
    ESP_Serial.write(Serial.read());
  }
}

void sendCommand(String cmd) {
  ESP_Serial.println(cmd);
}

void readResponse(unsigned int timeout) {
  unsigned long timeIn = millis(); //momento que entramos nessa funcao é salvo
  resposta = "";
  //cada comando AT tem um tempo de resposta diferente...
  while (timeIn + timeout > millis()) {
    if (ESP_Serial.available()) {
      char c = ESP_Serial.read();
      resposta += c;
    }
  }
  Serial.println(resposta);
}
