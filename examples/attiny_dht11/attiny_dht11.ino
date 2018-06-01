/*
 * 
 * IOT123 ATTINY85 I2C SLAVE AUTO-JOIN LAYER FOR SENSOR: DHT11
 * 
 * Take readings on DHT11 and send across wire on request via I2C in 3 segment 16byte packets
 *  ID of PROPERTY (set in _properties)
 *  VALUE of PROPERTY (set in getProperties)
 *  MORE TO COME (0/1 0 = last property)
 * 
 * Pins on ATTINY85
 * SDA PB0
 * SCL PB2
 * DHT11 PB1
 * 
//---------------------------------------
   DEVELOPER CODING AREAS MARKED LIKE THIS
 //---------------------------------------
 * 
 */

#include "AssimilateBusSlave.h"
#include "DHT.h"

AssimilateBusSlave _assim_slave;
dht _dht;

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
//--------------------------------------- RETURN STATUS OF ACTOR FUNCTIONS
  int chk =  _dht.read11(PIN_SENSOR);
  dtostrf(_dht.humidity,2,2,props[0].Value);
  dtostrf(_dht.temperature,2,2,props[1].Value);
//--------------------------------------- END RETURN STATUS OF ACTOR FUNCTIONS
}

void receive_command(String command){
//--------------------------------------- ACTIONS OF ACTOR BASED ON COMMANDS PASSEDVIA I2C
// pass through
//--------------------------------------- END ACTIONS OF ACTOR BASED ON COMMANDS PASSEDVIA I2C
}


//--------------------------------------- READING CALCULATIONS


