/*
  This file is part of the Arduino JSON library.
  Copyright (c) 2019 Arduino SA. All rights reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
*/

#ifndef _JSON_VAR_H_
#define _JSON_VAR_H_

#include <Arduino.h>

struct cJSON;

#define typeof typeof_
#define null nullptr

class JSONVar : public Printable {
public:
  JSONVar();
  JSONVar(bool b);
  JSONVar(int i);
  JSONVar(long l);
  JSONVar(unsigned long ul);
  JSONVar(double d);
  JSONVar(const char* s);
  JSONVar(const String& s);
  JSONVar(const JSONVar& v);
#if __cplusplus >= 201103L || defined(__GXX_EXPERIMENTAL_CXX0X__)
  JSONVar(JSONVar&& v);
#endif
  JSONVar(nullptr_t);
  virtual ~JSONVar();

  virtual size_t printTo(Print& p) const;

  operator bool() const;
  operator int() const;
  operator long() const;
  operator double() const;
  operator const char*() const;

  void operator=(const JSONVar& v);
#if __cplusplus >= 201103L || defined(__GXX_EXPERIMENTAL_CXX0X__)
  JSONVar& operator=(JSONVar&& v);
#endif
  void operator=(bool b);
  void operator=(int i);
  void operator=(long l);
  void operator=(unsigned long ul);
  void operator=(double d);
  void operator=(const char* s);
  void operator=(const String& s);
  void operator=(nullptr_t);

  bool operator==(const JSONVar& v) const;
  bool operator==(nullptr_t) const;

  JSONVar operator[](const char* key);
  JSONVar operator[](const String& key);
  JSONVar operator[](int index);
  JSONVar operator[](const JSONVar& key);

  int length() const;
  JSONVar keys() const;
  bool hasOwnProperty(const char* key) const;
  bool hasOwnProperty(const String& key) const;

  static JSONVar parse(const char* s);
  static JSONVar parse(const String& s);
  static String stringify(const JSONVar& value);
  static String typeof_(const JSONVar& value);

private:
  JSONVar(struct cJSON* json, struct cJSON* parent);

  void replaceJson(struct cJSON* json);

private:
  struct cJSON* _json;
  struct cJSON* _parent;
};

extern JSONVar undefined;

#endif
