#pragma once

#ifndef _ACCAPABILITIES
#define _ACCAPABILITIES
#include "IRTadiran.h"

enum class ACCapabilities : unsigned int
{
    None = 0,
    HasFanModeTurbo =      1 << 0,
    HasFanModeHigh =       1 << 1,
    HasFanModeMedium =     1 << 2,
    HasFanModeLow =        1 << 3,
    HasFanModeAuto =       1 << 4,
    HasACModeCool =        1 << 5,
    HasACModeHeat =        1 << 6,
    HasACModeDry =         1 << 7,
    HasACModeFan =         1 << 8,
    HasACModeHumid =       1 << 9,
    HasACModeRecycle =     1 << 10,
    HasACModeAuto =        1 << 11,
    HasSwingOnOff =        1 << 12,
    HasSleepMode =         1 << 13,
    HasOnOffLight =        1 << 14,
    HasOnOffXFan =         1 << 15,
    HasExtendedSwingMode = 1 << 16,
    HasiFeelMode =         1 << 17
};

inline ACCapabilities operator | (ACCapabilities lhs, ACCapabilities rhs)
{
    return static_cast<ACCapabilities>(static_cast<unsigned int>(lhs) | static_cast<unsigned int>(rhs));
}

inline ACCapabilities& operator |= (ACCapabilities& lhs, ACCapabilities rhs)
{
    lhs = static_cast<ACCapabilities>(static_cast<unsigned int>(lhs) | static_cast<unsigned int>(rhs));
    return lhs;
}

inline bool operator & (ACCapabilities lhs, ACCapabilities rhs)
{
    const bool result = (static_cast<unsigned int>(lhs) & static_cast<unsigned int>(rhs)) != 0;
    return result;
}




#endif // _ACCAPABILITIES