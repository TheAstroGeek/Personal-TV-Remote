#include <IRremote.hpp>
#include <Keypad.h>

enum Remotes {
  LIV_ROOM,
  BOY_ROOM
};

const int IR_pin = 12; // Connect the transmiter to this pin
const int Led_pin = 13; // for optional bug-checking led

unsigned long startMillis;
unsigned long currentMillis;
const unsigned long period = 1000;

const byte ROWS = 4;
const byte COLS = 4;

char hexaKeys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {9, 8, 7, 6}; // Pins for the first 4 wires of the keypad
byte colPins[COLS] = {5, 4, 3, 2}; // pins for the last 4 wires

Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);
bool I = 0;



void setup() {
  Serial.begin(9600);
  IrSender.begin(12); // assigns the transmitter to pin 12
  pinMode(Led_pin, OUTPUT); // optional Led config
  startMillis = millis(); // for optional use of a timer
  

}

void loop() {
  char customKey = customKeypad.getKey(); // returns the button pressed

  switch(customKey){
    case 'A':
     IrSender.sendSony(0x1, 0x15, 2, 12); // On/Off
     if (I == 0) {
      Serial.print("Turned On");
      I = 1;

      } else{
        Serial.print("Turned Off");
        I = 0;
      }
     
     break;

    case '1':
     IrSender.sendSony(0x1, 0x12, 2, 12); // V+
     Serial.print("Volume Up");
     break;

    case '4':
     IrSender.sendSony(0x1, 0x13, 2, 12); // V-
     Serial.print("Volume Down");
     break;

    case '2':
     IrSender.sendSony(0x1, 0x10, 2, 12); // Ch+
     Serial.print("Channel Up");
     break;

    case '5':
     IrSender.sendSony(0x1, 0x11, 2, 12); // Ch-
     Serial.print("Channel Down");
     break;

    case '*':
     IrSender.sendSony(0x1, 0x25, 2, 12); // Source
     Serial.print("Accessing the Source");
     break;

    case '#':
     IrSender.sendSony(0x1, 0xB, 2, 12); // Enter
     Serial.print("Entering");
     break;

    case '8':
     IrSender.sendSony(0x1, 0x74, 2, 12); // Up Arrow
     Serial.print("Going Up");
     break;

    case '0':
     IrSender.sendSony(0x1, 0x75, 2, 12); // Down Arrow
     Serial.print("Going Down");
     break;

    case '7':
     IrSender.sendSony(0x1, 0x34, 2, 12); // Left Arrow
     Serial.print("Slide to the Left");
     break;

    case '9':
     IrSender.sendSony(0x1, 0x33, 2, 12); // Right Arrow
     Serial.print("Slide to the Right");
     break;

    case 'D':
     digitalWrite(12, HIGH);
     Serial.print("LED test");
     break;



  }
  
  

  


  delay(10); // reduce for less latency between signals
  
}
