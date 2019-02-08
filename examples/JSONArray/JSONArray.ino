#include <JSON.h>

const char input[] = "[true, 42, \"apple\"]";

var array;

void setup() {
  Serial.begin(9600);
  while (!Serial);

  array = JSON.parse(input);

  Serial.print("array length = ");
  Serial.println(array.length());

  Serial.print("typeof(array[0]) = ");
  Serial.println(typeof(array[0]));

  Serial.print("array[0] = ");
  Serial.println(array[0]);

  Serial.print("array[1] = ");
  Serial.println((int) array[1]);

  Serial.print("array[1] = ");
  Serial.println((double) array[1]);

  Serial.print("array[2] = ");
  Serial.println((const char*) array[2]);

  Serial.println(JSON.stringify(array));

  array[0] = false;
  array[1] = 4242;
  array[2] = "orange";
  array[3] = "world";
  array[4] = true;
  array[5] = 42;

  array[10] = 11;

  Serial.print("array length = ");
  Serial.println(array.length());

  Serial.println(array);

  for (int i = 0; i < array.length(); i++) {
    var value = array[i];

    Serial.print("typeof(array[");
    Serial.print(i);
    Serial.print("]) = ");
    Serial.println(typeof(value));

    Serial.print("array[");
    Serial.print(i);
    Serial.print("] = ");
    Serial.println(value);
  }
}

void loop() {
}
