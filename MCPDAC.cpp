/***********************************************
 * Microchip DAC library
 * (c) 2012 Majenko Technologies
 *
 * This library is offered without any warranty as to
 * fitness for purpose, either explicitly or implicitly
 * implied.
 ***********************************************/

/*
 * Microchip DAC library.  This works with the MCP4822 chip and
 * similar chips that work with the same protocol.
 */

#include <Arduino.h>
#include <SPI.h>
#include "MCPDAC.h"

MCPDACClass MCPDAC;

void MCPDACClass::begin()
{
	this->begin(10);
}

void MCPDACClass::begin(uint8_t cspin)
{
	this->ldac = false;
	this->cspin = cspin;
	pinMode(this->cspin,OUTPUT);
	digitalWrite(this->cspin,HIGH);
	SPI.begin();
}

void MCPDACClass::begin(uint8_t cspin, uint8_t ldacpin)
{
	this->begin(cspin);
	this->ldac = true;
	this->ldacpin = ldacpin;
	pinMode(this->ldacpin,OUTPUT);
	digitalWrite(this->ldacpin,HIGH);
}

void MCPDACClass::setGain(bool chan, bool gain)
{
	this->gain[chan] = gain;
}

void MCPDACClass::shutdown(bool chan, bool sd)
{
	this->shdn[chan] = sd;
}

void MCPDACClass::setVoltage(bool chan, uint16_t mv)
{
	this->value[chan] = mv;
}

void MCPDACClass::update()
{
	if(this->ldac==false)
		return;
	digitalWrite(this->ldacpin,LOW);
	digitalWrite(this->ldacpin,HIGH);
}

void MCPDACClass::updateRegister(bool chan)
{
	uint16_t command = 0;
	command |= (chan << REGAB);                 // set channel in register
	command |= (!this->gain[chan] << REGGA);    // set gain in register
	command |= (!this->shdn[chan] << REGSHDN);  // set shutdown in register
	command |= (this->value[chan] & 0x0FFF);    // set input data bits (strip everything greater than 12 bit)

	SPI.setDataMode(SPI_MODE0);
	digitalWrite(this->cspin,LOW);
	SPI.transfer(command>>8);
	SPI.transfer(command&0xFF);
	digitalWrite(this->cspin,HIGH);
}
