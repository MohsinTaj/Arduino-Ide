#include <ESP8266WiFi.h>
const char* ssid = "wifi";
const char* password = "WagonR2016";
WiFiServer server(80); //Create Server object on Port 80 to talk to client(web browser)
void setup() {
 Serial.begin(9600);
 delay(10);
 // initialize D4 as an output pin. (D4=GPIO 2)
 pinMode(2, OUTPUT);
 digitalWrite(2,LOW);
 Serial.println();
 Serial.print("Connecting to ");
 Serial.println(ssid);
 WiFi.begin (ssid,password); // Actual connection to WiFi is initialized
 while (WiFi.status()!=WL_CONNECTED) // while loop checks the connection with WiFi
 { delay(500);
 Serial.print(".");
 }
 Serial.println("");
 Serial.println("WiFi connected");
 // Start the server
 server.begin();
 Serial.println("Server started");
 //Print the IP Address
 Serial.print("Use this url to connect: ");
 Serial.print("http://");
 Serial.print(WiFi.localIP());
 Serial.println("/");
}

 
void loop() {
WiFiClient client = server.available(); //to connect our module with webpage through IP
if (!client)
 { 
 return;
 }
 //Wait until the client sends some data
 Serial.println("new client");
 while (!client.available())
 {
 delay(1);
 }
 // Read the first line of the request
 String request = client.readStringUntil('\r');
 Serial.println(request);
 client.flush();
 //Match the request
 int value=LOW;
 if (request.indexOf(" /LED=ON")!=-1)
 {
 digitalWrite(2,1);
 value=HIGH ; 
 }
 if (request.indexOf(" /LED=OFF")!=-1)
 {
 digitalWrite(2,0);
 value=LOW ;
 }
 // HTML CODE FOR WEBPAGE TO ON AND OFF LED
 client.println("HTTP/1.1 200 OK");
 client.println("Content-Type: text/html");
 client.println("");// do not forget this one
 client.println("<!DOCTYPE HTML>");
 client.println("<html>");
 client.println("<title>switch</title>");
}
