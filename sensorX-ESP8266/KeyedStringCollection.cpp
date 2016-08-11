/**
 * KeyedStringCollection.cpp
 * A class to store key value pairs
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

#include <Arduino.h>
#include "KeyedStringCollection.h"



void KeyedStringCollection::freeAndNullString(char** s) {
  if(*s) free(*s);
  *s = NULL;
}

char* KeyedStringCollection::allocAndCopyString(const char* s) {
  // null pointers for s will result in an 
  // allocated but empty string. This way 
  // if we got problems allocating memory we indeed can
  // return NULL
  char* result = (char*)malloc(1 + (s ? strlen(s) : 0));
  if(result) {
    *result = '\0';
    if(s) strcpy(result, s);
  }
  return result;
}
    
bool KeyedStringCollection::resize(int newCapacity) {
  if(newCapacity <= _capacity) return true;
  struct _KEYVALUEPAIR* tv = (struct _KEYVALUEPAIR*)malloc(sizeof(struct _KEYVALUEPAIR) * newCapacity);
  if(!tv) return false;
  memset(tv, 0, sizeof(struct _KEYVALUEPAIR) * newCapacity);
  for(int i=0; i < _count; i++) {
    tv[i] = _pValues[i];
    // Because we copied the pointers to the new array we only 
    // need to NULL the pointers at the old array. No call
    // to free() allowed here!
    _pValues[i].pKey = NULL;
    _pValues[i].pValue = NULL;
  }
  if(_pValues) free(_pValues);
  _pValues = tv;
  _capacity = newCapacity;
  return true;    
}

int KeyedStringCollection::indexForKey(const char* lookForKey) {
  int result = -1;
  if(lookForKey && _pValues && _count) {
    String lookForKeyString = String(lookForKey);
    for(int index = 0; index < _count; index++) {
      if(lookForKeyString.equalsIgnoreCase(_pValues[index].pKey)) {
        result = index;
        break;
      }
    }    
  }
  return result;
}


int KeyedStringCollection::getCount() {
  return _count;
}


char* KeyedStringCollection::keyForIndex(int index) {
  if(index >= 0 && index < _count) {
    return _pValues[index].pKey;
  }
  return NULL;
}

bool KeyedStringCollection::setValue(const char* key, const char* value) {

  if(!key) return false;
  char* tv = allocAndCopyString(value);
  if(!tv) return false;
  
  int index = indexForKey(key);  
  
  if(-1 == index) {
    if(_count >= _capacity - 1) resize(_capacity + 4);
    char* tk = allocAndCopyString(key);
    if(!tk) {
      freeAndNullString(&tv);
      return false;
    }
    index = _count++;
    _pValues[index].pKey = tk;
  } 

  freeAndNullString(&_pValues[index].pValue);
  _pValues[index].pValue = tv;
}


bool KeyedStringCollection::setValue(const char* key, int value) {
  char buffer[30];
  return setValue(key, itoa(value, buffer, 10));
}


const char* KeyedStringCollection::getValue(const char* key, const char* def) {
  int index = indexForKey(key);
  if(-1 < index && _pValues[index].pValue ) {
    return _pValues[index].pValue;    
  }
  return def;
}

int KeyedStringCollection::getValue(const char* key, int def) {
  char buffer[30];
  const char *v = getValue(key, itoa(def, buffer, 10));
  if(v) return(atoi(v));
  return def;
}

void KeyedStringCollection::clear() {
  if(_pValues) {
    for(int index = 0; index < _count; index++ ) {        
      freeAndNullString(&_pValues[index].pKey);
      freeAndNullString(&_pValues[index].pValue);
    }
  }
  _count = 0;
}


KeyedStringCollection::KeyedStringCollection(const KeyedStringCollection& from) : KeyedStringCollection() {
  for(int index = 0; index < from._count; index++ ) {
    setValue(from._pValues[index].pKey, from._pValues[index].pValue);
  }
}

KeyedStringCollection::~KeyedStringCollection() {
  if(_pValues) {
    clear();
    free(_pValues);
  }
}

KeyedStringCollection::KeyedStringCollection() : _pValues(0L), _capacity(0), _count(0) {
}


