/*
AssimilateBusSlave.cpp - Library for i2c communication for assimilate iot network (via attiny85). 
Created by Nic Roche, May 23, 2018. 
Released into the public domain.
*/

#include "AssimilateBusSlave.h"
#include <EEPROM.h> 
#include <Wire.h> //SDA pin5/PB0, SCL pin7/PB2

#define arraySize(x)       (sizeof(x) / sizeof(x[0]))
#define NVC_NUM_STAGES 3

#define TIME_RESPONSE_MS 0 // will be last value sent to master + padding
#if (TIME_RESPONSE_MS)
  unsigned long startMillis; 
#endif

#define IDX_ADDRESS 0

byte _i2c_address;
uint16_t _unique_id;

Definitions _definitions;

SetPropertiesCallback _set_properties_callback;
ReceiveCommandCallback _receive_command_callback;

volatile int _packetStage = 0;
volatile int _propertyIndex = 0;
volatile bool _metasConfirmed = false;
volatile int _metaIndex = 0;
uint16_t _vcc; 

AssimilateBusSlave::AssimilateBusSlave(){}

char* nvcAsCharArray(Definitions::nvc nvc, int packetStage){  
  switch (packetStage){
    case 0:
      return nvc.Name;
      break;
    case 1: 
        #if (TIME_RESPONSE_MS)
          unsigned long currentMillis;
          currentMillis = millis();
          char millis[16];
          itoa(currentMillis - startMillis, millis, 10);
          return millis;
        #endif
      return nvc.Value;
      break;
    case 2:
      return nvc.Continue ? "1" : "0";
      break;
    default:
      char result[16];
      itoa(packetStage, result, 10);
      return result;
  }
}

void receiveEvent(int bytes){
/*
   * 0 - clear eeprom
   * 1 - metadata received
   * 2 - actor command
   * 3 - address change
*/
  byte register_code = Wire.read();
  char incoming[16];
  if((register_code == 1) && (bytes == 1)){
    _metasConfirmed = true;
    _packetStage = 0;
    _propertyIndex = 0;
    return;
  }
  for (int i = 0; i < bytes - 1; i++)// already read 1 byte
  {     
    const char c = Wire.read();     
    int intOfChar = int(c);
    incoming[i] = intOfChar > -1 && intOfChar < 255 ? c : 0x00;// replace invalid chars with zero char      
  }
  switch (register_code){
    case 0: // clear eeprom
      for (int i = 0 ; i < EEPROM.length() ; i++) {
        EEPROM.write(i, 0);
      }
      digitalWrite(3, HIGH);
      return;
      break;
//    case 2: // actor command
//      _receive_command_callback(String(incoming));
//      return;
//      break;
    case 3: // address change
      _i2c_address = atoi(incoming);
      EEPROM.put(IDX_ADDRESS, _i2c_address);
      digitalWrite(3, HIGH);
    break;
    default: return;
  }
}

void requestEvent() {
  char currentPacket[16];
  int propCount = 0;
  if (_metasConfirmed){ 
// PROPERTIES    
    if (_propertyIndex == 0){
      _set_properties_callback(_definitions.props);
    }
    strcpy(currentPacket, nvcAsCharArray(_definitions.props[_propertyIndex], _packetStage));
    propCount = arraySize(_definitions.props);
// METADATA    
  }else{ 
    propCount = META_COUNT;
    if (_metaIndex == ((META_COUNT * 3) - 2)){// if last metadata (VCC), runtime entry
      itoa(_vcc, currentPacket, 10);
    }else{ // just a normal metadata item
      strcpy_P(currentPacket, (char*)pgm_read_word(&(_metas[_metaIndex])));         
    }
    _metaIndex++;
  }
  Wire.write(currentPacket); // send metadate or sensor property
  _packetStage = _packetStage + 1;    
  // go to next property if at last stage of current property
  if (_packetStage == NVC_NUM_STAGES){
    _packetStage = 0;
    _propertyIndex++;
  }
  // all properties processed?
  if (_propertyIndex == propCount){
    _propertyIndex = 0;
    // "0" should terminate requests to this slave
  }
}

void AssimilateBusSlave::begin(byte address, SetPropertiesCallback set_properties_callback, ReceiveCommandCallback receive_command_callback){
  _set_properties_callback = set_properties_callback;
  _receive_command_callback = receive_command_callback;
  _vcc = getVcc();
  EEPROM.get(IDX_ADDRESS, _i2c_address);
  if (_i2c_address < 8 || _i2c_address > 127){
    _i2c_address = address;
  }
  Wire.begin(_i2c_address);   
  Wire.onReceive(receiveEvent);              
  Wire.onRequest(requestEvent);
}

// https://www.avrfreaks.net/forum/attiny85-vcc-measurement-skews-higher-vcc-voltages
//5v = 6393, 6504
//3.3V 3430
uint16_t AssimilateBusSlave::getVcc(){
    // Read 1.1V reference against AVcc
  // set the reference to Vcc and the measurement to the internal 1.1V reference
  ADMUX = _BV(MUX3) | _BV(MUX2);
  delay(2); // Wait for Vref to settle
  uint16_t result = 0;
  for (int x = 0; x < 32; x++){
    ADCSRA |= _BV(ADSC); // Start conversion
    while (bit_is_set(ADCSRA,ADSC)); // measuring
    if (x > 15){
      result += (int16_t)((int16_t)(ADC - result) / 2);
    }
    else{
      result = ADC;
    }
  }
  uint16_t voltage = 1125300 / result; // Calculate Vcc (in mV); 1125300 = 1.1*1023*1000
  return voltage;
}


