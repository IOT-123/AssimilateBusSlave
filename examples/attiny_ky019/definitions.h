#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#include "arduino.h"

//--------------------------------------- ADDRESS AND PIN
#define ADDRESS_SLAVE 12
#define PIN_ACTOR 3
//--------------------------------------- END ADDRESS AND PIN

//--------------------------------------- METADATA
#define META_COUNT 13
const static char m1[] PROGMEM = "ASSIM_NAME"; 
const static char m2[] PROGMEM = "KY-019"; 
const static char m3[] PROGMEM = "1"; 
const static char m4[] PROGMEM = "ASSIM_VERSION"; 
const static char m5[] PROGMEM = "2"; 
const static char m6[] PROGMEM = "1"; 
const static char m7[] PROGMEM = "ASSIM_ROLE"; 
const static char m8[] PROGMEM = "ACTOR"; 
const static char m9[] PROGMEM = "1"; 
const static char m10[] PROGMEM = "POWER_DOWN"; 
const static char m11[] PROGMEM = "1"; 
const static char m12[] PROGMEM = "1"; 
const static char m13[] PROGMEM = "PREPARE_MS"; 
const static char m14[] PROGMEM = "0"; 
const static char m15[] PROGMEM = "1"; 
const static char m16[] PROGMEM = "RESPONSE_MS"; 
const static char m17[] PROGMEM = "10"; 
const static char m18[] PROGMEM = "1"; 

const static char viz1[] PROGMEM = "VIZ_CARD_TYPE"; 
const static char viz2[] PROGMEM = "0:toggle"; // 13 CHAR MAX
const static char viz3[] PROGMEM = "1"; 
const static char viz4[] PROGMEM = "VIZ_ICONS"; 
const static char viz5[] PROGMEM = "0:0|sun-o"; 
const static char viz6[] PROGMEM = "1"; 
const static char viz7[] PROGMEM = "VIZ_ICONS"; 
const static char viz8[] PROGMEM = "0:1|sun-o"; 
const static char viz9[] PROGMEM = "1"; 
const static char viz10[] PROGMEM = "VIZ_LABELS"; 
const static char viz11[] PROGMEM = "0:0|OFF";  
const static char viz12[] PROGMEM = "1"; 
const static char viz13[] PROGMEM = "VIZ_LABELS"; 
const static char viz14[] PROGMEM = "0:1|ON"; 
const static char viz15[] PROGMEM = "1"; 
const static char viz16[] PROGMEM = "VIZ_VALUES"; 
const static char viz17[] PROGMEM = "0:value|0";  
const static char viz18[] PROGMEM = "1"; 

const static char vcc1[] PROGMEM = "VCC_MV";   // must be last
const static char vcc2[] PROGMEM = ""; 
const static char vcc3[] PROGMEM = "0"; 

const char* const _metas[] PROGMEM = { 
  m1, m2, m3, m4, m5, m6, m7, m8, m9, m10, 
  m11, m12, m13, m14, m15, m16, m17, m18, 
  viz1, viz2, viz3, viz4, viz5, viz6, viz7, viz8, viz9, viz10, viz11, viz12, viz13, viz14, viz15, viz16, viz17, viz18,
  vcc1, vcc2, vcc3};
//--------------------------------------- END METADATA

class Definitions{
public:
  struct nvc
  {
      char Name[16];
      char Value[16];
      bool Continue;
  };
//--------------------------------------- PUBLISHED PROPERTIES
  nvc props[1] ={
      {"Switch", "", false}
  };
//--------------------------------------- END PUBLISHED PROPERTIES
  Definitions(){};
private:
};

#endif