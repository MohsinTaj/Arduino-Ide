#include <SPI.h>
#include <mcp2515.h>

struct can_frame canMsg1;
struct can_frame canMsg;
MCP2515 mcp2515(10);


void setup() {
  canMsg1.can_id  = 0x18900140;
  canMsg1.can_dlc = 8;
  canMsg1.data[0] = 0x8E;
  canMsg1.data[1] = 0x87;
  canMsg1.data[2] = 0x32;
  canMsg1.data[3] = 0xFA;
  canMsg1.data[4] = 0x26;
  canMsg1.data[5] = 0x8E;
  canMsg1.data[6] = 0xBE;
  canMsg1.data[7] = 0x86;

//  canMsg2.can_id  = 0x18900140;
//  canMsg2.can_dlc = 8;
//  canMsg2.data[0] = 0x0E;
//  canMsg2.data[1] = 0x00;
//  canMsg2.data[2] = 0x00;
//  canMsg2.data[3] = 0x08;
//  canMsg2.data[4] = 0x01;
//  canMsg2.data[5] = 0x00;
//  canMsg2.data[6] = 0x00;
//  canMsg2.data[7] = 0xA0;
//  
  while (!Serial);
  Serial.begin(9600);
  
  mcp2515.reset();
  mcp2515.setBitrate(CAN_250KBPS,MCP_8MHZ);
  mcp2515.setNormalMode();
  
  Serial.println("Example: Write to CAN");
}

void loop() {
  mcp2515.sendMessage(&canMsg1);
//  mcp2515.sendMessage(&canMsg2);
 mcp2515.readMessage(&canMsg);
  Serial.println("Messages sent");
  
  delay(1000);
   if (mcp2515.readMessage(&canMsg) == MCP2515::ERROR_OK) {
    Serial.print(canMsg.can_id, HEX); // print ID
    Serial.print(" "); 
    Serial.print(canMsg.can_dlc, HEX); // print DLC
    Serial.print(" ");}
    else{
      Serial.println("error");}
    
    for (int i = 0; i<canMsg.can_dlc; i++)  {  // print the data
      Serial.print(canMsg.data[i],HEX);
      Serial.print(" ");
    }

    Serial.println();      
  }
