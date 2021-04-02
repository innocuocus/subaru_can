#include <TinyGPS++.h>
#include <SoftwareSerial.h>
#include <SPI.h>
#include <mcp2515.h>

struct can_frame canMsg1;
struct can_frame canMsg2;
struct can_frame canMsg3;
struct can_frame canMsg4;
byte sp1;
byte sp2;
int sp_gps;
MCP2515 mcp2515(10);
 
TinyGPSPlus gps;
 
#define S_RX    4                // Вывод RX
#define S_TX    3                // Вывод TX
 
SoftwareSerial SoftSerial(S_RX, S_TX);
 
void setup(void) {
  Serial.begin(9600);
  SoftSerial.begin(9600); 
  SPI.begin();  
  mcp2515.reset();
  mcp2515.setBitrate (CAN_500KBPS, MCP_8MHZ);
  mcp2515.setNormalMode(); 
}
 

void loop() {
  
 for (byte i=1; i<=255; i++){
   while (SoftSerial.available() > 0) {
 
    if (gps.encode(SoftSerial.read())) {
      
      if (gps.speed.isValid()) {
        Serial.print("Speed      = ");
        sp_gps=gps.speed.kmph();
        Serial.print(sp_gps);
        Serial.println(" kmph");
        sp_gps=sp_gps/0.05625;
      }
      else  sp_gps=0; 
    }
   }

  word x=sp_gps;
  Serial.println(x);
  sp1=x/256;
  sp2=x%256; 

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
  canMsg3.data[0] = sp2,HEX;
  canMsg3.data[1] = sp1,HEX;
  canMsg3.data[2] = sp2,HEX;
  canMsg3.data[3] = sp1,HEX;
  canMsg3.data[4] = sp2,HEX;
  canMsg3.data[5] = sp1,HEX;
  canMsg3.data[6] = sp2,HEX;
  canMsg3.data[7] = sp1,HEX;

  canMsg4.can_id  = 0x512;
  canMsg4.can_dlc = 8;
  canMsg4.data[0] = 0x00;
  canMsg4.data[1] = 0xE0;
  canMsg4.data[2] = sp2,HEX;
  canMsg4.data[3] = sp1,HEX;
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
