/*
 * 
 * IOT123 ATTINY85 I2C SLAVE AUTO-JOIN LAYER FOR SENSOR: 2CH RELAY
 * 
 * Receive commands across wire on via I2C in 3 segment 16byte packets
 *  ID of PROPERTY (set in _properties)
 *  VALUE of PROPERTY (set in getProperties)
 *  MORE TO COME (0/1 0 = last property)
 * 
 * Pins on ATTINY85
 * SDA PB0
 * SCL PB2
 * RELAY CH1 PB3
 * RELAY CH2 PB4
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
  pinMode(PIN_CH1, OUTPUT);
  pinMode(PIN_CH2, OUTPUT);
  digitalWrite(PIN_CH1, LOW);
  digitalWrite(PIN_CH2, LOW);
//--------------------------------------- END INITIALIZE ACTOR FUNCTIONS
  _assim_slave.begin(ADDRESS_SLAVE, set_properties, receive_command);
}

void loop(){}

// return status of the functions via the nvc array (props)
void set_properties(Definitions::nvc *props){
//--------------------------------------- RETURN STATUS OF ACTOR FUNCTIONS
  byte value1 = digitalRead(PIN_CH1);
  itoa(value1, props[0].Value, 10);
  byte value2 = digitalRead(PIN_CH2);
  itoa(value2, props[1].Value, 10);
//--------------------------------------- END RETURN STATUS OF ACTOR FUNCTIONS
}

void receive_command(String command){
//--------------------------------------- ACTIONS OF ACTOR BASED ON COMMANDS PASSED VIA I2C
// 0:1
  byte idx = atoi(strtok(command.c_str(), ":"));
  byte value = atoi(strtok(NULL, ":"));
  byte pin = idx == 0 ? PIN_CH1 : PIN_CH2;
  switch (value){
    case 0:
      digitalWrite(pin, LOW);
      break;
    case 1:
      digitalWrite(pin, HIGH);
      break;
    case 2:
      digitalWrite(pin, !digitalRead(pin));
      break;
      default: ;
      //pass through
  };
//--------------------------------------- END ACTIONS OF ACTOR BASED ON COMMANDS PASSED VIA I2C
}


