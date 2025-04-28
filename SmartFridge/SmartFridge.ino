#include <DHT.h>

#define DHTPIN 2
#define DHTTYPE DHT11

#define GREEN_LED 5
#define RED_LED 4
#define BUZZER_PIN 6

DHT dht(DHTPIN, DHTTYPE);
unsigned long lastSend = 0;

void setup() {
  pinMode(GREEN_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  digitalWrite(GREEN_LED, HIGH);
  digitalWrite(RED_LED, LOW);
  digitalWrite(BUZZER_PIN, LOW);

  Serial.begin(9600);
  dht.begin();
}

void loop() {
  if (Serial.available()) {
    String msg = Serial.readStringUntil('\n');
    msg.trim();
    if (msg == "ALERTE") {
      digitalWrite(GREEN_LED, LOW);
      digitalWrite(RED_LED, HIGH);
      digitalWrite(BUZZER_PIN, HIGH);
    }
  }

  if (millis() - lastSend > 10000) {
    float temp = dht.readTemperature();
    if (!isnan(temp)) {
      Serial.print("TEMP:");
      Serial.println(temp); // ✅ No prefix, only TEMP:xx.xx
    }
    lastSend = millis();
  }
}
