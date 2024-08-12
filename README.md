# MT8816
Arduino library to control a MT8816 crosspoint switch array via a GPIO-expander

This library is designed to control an MT8816 analog crosspoint switch using an MCP23017 GPIO expander. The MT8816 is a 16x8 crosspoint switch array, and this library provides an interface to connect or disconnect specific crosspoints. It utilizes I2C communication to interact with the MCP23017, which in turn manages the control pins of the MT8816. 

The library includes functions for initialization, resetting the MT8816, connecting and disconnecting specific crosspoints, and setting addresses. It's designed to simplify the process of controlling the MT8816 in Arduino-based projects, abstracting away the low-level pin management and timing requirements.
