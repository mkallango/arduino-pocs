/*******************************************************************************
* Kit Avançado para Arduino v4 - Projeto Clapper
* Acionar e/ou desativar um dispositivo com som de palmas.
*******************************************************************************/

const int pino_microfone = A0; // pino onde o potenciometro está conectado
int leitura = 0; // variável para armazenar o valor lido pelo ADC

const int pino_rele = 3; // pino onde o rele está conectado
int estado_rele = 0; // variável para armazenar o estado do rele

float amplitude = 0.0; // armazenará o valor de pico a pico da onda
unsigned int valor_max = 0; // armazenará o valor máximo lido pelo sensor
unsigned int valor_min = 1024; // armazenará o valor mínimo lido pelo sensor
float valor_limite = 4.5; // valor mínimo para considerar uma palma (0.0 - 5.0)
unsigned long inicio_amostragem; // armazena o instante que começou a amostragem
const unsigned long tempo_amostragem = 250; // tempo de amostragem em ms

int palmas = 0; // contador de palmas
unsigned long tempo_palmas; // armazena o instante que começou a amostragem
const unsigned long tempo_palmas_max = 500; // período de amostragem de palmas

void setup() {
  // Inicia e configura a Serial
  Serial.begin(9600); // 9600bps

  pinMode(pino_microfone, INPUT); // configura o pino com potenciometro como entrada
  pinMode(pino_rele, OUTPUT); // configura o pino com o rele como saída
}

void loop() {

  // Coleta dados durante o tempo de amostragem
  if (millis() - inicio_amostragem < tempo_amostragem) {

    // le o valor de tensão no pino do sensor
    leitura = analogRead(pino_microfone);

    // se valor lido for maior que valor máximo
    if (leitura > valor_max) {
      valor_max = leitura; // atualiza valor máximo
    }
     // se valor lido for menor que valor mínimo
    else if (leitura < valor_min) {
      valor_min = leitura; // atualiza valor mínimo
    }

  }
  else { // processa os dados
    inicio_amostragem = millis(); // reseta o tempo inicial da amostragem

    // calcula, converte e imprime o valor de pico-a-pico em tensão elétrica
    amplitude = valor_max - valor_min; // max - min = pico-a-pico, amplitude
    amplitude = (amplitude * 5.0) / 1023.0; // converte para tensão(V)

    Serial.println(amplitude); // imprime a amplitude no Monitor Serial

    // Reseta os valores máximos e mínimos
    valor_max = 0;
    valor_min = 1024;

    // Se o valor de amplitude superar o valor limite, inverte o estado da carga
    if (amplitude > valor_limite) {
      if (palmas == 0){ // se for a primeira palma daquele período
        tempo_palmas = millis(); // reinicia a amostragem de palmas
      }
      palmas++; // incrementa o número de palmas
    }

  }

  // se o tempo de amostragem de palmas é atingido
  if (millis() - tempo_palmas > tempo_palmas_max) {

    tempo_palmas = millis(); // reseta tempo inicial da amostragem de palmas

    // Se o número de palmas captadas naquele periodo for igual a 2
    if (palmas == 2) {
      estado_rele = ! estado_rele; // inverte o estado do rele e
      digitalWrite(pino_rele, estado_rele); // atualiza o estado do rele
    }

    palmas = 0; // reinicia o contador de palmas
  }

}
