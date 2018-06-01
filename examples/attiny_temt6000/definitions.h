#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#include "arduino.h"

//--------------------------------------- ADDRESS AND PIN
#define ADDRESS_SLAVE 9
#define PIN_SENSOR A3
// johnwasser: https://forum.arduino.cc/index.php?topic=185158.0
#define RATIO_LUX 0.9765625
//--------------------------------------- END ADDRESS AND PIN

//--------------------------------------- METADATA
#define META_COUNT 8                              // there is a limit on length of field and array count
const static char m1[] PROGMEM = "ASSIM_NAME"; 
const static char m2[] PROGMEM = "TEMT6000"; 
const static char m3[] PROGMEM = "1"; 
const static char m4[] PROGMEM = "ASSIM_VERSION"; 
const static char m5[] PROGMEM = "2"; 
const static char m6[] PROGMEM = "1"; 
const static char m7[] PROGMEM = "ASSIM_ROLE"; 
const static char m8[] PROGMEM = "SENSOR"; 
const static char m9[] PROGMEM = "1"; 

const static char viz1[] PROGMEM = "VIZ_CARD_TYPE"; 
const static char viz2[] PROGMEM = "0:chart-donut"; 
const static char viz3[] PROGMEM = "1"; 
const static char viz4[] PROGMEM = "VIZ_TOTL_UNIT"; 
const static char viz5[] PROGMEM = "0:1000|LUX";  
const static char viz6[] PROGMEM = "1"; 
const static char viz7[] PROGMEM = "VIZ_IS_SERIES"; 
const static char viz8[] PROGMEM = "0:true";  
const static char viz9[] PROGMEM = "1"; 
const static char viz10[] PROGMEM = "VIZ_HIGH"; 
const static char viz11[] PROGMEM = "0:1000";  
const static char viz12[] PROGMEM = "1"; 

const static char vcc1[] PROGMEM = "VCC_MV";   // must be last
const static char vcc2[] PROGMEM = ""; 
const static char vcc3[] PROGMEM = "0"; 

const char* const _metas[] PROGMEM = { 
  m1, m2, m3, m4, m5, m6, m7, m8, m9,  
  viz1, viz2, viz3, viz4, viz5, viz6, viz7, viz8, viz9, viz10, viz11, viz12,
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
nvc props[3] ={
    {"Ambiant Illum.", "", true}, // viz for LUX
    {"Amb Illum (FC)", "", true},// Foot Candel units
    {"Amb Irri (W/M2)", "", false},// Watt per Square Metre
};
//--------------------------------------- END PUBLISHED PROPERTIES
  Definitions(){};
private:
};

#endif
