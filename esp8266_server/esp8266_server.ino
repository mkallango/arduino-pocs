//Inclui as funÃ§Ãµes de Wifi do ESP
#include <ESP8266WiFi.h>

//Cria um server na porta 80 (porta padrÃ£o para onde os navegadores enviam as requisiÃ§Ãµes http)
WiFiServer server(80);

void setup()
{
  //Inicializa a Serial apenas para efeito de log
  Serial.begin(115200);

  //Configura o GPIO0 e GPIO2 como output, ou seja, como saÃ­da para podermos alterar o seu valor
  pinMode(0, OUTPUT);
  pinMode(2, OUTPUT);
  //Deixa o GPIO0 e o GPIO2 com saÃ­da LOW
  digitalWrite(0, LOW);
  digitalWrite(2, LOW);

  Serial.print("Conectando");
  //Faz o ESP se conectar Ã  rede WiFi. No nosso exemplo o ssid da rede Ã© TesteESP e a senha Ã© 87654321
  WiFi.begin("TesteESP", "87654321");

  //Enquanto o ESP nÃ£o se conectar Ã  rede
  while (WiFi.status() != WL_CONNECTED)
  {
    //Esperamos 100 milisegundos
    delay(100);
    Serial.print(".");
  }

  //Se chegou aqui Ã© porque conectou Ã  rede, entÃ£o mostramos no monitor serial para termos um feedback
  Serial.println("");
  Serial.println("Conectou");

  //ConfiguraÃ§Ãµes do IP fixo. VocÃª pode alterar conforme a sua rede
  IPAddress ip(192, 168, 2, 8);
  IPAddress gateway(192, 168, 2, 1);
  IPAddress subnet(255, 255, 255, 0);
  Serial.print("Configurando IP fixo para : ");
  Serial.println(ip);

  //Envia a configuraÃ§Ã£o
  WiFi.config(ip, gateway, subnet);

  //Inicializa o server que criamos na porta 80
  server.begin();

  //Mostramos no monitor serial o IP que o ESP possui para verificarmos se Ã© o mesmo que configuramos
  Serial.print("Server em: ");
  Serial.println(WiFi.localIP());
}

void loop()
{
  //Verifica se algum cliente estÃ¡ tentando se conectar
  WiFiClient client = server.available();
  if (!client)
  {
    //Se nÃ£o houver nenhum cliente podemos retornar pois nÃ£o hÃ¡ nada a fazer
    return;
  }

  Serial.println("Novo cliente conectou");

  //Fazemos a leitura da requisiÃ§Ã£o
  String req = client.readStringUntil('\r');
  Serial.print("RequisiÃ§Ã£o: ");
  Serial.println(req);

  //Este Ã© o html que iremos retornar para o cliente
  //Ã‰ composto basicamente de dois botÃµes (ON e OFF) para o GPIO0 e dois botÃµes (ON e OFF) para o GPIO2
  //A parte que nos interessa Ã© o <a href=' com a aÃ§Ã£o vinculada a cada botÃ£o
  //Quando clicamos em um destes botÃµes essa informaÃ§Ã£o chegarÃ¡ atÃ© o ESP para que ele verifique qual aÃ§Ã£o deve executar
  //A parte dentro de '<style>' Ã© apenas para modificarmos o visual da pÃ¡gina que serÃ¡ exibida, vocÃª pode alterÃ¡-la como queira
  String html = 
  "<html>"
    "<head>"
      "<meta name='viewport' content='width=device-width, initial-scale=1, user-scalable=no'/>"
      "<title>ESP8266</title>"
      "<style>"
        "body{"
          "text-align: center;"
          "font-family: sans-serif;"
          "font-size:14px;"
          "padding: 25px;"
        "}"

        "p{"
          "color:#444;"
        "}"

        "button{"
          "outline: none;"
          "border: 2px solid #1fa3ec;"
          "border-radius:18px;"
          "background-color:#FFF;"
          "color: #1fa3ec;"
          "padding: 10px 50px;"
        "}"

        "button:active{"
          "color: #fff;"
          "background-color:#1fa3ec;"
        "}"
      "</style>"
    "</head>"
    "<body>"
    "<p>GPIO0</p>"
    "<p><a href='?acao=gpio0On'><button>ON</button></a></p>"
    "<p><a href='?acao=gpio0Off'><button>OFF</button></a></p>"
    "<p>GPIO2</p>"
    "<p><a href='?acao=gpio2On'><button>ON</button></a></p>"
    "<p><a href='?acao=gpio2Off'><button>OFF</button></a></p>"
    "</body>"
  "</html>";

  //Escreve o html no buffer que serÃ¡ enviado para o cliente
  client.print(html);
  //Envia os dados do buffer para o cliente
  client.flush();

  //Verifica se a requisiÃ§Ã£o possui a aÃ§Ã£o gpio0On
  if (req.indexOf("acao=gpio0On") != -1)
  {
      //Se possui a aÃ§Ã£o gpio0On colocamos a saÃ­da do GPIO0 como alta
      digitalWrite(0, HIGH);
  }
  //SenÃ£o, verifica se a requisiÃ§Ã£o possui a aÃ§Ã£o gpio0Off
  else if (req.indexOf("acao=gpio0Off") != -1)
  {
    //Se possui a aÃ§Ã£o gpio0Off colocamos a saÃ­da do GPIO0 como baixa
    digitalWrite(0, LOW);
  }
  //SenÃ£o, verifica se a requisiÃ§Ã£o possui a aÃ§Ã£o gpio2On
  else if (req.indexOf("acao=gpio2On") != -1)
  {
    //Se possui a aÃ§Ã£o gpio2On colocamos a saÃ­da do GPIO2 como alta
    digitalWrite(2, HIGH);
  }
  //SenÃ£o, verifica se a requisiÃ§Ã£o possui a aÃ§Ã£o gpio2Off
  else if (req.indexOf("acao=gpio2Off") != -1)
  {
    //Se possui a aÃ§Ã£o gpio0Off colocamos a saÃ­da do GPIO2 como baixa
    digitalWrite(2, LOW);
  }

  //Fecha a conexÃ£o com o cliente
  client.stop();
  Serial.println("Cliente desconectado");
}
