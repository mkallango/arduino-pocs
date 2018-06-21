/*******************************************************************************
* Kit Avançado para Arduino v4 - Detectando Sons
* Mostrar os valores lidos pelo Sensor de Som no Monitor Serial.
*******************************************************************************/

const int pino_microfone = A0; // pino onde o sensor de som está conectado
int leitura = 0; // variável para armazenar o valor lido pelo ADC
float tensao = 0.0; // variável para armazenar a tensão

void setup() {
  // Inicia e configura a Serial
  Serial.begin(9600); // 9600bps

  // configura o pino com sensor de som como entrada
  pinMode(pino_microfone, INPUT); // pino A0
}

void loop() {
  // le o valor de tensão no pino do sensor de som
  leitura = analogRead(pino_microfone);

  // imprime valor lido pelo arduino (0 a 1023)
  Serial.println(leitura);

  // converte e imprime o valor em tensão elétrica
  tensao = leitura * 5.0 / 1023.0;
  Serial.println(tensao);

  Serial.println(); // nova linha
}
