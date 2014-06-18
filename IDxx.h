/*
 Arduino Library for IDxx family RFID readers
 go to https://www.sparkfun.com/datasheets/Sensors/ID-12-Datasheet.pdf for more information
 
 License: CC BY-SA 3.0: Creative Commons Share-alike 3.0. Feel free 
 to use and abuse this code however you'd like. If you find it useful
 please attribute, and SHARE-ALIKE!
 
 Created June 2014
 by Jonathan Ruiz de Garibay

 */

#ifndef IDXX_h
#define IDXX_h

#include "Arduino.h"

class IDxx
{
	public:
		void begin(Stream * serial);
		void begin(Stream * serial, uint8_t resetPin);
		void reset();
		String readTagId();

	private:
		Stream * _serial;
		uint8_t _resetPin;
};

#endif