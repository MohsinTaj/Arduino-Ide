#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESPAsyncWebServer.h>
  #include <SPIFFS.h>
  /* Put your SSID & Password */
const char* ssid = "m";  // Enter SSID here
const char* password = "123456789";  //Enter Password here
ESP8266WebServer server(80);
AsyncWebServer server(100);
int value;
int Relay1 = D0;
int Relay2 = D1;
int Relay3 = D2;
int Relay4 = D3;
void setup() {
Serial.begin(9600);
pinMode(13, OUTPUT); // put your setup code here, to run once:

 Serial.println();
 server.on("/sun", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/microwaveoven (1).jpg", "image/jpg");
  });
  pinMode(Relay1, OUTPUT); 
  pinMode(Relay2, OUTPUT);
  pinMode(Relay3, OUTPUT);
  pinMode(Relay4, OUTPUT); 

Serial.println("Connecting to ");
  Serial.println(ssid);

  //connect to your local wi-fi network
  WiFi.begin(ssid, password);

  //check NodeMCU is connected to Wi-fi network
  while (WiFi.status() != WL_CONNECTED) {
  delay(1000);
  Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected..!");
  Serial.print("Got IP: ");  
  Serial.println(WiFi.localIP());
 server.on("/", handle_OnConnect);
  server.on("/L1on",  handle_L1on);
  server.on("/L1off", handle_L1off);
  server.on("/L2on",  handle_L2on);
  server.on("/L2off", handle_L2off);
  server.on("/L3on",  handle_L3on);
  server.on("/L3off", handle_L3off);
  server.on("/L4on",  handle_L4on);
  server.on("/L4off", handle_L4off);
  server.onNotFound(handle_NotFound);
  
  server.begin();
  Serial.println("HTTP server started");
 }
void loop() {
 // put your main code here, to run repeatedly:
server.handleClient();
if(value=='1' ){ 
digitalWrite(D0, HIGH); 
} 
if(value=='2' ){ 
digitalWrite(D0 ,LOW); 
 }}
 void handle_OnConnect() {
  server.send(200, "text/html", SendHTML(load1,load2,load3,load4)); 
}

void handle_L1on()  {relay1=0;data();}
void handle_L1off() {relay1=1;data();}

void handle_L2on()  {relay2=0;data();}
void handle_L2off() {relay2=1;data();}

void handle_L3on()  {relay3=0;data();}
void handle_L3off() {relay3=1;data();}

void handle_L4on()  {relay4=0;data();}
void handle_L4off() {relay4=1;data();}
