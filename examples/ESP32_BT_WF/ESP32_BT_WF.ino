/****************************************************************************************************************************
   ESP32_BT_WF.ino
   For ESP32 using WiFi along with BlueTooth BT

   BlynkESP32_BT_WF is a library for inclusion of both ESP32 Blynk BT/BLE and WiFi libraries. Then select either one or both at runtime.
   Forked from Blynk library v0.6.1 https://github.com/blynkkk/blynk-library/releases
   Built by Khoi Hoang https://github.com/khoih-prog/BlynkGSM_ESPManager
   Licensed under MIT license
   Version: 1.0.4

   Based on orignal code by Crosswalkersam (https://community.blynk.cc/u/Crosswalkersam)
   posted in https://community.blynk.cc/t/select-connection-type-via-switch/43176
   Purpose: Use WiFi when posible by GPIO14 => HIGH or floating when reset.
            Use Bluetooth when WiFi not available (such as in the field) by by GPIO14 => LOW when reset.

   Version Modified By   Date      Comments
   ------- -----------  ---------- -----------
    1.0.0   K Hoang      25/01/2020 Initial coding
    1.0.1   K Hoang      27/01/2020 Enable simultaneously running BT/BLE and WiFi
    1.0.2   K Hoang      04/02/2020 Add Blynk WiFiManager support similar to Blynk_WM library
    1.0.3   K Hoang      24/02/2020 Add checksum, clearConfigData()
    1.0.4   K Hoang      14/03/2020 Enhance GUI. Reduce code size.
 *****************************************************************************************************************************/

#ifndef ESP32
#error This code is intended to run on the ESP32 platform! Please check your Tools->Board setting.
#endif

#define BLYNK_PRINT Serial

#define USE_BLYNK_WM      true
//#define USE_BLYNK_WM      false

#define USE_SPIFFS                  true
//#define USE_SPIFFS                  false

#if (!USE_SPIFFS)
// EEPROM_SIZE must be <= 2048 and >= CONFIG_DATA_SIZE
#define EEPROM_SIZE    (2 * 1024)
// EEPROM_START + CONFIG_DATA_SIZE must be <= EEPROM_SIZE
#define EEPROM_START   512
#endif

// Force some params in Blynk, only valid for library version 1.0.1 and later
#define TIMEOUT_RECONNECT_WIFI                    10000L
#define RESET_IF_CONFIG_TIMEOUT                   true
#define CONFIG_TIMEOUT_RETRYTIMES_BEFORE_RESET    5
// Those above #define's must be placed before #include <BlynkSimpleEsp32_WFM.h>

//#define BLYNK_USE_BT_ONLY      true
#define BLYNK_USE_BT_ONLY      false

#if BLYNK_USE_BT_ONLY
#include <BlynkSimpleEsp32_BT_WF.h>
#else
#include <BlynkSimpleEsp32_BT_WF.h>
#if USE_BLYNK_WM
#warning Please select 1.3MB+ for APP (Minimal SPIFFS (1.9MB APP, OTA), HugeAPP(3MB APP, NoOTA) or NoOA(2MB APP)
#include <BlynkSimpleEsp32_WFM.h>
#else
#include <BlynkSimpleEsp32_WF.h>

String cloudBlynkServer = "account.duckdns.org";
//String cloudBlynkServer = "192.168.2.110";
#define BLYNK_SERVER_HARDWARE_PORT    8080
char ssid[] = "SSID";
char pass[] = "PASS";
#endif
#endif

#if (BLYNK_USE_BT_ONLY || !USE_BLYNK_WM)
// Blynk token shared between BT and WiFi
char auth[] = "****";
#endif

bool USE_BT = true;
long timePreviousMeassure  = 0;

#define WIFI_BT_SELECTION_PIN      14   //Pin D14 mapped to pin GPIO14/HSPI_SCK/ADC16/TOUCH6/TMS of ESP32

#define MEASURE_INTERVAL_MS           20000L

void checkStatus()
{
  if (millis() - timePreviousMeassure > MEASURE_INTERVAL_MS)
  {
    if (!USE_BT)
    {
      if (Blynk.connected())
        Serial.println(F("B"));
      else
        Serial.println(F("F"));
    }

    timePreviousMeassure = millis();
  }
}

char BT_Device_Name[] = "GeigerCounter-BT";

void setup()
{
  Serial.begin(115200);
  Serial.println(F("\nStarting Geiger-Counter"));

  pinMode(WIFI_BT_SELECTION_PIN, INPUT);

#if BLYNK_USE_BT_ONLY
  Blynk_BT.setDeviceName(BT_Device_Name);
  Blynk_BT.begin(auth);
#else
  if (digitalRead(WIFI_BT_SELECTION_PIN) == HIGH)
  {
    USE_BT = false;
    Serial.println(F("GPIO14 HIGH, Use WiFi"));
#if USE_BLYNK_WM
    Blynk_WF.begin(BT_Device_Name);
#else
    //Blynk_WF.begin(auth, ssid, pass);
    Blynk_WF.begin(auth, ssid, pass, cloudBlynkServer.c_str(), BLYNK_SERVER_HARDWARE_PORT);
#endif
  }
  else
  {
    USE_BT = true;
    Serial.println(F("GPIO14 LOW, Use BT"));
    Blynk_BT.setDeviceName(BT_Device_Name);
#if USE_BLYNK_WM
    if (Blynk_WF.getBlynkBTToken() == String("nothing"))
    {
      Serial.println(F("No valid stored BT auth. Have to run WiFi then enter config portal"));
      USE_BT = false;
      Blynk_WF.begin(BT_Device_Name);
    }
    String BT_auth = Blynk_WF.getBlynkBTToken();
#else
    String BT_auth = auth;
#endif

    if (USE_BT)
    {
      Serial.print(F("Connecting Blynk via BT, using auth = "));
      Serial.println(BT_auth);
      Blynk_BT.begin(BT_auth.c_str());
    }
  }
#endif
}

void loop()
{
#if BLYNK_USE_BT_ONLY
  Blynk_BT.run();
#else
  if (USE_BT)
    Blynk_BT.run();
  else
    Blynk_WF.run();
#endif

  checkStatus();
}
