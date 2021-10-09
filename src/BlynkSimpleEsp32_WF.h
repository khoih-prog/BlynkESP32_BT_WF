/****************************************************************************************************************************
  BlynkSimpleESP32_WF.h
  For ESP32 using WiFiManager and WiFi along with BlueTooth / BLE

  BlynkESP32_BT_WF is a library for inclusion of both ESP32 Blynk BT/BLE and WiFi libraries. 
  Then select either one or both at runtime.

  Based on and modified from Blynk library v0.6.1 https://github.com/blynkkk/blynk-library/releases
  Built by Khoi Hoang https://github.com/khoih-prog/BlynkESP32_BT_WF
  Licensed under MIT license

  Original Blynk Library author:
  @file       BlynkSimpleESP32.h
  @author     Volodymyr Shymanskyy
  @license    This project is released under the MIT License (MIT)
  @copyright  Copyright (c) 2015 Volodymyr Shymanskyy
  @date       Oct 2016
  @brief

  Version: 1.2.2

  Version Modified By   Date      Comments
  ------- -----------  ---------- -----------
  1.0.0   K Hoang      25/01/2020 Initial coding
  1.0.1   K Hoang      27/01/2020 Enable simultaneously running BT/BLE and WiFi
  1.0.2   K Hoang      04/02/2020 Add Blynk WiFiManager support similar to Blynk_WM library
  1.0.3   K Hoang      24/02/2020 Add checksum, clearConfigData()
  1.0.4   K Hoang      14/03/2020 Enhance GUI. Reduce code size.
  1.0.5   K Hoang      18/04/2020 MultiWiFi/Blynk. Dynamic custom parameters. SSID password maxlen is 63 now. 
                                  Permit special chars # and % in input data.
  1.0.6   K Hoang      24/08/2020 Add Configurable Config Portal Title, Add USE_DEFAULT_CONFIG_DATA and DRD.
                                  Auto format SPIFFS. Update examples.
  1.1.0   K Hoang      30/12/2020 Add support to LittleFS. Remove possible compiler warnings. Update examples
  1.1.1   K Hoang      31/01/2021 Add functions to control Config Portal (CP) from software or Virtual Switches
                                  Fix CP and Dynamic Params bugs. To permit autoreset after timeout if DRD/MRD or forced CP   
  1.2.0   K Hoang      24/04/2021 Enable scan of WiFi networks for selection in Configuration Portal and many new features.
  1.2.1   K Hoang      13/08/2021 Add auto-reconnect feature for BLE
  1.2.2    K Hoang      13/08/2021 Update `platform.ini` and `library.json` 
 *****************************************************************************************************************************/

#pragma once

#ifndef BlynkSimpleEsp32_WF_h
#define BlynkSimpleEsp32_WF_h

#if !( defined(ESP32) )
  #error This code is intended to run on the ESP32 platform! Please check your Tools->Board setting.
#elif ( ARDUINO_ESP32S2_DEV || ARDUINO_FEATHERS2 || ARDUINO_ESP32S2_THING_PLUS || ARDUINO_MICROS2 || \
        ARDUINO_METRO_ESP32S2 || ARDUINO_MAGTAG29_ESP32S2 || ARDUINO_FUNHOUSE_ESP32S2 || \
        ARDUINO_ADAFRUIT_FEATHER_ESP32S2_NOPSRAM )
  #define BOARD_TYPE      "ESP32-S2"
  #error ESP32-S2 is not supported yet. Please check later.
#elif ( ARDUINO_ESP32C3_DEV )
  #define BOARD_TYPE      "ESP32-C3"
  #error ESP32-C3 is not supported yet. Please check later.
#else
  #define BOARD_TYPE      "ESP32"
#endif

#if !defined(BLYNK_ESP32_BT_WF_VERSION)
  #define BLYNK_ESP32_BT_WF_VERSION       "BlynkESP32_BT_WF v1.2.2"
#endif

#define BLYNK_SEND_ATOMIC

// KH
#define BLYNK_TIMEOUT_MS     30000UL

#include <BlynkApiArduino.h>
#include <Blynk/BlynkProtocol.h>
#include <Adapters/BlynkArduinoClient.h>
#include <WiFi.h>

class BlynkWifi
  : public BlynkProtocol<BlynkArduinoClient>
{
    typedef BlynkProtocol<BlynkArduinoClient> Base;
  public:
    BlynkWifi(BlynkArduinoClient& transp)
      : Base(transp)
    {}

    void connectWiFi(const char* ssid, const char* pass)
    {
      BLYNK_LOG2(BLYNK_F("Con2:"), ssid);
      WiFi.mode(WIFI_STA);
      if (pass && strlen(pass)) {
        WiFi.begin(ssid, pass);
      } else {
        WiFi.begin(ssid);
      }
      while (WiFi.status() != WL_CONNECTED) {
        BlynkDelay(500);
      }
      BLYNK_LOG1(BLYNK_F("Con2WiFi"));

      IPAddress myip = WiFi.localIP();
      BLYNK_LOG_IP("IP:", myip);
    }

    void config(const char* auth,
                const char* domain = BLYNK_DEFAULT_DOMAIN,
                uint16_t    port   = BLYNK_DEFAULT_PORT)
    {
      Base::begin(auth);
      this->conn.begin(domain, port);
    }

    void config(const char* auth,
                IPAddress   ip,
                uint16_t    port = BLYNK_DEFAULT_PORT)
    {
      Base::begin(auth);
      this->conn.begin(ip, port);
    }

    void begin(const char* auth,
               const char* ssid,
               const char* pass,
               const char* domain = BLYNK_DEFAULT_DOMAIN,
               uint16_t    port   = BLYNK_DEFAULT_PORT)
    {
      connectWiFi(ssid, pass);
      config(auth, domain, port);
      while (this->connect() != true) {}
    }

    void begin(const char* auth,
               const char* ssid,
               const char* pass,
               IPAddress   ip,
               uint16_t    port   = BLYNK_DEFAULT_PORT)
    {
      connectWiFi(ssid, pass);
      config(auth, ip, port);
      while (this->connect() != true) {}
    }

};

static WiFiClient _blynkWifiClient;
static BlynkArduinoClient _blynkTransport(_blynkWifiClient);

// KH
BlynkWifi Blynk_WF(_blynkTransport);

#if defined(Blynk)
#undef Blynk
#define Blynk Blynk_WF
#endif
//

#include <BlynkWidgets.h>

#endif
