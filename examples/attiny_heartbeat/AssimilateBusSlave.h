/*
AssimilateBusSlave.h - Library for i2c communication for assimilate iot network (via attiny85). 
Created by Nic Roche, May 23, 2018. 
Released into the public domain.
*/

#ifndef _ASSIMILATE_BUS_SLAVE_h
#define _ASSIMILATE_BUS_SLAVE_h

#include "definitions.h"

typedef void(*SetPropertiesCallback) (Definitions::nvc *props);
typedef void(*ReceiveCommandCallback) (String command);

class AssimilateBusSlave
{
public:
  AssimilateBusSlave();
  void begin(byte address, SetPropertiesCallback set_properties_callback, ReceiveCommandCallback receive_command_callback);
//  void receiveEvent(int howMany); //callbacks need to be in global space
//  void requestEvent();
private:
  volatile int _packetStage;
  volatile int _propertyIndex;
  volatile bool _metasConfirmed;
  volatile int _metaIndex;  
  uint16_t getVcc();
  char* nvcAsCharArray(Definitions::nvc nvc, int packetStage);
};

#endif
