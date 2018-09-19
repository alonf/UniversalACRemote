#pragma once
#ifndef ACTADIRANCONTROLLER_H
#define ACTADIRANCONTROLLER_H


#include <IRsend.h>

#include "ACController.h"
#include "Configuration.h"
#include "IRTadiran.h"

class ACTadiranController
{
    typedef ACController<ACTadiranController> Controller_t;
private:
    IRsend _irsend;
    IRTadiran _irTadiran;

public:
    const ACCapabilities Capabilities =
        ACCapabilities::IsStandardOnOff |
        ACCapabilities::HasFanModeTurbo |
        ACCapabilities::HasFanModeHigh |
        ACCapabilities::HasFanModeMedium |
        ACCapabilities::HasFanModeLow |
        ACCapabilities::HasFanModeAuto |
        ACCapabilities::HasACModeCool |
        ACCapabilities::HasACModeHeat |
        ACCapabilities::HasACModeHumid |
        ACCapabilities::HasACModeRecycle |
        ACCapabilities::HasACModeFan |
        ACCapabilities::HasSwingOnOff |
        ACCapabilities::HasSleepMode |
        ACCapabilities::HasOnOffLight |
        ACCapabilities::HasOnOffXFan |
        ACCapabilities::HasExtendedSwingMode;

    explicit ACTadiranController() : _irsend(IRLED), _irTadiran(&_irsend) {}


    void Initialize()
    {
        _irsend.begin();
        Serial.println("ACTadiranController begins...");
    };

    void SendAc(ACState state)
    {
        //const IRTadiranSwing swing = state.isSwingOn ? IRTadiranSwing::OnFull : IRTadiranSwing::Off;
        const IRTadiranPower power = state.isPowerOn ? IRTadiranPower::On : IRTadiranPower::Off;
        const IRTadiranLight light = state.isLightOn ? IRTadiranLight::On : IRTadiranLight::Off;
        const IRTadiranXFan xFan = state.isXfanOn ? IRTadiranXFan::On : IRTadiranXFan::Off;

        IRTadiranFan fan;
        switch (state.fan)
        {
        case ACFan::Low:
            fan = IRTadiranFan::Low;
            break;
        case ACFan::Medium:
            fan = IRTadiranFan::Medium;
            break;
        case ACFan::High:
            fan = IRTadiranFan::High;
            break;
        case ACFan::Turbo:
            fan = IRTadiranFan::Turbo;
            break;
        case ACFan::Auto:
        default:
            fan = IRTadiranFan::Auto;
        }

        IRTadiranMode mode;

        switch (state.mode)
        {
        case ACMode::Cool:
            mode = IRTadiranMode::Cool;
            break;
        case ACMode::Heat:
            mode = IRTadiranMode::Heat;
            break;
        case ACMode::Fan:
            mode = IRTadiranMode::Fan;
            break;
        case ACMode::Recycle:
            mode = IRTadiranMode::Recycle;
            break;
        case ACMode::Humid:
            mode = IRTadiranMode::Humid;
            break;
        case ACMode::Auto:
        default:
            mode = IRTadiranMode::Fan;
        }

        IRTadiranSwing swing {};

        switch (state.extendedSwing)
        {
        case ACExtendedSwingMode::Off: 
            swing = IRTadiranSwing::Off;
            break;
        case ACExtendedSwingMode::OnFull: 
            swing = IRTadiranSwing::OnFull;
            break;
        case ACExtendedSwingMode::On1: 
            swing = IRTadiranSwing::On1;
            break;
        case ACExtendedSwingMode::On2: 
            swing = IRTadiranSwing::On2;
            break;
        case ACExtendedSwingMode::On3: 
            swing = IRTadiranSwing::On3;
            break;
        case ACExtendedSwingMode::On4: 
            swing = IRTadiranSwing::On4;
            break;
        case ACExtendedSwingMode::On5: 
            swing = IRTadiranSwing::On5;
            break;
        case ACExtendedSwingMode::OnFullLower: 
            swing = IRTadiranSwing::OnFullLower;
            break;
        case ACExtendedSwingMode::OnFullMiddle: 
            swing = IRTadiranSwing::OnFullMiddle;
            break;
        case ACExtendedSwingMode::OnFullUpper: 
            swing = IRTadiranSwing::OnFullUpper;
            break;
        default: ;
        }
        _irTadiran.SendTadiran(power, mode, fan, state.temperature, swing, xFan, light);
    }
};
#endif //ACTADIRANCONTROLLER_H
