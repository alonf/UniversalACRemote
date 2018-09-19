#pragma once
#ifndef ACCONTROLLER
#define ACCONTROLLER
#include <Arduino.h>
#include "ACTypes.h"
#include "ACCapabilities.h"

/*
 * TRealACController:
 *  TRealACController.SendAc(ACState state);
 *  void TRealACController.Initialize();
 *  ACCapabilities TRealACController::Capabilities;
 */

template<typename TRealACController>
class ACController
{
public:
    
private:
    ACState _state {};
   //TRealACController _acController {};

public:
    ACController() { Serial.write("ACController *************\n"); }
    void SendAc(const ACState &acState)
    {
        _state = acState;
        TRealACController::SendAc(_state);
    }

    bool IsPowerOn() const { return _state.isPowerOn; }
    ACMode GetACMode() const { return _state.mode; }
    ACFan GetACfan() const { return _state.fan; }
    bool IsSwingModeOn() const { return _state.isSwingOn;}
    bool IsSleepModeOn() const { return _state.isSleepModeOn; }
    bool IsiFeelModeOn() const { return _state.isiFeelModeOn; }
    unsigned char GetTemperature() const { return _state.temperature; }
    bool IsLightOn() const { return _state.isLightOn; }
    bool IsXFanOn() const { return _state.isXfanOn; }
    ACExtendedSwingMode GetExtendedSwingMode() const { return _state.extendedSwing; }
    ACState GetACState() const { return _state; }

    ACCapabilities GetCapabilities() const { return TRealACController::Capabilities; }
    void Initialize() { TRealACController::Initialize(); }
};

#endif //ACCONTROLLER

