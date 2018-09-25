// ACManager.h

#ifndef _ACMANAGER_h
#define _ACMANAGER_h
#define RAWBUF 101

#include "Singleton.h"
#include "ArduinoLoopManager.h"
#include "Configuration.h"
#include "Util.h"
//#include <map>

#ifdef ELECTRA
#include "ACElectraController.h"
#elif defined(TADIRAN)
#include "ACTadiranController.h"
#elif defined (TADIRANTAC290)
#include "ACTadiranTac290Controller.h"
#else
#error("One AC type must be defined")
#endif


#include "ACController.h"


class ACManager final : public Singleton<ACManager>, public IProcessor
{
    friend class Singleton<ACManager>;
private:

#ifdef ELECTRA
    typedef ACController<ACElectraController> ACController_t;
#elif defined(TADIRAN)
    typedef ACController<ACTadiranController> ACController_t; 
#elif defined (TADIRANTAC290)
    typedef ACController<ACTadiranTac290Controller> ACController_t;
#else
#error("One AC type must be defined")
#endif

    ACController_t _acController;

public:

	virtual void Intialize(std::shared_ptr<ACManager> This) override;

    Util::Map<ACMode, const char *> _ACMode2TextMap = { 
	    { ACMode::Auto, "auto" },{ ACMode::Cool, "cool" },
	    { ACMode::Heat, "heat" },{ ACMode::Fan, "fan" },
	    { ACMode::Dry, "dry" },{ ACMode::Recycle, "recycle" },
        { ACMode::Humid, "humid" }
	};
    Util::Map<ACFan, const char *> _ACFan2TextMap = { 
	    { ACFan::Auto, "auto" },{ ACFan::Turbo, "turbo" } , { ACFan::High, "high" },
	    { ACFan::Low, "low" },{ ACFan::Medium, "medium" } };

    Util::Map<ACExtendedSwingMode, const char *> _ACExtendedSwingMode2TextMap = {
        { ACExtendedSwingMode::Off, "off" },{ ACExtendedSwingMode::On1, "on1" },
        { ACExtendedSwingMode::On2, "on2" },{ ACExtendedSwingMode::On3, "on3" },
        { ACExtendedSwingMode::On4, "on4" },{ ACExtendedSwingMode::On5, "on5" },
        { ACExtendedSwingMode::OnFull, "on full" },{ ACExtendedSwingMode::OnFullLower, "on full lower" },
        { ACExtendedSwingMode::OnFullMiddle, "on full middle" },{ ACExtendedSwingMode::OnFullUpper, "on full upper" },
    };

    Util::Map<bool, const char *> _ACOnOffTextMap = { { false, "off" },{ true, "on" } };
	
public:
	
	void OnButtonPressed();

    void SendState(ACState acState);
    bool IsPowerOn() const { return _acController.IsPowerOn(); }
    ACMode GetACMode() const { return _acController.GetACMode(); }
    ACFan GetACfan() const { return _acController.GetACfan(); }
    bool IsSwingModeOn() const { return _acController.IsSwingModeOn(); }
    bool IsSleepModeOn() const { return _acController.IsSleepModeOn(); }
    bool IsiFellModeOn() const { return _acController.IsiFeelModeOn(); }
    ACExtendedSwingMode GetACExtendedSwingMode() const { return _acController.GetExtendedSwingMode(); }
    bool IsXFanOn() const { return _acController.IsXFanOn(); }
    bool IsLightOn() const { return _acController.IsLightOn(); }
    ACState GetACState() const;
    ACCapabilities GetCapabilities() const { return _acController.GetCapabilities();}
	void Loop() override {}

private:
	ACState _acStatus;
};

typedef std::shared_ptr<ACManager> ACManagerPtr_t;
#endif

