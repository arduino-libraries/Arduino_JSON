/*
  This file is part of the JSON library.
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

class JSONVar : public Printable {
public:
  JSONVar();
  JSONVar(bool b);
  JSONVar(int i);
  JSONVar(double d);
  JSONVar(const char* s);
  JSONVar(const String& s);
  JSONVar(const JSONVar& v);
  virtual ~JSONVar();

  virtual size_t printTo(Print& p) const;

  operator bool();
  operator int();
  operator double();
  operator const char*();

  void operator=(const JSONVar& v);
  void operator=(bool b);
  void operator=(int i);
  void operator=(double d);
  void operator=(const char* s);
  void operator=(const String& s);

  bool operator==(const JSONVar& v);

  JSONVar operator[](const char* key);
  JSONVar operator[](int index);

  int length();
  JSONVar keys();

  static JSONVar parse(const char* s);
  static JSONVar parse(const String& s);
  static String stringify(const JSONVar& value);
  static const char* typeof_(const JSONVar& value);

private:
  JSONVar(struct cJSON* json, struct cJSON* parent);

  void replaceJson(struct cJSON* json);

private:
  struct cJSON* _json;
  struct cJSON* _parent;
};

#ifndef var
typedef JSONVar var;
#endif

#endif
