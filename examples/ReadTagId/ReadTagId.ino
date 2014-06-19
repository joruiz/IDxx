/*
  ReadTagId
  Read a tag id from IDxx reader.
 
  This example code is in the public domain.
*/

#include <IDxx.h>

// update serial number if it uses a hardware serial
#define ReaderSerial Serial
// uncomment next line and comment before if it uses software serial
//SoftwareSerial ReaderSerial(2,3);

IDxx idxx;

void setup() {

  Serial.begin(9600);

  //init RFID reader object  
  ReaderSerial.begin(9600);
  idxx.begin(&ReaderSerial);
}

void loop() {
  
  String tagId = idxx.readTagId();
  if (tagId.equals(""))
    Serial.println("No tag presented");
  else {
    Serial.print("Tag read: ");
    Serial.println(tagId);
  }
  delay(1000);
}
