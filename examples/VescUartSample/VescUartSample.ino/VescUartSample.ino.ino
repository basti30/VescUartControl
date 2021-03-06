/*
 Name:		VescUartSample.ino
 Created:	17/09/2018 14:23:00
 Author:	basti30
*/

//Example shows how to read the whole mc-config, change a value (l_max_erpm) and write the mc-config back to the vesc. 
//Made for Vesc 6 in September 2018. Please check if there were changes in the Vesc Firmware.

// To use VescUartControl stand alone you need to define a config.h file, that should contain the Serial or you have to comment the line
// #include Config.h out in VescUart.h

// Setup: tested on ESP8266. But RX and TX pins of Vesc 6 are 5V tolerant
// VESC 6  |  ESP8266
//  GND    |    GND
//  RX     |    TX
//  TX     |    RX


#define DEBUG 
#include "Config.h"
#include <VescUart.h>
#include <datatypes.h>


unsigned long count;

void setup() {
	
	//Setup UART port
	SetSerialPort(&SERIALIO);
	SERIALIO.begin(115200);
#ifdef DEBUG
	//SEtup debug port
	SetDebugSerialPort(&DEBUGSERIAL);
	DEBUGSERIAL.begin(115200);
	#endif
}

bldcMeasure Val;        //struct for telemetry data
mc_configuration mcVal; //struct for mc-config data
	
// the loop function runs over and over again until power down or reset
void loop() {
  
  DEBUGSERIAL.print("Loop: "); DEBUGSERIAL.println(count++);
  delay(4000);
  
  //Reading mc-config
  if (VescUartGet(mcVal)) {
    DEBUGSERIAL.println("Successfully read mc-config.");
    SerialPrint(mcVal);
    delay(100);
    
    mcVal.l_max_erpm = 34400.00;

    if(VescUartSet(mcVal))
    {
      DEBUGSERIAL.println("Successfully wrote mc-config.");
    }
    else
    {
      DEBUGSERIAL.println("Failed to write mc-config.");
    }
    delay(4000);
  }
  else
  {
    Serial.println("Failed to read mc-config.");
  }

  //Reading Telemetry
  if (VescUartGet(Val)) {
    SerialPrint(Val);
    delay(4000);
  }
  else
  {
    Serial.println("Failed to get telemetry!");
  }
	
}




