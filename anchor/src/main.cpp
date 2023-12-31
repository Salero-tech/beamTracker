 /*
 * 
 * @todo
 *  - move strings to flash (less RAM consumption)
 *  - fix deprecated convertation form string to char* startAsAnchor
 *  - give example description
 */
#include <Arduino.h>
#include <SPI.h>
#include <DW1000Ranging.h>
#include <stdint.h>

#define ANCHOR_COUNT 2

typedef struct {
  uint8_t pinRST, pinIRQ, pinSS;
  char macAdr[];
}anchorDef_t;

// connection pins
const uint8_t PIN_RST = 9; // reset pin
const uint8_t PIN_IRQ = 2; // irq pin
const uint8_t PIN_SS = SS; // spi select pin

anchorDef_t anchorDef[ANCHOR_COUNT]; //TODO: implement

DW1000RangingClass rangeSensors[ANCHOR_COUNT];

void setup() {
  Serial.begin(115200);
  delay(1000);
  for (uint8_t i = 0; i < ANCHOR_COUNT; i++)
  {
    //create obj
    rangeSensors[i] = DW1000RangingClass();
    //init the configuration
    rangeSensors[i].initCommunication(anchorDef[i].pinRST, anchorDef[i].pinSS, anchorDef[i].pinIRQ); //Reset, CS, IRQ pin
  }
  
  //define the sketch as anchor. It will be great to dynamically change the type of module
  for (uint8_t i = 0; i < ANCHOR_COUNT; i++)
  {
    rangeSensors[i].attachNewRange(newRange);
    rangeSensors[i].attachBlinkDevice(newBlink);
    rangeSensors[i].attachInactiveDevice(inactiveDevice);
    //Enable the filter to smooth the distance
    //rangeSensors[i].useRangeFilter(true);
  }
  
  
  //we start the module as an anchor
  for (uint8_t i = 0; i < ANCHOR_COUNT; i++)
  {
    rangeSensors[i].startAsAnchor(anchorDef[i].macAdr, DW1000.MODE_LONGDATA_RANGE_ACCURACY);
  }
  
}

void loop() {
  for (uint8_t i = 0; i < ANCHOR_COUNT; i++)
  {
    rangeSensors[i].loop();
  }
}

void newRange() {
  Serial.print("from: "); Serial.print(DW1000Ranging.getDistantDevice()->getShortAddress(), HEX);
  Serial.print("\t Range: "); Serial.print(DW1000Ranging.getDistantDevice()->getRange()); Serial.print(" m");
  Serial.print("\t RX power: "); Serial.print(DW1000Ranging.getDistantDevice()->getRXPower()); Serial.println(" dBm");
}

void newBlink(DW1000Device* device) {
  Serial.print("blink; 1 device added ! -> ");
  Serial.print(" short:");
  Serial.println(device->getShortAddress(), HEX);
}

void inactiveDevice(DW1000Device* device) {
  Serial.print("delete inactive device: ");
  Serial.println(device->getShortAddress(), HEX);
}
