#include <IDxx.h>

IDxx id12;

void setup() {

  Serial.begin(9600);
  
  Serial3.begin(9600);
  id12.begin(&Serial3);
}

void loop() {
  
  String tagId = id12.readTagId();
  if (tagId.equals(""))
    Serial.println("No he leido tag");
  else
    Serial.println(tagId);
  delay(500);
}
