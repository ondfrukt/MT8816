#include <Arduino.h>
#include "MT8816.h"
#include <Wire.h>

MT8816::MT8816(uint8_t mcp_address, 
               uint8_t ax0, uint8_t ax1, uint8_t ax2, uint8_t ax3,
               uint8_t ay0, uint8_t ay1, uint8_t ay2,
               uint8_t strobe, uint8_t data, uint8_t reset, uint8_t cs)
{
    _mcp_address = mcp_address;

    // Creating a vector of the address pins
    _ax_pins[0] = ax0;
    _ax_pins[1] = ax1;
    _ax_pins[2] = ax2;
    _ax_pins[3] = ax3;
    _ay_pins[0] = ay0;
    _ay_pins[1] = ay1;
    _ay_pins[2] = ay2;
    _strobe_pin = strobe;
    _data_pin = data;
    _reset_pin = reset;
    _cs_pin = cs;
}
    // Initiate connection matrix
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
        lineConnections[i][j] = false;
        }
    }

void MT8816::begin()
{
    Wire.begin();

    // Testing MCP address
    if (!_mcp.begin_I2C(_mcp_address)) {
        Serial.println("MCP23017 initialization failed. Check connections and address.");
        return;
    }
    Serial.println("MCP23017 initialized successfully.");

    // Configure address pins
    for (int i = 0; i < 4; ++i) {
        _mcp.pinMode(_ax_pins[i], OUTPUT);
    }
    for (int i = 0; i < 3; ++i) {
        _mcp.pinMode(_ay_pins[i], OUTPUT);
    }

    // Configure programming pins 
    _mcp.pinMode(_strobe_pin, OUTPUT);
    _mcp.pinMode(_data_pin, OUTPUT);
    _mcp.pinMode(_reset_pin, OUTPUT);
    _mcp.pinMode(_cs_pin, OUTPUT);

    // Set initial values
    _mcp.digitalWrite(_strobe_pin, LOW);
    _mcp.digitalWrite(_data_pin, LOW);
    _mcp.digitalWrite(_reset_pin, HIGH);
    _mcp.digitalWrite(_cs_pin, HIGH);

    // Reset MCP
    reset();
    Serial.println("MT8816 initialized successfully.");

}

void MT8816::reset()
{   
    // Pulse the reset pin to reset the IC
    _mcp.digitalWrite(_reset_pin, LOW);
    delayMicroseconds(10);
    _mcp.digitalWrite(_reset_pin, HIGH);
    delay(100);  
    _mcp.digitalWrite(_reset_pin, LOW);
    Serial.println("MT8816 reset performed.");
}

void MT8816::connect(uint8_t x, uint8_t y)
{
    setAddress(x, y);
    _mcp.digitalWrite(_data_pin, HIGH);
    delay(10);  // Short delay to ensure data pin is stable
    strobe();
    lineConnections[x][y] = true;

    setAddress(y, x);
    _mcp.digitalWrite(_data_pin, HIGH);
    delay(10);  // Short delay to ensure data pin is stable
    strobe();
    lineConnections[y][x] = true;

}

void MT8816::disconnect(uint8_t x, uint8_t y)
{
    setAddress(x, y);
    _mcp.digitalWrite(_data_pin, LOW);
    delay(10);  // Short delay to ensure data pin is stable
    strobe();
    lineConnections[x][y] = false;

    setAddress(y, x);
    _mcp.digitalWrite(_data_pin, LOW);
    delay(10);  // Short delay to ensure data pin is stable
    strobe();
    lineConnections[y][x] = false;
}

bool MT8816::getConnection(int x, int y) {
    // Check if the coordinates are within the valid range
    if (x >= 0 && x < 8 && y >= 0 && y < 8) {
        return lineConnections[x][y];
    } else {
        // Handle invalid coordinates, e.g., by returning a default value or throwing an exception
        std::cerr << "Error: Invalid coordinates (" << x << ", " << y << ")." << std::endl;
        return;
    }
}


void MT8816::setAddress(uint8_t x, uint8_t y)
{
    for (int i = 0; i < 4; ++i) {
        bool bit = (x >> i) & 0x01;
        _mcp.digitalWrite(_ax_pins[i], bit);
    }

    for (int i = 0; i < 3; ++i) {
        bool bit = (y >> i) & 0x01;
        _mcp.digitalWrite(_ay_pins[i], bit);
    }
}

void MT8816::strobe()
{
    _mcp.digitalWrite(_strobe_pin, HIGH);
    delayMicroseconds(5);
    _mcp.digitalWrite(_strobe_pin, LOW);
    delayMicroseconds(5);
}
