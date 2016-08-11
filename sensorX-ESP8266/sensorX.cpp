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

#include <FS.h>
#include "KeyedStringCollection.h"
#include "SensorX.h"

/**
 * We place strings in the programm memory to leave
 * more free dynamic memory.
 * 
 */
const char CONFIG_FILENAME[]       PROGMEM = "sensorX.conf";
const char CONFIG_BACKUPFILENAME[] PROGMEM = "sensorX.bak";



void SensorX::debugOut(const char* format, ... ) {
  if(_debugOutput && _debugOutputCallback) {
    char buffer[160];
    va_list vargs;
    va_start(vargs, format);
    vsnprintf(buffer, sizeof(buffer) - 1, format, vargs);
    va_end(vargs);
    _debugOutputCallback(buffer);
  }  
}

void SensorX::debugOut(const __FlashStringHelper* format, ... ) {
  if(_debugOutput && _debugOutputCallback) {
    char buffer[160];
    va_list vargs;
    va_start(vargs, format);
    vsnprintf_P(buffer, sizeof(buffer) - 1, (const char*)format, vargs);
    va_end(vargs);
    _debugOutputCallback(buffer);
  }  
}

void SensorX::setDebugOutput(bool flag) {
  _debugOutput = flag;
}

void SensorX::setDebugOutputCallback(void (*func)(const char* text)){
  _debugOutputCallback = func;
}

void SensorX::begin() {

  debugOut(F("begin()"));

  // Initialize the WiFi to a known state in case some 
  // software did "ugly" things with the radio.
  WiFi.mode(WIFI_STA);
  WiFi.disconnect(true);
  delay(500);
    
  // debugOut("sensorX: IPv4 = %s", WiFi.localIP().toString().c_str() );
  

}


SensorX::~SensorX() {
  if(_settings) delete(_settings);
}


SensorX::SensorX() : _debugOutputCallback(0L) {
  _settings = new KeyedStringCollection();
}


