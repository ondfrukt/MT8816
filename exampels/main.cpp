#include <Arduino.h>
#include <MT8816.h>

// Defining MCP23017 address
const uint8_t MCP_ADDRESS = 0x20;

// Defining pin connections between MCP23017 and MT8816
const uint8_t PIN_RESET = 0;   // GPA0
const uint8_t PIN_DATA = 1;    // GPA1
const uint8_t PIN_STROBE = 2;  // GPA2
const uint8_t PIN_CS = 3;      // GPA3

const uint8_t PIN_AX0 = 8;     // GPB0
const uint8_t PIN_AX1 = 9;     // GPB1
const uint8_t PIN_AX2 = 10;    // GPB2
const uint8_t PIN_AX3 = 11;    // GPB3
const uint8_t PIN_AY0 = 12;    // GPB4
const uint8_t PIN_AY1 = 13;    // GPB5
const uint8_t PIN_AY2 = 14;    // GPB6

// Creating an object from the MT8816 library
MT8816 mt8816(MCP_ADDRESS, 
              PIN_AX0, PIN_AX1, PIN_AX2, PIN_AX3,
              PIN_AY0, PIN_AY1, PIN_AY2,
              PIN_STROBE, PIN_DATA, PIN_RESET, PIN_CS);

void setup() {
  Serial.begin(9600);
  Serial.println("MCP23017 + MT8816 Test Started");
  mt8816.begin();
}

void loop() {
  // Looping through all crosspoints in the MT8816 Matrix
  for (int j = 0; j < 16; ++j) {
    for (int i = 0; i < 8; i++) {
      mt8816.connect(j, i);
      Serial.print("X");
      Serial.print(j);
      Serial.print(" and Y");
      Serial.print(i);
      Serial.println(" Connected");
      delay(20);
    }
    mt8816.reset();
  }
}
