#ifndef MT8816_h
#define MT8816_h

#include <Arduino.h>
#include <Adafruit_MCP23X17.h>

class MT8816
{
  public:
    MT8816(uint8_t mcp_address, 
           uint8_t ax0, uint8_t ax1, uint8_t ax2, uint8_t ax3,
           uint8_t ay0, uint8_t ay1, uint8_t ay2,
           uint8_t strobe, uint8_t data, uint8_t reset, uint8_t cs_pin);
    void begin();
    void reset();
    void connect(uint8_t x, uint8_t y);
    void disconnect(uint8_t x, uint8_t y);
    bool getConnection(int x, int y);
  private:
    Adafruit_MCP23X17 _mcp;
    uint8_t _mcp_address;
    uint8_t _ax_pins[4];  // AX0-AX3
    uint8_t _ay_pins[3];  // AY0-AY2
    uint8_t _strobe_pin;
    uint8_t _data_pin;
    uint8_t _reset_pin;
    uint8_t _cs_pin;
    bool Connections [8][8];
    void setAddress(uint8_t x, uint8_t y);
    void strobe();
};

#endif
