/**
 * sensorX-ESP8266.ino
 * Operation system for wireless sensor based on ESP8266.
 * 
 * Project home: https://github.com/AndiSHFR/sensorX-ESP8266
 * 
 * Copyright (c) 2016 Andreas Schaefer <asc@schaefer-it.net>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 * Development is based on documentation found on: https://github.com/esp8266/Arduino
 *
 */

#ifdef ESP8266
extern "C" {
#include "user_interface.h"        // system_update_cpu_frequency(), ...
}
#endif


#include "sensorX.h"

/**
 * Declare the ESP8266-12E pin names
 * and their respective GPIO port numbers.
 * This makes wiring up hardware a lot easier.
 * i.e.: "Connect MOSI to GPIO12" - aehm 
 *       where was it on the ESP8266?
 *       Yeah, you're right. use pin D6! ;-)
 */
static const uint8_t PIN_D0  = 16; // GPIO16  - User, Wake
static const uint8_t PIN_D1  =  5; // GPIO5   - I2C Bus SCL (clock)
static const uint8_t PIN_D2  =  4; // GPIO4   - I2C Bus (data)
static const uint8_t PIN_D3  =  0; // GPIO0   - Flash
static const uint8_t PIN_D4  =  2; // GPIO2   - TXD1, Same as BUILTIN_LED but inverted logic
static const uint8_t PIN_D5  = 14; // GPIO14  - SPI Bus SCK (clock, HSCLK)
static const uint8_t PIN_D6  = 12; // GPIO12  - SPI Bus MISO
static const uint8_t PIN_D7  = 13; // GPIO13  - SPI Bus MOSI, RXD2
static const uint8_t PIN_D8  = 15; // GPIO15  - SPI Bus SS (CS), TXD2
static const uint8_t PIN_D9  =  3; // GPIO3   - RXD0 (Serial console, UART0)
static const uint8_t PIN_D10 =  1; // GPIO1   - TXD0 (Serial console, UART0)

/**
 * If you see "heavy traffic" on GPIO10 (aka SD3) and
 * it seems you cannot get GPIO9 and GPIO10 working, 
 * then it looks like those GPIO are used by the 
 * flash in QIO mode.
 * 
 * If one want to use those GPIO, one need to use flah
 * in DIO mode. This may lead to cut a lot of wires on 
 * board and pull them up. :(
 */
static const uint8_t PIN_SD2 =  9; // GPIO9   - SDD2
static const uint8_t PIN_SD3 = 10; // GPIO10  - SDD3

/*
 * Well, the one and only sensorX instance 
 * We will use Serial for debug output.
 */
SensorX sensorX;

void setup() {

#ifdef ESP8266
  // Try to push frequency up to 160MHz when running on ESP8266 board
  system_update_cpu_freq(SYS_CPU_160MHZ);
#endif

  // Initialize the serial port to the default speed at board startup
  // This way we can see firmware output in the serial monitor
  Serial.begin(74880);

  // Enable diagnostic output from the WiFi libraries.
  // A call to Serial.begin() disables this output.
  Serial.setDebugOutput(true);
  
  // Delay for 2 seconds to stabilize the serial line.
  for(int i = 4; i > 0; i--) { Serial.print("."); delay(500); }

  // Enable debug output to the serial connection
  sensorX.setDebugOutputStream(Serial);
  sensorX.setDebugOutput(true);

  // Initialize sensorX
  sensorX.begin();

}


void loop() {

}
