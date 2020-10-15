//Download from https://github.com/stevemarple/SoftWire
#include <SoftWire.h>
//Download from https://github.com/stevemarple/AsyncDelay
#include <AsyncDelay.h>

// Setting Parameter SoftWire
#define P0  0
#define P1  1
#define P2  2
#define P3  3
#define P4  4
#define P5  5
#define P6  6
#define P7  7
const uint8_t address = 0x21;
const uint8_t sdaPin = 23;
const uint8_t sclPin = 22;
const uint16_t timeout = 1000;

//Remapping Object
SoftWire sw(sdaPin, sclPin);

// These buffers must be at least as large as the largest read or write you perform.
char swTxBuffer[16];
char swRxBuffer[16];

void setup() {
  //Initialize Serial
  Serial.begin(115200);
  
  //Initialize Software Wire
  sw.setTxBuffer(swTxBuffer, sizeof(swTxBuffer));
  sw.setRxBuffer(swRxBuffer, sizeof(swRxBuffer));
  sw.setDelay_us(5);
  sw.setTimeout(timeout);
  sw.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  ioWrite(P7,HIGH);
  delay(300);
  ioWrite(P7,LOW);
  delay(300);  
  Serial.print("P0:");
  Serial.println(ioRead(P0));
}
void ioWrite(byte pin, byte state){
  byte maskPin = 0;
  if(state == HIGH){
    maskPin |= bit(pin);
  }else{
    maskPin &= ~bit(pin);
  }
  sw.llStart((address << 1) + 0);
  sw.llWrite(maskPin);
  sw.stop();  
}

byte ioRead(byte pin){
  byte maskPin=0;
  byte value;
  sw.requestFrom(address,(uint8_t)1);
  maskPin = sw.read();
  if ((bit(pin) & maskPin)>0){ 
    value = 1;
  }else{
    value = 0;
  }
  return value;  
}
