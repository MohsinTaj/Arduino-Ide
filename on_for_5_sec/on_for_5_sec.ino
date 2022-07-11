#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

/*Put WiFi SSID & Password*/
const char* ssid = "m";   // Enter SSID here
const char* password = "123456789"; // Enter Password here

ESP8266WebServer server(80);
uint8_t Relay1 = D0;
uint8_t Relay2 = D1;
uint8_t Relay3 = D2;
uint8_t Relay4 = D3;
int load1, load2, load3, load4;

void setup() {
  Serial.begin(9600);
  delay(100);
 
   
  pinMode(Relay1, OUTPUT); 
  pinMode(Relay2, OUTPUT);
  pinMode(Relay3, OUTPUT);
  pinMode(Relay4, OUTPUT); 

 digitalWrite(Relay1, load1); 
  digitalWrite(Relay2, load2); 
  digitalWrite(Relay3, load3); 
  digitalWrite(Relay4, load4);


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
  Serial.println("HTTP Server Started");
}
void loop() {
  server.handleClient();

digitalWrite(Relay1, load1); 
  digitalWrite(Relay2, load2); 
  digitalWrite(Relay3, load3); 
  digitalWrite(Relay4, load4);

  void handle_OnConnect() {
  server.send(200, "text/html", updateWebpage(load1,load2,load3,load4)); 
}
if(Relay1)
  {
    digitalWrite(D0, HIGH);}
  else
  {
    digitalWrite(D0, LOW);}
}
if(Relay2)
  {
    digitalWrite(D1, HIGH);}
  else
  {
    digitalWrite(D1, LOW);}
}
if(Relay3)
  {
    digitalWrite(D2, HIGH);}
  else
  {
    digitalWrite(D2, LOW);}
}
if(Relay3)
  {
    digitalWrite(D3, HIGH);}
  else
  {
    digitalWrite(D3, LOW);}
}
  
  


void handle_OnConnect() {
  server.send(200, "text/html", updateWebpage(load1,load2,load3,load4)); 
}

void handle_NotFound(){
  server.send(404, "text/plain", "Not found");
}
void handle_L1on()  {load1=0;data();}
void handle_L1off() {load1=1;data();}

void handle_L2on()  {load2=0;data();}
void handle_L2off() {load2=1;data();}

void handle_L3on()  {load3=0;data();}
void handle_L3off() {load3=1;data();}

void handle_L4on()  {load4=0;data();}
void handle_L4off() {load4=1;data();}


String updateWebpage(uint8_t l1stat,uint8_t l2stat,uint8_t l3stat,uint8_t l4stat){
  String ptr = "<!DOCTYPE html> <html>\n";
  ptr +="<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n";
  ptr +="<title>4Load Control</title>\n";
  ptr +="<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}\n";
  ptr +="body{margin-top: 50px;} h1 {color: #444444;margin: 50px auto 30px;} h3 {color: #444444;margin-bottom: 50px;}\n";
  ptr +=".button {display: block;width: 80px;background-color: #1abc9c;border: none;color: white;padding: 13px 30px;text-decoration: none;font-size: 25px;margin: 0px auto 35px;cursor: pointer;border-radius: 4px;}\n";
  ptr +=".button-on {background-color: #1abc9c;}\n";
  ptr +=".button-on:active {background-color: #16a085;}\n";
  ptr +=".button-off {background-color: #34495e;}\n";
  ptr +=".button-off:active {background-color: #2c3e50;}\n";
  ptr +="p {font-size: 14px;color: #888;margin-bottom: 10px;}\n";
  ptr +="</style>\n";
  ptr +="</head>\n";
  ptr +="<body>\n";
  ptr +="<h2>Wifi based Home Appliance Control</h2>\n";
  
   if(l1stat==0)
  {ptr +="<p>Load1 Status: ON</p><a class=\"button button-off\" href=\"/L1off\">OFF</a>\n";}
  else
  {ptr +="<p>Load1 Status: OFF</p><a class=\"button button-on\" href=\"/L1on\">ON</a>\n";}

  if(l2stat==0)
  {ptr +="<p>Load2 Status: ON</p><a class=\"button button-off\" href=\"/L2off\">OFF</a>\n";}
  else
  {ptr +="<p>Load2 Status: OFF</p><a class=\"button button-on\" href=\"/L2on\">ON</a>\n";}

  if(l3stat==0)
  {ptr +="<p>Load3 Status: ON</p><a class=\"button button-off\" href=\"/L3off\">OFF</a>\n";}
  else
  {ptr +="<p>Load3 Status: OFF</p><a class=\"button button-on\" href=\"/L3on\">ON</a>\n";}

  if(l4stat==0)
  {ptr +="<p>Load4 Status: ON</p><a class=\"button button-off\" href=\"/L4off\">OFF</a>\n";}
  else
  {ptr +="<p>Load4 Status: OFF</p><a class=\"button button-on\" href=\"/L4on\">ON</a>\n";}

  ptr +="</body>\n";
  ptr +="</html>\n";
  return ptr;
}
