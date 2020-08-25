#pragma once
#ifndef ACTADIRANTAC290CONTROLLER_H
#define ACTADIRANTAC290CONTROLLER_H


#include <IRsend.h>

#include "ACController.h"
#include "Configuration.h"
#include "IRTadiranTac290.h"

class ACTadiranTac290Controller
{
    typedef ACController<ACTadiranTac290Controller> Controller_t;
private:
    IRsend _irsend;
    IRTadiranTac290 _irTadiranTac290;

public:
    static ACCapabilities GetCapabilities()
    {
        return
            ACCapabilities::HasFanModeTurbo |
            ACCapabilities::HasFanModeLow |
            ACCapabilities::HasACModeCool |
            ACCapabilities::HasACModeHeat;
    }

    explicit ACTadiranTac290Controller() : _irsend(IRLED), _irTadiranTac290(&_irsend) {}


    void Initialize()
    {
        _irsend.begin();
        Serial.println("ACTadiranTac290Controller begins...");
    }

    void SetACStateFromMonitorDevice(bool isAcOn) //no need to know. this AC has different code for on and off
    {
    }

    void SendAc(const ACState &state) const
    {
        const IRTadiranTac290Power power = state.isPowerOn ? IRTadiranTac290Power::On : IRTadiranTac290Power::Off;
        const IRTadiranTac290Fan fan = state.fan == ACFan::Low ? IRTadiranTac290Fan::Low : IRTadiranTac290Fan::Turbo; //default Turbo
        const IRTadiranTac290Mode mode = state.mode == ACMode::Heat ? IRTadiranTac290Mode::Heat : IRTadiranTac290Mode::Cool; //default cool
        _irTadiranTac290.SendTadiranTac290(power, mode, fan, state.temperature);
    }
};
#endif //ACTADIRANTAC290CONTROLLER_H
