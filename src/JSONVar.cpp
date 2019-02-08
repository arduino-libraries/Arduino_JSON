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

#include "cjson/cJSON.h"

#include "JSONVar.h"

JSONVar::JSONVar(struct cJSON* json, struct cJSON* parent) :
  _json(json),
  _parent(parent)
{
}

JSONVar::JSONVar(bool b) :
  JSONVar()
{
  *this = b;
}

JSONVar::JSONVar(int i) :
  JSONVar()
{
  *this = i;
}

JSONVar::JSONVar(double d) :
  JSONVar()
{
  *this = d;
}

JSONVar::JSONVar(const char* s)  :
  JSONVar()
{
  *this = s;
}

JSONVar::JSONVar(const String& s)  :
  JSONVar()
{
  *this = s;
}

JSONVar::JSONVar(const JSONVar& v)
{
  _json = cJSON_Duplicate(v._json, true);
  _parent = NULL;
}

JSONVar::JSONVar() :
  JSONVar(NULL, NULL)
{
}

JSONVar::~JSONVar()
{
  if (_json != NULL && _parent == NULL) {
    cJSON_Delete(_json);

    _json = NULL;
  }
}

size_t JSONVar::printTo(Print& p) const
{
  if (_json == NULL) {
    return 0;
  }

  char* s = cJSON_PrintUnformatted(_json);

  size_t writen = p.print(s);

  cJSON_free(s);

  return writen;
}

JSONVar::operator bool() const
{
  return cJSON_IsBool(_json) && cJSON_IsTrue(_json);
}

JSONVar::operator int() const
{
  return cJSON_IsNumber(_json) ? _json->valueint : 0;
}

JSONVar::operator double() const
{
  return cJSON_IsNumber(_json) ? _json->valuedouble : NAN;
}

JSONVar::operator const char*() const
{
  if (cJSON_IsString(_json)) {
    return _json->valuestring;
  }

  return NULL;
}

void JSONVar::operator=(const JSONVar& v)
{
  replaceJson(cJSON_Duplicate(v._json, true));
}

void JSONVar::operator=(bool b)
{
  replaceJson(b ? cJSON_CreateTrue() : cJSON_CreateFalse());
}

void JSONVar::operator=(int i)
{
  replaceJson(cJSON_CreateNumber(i));
}

void JSONVar::operator=(double d)
{
  replaceJson(cJSON_CreateNumber(d));
}

void JSONVar::operator=(const char* s)
{
  replaceJson(cJSON_CreateString(s));
}

void JSONVar::operator=(const String& s)
{
  *this = s.c_str();
}

bool JSONVar::operator==(const JSONVar& v) const
{
  return cJSON_Compare(_json, v._json, 1);
}

JSONVar JSONVar::operator[](const char* key)
{
  if (!cJSON_IsObject(_json)) {
    replaceJson(cJSON_CreateObject());
  }

  cJSON* json = cJSON_GetObjectItemCaseSensitive(_json, key);

  if (json == NULL) {
    json = cJSON_AddNullToObject(_json, key);
  }
  
  return JSONVar(json, _json);    
}

JSONVar JSONVar::operator[](int index)
{
  if (!cJSON_IsArray(_json)) {
    replaceJson(cJSON_CreateArray());
  }

  cJSON* json = cJSON_GetArrayItem(_json, index);

  if (json == NULL) {
    while (index >= cJSON_GetArraySize(_json)) {
      json = cJSON_CreateNull();

      cJSON_AddItemToArray(_json, json);
    }
  }

  return JSONVar(json, _json);
}

JSONVar JSONVar::operator[](const JSONVar& key)
{
  if (cJSON_IsArray(_json) && cJSON_IsNumber(key._json)) {
    int index = (int)key;

    return (*this)[index];
  }

  if (cJSON_IsObject(_json) && cJSON_IsString(key._json)) {
    const char* str = (const char*) key;

    return (*this)[str];
  }

  return JSONVar(NULL, NULL);
}

int JSONVar::length() const
{
  if (cJSON_IsString(_json)) {
    return strlen(_json->string);
  } else if (cJSON_IsArray(_json)) {
    return cJSON_GetArraySize(_json);
  } else {
    return -1;
  }
}

JSONVar JSONVar::keys() const
{
  if (!cJSON_IsObject(_json)) {
    return JSONVar(NULL, NULL);
  }

  int length = cJSON_GetArraySize(_json);

  const char* keys[length];
  cJSON* child = _json->child;

  for (int i = 0; i < length; i++, child = child->next) {
    keys[i] = child->string;
  }

  return JSONVar(cJSON_CreateStringArray(keys, length), NULL);
}

JSONVar JSONVar::parse(const char* s)
{
  cJSON* json = cJSON_Parse(s);

  return JSONVar(json, NULL);
}

JSONVar JSONVar::parse(const String& s)
{
  return parse(s.c_str());
}

String JSONVar::stringify(const JSONVar& value)
{
  if (value._json == NULL) {
    return String((const char *)NULL);
  }

  char* s = cJSON_PrintUnformatted(value._json);

  String str = s;

  cJSON_free(s);

  return str;
}

const char* JSONVar::typeof_(const JSONVar& value)
{
  struct cJSON* json = value._json;

  if (cJSON_IsBool(json)) {
    return "boolean";
  } else if (json == NULL || cJSON_IsNull(json)) {
    return "null"; // TODO: should this return "object" to be more JS like?
  } else if (cJSON_IsNumber(json)) {
    return "number";
  } else if (cJSON_IsString(json)) {
    return "string";
  } else if (cJSON_IsArray(json)) {
    return "array"; // TODO: should this return "object" to be more JS like?
  } else if (cJSON_IsObject(json)) {
    return "object";
  } else {
    return "unknown";
  }
}

void JSONVar::replaceJson(struct cJSON* json)
{
  cJSON* old = _json;

  _json = json;

  if (old) {
    if (_parent) {
      if (cJSON_IsObject(_parent)) {
        cJSON_ReplaceItemInObjectCaseSensitive(_parent, old->string, _json);
      } else if (cJSON_IsArray(_parent)) {
        cJSON_ReplaceItemViaPointer(_parent, old, _json);
      }
    } else {
      cJSON_Delete(old);
    }
  }
}
