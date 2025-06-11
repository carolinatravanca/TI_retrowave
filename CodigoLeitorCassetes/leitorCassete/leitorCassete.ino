#include <SPI.h>
#include <MFRC522.h>
#include <WiFi.h>
#include <PubSubClient.h>

#define SS_PIN 4
#define RST_PIN 13
#define BUTTON_PIN 14

const char* ssid = "FE6FDB";
const char* password = "zmzz1626";
const char* mqtt_server = "broker.hivemq.com";

WiFiClient espClient;
PubSubClient client(espClient);
MFRC522 rfid(SS_PIN, RST_PIN);


unsigned long ultimoPress = 0;
const unsigned long debounceDelay = 50;
bool ultimoEstado = HIGH;

void setup_wifi() {
  Serial.print("A conectar a: ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("Ligado ao wifi: ");
  Serial.println(WiFi.localIP());
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("A tentar conexão com servidor de MQTT");
    if (client.connect("ESP32Client1234")) {
      Serial.println("conectado!");
      client.publish("leitor", "Leitor pronto :)");
    } else {
      Serial.print("erro na conexão :( , rc=");
      Serial.print(client.state());
      Serial.println(" nova tentativa daqui a 5 segundo");
      delay(5000);
    }
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  SPI.begin();
  rfid.PCD_Init();
  setup_wifi();
  client.setServer(mqtt_server, 1883);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();


  bool estadoAtual = digitalRead(BUTTON_PIN);
  if (ultimoEstado == HIGH && estadoAtual == LOW) {
    unsigned long now = millis();
    if (now - ultimoPress > debounceDelay) {
      Serial.println("STOP");
      client.publish("leitor", "STOP");
      ultimoPress = now;
    }
  }
  ultimoEstado = estadoAtual;


  if (rfid.PICC_IsNewCardPresent() && rfid.PICC_ReadCardSerial()) {
    String uidString = "";
    for (byte i = 0; i < rfid.uid.size; i++) {
      uidString += String(rfid.uid.uidByte[i], HEX);
    }
    uidString.toUpperCase();
    Serial.println("Card UID: " + uidString);
    client.publish("leitor", uidString.c_str());
    rfid.PICC_HaltA();
  }
}

