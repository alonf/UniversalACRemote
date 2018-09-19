#pragma once
#include "ACElectraController.h"

IRsend *ACElectraController::_irsend;
IRelectra *ACElectraController::_irElectra;
bool ACElectraController::_powerState = false;
ACCapabilities Capabilities =
         ACCapabilities::IsOnOffToggle |
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
         ACCapabilities::HasSleepMode;
