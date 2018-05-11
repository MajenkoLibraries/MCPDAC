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

#define CHANNEL_A false
#define CHANNEL_B true
#define GAIN_LOW false
#define GAIN_HIGH true

#define REGAB    15
#define REGGA    13
#define REGSHDN  12

class MCPDACClass {

	public:
		boolean ldac;
		boolean gain[2] = { GAIN_LOW, GAIN_LOW };
		boolean shdn[2] = { true, true };
		unsigned int cspin;
		unsigned int ldacpin;

	public:
		void begin();
		void begin(unsigned int cspin);
		void begin(unsigned int cspin, unsigned int ldacpin);
		void setGain(bool chan, bool gain);
		void shutdown(bool chan, bool sd);
		void setVoltage(bool channel, unsigned int mv);
		void update();
};

extern MCPDACClass MCPDAC;
