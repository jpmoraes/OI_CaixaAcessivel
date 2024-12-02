#include <WiFi.h>
#include <WebServer.h>

// Substitua pelos dados da sua rede Wi-Fi
const char* ssid = "VISITANTE";
const char* password = "Senac2018";

// Define o pino do LED
const int ledPin = ;  // Substitua pelo pino que você está usando

WebServer server(80);

void handleTurnOn() {
  digitalWrite(ledPin, HIGH);  // Acende o LED
  server.send(200, "text/plain", "LED ON");
}

void handleTurnOff() {
  digitalWrite(ledPin, LOW);   // Apaga o LED
  server.send(200, "text/plain", "LED OFF");
}

void setup() {
  Serial.begin(115200);

  // Conecta-se à rede Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Connected to WiFi");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);  // Inicialmente o LED está apagado

  // Define os manipuladores de rota
  server.on("/turn_on", handleTurnOn);
  server.on("/turn_off", handleTurnOff);

  // Inicia o servidor
  server.begin();
}

void loop() {
  server.handleClient();
}
