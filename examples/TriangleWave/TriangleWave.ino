// MCPDAC relies on SPI.
#include <SPI.h>
#include <MCPDAC.h>

void setup()
{
  // CS on pin 10, no LDAC pin (tie it to ground).
  MCPDAC.begin(10);
  
  // Set the gain to "HIGH" mode - 0 to 4096mV.
  MCPDAC.setGain(CHANNEL_A,GAIN_HIGH);
  
  // Do not shut down channel A, but shut down channel B.
  MCPDAC.shutdown(CHANNEL_A,false);
  MCPDAC.shutdown(CHANNEL_B,true);
}

void loop()
{
  static unsigned int volts;
  
  // Set the voltage of channel A.
  MCPDAC.setVoltage(CHANNEL_A,volts&0x0fff);

  // Increase the voltage in steps of 100mV.
  volts+=100;
}
