#include "Wire.h"
#include "SoftwareSerial.h"

SoftwareSerial ESP_Serial(0,1);
const int endereco_MPU = 0x68;

float acel_x, acel_y, acel_z;
float giro_x, giro_y, giro_z;
float temp;

const int pir_signal_pin = 10;
const int relay = 9;
const int LED = 13;
const int buzzer = 11;
const int button = 12;

boolean pir_status, ledState;
int button_status, flag = 0;
unsigned long previousMillis_liga = 0, previousMillis_desliga = 0;
const long interval = 100, alarme_liga = 500, alarme_desliga = 1000;

void setup() {
  Serial.begin(9600);
  ESP_Serial.begin(9600);
  Wire.begin();
  Wire.beginTransmission(endereco_MPU);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(true);
  
  pinMode(pir_signal_pin, INPUT);
  pinMode(button, INPUT);
  pinMode(relay, OUTPUT);
  pinMode(LED, OUTPUT);
  pinMode(buzzer, OUTPUT);
  digitalWrite(LED, HIGH);
}

void loop() {
  Wire.beginTransmission(endereco_MPU);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  Wire.requestFrom(endereco_MPU, 14, true);

  acel_x = Wire.read() << 8 | Wire.read();
  acel_y = Wire.read() << 8 | Wire.read();
  acel_z = Wire.read() << 8 | Wire.read();

  temp = Wire.read() << 8 | Wire.read();

  giro_x = Wire.read() << 8 | Wire.read();
  giro_y = Wire.read() << 8 | Wire.read();
  giro_z = Wire.read() << 8 | Wire.read();

  acel_x = acel_x / 16384.0;
  acel_y = acel_y / 16384.0;
  acel_z = acel_z / 16384.0;

  temp = temp / 340.00 + 36.53;

  giro_x = giro_x / 131.0;
  giro_y = giro_y / 131.0;
  giro_z = giro_z / 131.0;

  Serial.print("AcX: ");
  Serial.print(acel_x, 2);
  Serial.print(" | AcY: ");
  Serial.print(acel_y, 2);
  Serial.print(" | AcZ: ");
  Serial.print(acel_z, 2);
  Serial.print("");

  Serial.print(" | Tmp: ");
  Serial.print(temp);

  Serial.print(" | GyX: ");
  Serial.print(giro_x, 2);
  Serial.print(" | GyY: ");
  Serial.print(giro_y, 2);
  Serial.print(" | GyZ: ");
  Serial.print(giro_z, 2);

  Serial.println();
    
  button_status = digitalRead(button);
  if (button_status == HIGH) {
    while (button_status == HIGH) {
      button_status = digitalRead(button);
    }
    digitalWrite(relay, LOW);
    digitalWrite(LED, LOW);
    noTone(buzzer);
    flag++;
    if (flag == 0) {
      digitalWrite(LED, HIGH);
    }
    else {
      delay(10000);
      while (flag > 0) {
        pir_status = digitalRead(pir_signal_pin);
        if (pir_status == LOW) {
          unsigned long present = millis();
          if (present - previousMillis_liga >= interval) {
            previousMillis_liga = present;
            if (ledState == LOW) {
              ledState = HIGH;
            }
            else {
              ledState = LOW;
            }
            digitalWrite(LED, ledState);
          }
          digitalWrite(relay, LOW);
        }
        else {
          digitalWrite(relay, HIGH);
          digitalWrite(LED, LOW);
          while (flag > 0) {
            unsigned long present = millis();
            if (present -  previousMillis_liga >= alarme_liga) {
              previousMillis_liga = present;
              tone(buzzer, 2000);
            }
            if (present - previousMillis_desliga >= alarme_desliga) {
              previousMillis_desliga = present;
              noTone(buzzer);
            }
            button_status = digitalRead(button);
            if (button_status == HIGH) {
              flag = -1;
            }
          }
        }
      }
    }
  }

  delay(500);  
}
