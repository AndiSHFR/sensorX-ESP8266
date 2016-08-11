/**
 * KeyedStringCollection.h
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

#include <stdlib.h>


class KeyedStringCollection {  
protected:
  
  // Internal structure to keep key/value pair
  struct _KEYVALUEPAIR {
    char* pKey;
    char* pValue;
  };

  // Pointer to an array of key/value pairs
  struct _KEYVALUEPAIR* _pValues;

  // Size of the key/value array;
  int _capacity;

  // Number of elements in the key/value array;
  int _count;

  // Free memory that was allocted for a string
  void freeAndNullString(char** s);
  
  // Allocate memory and return pointer to a copy of string s  
  char* allocAndCopyString(const char* s);    

  // Resize the key/value array
  bool resize(int newCapacity);  

  // Return the index for a given key in the array. 
  // Return -1 if the key was nto found.
  int indexForKey(const char* lookForKey);
  
public:

  // Return the numnber of elements in the array
  int getCount();

  // Return the key for a given index.
  // This is handy when looping thru the array.
  // Return NULL for invalid index values.
  char* keyForIndex(int index);

  // Set the string value for a key.
  bool setValue(const char* key, const char* value);

  // Set the integer value for a key
  bool setValue(const char* key, int value);

  // Return a pointer to the string value of a key.
  // If the key was not found return the default value.
  const char* getValue(const char* key, const char* def);
  
  // Return a pointer to the integer value of a key.
  // If the key was not found return the default value.
  int getValue(const char* key, int def);

  // Remove all items
  void clear();

  // Copy constructor for the class
  KeyedStringCollection(const KeyedStringCollection& from);

  // Class destructor
  ~KeyedStringCollection();

  // Default constructor
  KeyedStringCollection();
  
};

