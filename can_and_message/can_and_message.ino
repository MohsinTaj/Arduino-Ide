#include <SPI.h>
#include "SD.h"
#include <mcp2515.h>
int period = 5000;
unsigned long time_now = 0;
 
struct can_frame canMsg;
struct can_frame canMsg1;
MCP2515 mcp2515(PA4);
File myFile;


void setup() {
   time_now = millis();
   canMsg1.can_id  = 0x18900140 ;
  canMsg1.can_dlc = 8;
canMsg1.data[0] = 0x8E;
canMsg1.data[1] = 0x87;
canMsg1.data[2] = 0x32;
canMsg1.data[3] = 0xFA;
canMsg1.data[4] = 0x26;
canMsg1.data[5] = 0x8E;
 canMsg1.data[6] = 0xBE;
canMsg1.data[7] = 0x86;
  Serial.begin(9600);
  
  mcp2515.reset();
  mcp2515.setBitrate(CAN_250KBPS,MCP_8MHZ);
  mcp2515.setNormalMode();
  
  Serial.println("------- CAN Read ----------");
   Serial.println("\nExample: Write to CAN");
  Serial.println("ID  DLC   DATA\n");
  Serial.print("Initializing SD card...");
  if (!SD.begin(PA4)) {
    Serial.println("initialization failed!");
    while (1);
  }
  Serial.println("initialization done.");
  myFile = SD.open("data.txt", FILE_WRITE);
  if (myFile) {
    myFile.println( "cccccTemperature(°C), Humidity(%) \r\n");
    myFile.close();
     } 
  else {
    Serial.println("error opening data.txt");
  }
}

void loop() {
   if(millis() >= time_now + period){
        time_now += period;
   
 Serial.println("loop");
//  data_logging(); 
   void data_logging() 
{
  //String Temperature = String(dht.readTemperature ( ), 2);
  //String Humidity = String(dht.readHumidity ( ), 2);
 // Data = Temperature + "," + Humidity;
//  String voltage=String(pzem.voltage(),3);
//  String current=String(pzem.current(),3);
//   Data = voltage + "," +current;
  Serial.print("Save data: ");
 // Serial.println(Data);
  
  myFile = SD.open("data.txt", FILE_WRITE);
  if (myFile) {
    Serial.print("Writing to data.txt...");
    myFile.println("test");
    myFile.close();
    Serial.println("done.");
  } else {
    Serial.println("error opening data.txt");
  }  
  Serial.println();
  mcp2515.sendMessage(&canMsg1);
  Serial.println("Messages sent");
  
  if (mcp2515.readMessage(&canMsg) == MCP2515::ERROR_OK) {
    if(canMsg1.can_id==0x18900140){
    Serial.print(canMsg.can_id, HEX); // print ID
    Serial.print(" "); 
    Serial.print(canMsg.can_dlc, HEX); // print DLC
    Serial.print(" ");
    
    for (int i = 0; i<canMsg.can_dlc; i++)  {  // print the data
      Serial.print(canMsg.data[i],HEX);
      Serial.print(" ");
    }

    Serial.println();      
  }
 
}
   }  
}
