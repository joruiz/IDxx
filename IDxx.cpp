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
// constructor
//
// This library use I2C protocol so, it is necesary to specified an I2C address.
void IDxx::begin(Stream * serial){

	_serial = serial;
	_resetPin = 0xFF;
}                             

void IDxx::begin(Stream * serial, uint8_t resetPin){

	_serial = serial;
	_resetPin = resetPin;
	pinMode(_resetPin, OUTPUT);
	digitalWrite(_resetPin, HIGH);
}                             

void IDxx::reset() {

	if (_resetPin != 0xFF) {
		digitalWrite(_resetPin, LOW);
		delay(10);
		digitalWrite(_resetPin, HIGH);
	}
}

String IDxx::readTagId() {

	String tagId = "";
	char data;
	
	while(_serial->available() > 0) {
		data = _serial->read();
		if (data == 0x02) {
			do {
				if(_serial->available() > 0) {
					data = _serial->read();
					if((data == 0x0D) || (data == 0x0A) || (data == 0x03) || (data == 0x02)) // if header or stop bytes before the 10 digit reading 
						return "";    // stop reading
					tagId += data;
				}
			}
			while (tagId.length() < 12);
			break;
		}
	}
	return tagId;
}


/*	
byte i = 0;
	byte val = 0;
	byte code[6];
	byte checksum = 0;
	byte bytesread = 0;
	byte tempbyte = 0;
	
		if((val = _serial.read()) == 2) {                  // check for header 
			bytesread = 0; 
			while (bytesread < 12) {                        // read 10 digit code + 2 digit checksum
				if( Serial.available() > 0) { 
					val = Serial.read();
					if((val == 0x0D)||(val == 0x0A)||(val == 0x03)||(val == 0x02)) { // if header or stop bytes before the 10 digit reading 
						break;                                    // stop reading
					}

					// Do Ascii/Hex conversion:
					if ((val >= '0') && (val <= '9'))
						val = val - '0';
					else if ((val >= 'A') && (val <= 'F'))
						val = 10 + val - 'A';

					// Every two hex-digits, add byte to code:
					if (bytesread & 1 == 1) {
					// make some space for this hex-digit by
					// shifting the previous hex-digit with 4 bits to the left:
					code[bytesread >> 1] = (val | (tempbyte << 4));

					if (bytesread >> 1 != 5)                // If we're at the checksum byte,
						checksum ^= code[bytesread >> 1];       // Calculate the checksum... (XOR)
					else
						tempbyte = val;                           // Store the first hex digit first...

					bytesread++;                                // ready to read next digit
				} 
			} 

			// Output to Serial:

			if (bytesread == 12) {                          // if 12 digit read is complete
				Serial.print("5-byte code: ");
				for (i=0; i<5; i++) {
					if (code[i] < 16) Serial.print("0");
					Serial.print(code[i], HEX);
					Serial.print(" ");
				}
				Serial.println();

				Serial.print("Checksum: ");
				Serial.print(code[5], HEX);
				Serial.println(code[5] == checksum ? " -- passed." : " -- error.");
				Serial.println();
			}

			bytesread = 0;
		}
	}
}*/