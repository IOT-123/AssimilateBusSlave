/*
 * 
 * IOT123 ATTINY85 I2C SLAVE AUTO-JOIN LAYER FOR ACTOR: HEARTBEAT
 * 
 * Receive commands across wire on via I2C in 3 segment 16byte packets
 *  ID of PROPERTY (set in _properties)
 *  VALUE of PROPERTY (set in getProperties)
 *  MORE TO COME (0/1 0 = last property)
 * 
 * Pins on ATTINY85
 * SDA PB0
 * SCL PB2
 * LED I2C REQUEST PB3
 * LED I2C RECEIVE PB4
 * LED ATTINY RUNNING PB1
 * 
<CH>:<CMD>
  - on 0 switches off relay
  - on 1 switches on relay
  - on 2 switches the state of the relay

  //---------------------------------------
   DEVELOPER CODING AREAS MARKED LIKE THIS
 //---------------------------------------
*/

#include "AssimilateBusSlave.h"

AssimilateBusSlave _assim_slave;


void setup()
{
//--------------------------------------- INITIALIZE ACTOR FUNCTIONS
  pinMode(PIN_REQ, OUTPUT);
  pinMode(PIN_REC, OUTPUT);
  pinMode(PIN_RUN, OUTPUT);
  digitalWrite(PIN_REQ, LOW);
  digitalWrite(PIN_REC, LOW);
  digitalWrite(PIN_RUN, HIGH);
//--------------------------------------- END INITIALIZE ACTOR FUNCTIONS
  _assim_slave.begin(ADDRESS_SLAVE, set_properties, receive_command);
}

void loop(){}

// return status of the functions via the nvc array (props)
void set_properties(Definitions::nvc *props){
//--------------------------------------- RETURN STATUS OF ACTOR FUNCTIONS
// if we are alive we are willing to broadcast it
  strcpy(props[0].Value, "ALIVE");
  digitalWrite(PIN_REQ, !digitalRead(PIN_REQ));
//--------------------------------------- END RETURN STATUS OF ACTOR FUNCTIONS
}

void receive_command(String command){
//--------------------------------------- ACTIONS OF ACTOR BASED ON COMMANDS PASSED VIA I2C
// 0:1
  digitalWrite(PIN_REC, !digitalRead(PIN_REC));
//--------------------------------------- END ACTIONS OF ACTOR BASED ON COMMANDS PASSED VIA I2C
}


