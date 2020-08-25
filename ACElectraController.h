#pragma once
#ifndef ACELECTRACONTROLLER
#define ACELECTRACONTROLLER
#include "ACController.h"
#include "Configuration.h"
#include "IRelectra.h"


class ACElectraController
{
    typedef ACController<ACElectraController> Controller_t;
private:
    IRsend _irsend;
    IRelectra _irElectra;
    bool _powerState = false;
    
public:

    ACElectraController() : _irsend(IRLED), _irElectra(&_irsend) {}
    static ACCapabilities GetCapabilities()
    {
        return
            ACCapabilities::HasFanModeHigh |
            ACCapabilities::HasFanModeMedium |
            ACCapabilities::HasFanModeLow |
            ACCapabilities::HasFanModeAuto |
            ACCapabilities::HasACModeCool |
            ACCapabilities::HasACModeHeat |
            ACCapabilities::HasACModeDry |
            ACCapabilities::HasACModeFan |
            ACCapabilities::HasACModeAuto |
            ACCapabilities::HasSwingOnOff |
            ACCapabilities::HasSleepMode |
            ACCapabilities::HasiFeelMode;
    }

    void Initialize()
    {
        _irsend.begin();
        Serial.println("ACElectraController begins...");
    }

    void SetACStateFromMonitorDevice(bool isAcOn)
    {
        _powerState = isAcOn;
    }

    void SendAc(ACState state)
    {
        const IRElectraSwing swing = state.isSwingOn ? IRElectraSwing::On : IRElectraSwing::Off;
        const IRElectraPower power = state.isPowerOn != _powerState ? IRElectraPower::OnOffToggle : IRElectraPower::None;
        const IRElectraSleep sleep = state.isSleepModeOn ? IRElectraSleep::On : IRElectraSleep::Off;
        const IRElectraIFeel iFeel = state.isiFeelModeOn ? IRElectraIFeel::On : IRElectraIFeel::Off;
       
        _powerState = state.isPowerOn;

        IRElectraFan fan;
        switch (state.fan)
        {
        case ACFan::Low:
                fan = IRElectraFan::Low;
                break;
        case ACFan::Medium:
                fan = IRElectraFan::Medium;
                break;
        case ACFan::High:
                fan = IRElectraFan::High;
                break;
        case ACFan::Auto:
            default:
                fan = IRElectraFan::Auto;
        }

        IRElectraMode mode;

        switch (state.mode)
        {
        case ACMode::Cool:
                mode = IRElectraMode::Cool;
                break;
            case ACMode::Heat:
                mode = IRElectraMode::Heat;
                break;
            case ACMode::Fan:
                mode = IRElectraMode::Fan;
                break;
            case ACMode::Dry:
                mode = IRElectraMode::Dry;
                break;
            case ACMode::Auto:
            default:
                mode = IRElectraMode::Auto;
        }
        _irElectra.SendElectra(power, mode, fan, state.temperature, swing, sleep, iFeel);
    }
};
#endif //ACELECTRACONTROLLER
