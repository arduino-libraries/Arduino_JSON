#include <JSON.h>

const char input[] = "{\"result\":true,\"count\":42,\"foo\":\"bar\"}";

var obj;

void setup() {
  Serial.begin(9600);
  while (!Serial);

  obj = JSON.parse(input);

  Serial.print("obj keys = ");
  Serial.println(obj.keys());

  Serial.println((bool) obj["result"]);
  Serial.println((int) obj["count"]);
  Serial.println((double) obj["count"]);
  Serial.println((const char*) obj["foo"]);

  Serial.println(JSON.stringify(obj));

  obj["result"] = false;
  obj["count"] = 4242;
  obj["foo"] = "ciao";
  obj["hello"] = "world";
  obj["true"] = true;
  obj["x"] = 42;

  Serial.print("obj keys = ");
  Serial.println(obj.keys());

  Serial.println(obj);
}

void loop() {
}
