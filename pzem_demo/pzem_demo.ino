#include<ESP8266WiFi.h>
#include<WiFiClient.h>
#include<ESP8266WebServer.h>
#include <PZEM004Tv30.h>
PZEM004Tv30 pzem(D1,D2);  //RX/TX
const char* ssid = "Wifi";//Replace with your network SSID
const char* password = "WagonR2016";//Replace with your network password

ESP8266WebServer server(80);
float voltage,current,pf,frequency,power;
String page = "";
void setup() 
{
Serial.begin(115200);
WiFi.begin(ssid, password);
while (WiFi.status() != WL_CONNECTED)
  {
  delay(500);
  Serial.print(".");
  }
  Serial.println(WiFi.localIP());
  server.on("/", []()
  {
    page = "<html><head><title>Smart Energy Meter using IoT</title></head><style type=\"text/css\">";
    page += "table{border-collapse: collapse;}th {background-color:  green ;color: white;}table,td {border: 4px solid black;font-size: x-large;";
    page += "text-align:center;border-style: groove;border-color: rgb(255,0,0);}</style><body><center>";
    page += "<h1>Smart Energy Meter using IoT</h1><br><br><table style=\"width: 1200px;height: 450px;\"><tr>";
    page += "<th>Parameters</th><th>Value</th><th>Units</th></tr><tr><td>Voltage</td><td>"+String(voltage)+"</td><td>Volts</td></tr>";
    page += "<tr><td>Current</td><td>"+String(current)+"</td><td>Amperes</td></tr><tr><td>Power Factor</td><td>"+String(pf)+"</td><td>XXXX</td>";
    page += "<tr><td>Power</td><td>"+String(power)+"</td><td>Watts</td></tr><tr>";
    page += "</tr><tr><td>Frequency</td><td>"+String(frequency,1)+"</td><td>Hz</td></tr>";
    page += "<meta http-equiv=\"refresh\" content=\"3\">";
    server.send(200, "text/html", page);
  });
  server.begin();
}
void loop() 
{
voltage = pzem.voltage();
current = pzem.current();
power = pzem.power();
frequency = pzem.frequency();
pf = pzem.pf();
server.handleClient();
}
