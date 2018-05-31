# AssimilateBusSlave

Arduino library for I2C communication from an ATTINY85 slave (this library) to an ESP8266 master (AssimilateBus) on the auto logging (MQTT) and visualization (Crouton) platform: ASSIMILATE IOT NETWORK.

Use ATtinyCore to build the source.

Although this is a library, it is used more like a local module. Due to extensive use of PROGMEM because to the size constraints of the ATTINY, the Library file is referencing a Header file with the PROGMEM entries.

Install as you do normally for Arduino Libraries. The examples will will show the local copies of the library.
