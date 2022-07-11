#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
 
const char *ssid = "MyESP8266AP";
const char *password = "testpassword";
 
ESP8266WebServer server(80);
 
void handleRoot() {
  server.send(200, "text/html", "<h1>Hello from ESP8266 AP!</h1>");
}
 
void setup() {
 
  Serial.begin(115200);
 
  WiFi.softAP(ssid, password);
 
  Serial.println();
  Serial.print("Server IP address: ");
  Serial.println(WiFi.softAPIP());
  Serial.print("Server MAC address: ");
  Serial.println(WiFi.softAPmacAddress());
 
  server.on("/", handleRoot);
  server.begin();
 
  Serial.println("Server listening");
}
 
void loop() {
  server.handleClient();
}
