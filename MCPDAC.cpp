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

void MCPDACClass::begin(unsigned int cspin)
{
	this->ldac = false;
	this->begin(cspin,0);
}

void MCPDACClass::begin(unsigned int cspin, unsigned int ldacpin)
{
	this->ldac = true;
	this->cspin = cspin;
	this->ldacpin = ldacpin;
	this->shdn[CHANNEL_A] = false;
	this->shdn[CHANNEL_B] = false;
	this->gain[CHANNEL_A] = false;
	this->gain[CHANNEL_B] = false;
	pinMode(this->ldacpin,OUTPUT);
	digitalWrite(this->ldacpin,HIGH);
	pinMode(this->cspin,OUTPUT);
	digitalWrite(this->cspin,HIGH);
	SPI.begin();
}

void MCPDACClass::setGain(bool chan, bool gain)
{
	this->gain[chan] = gain;
}

void MCPDACClass::shutdown(bool chan, bool sd)
{
	this->shdn[chan] = sd;
}

void MCPDACClass::setVoltage(bool channel, unsigned int mv)
{
	uint16_t command = 0;
	command |= (channel << REGAB);                 // set channel in register
	command |= (!this->gain[channel] << REGGA);    // set gain in register
	command |= (!this->shdn[channel] << REGSHDN);  // set shutdown in register
	command |= (mv & 0x0FFF);                      // set input data bits (strip everything greater than 12 bit)

	SPI.setDataMode(SPI_MODE0);
	digitalWrite(this->cspin,LOW);
	SPI.transfer(command>>8);
	SPI.transfer(command&0xFF);
	digitalWrite(this->cspin,HIGH);
}

void MCPDACClass::update()
{
	if(this->ldac==false)
		return;
	digitalWrite(this->ldacpin,LOW);
	digitalWrite(this->ldacpin,HIGH);
}
