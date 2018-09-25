#include "IRTadiranTac290.h"
#include <Arduino.h>
IRTadiranTac290::IRTadiranTac290(IRsend* remote) : _remote(remote) 
{
}


void DumpBits(const String& msg, uint64_t data)
{
    Serial.print(msg);
    Serial.print(":");
    for (int i = 63; i >= 0; --i)
    {
        Serial.write(data & 1ull << i ? '1' : '0');
    }
    Serial.println();
}

bool IRTadiranTac290::SendTadiranTac290(IRTadiranTac290Power power, IRTadiranTac290Mode mode, IRTadiranTac290Fan fan, int temperature) const
{
    uint16_t signal[263];
    signal[0] = 7930;
    signal[1] = 4315;
    signal[130] = 1630;
    signal[131] = 30700;
    EncodeTadiranTac290(&signal[2], power, mode, fan, temperature);
    //Repeat the code
    memcpy(signal + 132, signal, 131 * sizeof(uint16_t));
    Serial.println("Tac 290 code:");
    for (unsigned int i = 0; i < 263; ++i)
    {
        Serial.print(signal[i]);
        Serial.print(',');
    }
    Serial.println();

    _remote->sendRaw(signal, 263, 38);
    return true;
}

void IRTadiranTac290::EncodeTadiranTac290(uint16_t *signal, IRTadiranTac290Power power, IRTadiranTac290Mode mode,
    IRTadiranTac290Fan fan, uint64_t temperature) const
{
    //Bit Pattern:    10000000MM00F0000TTTTTT000000000000000000000PPPP00000000CCCCCCCC
    //"01" ==> 0
    //"10" ==> 1

    uint64_t payload = 0;
    DumpBits("Start", payload);
    payload |= 1ull << 63;
    DumpBits("First 1 in the MSB", payload);
    payload |= static_cast<uint64_t>(mode) << 54;
    DumpBits("Mode", payload);
    payload |= static_cast<uint64_t>(fan) << 51;
    DumpBits("Fan", payload);
    unsigned int b = 1ull << 5;
    for (unsigned int i = 41; i <= 46;++i)
    {
        payload |= (temperature & b) ? 1ull << i : 0;
        b >>= 1;
    }
    
    DumpBits("temperature", payload);
    payload |= static_cast<uint64_t>(power) << 16;
    DumpBits("power", payload);
    //claculate checksum
    //start after the checksum bits
    uint8_t checksum = 0;
    for(unsigned int i = 8; i < 64; i+=4)
    {
        const auto currentNibble = (payload >> i) & 0xF;
        const auto reverseBits = ((currentNibble & 8) >> 3) + ((currentNibble & 4) >> 1) + ((currentNibble & 2) << 1) + ((currentNibble & 1) << 3);
        checksum += reverseBits;
    }
    const auto reversChecksum = ((checksum & 128) >> 7) + ((checksum & 64) >> 5) + ((checksum & 32) << 3) + ((checksum & 16) >> 1) + ((checksum & 8) << 1) + ((checksum & 4) << 3) + ((checksum & 2) << 5) + ((checksum & 1) << 7);
    
    payload |= reversChecksum;
    DumpBits("checksum", payload);
    
    //convert and copy payload to signal
    for (unsigned int i = 0; i < 64; i++)
    {
        const auto bit = (payload >> (63 - i)) & 1;
        signal[i * 2] = bit ? oneLenght : zeroLength;
        signal[i * 2 + 1] = bit ? zeroLength : oneLenght;
    }
}



