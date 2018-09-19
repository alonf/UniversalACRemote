// WebServer.h

#ifndef _WEBSERVER_h
#define _WEBSERVER_h

#include "Arduino.h"
#include <ESP8266WebServer.h>
#undef ARDUINO_BOARD
#define ARDUINO_BOARD "generic"
#include <ESP8266mDNS.h>
#include <String>
#include <memory>
#include "WiFiManager.h"
#include "Singleton.h"
#include "PubSub.h"
#include "ArduinoLoopManager.h"
#include "Util.h"
#include "DHTReader.h"
#include "ACTypes.h"
#include "ACCapabilities.h"

struct DeviceSettings
{
	bool isFactoryReset;
	String ssidName;
	String accessPointPassword;
	String ACNameStr;
	unsigned int longButtonPeriod;
	unsigned int veryLongButtonPeriod;
};

class P
{
public:
    P(int i = 0)
    {
        Serial.write(i);
        Serial.write(")************* :( :(\n");
    }
};



typedef std::function<void(const String&, int)> WebNotificationPtr_t;
class WebServer : public Singleton<WebServer>, public IProcessor
{
	friend class Singleton<WebServer>;
private:
    P p {};
	char _htmlBuffer[3600]{}; //for setup html result
	std::unique_ptr<DeviceSettings> _deviceSettings{};
	ESP8266WebServer _server;
	PubSub<WebServer, const String&, int> _pubsub;
	String _header;
	const String _authorizedUrl;
	bool _isInit = false;
	std::function<void(const DeviceSettings&)> _configurationUpdater;
	DHTReader _dhtReader;

	Util::StringMap _templateValuesMap;
    Util::Map<String, ACMode> _ACText2ModeMap = { {"AUTO", ACMode::Auto}, {"COOL", ACMode::Cool}, {"HEAT", ACMode::Heat}, {"FAN", ACMode::Fan}, {"DRY", ACMode::Dry}, { "HUMID", ACMode::Humid },{ "RECYCLE", ACMode::Recycle } };
    Util::Map<String, ACFan> _ACText2FanMap = { { "AUTO", ACFan::Auto },{ "HIGH", ACFan::High },{ "LOW", ACFan::Low },{ "MEDIUM", ACFan::Medium },{ "TURBO", ACFan::Turbo } };
    Util::Map<String, ACExtendedSwingMode> _ACText2ExtendedSwingModeMap = { { "OFF", ACExtendedSwingMode::Off }, {"ONFULL", ACExtendedSwingMode::OnFull }, {"ON1", ACExtendedSwingMode::On1}, {"ON2", ACExtendedSwingMode::On2 },{ "ON3", ACExtendedSwingMode::On3 },{ "ON4", ACExtendedSwingMode::On4},{ "ON5", ACExtendedSwingMode::On5 },{ "ONFULLLOWER", ACExtendedSwingMode::OnFullLower},{ "ONFULLMIDDLE", ACExtendedSwingMode::OnFullMiddle },{ "ONFULLUPPER", ACExtendedSwingMode::OnFullUpper} };
    Util::Map<ACMode, String> _ACMode2TextMap = { { ACMode::Auto, "auto" },{ ACMode::Cool, "cool" },{ ACMode::Heat, "heat" },{ ACMode::Fan, "fan" },{ ACMode::Dry, "dry" },{ ACMode::Humid, "humid" },{ ACMode::Recycle, "recycle" } };
    Util::Map<ACFan, String> _ACFan2TextMap = { { ACFan::Auto, "auto" },{ ACFan::High, "high" },{ ACFan::Low, "low" },{ ACFan::Medium, "medium" }, { ACFan::Turbo, "turbo" } };
    Util::Map<ACExtendedSwingMode, String> _ACExtendedSwingMode2TextMap = { {ACExtendedSwingMode::Off, "off"},{ ACExtendedSwingMode::On1, "on1" },{ ACExtendedSwingMode::On2, "on2" },{ ACExtendedSwingMode::On3, "on3" },{ ACExtendedSwingMode::On4, "on4" },{ ACExtendedSwingMode::On5, "on5" },{ ACExtendedSwingMode::OnFullLower, "OnFullLower" },{ ACExtendedSwingMode::OnFullMiddle, "OnFullMiddle" }, { ACExtendedSwingMode::OnFullUpper, "OnFullUpper" } };
    const ACCapabilities _acCapabilities;
    void SendBackHtml(const String &message);
	void UpdateStatus(ConnectionStatus status);
	std::function<ACState()> GetCurrentACState;
	String CreateUrl(const String &s) const;
	bool GetServerArgBoolValue(const String &argName, ACCapabilities capability);
	void ProcessHTTPACView();
	std::function<void(const ACState &)> UpdateACState;

	void PopulateHTMLSetupFromTemplate(const String& htmlTemplate, const Util::StringMap &map);
	WebServer(WiFiManagerPtr_t wifiManager, int port, const char *appKey, std::unique_ptr<DeviceSettings> deviceSettings, std::function<void (const ACState&)> updateACState, std::function<ACState()> getCurrentACState, ACCapabilities acCapabilities);
	void HandleMain();
	void ProcessHTTPSetupRequest();
	void HandleSendAPScript();
	void HandleSetup();
	void HandleSendViewCSS();
	void HandleSendAPList();
	void HandleSetConfiguration();
	void HandleResetAccessPoint();
	void HandleError();
	bool CheckSecurity();
	void SendACState();
	static bool GetSimpleJsonEntry(const String& text, String& variable, String& value, int& lastIndex);
	static void PopulateJsonStringMap(const String& body, Util::Map<String, String>& result);
	void SetACState();
	void HandleGetCurrentTemperature();
	void GetACState();
	void SetACOnState(bool action);
	void TurnOn();
	void TurnOff();

public:
	template<typename T>
	void SetWebSiteHeader(T header) { _header = std::forward<T>(header); }
	void Register(WebNotificationPtr_t subscriber) { _pubsub.Register(subscriber); }
	bool IsConnected() const;
	void Loop() override;
	void SetUpdateConfiguration(std::function<void(const DeviceSettings&)> configurationUpdater);
};

typedef std::shared_ptr<WebServer> WebServerPtr_t;
#endif

