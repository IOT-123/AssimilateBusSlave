/*
 * 
 * IOT123 ATTINY85 I2C SLAVE AUTO-JOIN LAYER FOR SENSOR: KY-019
 * 
 * Receive commands across wire on via I2C in 3 segment 16byte packets
 *  ID of PROPERTY (set in _properties)
 *  VALUE of PROPERTY (set in getProperties)
 *  MORE TO COME (0/1 0 = last property)
 * 
 * Pins on ATTINY85
 * SDA PB0
 * SCL PB2
 * RELAY PB3
 * 
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
  pinMode(PIN_ACTOR, OUTPUT);
  digitalWrite(PIN_ACTOR, LOW);// set for digital read in set_properties
//--------------------------------------- END INITIALIZE ACTOR FUNCTIONS
  _assim_slave.begin(ADDRESS_SLAVE, set_properties, receive_command);
}

void loop(){}

// return status of the functions via the nvc array (props)
void set_properties(Definitions::nvc *props){
//--------------------------------------- RETURN STATUS OF ACTOR FUNCTIONS
  byte value = digitalRead(PIN_ACTOR);
  itoa(value, props[0].Value, 10);
//--------------------------------------- END RETURN STATUS OF ACTOR FUNCTIONS
}

void receive_command(String command){
//--------------------------------------- ACTIONS OF ACTOR BASED ON COMMANDS PASSEDVIA I2C
  int commandInt = atoi(command.c_str());
  switch (commandInt){
    case 0:
      digitalWrite(PIN_ACTOR, LOW);
      break;
    case 1:
      digitalWrite(PIN_ACTOR, HIGH);
      break;
    case 2:
      digitalWrite(PIN_ACTOR, !digitalRead(PIN_ACTOR));
      break;
      default: ;
      //pass through
  };
//--------------------------------------- END ACTIONS OF ACTOR BASED ON COMMANDS PASSEDVIA I2C
}


