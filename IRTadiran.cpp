// Tadiran A/C Control via serial connection w/ Arduino
// Originally created By Alex Shubovich - ALEXSHU.COM
// Edited By Evyatar Yitzhack

#include "IRTadiran.h"
#include <Arduino.h>

void IRTadiran::SendTadiran(IRTadiranPower power, IRTadiranMode mode, IRTadiranFan fan, int temperature, IRTadiranSwing swing, IRTadiranXFan xFan, IRTadiranLight light)
{
    uint16_t newCode[139] = { 3,2,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,1,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
    int incomingByte = 0;
    int irHigh = 1650;
    int irLow = 600;
    
    //power
    switch (power) {
    case IRTadiranPower::Off:
        if (xFan == IRTadiranXFan::Off) {
            newCode[11] = 1;
            newCode[25] = 1;
            newCode[131] = 1;
            newCode[135] = 1;
            newCode[137] = 0;
        }
        else
        {
            newCode[11] = 1;
            newCode[25] = 1;
            newCode[49] = 1;
            newCode[131] = 1;
            newCode[135] = 1;
            newCode[137] = 0;
        }
        break;
    case IRTadiranPower::On:
        newCode[9] = 1;
        newCode[47] = 1;
        break;
    }
    if (power == IRTadiranPower::Off)
    {
        goto fin;
    }
    // Modes
    switch (mode) {
    case IRTadiranMode::Cool:
            //Temperatue
        switch (temperature) {
        case 16:
            newCode[131] = 1;
            newCode[135] = 1;
            break;
        case 17:
            newCode[19] = 1;
            newCode[133] = 1;
            newCode[135] = 1;
            break;
        case 18:
            newCode[21] = 1;
            newCode[131] = 1;
            newCode[133] = 1;
            newCode[135] = 1;
            break;
        case 19:
            newCode[19] = 1;
            newCode[21] = 1;
            newCode[137] = 1;
            break;
        case 20:
            newCode[23] = 1;
            newCode[131] = 1;
            newCode[137] = 1;
            break;
        case 21:
            newCode[19] = 1;
            newCode[23] = 1;
            newCode[133] = 1;
            newCode[137] = 1;
            break;
        case 22:
            newCode[21] = 1;
            newCode[23] = 1;
            newCode[131] = 1;
            newCode[133] = 1;
            newCode[137] = 1;
            break;
        case 23:
            newCode[19] = 1;
            newCode[21] = 1;
            newCode[23] = 1;
            newCode[135] = 1;
            newCode[137] = 1;
            break;
        case 24:
            newCode[25] = 1;
            newCode[131] = 1;
            newCode[135] = 1;
            newCode[137] = 1;
            break;
        case 25:
            newCode[25] = 1;
            newCode[19] = 1;
            newCode[133] = 1;
            newCode[135] = 1;
            newCode[137] = 1;
            break;
        case 26:
            newCode[21] = 1;
            newCode[25] = 1;
            newCode[131] = 1;
            newCode[133] = 1;
            newCode[135] = 1;
            newCode[137] = 1;
            break;
        case 27:
            newCode[19] = 1;
            newCode[21] = 1;
            newCode[25] = 1;
            break;
        case 28:
            newCode[23] = 1;
            newCode[25] = 1;
            newCode[131] = 1;
            break;
        case 29:
            newCode[19] = 1;
            newCode[23] = 1;
            newCode[25] = 1;
            newCode[133] = 1;
            break;
        case 30:
            newCode[21] = 1;
            newCode[23] = 1;
            newCode[25] = 1;
            newCode[131] = 1;
            newCode[133] = 1;
            break;
        }
        break;
    case IRTadiranMode::Heat:
        newCode[3] = 0;
        newCode[7] = 1;
        //Temperatue
        switch (temperature) {
        case 16:
            newCode[131] = 1;
            newCode[137] = 1;
            break;
        case 17:
            newCode[19] = 1;
            newCode[131] = 1;
            newCode[137] = 1;
            break;
        case 18:
            newCode[21] = 1;
            newCode[133] = 1;
            newCode[137] = 1;
            break;
        case 19:
            newCode[19] = 1;
            newCode[21] = 1;
            newCode[131] = 1;
            newCode[133] = 1;
            newCode[137] = 1;
            break;
        case 20:
            newCode[23] = 1;
            newCode[135] = 1;
            newCode[137] = 1;
            break;
        case 21:
            newCode[19] = 1;
            newCode[23] = 1;
            newCode[131] = 1;
            newCode[135] = 1;
            newCode[137] = 1;
            break;
        case 22:
            newCode[21] = 1;
            newCode[23] = 1;
            newCode[133] = 1;
            newCode[135] = 1;
            newCode[137] = 1;
            break;
        case 23:
            newCode[19] = 1;
            newCode[21] = 1;
            newCode[23] = 1;
            newCode[131] = 1;
            newCode[133] = 1;
            newCode[135] = 1;
            newCode[137] = 1;
            break;
        case 24:
            newCode[25] = 1;
            break;
        case 25:
            newCode[25] = 1;
            newCode[19] = 1;
            newCode[131] = 1;
            break;
        case 26:
            newCode[21] = 1;
            newCode[25] = 1;
            newCode[133] = 1;
            break;
        case 27:
            newCode[19] = 1;
            newCode[21] = 1;
            newCode[25] = 1;
            newCode[131] = 1;
            newCode[133] = 1;
            break;
        case 28:
            newCode[23] = 1;
            newCode[25] = 1;
            newCode[135] = 1;
            break;
        case 29:
            newCode[19] = 1;
            newCode[23] = 1;
            newCode[25] = 1;
            newCode[131] = 1;
            newCode[135] = 1;
            break;
        case 30:
            newCode[21] = 1;
            newCode[23] = 1;
            newCode[25] = 1;
            newCode[133] = 1;
            newCode[135] = 1;
            break;
        }
        break;
    case IRTadiranMode::Fan:
        newCode[5] = 1;
        //Temperatue
        switch (temperature) {
        case 16:
            newCode[131] = 1;
            newCode[133] = 1;
            newCode[135] = 1;
            break;
        case 17:
            newCode[19] = 1;
            newCode[137] = 1;
            break;
        case 18:
            newCode[21] = 1;
            newCode[131] = 1;
            newCode[137] = 1;
            break;
        case 19:
            newCode[19] = 1;
            newCode[21] = 1;
            newCode[133] = 1;
            newCode[137] = 1;
            break;
        case 20:
            newCode[23] = 1;
            newCode[131] = 1;
            newCode[133] = 1;
            newCode[137] = 1;
            break;
        case 21:
            newCode[19] = 1;
            newCode[23] = 1;
            newCode[135] = 1;
            newCode[137] = 1;
            break;
        case 22:
            newCode[21] = 1;
            newCode[23] = 1;
            newCode[131] = 1;
            newCode[135] = 1;
            newCode[137] = 1;
            break;
        case 23:
            newCode[19] = 1;
            newCode[21] = 1;
            newCode[23] = 1;
            newCode[133] = 1;
            newCode[135] = 1;
            newCode[137] = 1;
            break;
        case 24:
            newCode[25] = 1;
            newCode[131] = 1;
            newCode[131] = 1;
            newCode[133] = 1;
            newCode[135] = 1;
            newCode[137] = 1;
            break;
        case 25:
            newCode[25] = 1;
            newCode[19] = 1;
            break;
        case 26:
            newCode[21] = 1;
            newCode[25] = 1;
            newCode[131] = 1;
            break;
        case 27:
            newCode[19] = 1;
            newCode[21] = 1;
            newCode[25] = 1;
            newCode[133] = 1;
            break;
        case 28:
            newCode[23] = 1;
            newCode[25] = 1;
            newCode[131] = 1;
            newCode[133] = 1;
            break;
        case 29:
            newCode[19] = 1;
            newCode[23] = 1;
            newCode[25] = 1;
            newCode[135] = 1;
            break;
        case 30:
            newCode[21] = 1;
            newCode[23] = 1;
            newCode[25] = 1;
            newCode[131] = 1;
            newCode[135] = 1;
            break;
        }
        break;
    case IRTadiranMode::Humid:
        newCode[3] = 0;
        newCode[5] = 1;
        switch (temperature) {
        case 16:
            newCode[133] = 1;
            newCode[135] = 1;
            break;
        case 17:
            newCode[19] = 1;
            newCode[131] = 1;
            newCode[133] = 1;
            newCode[135] = 1;
            break;
        case 18:
            newCode[21] = 1;
            newCode[137] = 1;
            break;
        case 19:
            newCode[19] = 1;
            newCode[21] = 1;
            newCode[131] = 1;
            newCode[137] = 1;
            break;
        case 20:
            newCode[23] = 1;
            newCode[133] = 1;
            newCode[137] = 1;
            break;
        case 21:
            newCode[19] = 1;
            newCode[23] = 1;
            newCode[131] = 1;
            newCode[133] = 1;
            newCode[137] = 1;
            break;
        case 22:
            newCode[21] = 1;
            newCode[23] = 1;
            newCode[135] = 1;
            newCode[137] = 1;
            break;
        case 23:
            newCode[19] = 1;
            newCode[21] = 1;
            newCode[23] = 1;
            newCode[131] = 1;
            newCode[135] = 1;
            newCode[137] = 1;
            break;
        case 24:
            newCode[25] = 1;
            newCode[133] = 1;
            newCode[135] = 1;
            newCode[137] = 1;
            break;
        case 25:
            newCode[25] = 1;
            newCode[19] = 1;
            newCode[131] = 1;
            newCode[133] = 1;
            newCode[135] = 1;
            newCode[137] = 1;
            break;
        case 26:
            newCode[21] = 1;
            newCode[25] = 1;
            break;
        case 27:
            newCode[19] = 1;
            newCode[21] = 1;
            newCode[25] = 1;
            newCode[131] = 1;
            break;
        case 28:
            newCode[23] = 1;
            newCode[25] = 1;
            newCode[133] = 1;
            break;
        case 29:
            newCode[19] = 1;
            newCode[23] = 1;
            newCode[25] = 1;
            newCode[131] = 1;
            newCode[133] = 1;
            break;
        case 30:
            newCode[21] = 1;
            newCode[23] = 1;
            newCode[25] = 1;
            newCode[135] = 1;
            break;
        }
        break;
    case IRTadiranMode::Recycle:
        newCode[3] = 0;
        newCode[19] = 1;
        newCode[25] = 1;
        newCode[131] = 1;
        newCode[135] = 1;
        newCode[137] = 1;
        break;
    }
    //END modes
    // Fans Speeds
    switch (fan) {
    case IRTadiranFan::Auto: 
            //do nothing
        break;
    case IRTadiranFan::Low: 
        newCode[11] = 1;
        break;
    case IRTadiranFan::Medium: 
        newCode[13] = 1;
        break;
    case IRTadiranFan::High: 
        newCode[11] = 1;
        newCode[13] = 1;
        break;
    case IRTadiranFan::Turbo:
        newCode[11] = 1;
        newCode[13] = 1;
        newCode[15] = 1;
        newCode[43] = 1;
        break;

    } //End Fan speeds
      // Toggles

      // Light
    switch (light) {
    case IRTadiranLight::On:
            //Do Nothing
        break;
    case IRTadiranLight::Off:
        newCode[45] = 0;
        break;
    } //End light
      //swing
    switch (swing) {
    case IRTadiranSwing::Off:
            //do nothing
        break;
    case IRTadiranSwing::OnFull:
        newCode[75] = 1;
        break;
    case IRTadiranSwing::On1:
        newCode[77] = 1;
        break;
    case IRTadiranSwing::On2:
        newCode[75] = 1;
        newCode[77] = 1;
        break;
    case IRTadiranSwing::On3:
        newCode[79] = 1;
        break;
    case IRTadiranSwing::On4:
        newCode[75] = 1;
        newCode[79] = 1;
        break;
    case IRTadiranSwing::On5:
        newCode[77] = 1;
        newCode[79] = 1;
        break;
    case IRTadiranSwing::OnFullLower: 
        newCode[75] = 1;
        newCode[77] = 1;
        newCode[79] = 1;
        break;
    case IRTadiranSwing::OnFullMiddle:
        newCode[81] = 1;
        break;
    case IRTadiranSwing::OnFullUpper:
        newCode[75] = 1;
        newCode[81] = 1;
        break;
    }
    
    //generate insert microseconds
fin:
    for (int i = 0; i<139; i++) {
        switch (newCode[i]) {
        case 0:
            newCode[i] = irLow;
            break;
        case 1:
            newCode[i] = irHigh;
            break;
        case 2:
            newCode[i] = 4400;
            break;
        case 3:
            newCode[i] = 9000;
            break;
        case 4:
            newCode[i] = 20500;
            break;
        }
    }
    //Send Code
    _remote->sendRaw(newCode, 139, 38);
}



