/*
 * 
 * IOT123 ATTINY85 I2C SLAVE AUTO-JOIN LAYER FOR SENSOR: MAX9812
 * 
 * Take readings on MAX9812 and send across wire on request via I2C in 3 segment 16byte packets
 *  ID of PROPERTY (set in _properties)
 *  VALUE of PROPERTY (set in getProperties)
 *  MORE TO COME (0/1 0 = last property)
 * 
 * Pins on ATTINY85
 * SDA PB0
 * SCL PB2
 * MAX9812 A3
 * 
  - on 0 switches off relay
  - on 1 switches on relay
  - on 2 switches the state of the relay

  //---------------------------------------
   DEVELOPER CODING AREAS MARKED LIKE THIS
 //---------------------------------------


      "occupancy": {
        "card-type": "crouton-chart-donut",
        "title": "Occupancy",
        "centerSum": true,
        "values": {
          "labels": [],
          "series": 76
        },
        "total": 100,
        "units": "%"
      },

//"centerSum": true,


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
//--------------------------------------- RETURN STATUS OF ACTOR FUNCTIONS
   unsigned int peakToPeak = 0;   // peak-to-peak level
   unsigned int signalMax = 0;
   unsigned int signalMin = 1024;
   // collect data for 50 mS
   for (int i = 0; i < _micSamples; i++) // does not like millis!
   {
        int k = analogRead(PIN_SENSOR);
        signalMin = min(signalMin, k);
        signalMax = max(signalMax, k);
   }
   peakToPeak = signalMax - signalMin;  // max - min = peak-peak amplitude
  // put values in table
   itoa(signalMin, props[0].Value, 10);
   itoa(signalMax, props[1].Value, 10);
   itoa(peakToPeak, props[2].Value, 10);
//--------------------------------------- END RETURN STATUS OF ACTOR FUNCTIONS
}

void receive_command(String command){
//--------------------------------------- ACTIONS OF ACTOR BASED ON COMMANDS PASSEDVIA I2C
// pass through
//--------------------------------------- END ACTIONS OF ACTOR BASED ON COMMANDS PASSEDVIA I2C
}



