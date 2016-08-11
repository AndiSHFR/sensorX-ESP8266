/**
 * sensorX.h
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

#ifndef sensorX_H
#define sensorX_H

#include <stdarg.h>
#include <Stream.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

class KeyedStringCollection;

class SensorX {
  protected:

    KeyedStringCollection* _settings;

    bool _debugOutput;
    void (*_debugOutputCallback)(const char*);            

    void debugOut(const char* format, ... );
    void debugOut(const __FlashStringHelper* format, ... );

  public:

    void setDebugOutput(bool flag);
    void setDebugOutputCallback(void (*func)(const char* text));

    void begin();
    
    ~SensorX();
    SensorX();
};

#endif // #ifndef sensorX_H

