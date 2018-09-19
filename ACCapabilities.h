#pragma once

#ifndef _ACCAPABILITIES
#define _ACCAPABILITIES
#include "IRTadiran.h"

enum class ACCapabilities : unsigned int
{
    None = 0,
    IsStandardOnOff =      1 << 0,
    IsOnOffToggle =        1 << 1,
    HasFanModeTurbo =      1 << 2,
    HasFanModeHigh =       1 << 3,
    HasFanModeMedium =     1 << 4,
    HasFanModeLow =       1 << 5,
    HasFanModeAuto =       1 << 6,
    HasACModeCool =        1 << 7,
    HasACModeHeat =        1 << 8,
    HasACModeDry =         1 << 9,
    HasACModeFan =         1 << 10,
    HasACModeHumid =       1 << 11,
    HasACModeRecycle =     1 << 12,
    HasACModeAuto =        1 << 13,
    HasSwingOnOff =        1 << 14,
    HasSleepMode =         1 << 15,
    HasOnOffLight =        1 << 16,
    HasOnOffXFan =         1 << 17,
    HasExtendedSwingMode = 1 << 18,
    HasiFeelMode =         1 << 19
};

inline ACCapabilities operator | (ACCapabilities lhs, ACCapabilities rhs)
{
    return static_cast<ACCapabilities>(static_cast<ACCapabilities>(lhs) | static_cast<ACCapabilities>(rhs));
}

inline ACCapabilities& operator |= (ACCapabilities& lhs, ACCapabilities rhs)
{
    lhs = static_cast<ACCapabilities>(static_cast<ACCapabilities>(lhs) | static_cast<ACCapabilities>(rhs));
    return lhs;
}

inline bool operator & (ACCapabilities lhs, ACCapabilities rhs)
{
    const bool result = (static_cast<int>(lhs) & static_cast<int>(rhs)) != 0;
    return result;
}




#endif // _ACCAPABILITIES