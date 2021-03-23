#include <SPI.h>
#include <mcp2515.h>

struct can_frame canMsg1;
struct can_frame canMsg2;
struct can_frame canMsg3;
struct can_frame canMsg4;
byte sp1;
byte sp2;
MCP2515 mcp2515(10);


void setup() {

  SPI.begin();
  
  mcp2515.reset();
  mcp2515.setBitrate (CAN_500KBPS, MCP_8MHZ);
  mcp2515.setNormalMode();
}

void loop() {
  for (byte i=1; i<=255; i++){
  
  sp2 =  
  canMsg1.can_id  = 0x511;
  canMsg1.can_dlc = 8;
  canMsg1.data[0] = 0x00;
  canMsg1.data[1] = 0x00;
  canMsg1.data[2] = 0x00;
  canMsg1.data[3] = 0x00;
  canMsg1.data[4] = 0x00;
  canMsg1.data[5] = 0x00;
  canMsg1.data[6] = 0x00;
  canMsg1.data[7] = 0x00;

  canMsg2.can_id  = 0x501;
  canMsg2.can_dlc = 6;
  canMsg2.data[0] = 0x00;
  canMsg2.data[1] = 0x00;
  canMsg2.data[2] = 0x00;
  canMsg2.data[3] = 0x00;
  canMsg2.data[4] = 0x00;
  canMsg2.data[5] = i,HEX;

  canMsg3.can_id  = 0x513;
  canMsg3.can_dlc = 8;
  canMsg3.data[0] = 0x02;
  canMsg3.data[1] = 0xC7;
  canMsg3.data[2] = 0x02;
  canMsg3.data[3] = 0xC7;
  canMsg3.data[4] = 0x02;
  canMsg3.data[5] = 0xC7;
  canMsg3.data[6] = 0x02;
  canMsg3.data[7] = 0xC7;

  canMsg4.can_id  = 0x512;
  canMsg4.can_dlc = 8;
  canMsg4.data[0] = 0x00;
  canMsg4.data[1] = 0xE0;
  canMsg4.data[2] = 0x02;
  canMsg4.data[3] = 0xC7;
  canMsg4.data[4] = 0x10;
  canMsg4.data[5] = i,HEX;
  canMsg4.data[6] = 0x40;
  canMsg4.data[7] = 0x01;
  
  mcp2515.sendMessage(&canMsg1);
  mcp2515.sendMessage(&canMsg2);
  mcp2515.sendMessage(&canMsg3);
  mcp2515.sendMessage(&canMsg4);
  
  delay(20);
  }
}
