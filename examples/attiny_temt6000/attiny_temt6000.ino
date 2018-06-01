/*
 * 
 * IOT123 ATTINY85 I2C SLAVE AUTO-JOIN LAYER FOR SENSOR: TEMT6000
 * 
 * Take readings on TEMT6000 and send across wire on request via I2C in 3 segment 16byte packets
 *  ID of PROPERTY (set in _properties)
 *  VALUE of PROPERTY (set in getProperties)
 *  MORE TO COME (0/1 0 = last property)
 * 
 * Pins on ATTINY85
 * SDA PB0
 * SCL PB2
 * TEMT6000 A3
 * 
//---------------------------------------
   DEVELOPER CODING AREAS MARKED LIKE THIS
 //---------------------------------------
 * 
 */

#include "AssimilateBusSlave.h"

AssimilateBusSlave _assim_slave;

void setup()
{
//--------------------------------------- INITIALIZE ACTOR FUNCTIONS
//NA
//--------------------------------------- END INITIALIZE ACTOR FUNCTIONS
  _assim_slave.begin(ADDRESS_SLAVE, set_properties, receive_command);
}

void loop(){}

// return status of the functions via the nvc array (props)
void set_properties(Definitions::nvc *props){
//--------------------------------------- RETURN STATUS OF SENSOR FUNCTIONS
  float lux = analogRead(PIN_SENSOR) * RATIO_LUX;
  float ftCd = lux/10.764;
  float wattsm2 = lux/683.0;
  dtostrf(lux,5,3,props[0].Value);
  dtostrf(ftCd,5,3,props[1].Value);
  dtostrf(wattsm2,5,3,props[2].Value);
//--------------------------------------- END RETURN STATUS OF SENSOR FUNCTIONS
}

void receive_command(String command){
//--------------------------------------- ACTIONS OF ACTOR BASED ON COMMANDS PASSEDVIA I2C
// pass through
//--------------------------------------- END ACTIONS OF ACTOR BASED ON COMMANDS PASSEDVIA I2C
}



