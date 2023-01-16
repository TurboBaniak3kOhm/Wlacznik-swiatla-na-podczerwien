#define DECODE_NEC
#define DECODE_RC5
#define NO_LED_FEEDBACK_CODE
#include <IRremote.hpp>
#include <EEPROM.h>

int state1, state2, state3, state4;
int IR_RECEIVE_PIN = 0;
int LED_PIN = 19;
int ch1 = 17;
int ch2 = 16;
int ch3 = 15;
int ch4 = 14;
int button1 = 18;
int button2 = 9;
int button3 = 8;
int button4 = 7;
uint32_t code1, code2, code3, code4;

//zapis kodu do pamięci (adres + dane)
char writeCode(uint8_t addr, uint32_t data) {
  EEPROM.write(addr + 3, data);
  data = data >> 8;
  EEPROM.write(addr + 2, data);
  data = data >> 8;
  EEPROM.write(addr + 1, data);
  data = data >> 8;
  EEPROM.write(addr , data);
}

//odczyt kodu z pamięci
uint32_t readCode(uint8_t addr) {
  uint32_t data = 0;

  data += EEPROM.read(addr);
  data = data << 8;
  data += EEPROM.read(addr + 1);
  data = data << 8;
  data += EEPROM.read(addr + 2);
  data = data << 8;
  data += EEPROM.read(addr + 3);
  return data;
}

void setup() {
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);
  //EEPROM.write(0, 0);
 
  //Serial.begin(9600);
  IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK);  // Start the receiver
  //ustaw PINy na output
  pinMode(ch1, OUTPUT);
  pinMode(ch2, OUTPUT);
  pinMode(ch3, OUTPUT);
  pinMode(ch4, OUTPUT);
  code1=readCode(0);  
  code2=readCode(4);
  code3=readCode(8);
  code4=readCode(12);
  //zapisz do pamięci na 32 bitach
  //writeCode(0, code1);
  //code1 = readCode(0);
  //writeCode(0, code1);
  //odczytaj zaczynając od adresu zerowego
  //uint32_t bufor = readCode(0);
  //wypisz odczytaną wartość
  //Serial.println((uint8_t)bufor);
  pinMode(button1, INPUT_PULLUP);
  pinMode(button2, INPUT_PULLUP);
  pinMode(button3, INPUT_PULLUP);
  pinMode(button4, INPUT_PULLUP);
}

void loop() {
  /*
  if (button == HIGH && IrReceiver.decode() != NULL){
    code1 = IrReceiver.decodedIRData.decodedRawData;
  }
  */



  if (IrReceiver.decode()) {
    
    uint32_t kod = IrReceiver.decodedIRData.decodedRawData; //zapisz dekodowany sygnał jako "kod"
    if (kod==0) {
      IrReceiver.resume();  // Receive the next value
      return;
    }//jeśli nie otrzymał kodu, sprawdzaj dalej
    //Serial.println(kod, HEX);//wypisz kod
    //ch1--------------------------------
    
    if (digitalRead(button1) == LOW){
      code1 = kod;
      writeCode(0, code1);
      digitalWrite(LED_PIN, HIGH);
      IrReceiver.resume();  // Receive the next value
      return;
    }
    if (digitalRead(button2) == LOW){
      code2 = kod;
      writeCode(4, code2);
      digitalWrite(LED_PIN, HIGH);
      IrReceiver.resume();  // Receive the next value
      return;
    }
    if (digitalRead(button3) == LOW){
      code3 = kod;
      writeCode(8, code3);
      digitalWrite(LED_PIN, HIGH);
      IrReceiver.resume();  // Receive the next value
      return;
    }
    if (digitalRead(button4) == LOW){
      code4 = kod;
      writeCode(12, code4);
      digitalWrite(LED_PIN, HIGH);
      IrReceiver.resume();  // Receive the next value
      return;
    }
    digitalWrite(LED_PIN, LOW);
    
    if (kod == code1) {
      if (state1 == 0) {
        digitalWrite(ch1, HIGH);
        state1 = 1;
      } else {
        digitalWrite(ch1, LOW);
        state1 = 0;
      }
    }
    if (kod == code2) {
      if (state2 == 0) {
        digitalWrite(ch2, HIGH);
        state2 = 1;
      } else {
        digitalWrite(ch2, LOW);
        state2 = 0;
      }
    }
    if (kod == code3) {
      if (state3 == 0) {
        digitalWrite(ch3, HIGH);
        state3 = 1;
      } else {
        digitalWrite(ch3, LOW);
        state3 = 0;
      }
    }
    if (kod == code4) {
      if (state4 == 0) {
        digitalWrite(ch4, HIGH);
        state4 = 1;
      } else {
        digitalWrite(ch4, LOW);
        state4 = 0;
      }
    }

    IrReceiver.resume();  // Receive the next value
  }
  //delay(100);
}