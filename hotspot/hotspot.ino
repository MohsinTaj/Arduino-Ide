#include <ESP8266WiFi.h>
#include<Arduino.h>
#include <WiFiClient.h> 
#include <ESP8266WebServer.h>
//user interface HTML code----------------
String html = R"*(
<!DOCTYPE html>
<html>
  <head>    
    <title>SWITCH LED</title>
  </head>
  <body>
    <h1>SWITCH LED</h1>
    <p><a href=/ledon>LED on</a></p>
    <p><a href=/ledoff>LED off</a></p>
  </body>
</html>
)*";

const char *ssid = "AC-ESP8266";
const char *password = "987654321";

IPAddress local_IP(192,168,4,22);
IPAddress gateway(192,168,4,9);
IPAddress subnet(255,255,255,0);
ESP8266WebServer server(80);
void handleRoot()
{
  server.send(200, "text/html", html);
}
void ledon()
{
  digitalWrite(LED_BUILTIN, 1);
  server.send(200, "text/html", html);
}
void ledoff()
{
  digitalWrite(LED_BUILTIN, 0);
  server.send(200, "text/html", html);
}
//===============================================
void setup()
{
  pinMode(LED_BUILTIN, OUTPUT); delay(1000);
  Serial.begin(115200);
  Serial.println();

  Serial.print("Setting soft-AP configuration ... ");
  Serial.println(WiFi.softAPConfig(local_IP, gateway, subnet) ? "Ready" : "Failed!");

  Serial.print("Setting soft-AP ... ");
  Serial.println(WiFi.softAP(ssid,password) ? "Ready" : "Failed!");
  //WiFi.softAP(ssid);
  //WiFi.softAP(ssid, password, channel, hidden, max_connection)
  
  Serial.print("Soft-AP IP address = ");
  Serial.println(WiFi.softAPIP());
    server.on("/", handleRoot);
  server.on("/ledon", ledon);
  server.on("/ledoff", ledoff);
  server.begin();
  Serial.println("HTTP server started");
}


void loop() {
  Serial.print("[Server Connected] ");
  Serial.println(WiFi.softAPIP());
//server.handleClient();
  delay(500);
}
