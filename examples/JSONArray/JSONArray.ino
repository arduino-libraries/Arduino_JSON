/*
  JSON Array

  This sketch demonstrates how to use various features
  of the JSON library, in particular for JSON arrays.

  This example code is in the public domain.
*/

#include <JSON.h>

const char input[] = "[true, 42, \"apple\"]";

void setup() {
  Serial.begin(9600);
  while (!Serial);

  demoParse();

  demoCreation();
}

void loop() {
}

void demoParse() {
  Serial.println("parse");
  Serial.println("=====");

  var myArray = JSON.parse(input);

  // typeof(jsonVar) can be used to get the type of the var
  if (typeof(myArray) == "undefined") {
    Serial.println("Parsing input failed!");
    return;
  }

  Serial.print("typeof(myArray) = ");
  Serial.println(typeof(myArray)); // prints: array

  // myArray.length() can be used to get the length of the array
  Serial.print("myArray.length() = ");
  Serial.println(myArray.length());
  Serial.println();

  Serial.print("typeof(myArray[0]) = ");
  Serial.println(typeof(myArray[0]));

  Serial.print("myArray[0] = ");
  Serial.println(myArray[0]);
  Serial.println();

  Serial.print("myArray[1] = ");
  Serial.println((int) myArray[1]);
  Serial.println();

  Serial.print("myArray[2] = ");
  Serial.println((const char*) myArray[2]);
  Serial.println();

  Serial.println();
}

void demoCreation() {
  Serial.println("creation");
  Serial.println("========");

  var myArray;
  
  myArray[0] = false;
  myArray[1] = 4242.5;
  myArray[2] = "orange";
  myArray[3] = "world";
  myArray[4] = true;
  myArray[5] = 42;

  Serial.print("myArray.length() = ");
  Serial.println(myArray.length());

  // JSON.stringify(myVar) can be used to convert the json var to a String
  String jsonString = JSON.stringify(myArray);

  Serial.print("JSON.stringify(myArray) = ");
  Serial.println(jsonString);
  Serial.println();

  for (int i = 0; i < myArray.length(); i++) {
    var value = myArray[i];

    Serial.print("typeof(myArray[");
    Serial.print(i);
    Serial.print("]) = ");
    Serial.println(typeof(value));

    Serial.print("myArray[");
    Serial.print(i);
    Serial.print("] = ");
    Serial.println(value);

    Serial.println();
  }

  Serial.println();
}
