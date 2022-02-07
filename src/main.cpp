#include <Arduino.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

#include <ESP8266WiFi.h>
#include <ESP8266Ping.h>

#define RL 0
const char *ssid = "ESP1CNC";
const char *psk = "dustCollector";
int pingsFailed = 0;

ESP8266WebServer server(80);
//IPAddress ip (192, 168, 4, 2);

void handleRoot();
void CollectorOn();
void CollectorOff();

void setup() {
  // put your setup code here, to run once:
  delay(1000);
  Serial.begin(115200);
  while (!Serial);
  Serial.println();
  Serial.println("Configuring access point...");
  pinMode(RL, OUTPUT);
  digitalWrite(RL, LOW);

  // setup acces point
  WiFi.softAP(ssid, psk, 1, true, 4);
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);


  // define end points
  server.on("/", handleRoot);
  server.on("/oncollector", CollectorOn);
  server.on("/offcollector", CollectorOff);

  //start serving
  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();
  /*if (Ping.ping(ip)){ 
    //Serial.println("Client is alive!");
    pingsFailed = 0;
  }
  else pingsFailed++;
  if (pingsFailed > 3) {
    //Serial.println("Controller(client) is down!");
    digitalWrite(RL, LOW);
    pingsFailed = 0;
  }*/
}

void CollectorOn(){
  Serial.println("Request received ON");
  digitalWrite(RL, HIGH);
  server.send(200, "text/html", "<h1 style='color:green; font-family:sans-serif'>Collector is ON</h1>");
}
void CollectorOff(){
  Serial.println("Request received OFF");
  digitalWrite(RL, LOW);
  server.send(200, "text/html", "<h1 style='color:#D3D3D3; font-family:sans-serif'>Collector is OFF</h1>");
}

void handleRoot(){
  server.send(200, "text/html", "<h1>You are connected</h1>");
}