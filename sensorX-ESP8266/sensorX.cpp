/**
 * sensorX.cpp
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
 */

#include "SensorX.h"


/**
 * NullStream
 * A Stream based class that does nothing.
 * Very handy to be passed to log functions that require a Stream& to log to.
 * i.e. Stream& debugConsole(Serial); 
 *      -> myFunc(debugConsole);  // Output to the serial port 
 *      -> myFunc(NullStream)     // No output at all
 */


class NullStream : public Stream{
public:
  size_t write( uint8_t u_Data ) { return u_Data, 0x01; }
  int available( void ) { return 0; }
  void flush( void ) { }
  int peek( void ) { return -1; }
  int read( void ){ return -1; };
  NullStream( void ) { }
};

static NullStream nullStream;

void SensorX::debugOut(const char* format, ... ) {
  if(_debugOutput) {
    char buffer[160];
    va_list vargs;
    va_start(vargs, format);
    vsnprintf(buffer, sizeof(buffer) - 1, format, vargs);
    va_end(vargs);
    buffer[sizeof(buffer)-1] = '\0';
    _debugOutputStream.print(F("SX: "));
    _debugOutputStream.println(buffer);
  }  
}

void SensorX::debugOut(const __FlashStringHelper* format, ... ) {
  if(_debugOutput) {
    char buffer[160];
    va_list vargs;
    va_start(vargs, format);
    vsnprintf(buffer, sizeof(buffer) - 1, (const char*)format, vargs);
    va_end(vargs);
    buffer[sizeof(buffer)-1] = '\0';
    _debugOutputStream.print(F("SX: "));
    _debugOutputStream.println(buffer);
  }  
}

void SensorX::setDebugOutput(bool flag) {
  _debugOutput = flag;
}

void SensorX::setDebugOutputStream(Stream& stream) {
  _debugOutputStream = stream;
}


void SensorX::begin() {
  debugOut(F("begin()"));

  // Initialize the WiFi to a known state in case some software
  // did "ugly" things with the radio part.
  WiFi.mode(WIFI_STA);
  WiFi.disconnect(true);
  delay(500);
  
}


SensorX::~SensorX() {
}


SensorX::SensorX() : _debugOutputStream(nullStream) {
}


