#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include<WiFiClient.h>
 String html = R"*(
<!DOCTYPE html>
<html>
  <head>    
    <title>SWITCH LED</title>
  </head>
  <body>
  <img src="microwaveoven (1).jpg">
   
    <h1>SWITCH LED</h1>
    <p><a href="/ledon>LED on" class="button">button text</a> </p>
    <p><a href=/ledoff>LED off</a></p>
  </body>
</html>
)*";
const char *ssid = "MyESP8266AP";
const char *password = "testpassword";
 
ESP8266WebServer server(80);
 
void handleRoot() {
  server.send(200, "text/html", html);
}
 void ledon()
{
  digitalWrite(LED_BUILTIN, 0);
  server.send(200, "text/html", html);
}
void ledoff()
{
  digitalWrite(LED_BUILTIN, 1);
  server.send(200, "text/html", html);
}
void setup() {
 pinMode(LED_BUILTIN, OUTPUT); delay(1000);
  Serial.begin(115200);
 
  WiFi.softAP(ssid, password);
 
  Serial.println();
  Serial.print("Server IP address: ");
  Serial.println(WiFi.softAPIP());
  Serial.print("Server MAC address: ");
  Serial.println(WiFi.softAPmacAddress());
 
  server.on("/", handleRoot);
  server.on("/ledon", ledon);
  server.on("/ledoff", ledoff);
  server.begin();
 
  Serial.println("Server listening");
}
 
void loop() {
  server.handleClient();
}
