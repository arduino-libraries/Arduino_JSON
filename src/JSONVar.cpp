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

JSONVar::operator bool()
{
  return cJSON_IsBool(_json) && cJSON_IsTrue(_json);
}

JSONVar::operator int()
{
  return cJSON_IsNumber(_json) ? _json->valueint : 0;
}

JSONVar::operator double()
{
  return cJSON_IsNumber(_json) ? _json->valuedouble : NAN;
}

JSONVar::operator const char*()
{
  if (cJSON_IsString(_json)) {
    return _json->valuestring;
  }

  return NULL;
}

void JSONVar::operator= (const JSONVar& v)
{
  replaceJson(cJSON_Duplicate(v._json, true));
  _parent = NULL;
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

JSONVar JSONVar::operator[](const char* key)
{
  cJSON* json = cJSON_GetObjectItemCaseSensitive(_json, key);

  if (json == NULL) {
    json = cJSON_AddNullToObject(_json, key);
  }
  
  return JSONVar(json, _json);    
}

JSONVar JSONVar::operator[](int index)
{
  cJSON* json = cJSON_GetArrayItem(_json, index);

  // TODO: create NULL cJSON if null?

  return JSONVar(json, _json);
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
