/*
 Arduino Library for IDxx family RFID readers
 go to https://www.sparkfun.com/datasheets/Sensors/ID-12-Datasheet.pdf for more information
 
 License: CC BY-SA 3.0: Creative Commons Share-alike 3.0. Feel free 
 to use and abuse this code however you'd like. If you find it useful
 please attribute, and SHARE-ALIKE!
 
 Created June 2014
 by Jonathan Ruiz de Garibay

 */

#include <Arduino.h>
#include "IDxx.h"

//
// begin
//
// initialize IDxx serial port
void IDxx::begin(Stream * serial){

	_serial = serial;
	_resetPin = 0xFF;
}                             

//
// begin
//
// initialize IDxx serial port and reset pin
void IDxx::begin(Stream * serial, uint8_t resetPin){

	_serial = serial;
	_resetPin = resetPin;
	pinMode(_resetPin, OUTPUT);
	digitalWrite(_resetPin, HIGH);
}                             

//
// reset
//
// reset RFID reader (require resetPin)
void IDxx::reset() {

	if (_resetPin != 0xFF) {
		digitalWrite(_resetPin, LOW);
		delay(10);
		digitalWrite(_resetPin, HIGH);
	}
}

//
// realTagId
//
// read tagId from RFID reader (12 hexadecimal characters); return "" if there is not a tag
String IDxx::readTagId() {

	String tagId = "";
	char data;
	
	while(_serial->available() > 0) {
		data = _serial->read();
		//wait start byte
		if (data == 0x02) {
			//read 12 characters
			do {
				if(_serial->available() > 0) {
					data = _serial->read();
					//check data read; if header or stop bytes before 12 digits
					if((data == 0x0D) || (data == 0x0A) || (data == 0x03) || (data == 0x02)) 
						return "";
					tagId += data;
				}
			}
			while (tagId.length() < 12);
			break;
		}
	}
	return tagId;
}