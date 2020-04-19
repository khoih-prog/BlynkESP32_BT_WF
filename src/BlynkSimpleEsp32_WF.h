/****************************************************************************************************************************
   BlynkSimpleESP32_WF.h
   For ESP32 using WiFi along with BlueTooth / BLE

   BlynkESP32_BT_WF is a library for inclusion of both ESP32 Blynk BT/BLE and WiFi libraries. Then select either one or both at runtime.
   Forked from Blynk library v0.6.1 https://github.com/blynkkk/blynk-library/releases
   Built by Khoi Hoang https://github.com/khoih-prog/BlynkGSM_ESPManager
   Licensed under MIT license
   Version: 1.0.5

   Original Blynk Library author:
   @file       BlynkSimpleESP32.h
   @author     Volodymyr Shymanskyy
   @license    This project is released under the MIT License (MIT)
   @copyright  Copyright (c) 2015 Volodymyr Shymanskyy
   @date       Oct 2016
   @brief

   Version Modified By   Date      Comments
   ------- -----------  ---------- -----------
    1.0.0   K Hoang      25/01/2020 Initial coding
    1.0.1   K Hoang      27/01/2020 Enable simultaneously running BT/BLE and WiFi
    1.0.2   K Hoang      04/02/2020 Add Blynk WiFiManager support similar to Blynk_WM library
    1.0.3   K Hoang      24/02/2020 Add checksum, clearConfigData()
    1.0.4   K Hoang      14/03/2020 Enhance GUI. Reduce code size.
    1.0.5   K Hoang      18/04/2020 MultiWiFi/Blynk. Dynamic custom parameters. SSID password maxlen is 63 now. 
                                    Permit special chars # and % in input data.
 *****************************************************************************************************************************/

#ifndef BlynkSimpleEsp32_WF_h
#define BlynkSimpleEsp32_WF_h

#ifndef ESP32
#error This code is intended to run on the ESP32 platform! Please check your Tools->Board setting.
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
