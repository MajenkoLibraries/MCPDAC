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

	private:
		bool ldac = false;
		bool gain[2] = { GAIN_LOW, GAIN_LOW };
		bool shdn[2] = { true, true };
    uint16_t value[2] = { 0, 0 };
		uint8_t cspin;
		uint8_t ldacpin = 0;

	public:
		void begin();
		void begin(uint8_t cspin);
		void begin(uint8_t cspin, uint8_t ldacpin);
		void setGain(bool chan, bool gain);
		void shutdown(bool chan, bool sd);
		void setVoltage(bool chan, uint16_t mv);
		void update();
		void updateRegister(bool chan);
};

extern MCPDACClass MCPDAC;
