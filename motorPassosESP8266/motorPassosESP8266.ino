#include "SoftwareSerial.h"

SoftwareSerial ESP_Serial(2, 3); // RX, TX

String redeWork = "dbs-note-153";
String rede = "NET_2G40A775";
String senha = "F840A775";
String resposta = "";

const int pot = A0;
int i;
int pins[] = {8, 9, 10, 11};
int side = 0;
int velocidade = 0;
String direcao = "";

void setup() {
  ESP_Serial.begin(9600);

  sendCommand("AT");
  readResponse(1000);

  sendCommand("AT+CWMODE=1");
  readResponse(1000);

  Serial.println("Inicializando...");
  delay(1000);

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

    Serial.println("Obtendo endereco de IP na rede...");
    sendCommand("AT+CIFSR");
    readResponse(1000);

    Serial.println("Configurando para multiplas conexoes...");
    sendCommand("AT+CIPMUX=1");
    readResponse(1000);

    Serial.println("Ligando servidor...");
    sendCommand("AT+CIPSERVER=1,80");
    readResponse(1000);

    Serial.print("Pronto, acesse o IP atraves de um dispositivo ligado na mesma rede do ESP8266.");
  }

  for ( i = 0 ; i < 4 ; i++ ) {
    pinMode(pins[i], OUTPUT); // Configura os pinos como saída
  }
}

void loop() {

  velocidade = analogRead(pot); // Faz a leitura do potenciometro
  velocidade = map(velocidade, 0, 1023, 1, 100); // Mapeia para ficar entre 1 e 100

  if (side == 0) { // Aciona o motor no sentido Horário
    direcao = "Horario";
    Serial.println(direcao);
    Serial.println(velocidade);
    for ( i = 0 ; i < 4 ; i++ ) { // Intercala o as bobinas acionadas
      digitalWrite(pins[i], HIGH); // Envia um pulso de um passo
      delay(velocidade);
      digitalWrite(pins[i], LOW);
    }
    atualizaServico(velocidade, direcao);
  }
  if (side == 1) { // Aciona o motor no sentido Anti-Horário
    direcao = "Anti-Horario";
    Serial.println("Anti-Horario");
    Serial.println(velocidade);
    for ( i = 4 ; i > -1 ; i-- ) { // Intercala o as bobinas acionadas
      digitalWrite(pins[i], HIGH); // Envia um pulso de um passo
      delay(velocidade);
      digitalWrite(pins[i], LOW);
    }
    atualizaServico(velocidade, direcao);
  }

}

void atualizaServico(int v, String d) {
  if (ESP_Serial.available()) {

    //.find le os dados vindos da serial ate o alvo, neste caso +IPD,
    if (ESP_Serial.find((char*)"+IPD,")) {
      delay(500);
      char id = ESP_Serial.peek();//pega ID da conexao

      //nossa pagina web em HTML
      String webpage = String("HTTP/1.1 200 OK\r\n") +
                       "Content-Type: text/html\r\n" +
                       "Connection: close\r\n" +
                       "Refresh: 7.5\r\n" +                       
                       "\r\n" +
                       "<!DOCTYPE HTML>" +
                       "<html style=\"font-size:1em\">" +
                       "<h1>" +
                       "Velocidade: " + v +
                       "</h1><br/>" +
                       "<h1>" +
                       "Direção: " + d +
                       "</h1><br/></html>" +
                       "\r\n";

      String cipSend = "AT+CIPSEND=";
      cipSend += (int(id) - 48);
      cipSend += ",";
      cipSend += webpage.length();
      Serial.println(webpage.length());
      sendCommand(cipSend);
      readResponse(500);

      sendCommand(webpage);
      readResponse(750);

      String closeCommand = "AT+CIPCLOSE=";
      closeCommand += (int(id) - 48);
      sendCommand(closeCommand);
      readResponse(750);
    }
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

