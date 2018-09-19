#include <ir_Trotec.h>
#include <ir_Mitsubishi.h>
#include <ir_LG.h>
#include <ir_Kelvinator.h>
#include <ir_Fujitsu.h>
#include <ir_Daikin.h>
#include <ir_Argo.h>
#include <IRutils.h>
#include <IRtimer.h>
#include <IRsend.h>
#include <IRrecv.h>
#include <DHT_U.h>
#include <DHT.h>
#include <Adafruit_Sensor.h>
#define RAWBUF 101


#include <IRremoteESP8266.h>
//#include "IRelectra.h"
#include <ESP8266mDNS.h>
#include <ESP8266WebServer.h>
#include <WiFiUdp.h>
#include <WiFiServer.h>
#include <WiFiClientSecure.h>
#include <WiFiClient.h>
#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <WiFiUdp.h>
#include <dummy.h>
#include <EEPROM.h>
#include <Arduino.h>
#include "ConfigurationManager.h"
#include "ArduinoLoopManager.h"
#include "PubSub.h"
#include "Singleton.h"
#include "Util.h"
#include "WiFiManager.h"
#include "WebServer.h"
#include "Logger.h"
#include <memory>
#include "Configuration.h"
#include "PushButtonManager.h"
#include "ACManager.h"

using namespace std;

void OnButtonPressed();
void Reset();
void ResetToAccessPointMode();
LoggerPtr_t logger;
WiFiManagerPtr_t wifiManager;
PushButtonManagerPtr_t pushButtonManager;
ACManagerPtr_t acManager;
ArduinoLoopManager_t loopManager;
ConfigurationManager_t configurationManger;
WebServerPtr_t webServer;

void UpdateACState(const ACState& acState)
{
    acManager->SendState(acState);
}

ACState GetACState()
{
    return acManager->GetACState();
}

void SetupWebServer()
{
    Serial.write("1 ********************\n");
    auto deviceSettings = unique_ptr<DeviceSettings>(new DeviceSettings());
    Serial.write("2 ********************\n");
    deviceSettings->isFactoryReset = false;
    deviceSettings->ssidName = configurationManger->GetSSID();
    deviceSettings->accessPointPassword = configurationManger->GetAccessPointPassword();
    deviceSettings->ACNameStr = configurationManger->GetACName();
    deviceSettings->longButtonPeriod = configurationManger->GetLongPeriodButonPressTimesMilliSeconds();
    deviceSettings->veryLongButtonPeriod = configurationManger->GetVeryLongPeriodButonPressTimesMilliSeconds();
    Serial.write("3 ********************\n");
    webServer = WebServer::Create(wifiManager, 80, appKey, move(deviceSettings), UpdateACState, GetACState, ACCapabilities::HasSleepMode /* acManager->GetCapabilities()*/);
    Serial.write("4 ********************\n");
    webServer->SetWebSiteHeader(String(webSiteHeader));
    webServer->SetUpdateConfiguration([](const DeviceSettings& deviceSettings)
    {
        if (deviceSettings.isFactoryReset)
        {
            configurationManger->FacrotyReset();
            return; //never reach this line, the device should reset itself
        }

        configurationManger->SetWiFiCredentials(deviceSettings.ssidName, deviceSettings.accessPointPassword);
        configurationManger->SetButonPressTimesMilliSeconds(deviceSettings.longButtonPeriod, deviceSettings.veryLongButtonPeriod);
        configurationManger->SetACName(deviceSettings.ACNameStr);
        configurationManger->FlashEEProm();
    });
}


class PushButtonActions final : public IPushButtonActions
{
private:
    void OnPress() override { OnButtonPressed(); }
    int GetLongPressPeriod() override { return 5000; } //5 seconds
    void OnLongPressDetected() override { logger->OnLongButtonPressDetection(); }
    void OnLongPress() override { Reset(); }
    int GetVeryLongPressPeriod() override { return 20000; }//20 seconds
    void OnVeryLongPressDetected() override { logger->OnVeryLongButtonPressDetection(); }
    void OnVeryLongPress() override { ResetToAccessPointMode(); }
};

void setup()
{
    configurationManger = ConfigurationManager::Create();

    auto storedSSID = configurationManger->GetSSID();
    auto storedPassword = configurationManger->GetAccessPointPassword();

    logger = Logger::Create(redLed, greenLed, 115200);

    if (!configurationManger->IsAccessPointMode())
    {
        Serial.println("Try to connect to WiFi Access Point");
        Serial.print("Stored SSID is:");
        Serial.println(storedSSID.c_str());

        wifiManager = WiFiManager::Create(storedSSID, storedPassword, false);
    }
    else //Set access point mode
    {
        Serial.println("Create Access Point Mode");
        Serial.print("Stored SSID is:");
        Serial.println(storedSSID.c_str());

        wifiManager = WiFiManager::Create(SSID, password, true);
    }

    wifiManager->RegisterClient([](const ConnectionStatus &status) { logger->OnWiFiStatusChanged(status); });

    acManager = ACManager::Create();

    SetupWebServer();

    pushButtonManager = PushButtonManager::Create(pushButton, make_shared<PushButtonActions>());

    loopManager = ArduinoLoopManager::Create(initializer_list<processor_t>{logger, wifiManager, pushButtonManager, acManager, webServer });

    logger->TestLeds();
    configurationManger->DumpEEPromInfo();
}



void loop()
{
    loopManager->Loop();
}

void OnButtonPressed()
{
    acManager->OnButtonPressed();
}

void ResetToAccessPointMode()
{
    configurationManger->FacrotyReset(); //switch to access point mode and reset the device
}

void Reset()
{
    Util::software_Reboot();
}