/*
* IRTadiranTac290
* Reverse engineering by Alon Fliess with AnalysIR
*/
#pragma once
#ifndef IRTadeiranTac290_h
#define IRTADIRANTAC290_H
//#include <IRremoteInt.h>
#include <IRsend.h>


enum class IRTadiranTac290Mode : uint64_t
{
	Cool = 0b10,
	Heat = 0b01,
};

enum class IRTadiranTac290Fan : uint64_t
{
	Low = 0b1,
	Turbo = 0b0,
};

enum class IRTadiranTac290Power : uint64_t
{
	Off = 0b0011,
	On = 0b1100
};

class IRTadiranTac290
{
public:
	// Ctor, remote will be used to send the raw IR data
    IRTadiranTac290(IRsend* remote);

	// Sends the specified configuration to the IR led using IRremote
	bool SendTadiranTac290(IRTadiranTac290Power power, IRTadiranTac290Mode mode, IRTadiranTac290Fan fan, int temperature) const;

private:
    const uint16_t zeroLength = 600;
    const uint16_t oneLenght = 1770;
	IRsend* _remote;
	void EncodeTadiranTac290(uint16_t *signal, IRTadiranTac290Power power, IRTadiranTac290Mode mode, IRTadiranTac290Fan fan, uint64_t temperature) const;
};
#endif //IRTadiranTac290