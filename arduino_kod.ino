#define DECODE_NEC
#define DECODE_RC5
#define NO_LED_FEEDBACK_CODE 
#include <IRremote.hpp>

int state1=0;
int state2=0;
int IR_RECEIVE_PIN = 6;
int ch1 = 3;
int ch2 = 2;

void setup()
{
  Serial.begin(9600);
  IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK); // Start the receiver
  pinMode (ch1, OUTPUT);
  pinMode (ch2, OUTPUT);
}

void loop() {
 if (IrReceiver.decode()) {
      Serial.println(IrReceiver.decodedIRData.decodedRawData, HEX);
    //ch1--------------------------------
    if (IrReceiver.decodedIRData.decodedRawData==0xBA45FF00)
    {
      if (state1==0){
        digitalWrite(ch1,HIGH);
        state1=1;
      }
      else{
        digitalWrite(ch1,LOW);
        state1=0;
      }}
      //ch2-------------------------------
      if (IrReceiver.decodedIRData.decodedRawData==0xB946FF00){
      if (state2==0){
        digitalWrite(ch2,HIGH);
        state2=1;
      }
      else{
        digitalWrite(ch2,LOW);
        state2=0;
      }}
    IrReceiver.resume(); // Receive the next value
  }
  delay(100);
}