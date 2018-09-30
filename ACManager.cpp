#include "ACManager.h"

using namespace std;


void ACManager::Intialize(shared_ptr<ACManager> This) //called by the singleton create, after ctor
{
    _acController.Initialize();
	Serial.println("AC Manager begins...");
};

void ACManager::SendState(ACState acState)
{
	if (acState.temperature < 15)
        acState.temperature = 15;
	if (acState.temperature > 30)
        acState.temperature = 30;

    _acController.SendAc(acState);

	Serial.printf("Send AC command with these values: Power is %s, Mode is %s, Fan is %s, Temperature is %d, Swing is %s, Sleep mode is %s iFeel mode is %s, Light is %s, XFan is %s, Swing mode is %s\n",
        _ACOnOffTextMap[_acController.IsPowerOn()],
		_ACMode2TextMap[_acController.GetACMode()],
		_ACFan2TextMap[_acController.GetACfan()],
        _acController.GetTemperature(),
        _ACOnOffTextMap[_acController.IsSwingModeOn()],
        _ACOnOffTextMap[_acController.IsSleepModeOn()],
        _ACOnOffTextMap[_acController.IsiFeelModeOn()],
        _ACOnOffTextMap[_acController.IsLightOn()],
        _ACOnOffTextMap[_acController.IsXFanOn()],
        _ACExtendedSwingMode2TextMap[_acController.GetExtendedSwingMode()]);
}

ACState ACManager::GetACState() const
{
    return _acController.GetACState();
}
void ACManager::OnButtonPressed()
{
    ACState state; // Set default, but toggle power
    state.isPowerOn = !IsPowerOn(); //toggle power state

    SendState(state); //default values are what we need
}






