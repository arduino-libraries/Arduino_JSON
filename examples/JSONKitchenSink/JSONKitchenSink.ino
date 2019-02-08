#include <JSON.h>

void setup() {
  Serial.begin(9600);
  while (!Serial);

  // boolean
  var b = true;

  Serial.print("typeof(b) = ");
  Serial.println(typeof(b));

  Serial.print("b = ");
  Serial.println(b);

  b = false;

  // integer
  Serial.print("b = ");
  Serial.println(b);

  var i = 42;

  Serial.print("typeof(i) = ");
  Serial.println(typeof(i));

  Serial.print("i = ");
  Serial.println(i);

  i = 4242;

  Serial.print("i = ");
  Serial.println(i);

  // double
  var d = 42.42;

  Serial.print("typeof(d) = ");
  Serial.println(typeof(d));

  Serial.print("d = ");
  Serial.println(d);

  d = 4242.4242;

  Serial.print("d = ");
  Serial.println(d);

  // string
  var s = "Hello World!";

  Serial.print("typeof(s) = ");
  Serial.println(typeof(s));

  Serial.print("s = ");
  Serial.println(s);

  s = ":)";

  Serial.print("s = ");
  Serial.println(s);

  // array
  var array;

  array[0] = 42;

  Serial.print("typeof(array) = ");
  Serial.println(typeof(array));

  Serial.println((int)array[0] == 42);

  Serial.print("array = ");
  Serial.println(array);

  array[1] = 42.42;

  Serial.print("array = ");
  Serial.println(array);

  // object
  var object;

  object["foo"] = "bar";

  Serial.print("typeof(object) = ");
  Serial.println(typeof(object));

  Serial.print("object keys = ");
  Serial.println(object.keys());

  Serial.print("object = ");
  Serial.println(object);

  object["blah"]["abc"] = 42;

  Serial.print("object = ");
  Serial.println(object);
}

void loop() {
}
