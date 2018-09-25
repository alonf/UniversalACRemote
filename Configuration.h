// Configuration.h
#pragma once

#ifndef _CONFIGURATION_h
#define _CONFIGURATION_h

//#define ELECTRA
#define TADIRAN
//#define TADIRANTAC290

//Wifi Configuration
static const char *SSID = "ACIoT"; //The default configuration access point ssid
static const char *password = "12345678"; //The default configuration access point password - at least 8 chars
static const char *appKey = "api"; 
static const char *ApiKey = "{7802286f-5cb1-43a3-b9fa-28b0352216ec}"; //TODO: Move to EPROM

const unsigned int defaultButtonLongTimePeriod = 5000; //5 seconds -> reset
const unsigned int defaultButtonVeryLongTimePeriod = 20000; //20 seconds -> factory reset

//NodeMCU configuration
const int pushButton = D3; 
const int redLed = D5;
const int greenLed = D6; 
const int IRLED = D0;
const int ButtonPressed = LOW;
const int ButtonReleased = ButtonPressed == HIGH ? LOW : HIGH;
const int DhtPin = D4;

#endif

