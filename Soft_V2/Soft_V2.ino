#define DECODE_NEC
#define DECODE_RC5
#define NO_LED_FEEDBACK_CODE
#include <IRremote.hpp>
#include <EEPROM.h>

int state1 = 0;
int state2 = 0;
int IR_RECEIVE_PIN = 6;
int ch1 = 4;
int ch2 = 5;

char writeCode(uint8_t addr, uint32_t data) {
  EEPROM.write(addr, data);
  data >> 8;
  EEPROM.write(addr + 1, data);
  data >> 8;
  EEPROM.write(addr + 2, data);
  data >> 8;
  EEPROM.write(addr + 3, data);
}

uint32_t readCode(uint8_t addr) {
  uint32_t data = 0;

  data += EEPROM.read(addr + 3);
  data = data << 8;
  data += EEPROM.read(addr + 2);
  data = data << 8;
  data += EEPROM.read(addr + 1);
  data = data << 8;
  data += EEPROM.read(addr);
  return data;
}

void setup() {
  Serial.begin(9600);
  IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK);  // Start the receiver
  pinMode(ch1, OUTPUT);
  pinMode(ch2, OUTPUT);
  writeCode(0, 0x01234567);
  uint32_t bufor = readCode(0);
  Serial.println((uint8_t)bufor);
}

void loop() {
  if (IrReceiver.decode()) {
    uint32_t kod = IrReceiver.decodedIRData.decodedRawData;
    if (!kod) {
      IrReceiver.resume();  // Receive the next value
      return;
    }
    Serial.println(kod, HEX);
    //ch1--------------------------------
    if (kod == 0xBA45FF00) {
      if (state1 == 0) {
        digitalWrite(ch1, HIGH);
        state1 = 1;
      } else {
        digitalWrite(ch1, LOW);
        state1 = 0;
      }
    }
    //ch2-------------------------------
    if (kod == 0xB946FF00) {
      if (state2 == 0) {
        digitalWrite(ch2, HIGH);
        state2 = 1;
      } else {
        digitalWrite(ch2, LOW);
        state2 = 0;
      }
    }
    IrReceiver.resume();  // Receive the next value
  }
  delay(100);
}