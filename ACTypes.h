#pragma once
#ifndef ACTYPES
#define ACTYPES

enum class ACMode
{
    Cool,
    Heat,
    Fan,
    Dry,
    Auto,
    Humid,
    Recycle
};

enum class ACFan
{
    Low,
    Medium,
    High,
    Turbo,
    Auto
};

enum class ACExtendedSwingMode
{
    Off = 0,
    OnFull = 1,
    On1 = 2,
    On2 = 3,
    On3 = 4,
    On4 = 5,
    On5 = 6,
    OnFullLower = 7,
    OnFullMiddle = 8,
    OnFullUpper = 9
};

struct ACState
{
    bool isPowerOn = true;
    int roomTemperature = 24;
    int roomHumidity = 70;
    ACMode mode = ACMode::Auto;
    ACFan fan = ACFan::Auto;
    int temperature = 24;
    bool isSwingOn = false;
    bool isSleepModeOn = false;
    int isiFeelModeOn = false;
    bool isXfanOn = false;
    bool isLightOn = false;
    ACExtendedSwingMode extendedSwing = ACExtendedSwingMode::Off;
    
};

#endif //#define ACTYPES