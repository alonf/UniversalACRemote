#pragma once
#ifndef IRTADIRAN_h
#define IRTADIRAN_h
#include <IRsend.h>

enum class IRTadiranMode : uint8_t
{
    Cool = 0,
    Heat = 1,
    Fan = 2,
    Humid = 3,
    Recycle = 4
};

enum class IRTadiranFan : uint8_t
{
    Auto = 0,
    Low = 1,
    Medium = 2,
    High = 3,
    Turbo = 4
};

enum class IRTadiranSwing : uint8_t
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


enum class IRTadiranXFan : uint8_t
{
    Off = 0,
    On = 1
};

enum class IRTadiranLight : uint8_t
{
    On = 1,
    Off = 2
};

enum class IRTadiranPower : uint8_t
{
    Off = 0,
    On = 1
};

class IRTadiran
{
public:
    // Ctor, remote will be used to send the raw IR data
    IRTadiran(IRsend* remote) : _remote(remote) {}

    // Sends the specified configuration to the IR led using IRremote
    void SendTadiran(IRTadiranPower power, IRTadiranMode mode, IRTadiranFan fan, int temperature, IRTadiranSwing swing, IRTadiranXFan xFan, IRTadiranLight light);

private:
    IRsend * _remote;
};
#endif //IRTADIRAN_h