#include <Arduino.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

#include <ESP8266WiFi.h>

#define RL 0
const char *ssid = "ESP1CNC";
const char *psk = "dustCollector";

ESP8266WebServer server(80);

void handleRoot();
void CollectorOn();
void CollectorOff();

void setup() {
  delay(1000);
  pinMode(RL, OUTPUT);
  digitalWrite(RL, LOW);

  // setup access point
  WiFi.softAP(ssid, psk, 1, true, 4);

  // define end points
  server.on("/", handleRoot);
  server.on("/oncollector", CollectorOn);
  server.on("/offcollector", CollectorOff);

  //start serving
  server.begin();
  }

void loop() {
  server.handleClient();
}

void CollectorOn(){ // Callback function for request "ON" message
  digitalWrite(RL, HIGH);
  server.send(200, "text/html", "<h1 style='color:green; font-family:sans-serif'>Collector is ON</h1>");
}
void CollectorOff(){ // Callback function for request "OFF" message
  digitalWrite(RL, LOW);
  server.send(200, "text/html", "<h1 style='color:#D3D3D3; font-family:sans-serif'>Collector is OFF</h1>");
}

void handleRoot(){ // Connection handler
  server.send(200, "text/html", "<h1>You are connected</h1>");
}