// Configuration.h
#pragma once

#ifndef _CONFIGURATION_h
#define _CONFIGURATION_h

#define ELECTRA
//#define TADIRAN
//#define TADIRANTAC290

//Wifi Configuration
static const char *SSID = "ACIoT"; //The default configuration access point ssid
static const char *password = "12345678"; //The default configuration access point password - at least 8 chars
static const char *appKey = "apikey"; 
static const char *ApiKey = "{ca3c9e58-00c5-43cb-a2f5-cfed90b46b0e}"; //TODO: Move to EPROM

const unsigned int defaultButtonLongTimePeriod = 5000; //5 seconds -> reset
const unsigned int defaultButtonVeryLongTimePeriod = 20000; //20 seconds -> factory reset
const int temperatureDeltaCalibration = -4;
/*
//WeMos configuration (Yarden & Children)
const int pushButton = D3; 
const int redLed = D5;
const int greenLed = D6; 
const int IRLED = D0;
const int ButtonPressed = LOW;
const int ButtonReleased = ButtonPressed == HIGH ? LOW : HIGH;
const int DhtPin = D4;
*/

//configuration - Parent and living room
const int pushButton = D1;
const int redLed = D2;
const int greenLed = D8;
const int IRLED = D5;
const int ButtonPressed = HIGH;
const int ButtonReleased = ButtonPressed == HIGH ? LOW : HIGH;
const int DhtPin = D4;
#endif

