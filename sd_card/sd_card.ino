#include "SD.h"
#include <SPI.h>
#include "DHT.h" 
#include <PZEM004Tv30.h>
#include <SoftwareSerial.h>

 #define DHTPIN 2     
 #define DHTTYPE DHT22
 DHT dht (DHTPIN, DHTTYPE) ;
 #define PZEM_RX_PIN 9
#define PZEM_TX_PIN 8



SoftwareSerial pzemSWSerial(PZEM_RX_PIN, PZEM_TX_PIN);
PZEM004Tv30 pzem(pzemSWSerial);

File myFile;
String Temperature, Humidity, Data;
String voltage, current;


void setup() {
  Serial.begin(115200);
  dht.begin (  ) ;  

  Serial.print("Initializing SD card...");
  if (!SD.begin(10)) {
    Serial.println("initialization failed!");
    while (1);
  }
  Serial.println("initialization done.");
  myFile = SD.open("data.txt", FILE_WRITE);
  if (myFile) {
    myFile.println( "Temperature(°C), Humidity(%) \r\n");
    myFile.println("voltage(v), current(I) \n"); 
    myFile.close();
  } 
  else {
    Serial.println("error opening data.txt");
  }
}

void loop() {
   if ( isnan (dht.readTemperature ( ) ) || isnan (dht.readHumidity ( ) ) )
   {
     Serial.println ("DHT22 Sensor not working!") ;
     
      Serial.print(Temperature);
      Serial.print(Humidity);
      
   }
   if(isnan(pzem.voltage())||isnan(pzem.current())){
    Serial.println("pzem not working");
    
    Serial.print(voltage);
     Serial.print(current);
    
   }
 else
{   
  data_logging();                                                 
 }
delay(20000); 
}

void data_logging() 
{
  String Temperature = String(dht.readTemperature ( ), 2);
  String Humidity = String(dht.readHumidity ( ), 2);
  Data = Temperature + "," + Humidity;
  String voltage=String(pzem.voltage(),3);
  String current=String(pzem.current(),3);
   Data = voltage + "," +current;
  Serial.print("Save data: ");
  Serial.println(Data);
  
  myFile = SD.open("data.txt", FILE_WRITE);
  if (myFile) {
    Serial.print("Writing to data.txt...");
    myFile.println(Data);
    myFile.close();
    Serial.println("done.");
  } else {
    Serial.println("error opening data.txt");
  }  
  Serial.println();
}
