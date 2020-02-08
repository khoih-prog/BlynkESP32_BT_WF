## BlynkESP32_BT_WF

[![arduino-library-badge](https://www.ardu-badge.com/badge/BlynkESP32_BT_WF.svg?)](https://www.ardu-badge.com/BlynkESP32_BT_WF)

By design, Blynk user can run ESP32 boards with either WiFi or BT/BLE by using different sketches, and have to upload / update firmware to change. This library enables user to include both Blynk BT / BLE and WiFi libraries in one sketch, run both WiFi and BT/BLE simultaneously, or select one to use at runtime after reboot.

Now from Version 1.0.2, you can eliminate `hardcoding` your Wifi and Blynk credentials, thanks to the `Smart Config Portal`, and have Credentials (WiFi SID/PW, Blynk WiFi/BT/BLE Tokens/ Hardware Port) saved in either SPIFFS or EEPROM.


### Installation

#### Use Arduino Library Manager
The suggested and easiest way is to use `Arduino Library Manager`. Search for `BlynkESP32_BT_WF`, then select / install the latest version.

#### Manual Install

The suggested way to install manually is to:

1. Navigate to [BlynkESP32_BT_WF](https://github.com/khoih-prog/BlynkESP32_BT_WF) page.
2. Download the latest release `BlynkESP32_BT_WF-master.zip`.
3. Extract the zip file to `BlynkESP32_BT_WF-master` directory 
4. Copy whole `BlynkESP32_BT_WF-master` folder to Arduino libraries' directory such as `~/Arduino/libraries`.


### How to use

In your code, replace
1. `BlynkSimpleEsp32_BT.h`    with `BlynkSimpleEsp32_BT_WF.h`
2. `BlynkSimpleEsp32_BLE.h`   with `BlynkSimpleEsp32_BLE_WF.h`
3. 
  - `BlynkSimpleEsp32.h`       with `BlynkSimpleEsp32_WFM.h` if ***using*** WiFiManager's Config Portal features
  - `BlynkSimpleEsp32.h`       with `BlynkSimpleEsp32_WF.h`  if ***not using*** WiFiManager's Config Portal features
  
4. Then replace WiFi's `Blynk.begin(...)` with :

  - `Blynk_WF.begin()` to use default DHCP hostname `ESP8266-XXXXXX` or `ESP32-XXXXXX`

  - or to have a personalized hostname `(RFC952-conformed,- 24 chars max,- only a..z A..Z 0..9 '-' and no '-' as last char)`

    `Blynk_WF.begin("Personalized-HostName")`

5. `Blynk.run();`             with `Blynk_WF.run()` for WiFi related function calls
6. `Blynk.run();`             with `Blynk_BT.run()` for BlueTooth related function calls
or 
7. `Blynk.run();`             with `Blynk_BLE.run()` for BLE related function calls


That's it.

Also see examples: 
1. [ESP32_BLE_WF](examples/ESP32_BLE_WF)
2. [ESP32_BT_WF](examples/ESP32_BT_WF)
3. [Geiger_Counter_BLE](examples/Geiger_Counter_BLE)
4. [Geiger_Counter_BT](examples/Geiger_Counter_BT)
5. [Geiger_Counter_OLED](examples/Geiger_Counter_OLED)
6. [Geiger_Counter_OLED_BT_WF](examples/Geiger_Counter_OLED_BT_WF)
7. [Geiger_Counter_OLED_BT_BLE_WF](examples/Geiger_Counter_OLED_BT_BLE_WF)

and real-life project [Hack GMC Geigercounter With Blynk](https://www.instructables.com/id/Hack-GMC-Geigercounter-With-Blynk/) of [Crosswalkersam](https://www.instructables.com/member/Crosswalkersam/)

<p align="center">
    <img src="https://github.com/khoih-prog/BlynkESP32_BT_WF/blob/master/examples/Geiger_Counter_OLED/pics/Box1.jpg">
</p>

<p align="center">
    <img src="https://github.com/khoih-prog/BlynkESP32_BT_WF/blob/master/examples/Geiger_Counter_OLED/pics/Box2.jpg">
</p>

<p align="center">
    <img src="https://github.com/khoih-prog/BlynkESP32_BT_WF/blob/master/examples/Geiger_Counter_OLED/pics/Schematics.jpg">
</p>

<p align="center">
    <img src="https://github.com/khoih-prog/BlynkESP32_BT_WF/blob/master/examples/Geiger_Counter_OLED/pics/Blynk.jpg">
</p>


## So, how it works?
If the necessary credentials are not valid or it cannot connect to the Blynk server in 30 seconds, it will switch to `Configuration Mode`. You will see your built-in LED turned ON. In `Configuration Mode`, it starts an access point called `ESP_xxxxxx`. Connect to it using password `MyESP_xxxxxx` .

<p align="center">
    <img src="https://github.com/khoih-prog/BlynkESP32_BT_WF/blob/master/pics/WiFi_AP.jpg">
</p>

After you connected, please, go to http://192.168.4.1.

<p align="center">
    <img src="https://github.com/khoih-prog/BlynkESP32_BT_WF/blob/master/pics/ConfigPortal.png">
</p>

Enter your credentials, then click `Save`. After you restarted, you will see your built-in LED turned OFF. That means, it connected to your Blynk server successfully.


## Prerequisite
* Release `1.0.4` or newer of the [ESP32 core for Arduino](https://github.com/espressif/arduino-esp32)
* [`Blynk library 0.6.1 or later`](https://github.com/blynkkk/blynk-library/releases)

## Sample code
```
#define BLYNK_PRINT Serial

#define USE_BLYNK_WM      true
//#define USE_BLYNK_WM      false

#define USE_SPIFFS        true
//#define USE_SPIFFS      false

#if (!USE_SPIFFS)
  // EEPROM_SIZE must be <= 2048 and >= CONFIG_DATA_SIZE
  #define EEPROM_SIZE    (2 * 1024)
  // EEPROM_START + CONFIG_DATA_SIZE must be <= EEPROM_SIZE
  #define EEPROM_START   768
#endif

// Force some params in Blynk, only valid for library version 1.0.1 and later
#define TIMEOUT_RECONNECT_WIFI                    10000L
#define RESET_IF_CONFIG_TIMEOUT                   true
#define CONFIG_TIMEOUT_RETRYTIMES_BEFORE_RESET    5
// Those above #define's must be placed before #include <BlynkSimpleEsp32_WFM.h>

//#define BLYNK_USE_BLE_ONLY      true
#define BLYNK_USE_BLE_ONLY      false

#include <BlynkSimpleEsp32_BLE_WF.h>
#include <BLEDevice.h>
#include <BLEServer.h>

#if !BLYNK_USE_BLE_ONLY
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

#if (BLYNK_USE_BLE_ONLY || !USE_BLYNK_WM)
  // Blynk token shared between BLE and WiFi
  char auth[] = "****";
#endif

bool USE_BLE = true;

void setup()
{
  Serial.begin(115200);
  Serial.println(F("\nStarting ESP32_BLE_WF"));

  pinMode(WIFI_BLE_SELECTION_PIN, INPUT);
 
#if BLYNK_USE_BLE_ONLY
  Blynk_BLE.setDeviceName(BLE_Device_Name);
  Blynk_BLE.begin(auth);
#else
  if (digitalRead(WIFI_BLE_SELECTION_PIN) == HIGH)
  {
    USE_BLE = false;
    Serial.println(F("GPIO14 HIGH, Use WiFi"));
    #if USE_BLYNK_WM
      Blynk_WF.begin(BLE_Device_Name);
    #else
      Blynk_WF.begin(auth, ssid, pass, cloudBlynkServer.c_str(), BLYNK_SERVER_HARDWARE_PORT);
    #endif
  }
  else
  {
    USE_BLE = true;
    Serial.println(F("GPIO14 LOW, Use BLE"));
    Blynk_BLE.setDeviceName(BLE_Device_Name);
    #if USE_BLYNK_WM
      if (Blynk_WF.getBlynkBLEToken() == String("nothing"))
      {
        Serial.println(F("No valid stored BLE auth. Have to run WiFi then enter config portal"));
        USE_BLE = false;
        Blynk_WF.begin(BLE_Device_Name);
      }
      String BLE_auth = Blynk_WF.getBlynkBLEToken();
    #else
      String BLE_auth = auth;
    #endif

    if (USE_BLE)
    {
      Serial.print(F("Connecting Blynk via BLE, using auth = "));
      Serial.println(BLE_auth);
      Blynk_BLE.begin(BLE_auth.c_str());
    }
  }
#endif
}

void loop()
{
#if BLYNK_USE_BLE_ONLY
  Blynk_BLE.run();
#else
  if (USE_BLE)
    Blynk_BLE.run();
  else
    Blynk_WF.run();
#endif
}
```

and this is the terminal debug output when running both WiFi and BT at the same time using example  [ESP32_BLE_WF](examples/ESP32_BLE_WF)

```

Starting ESP32_BLE_WF
GPIO14 LOW, Use BLE
[51] Load configfile 
[52] OK
[52] Header = ESP32_WFM, SSID = ***, PW = ***
[52] Server = account.duckdns.org, Port = 8080, Token = ****
[56] BT Token = ****, BLE Token = ****
[64] Board Name = Geiger-OLED-BLE-BT
Connecting Blynk via BLE, using auth = ****
[149] 
    ___  __          __
   / _ )/ /_ _____  / /__
  / _  / / // / _ \/  '_/
 /____/_/\_, /_//_/_/\_\
        /___/ v0.6.1 on ESP32

[75491] BLE connect
[77327] Ready

```

## DONE

  1. Permit EEPROM size and location configurable to avoid conflict with others.
  2. More flexible to configure reconnection timeout.
  3. For fresh config data, don't need to wait for connecting timeout before entering config portal.
  4. If the config data not entered completely (SSID, password, Server and Blynk tokens), entering config portal
  5. Correct the operation of BUILTIN_LED
  6. Reduce EEPROM size to 2K from 4K to avoid ESP_ERR_NVS_NOT_ENOUGH_SPACE error.
  7. Add RFC952 hostname
  8. Add configurable Config Portal IP, SSID and Password
  9. Add configurable Static IP, GW, Subnet Mask and 2 DNS Servers' IP Addresses.
 10. Use dynamically alocated Config Portal WebServer
 11. Fix BT/BLE login timeout
 
### Releases v1.0.2

***Why this version***

This new version enables user to eliminate `hardcoding` your Wifi and Blynk credentials, thanks to the `Smart Config Portal`, and have Credentials (WiFi SID/PW, Blynk WiFi/BT/BLE Tokens/ Hardware Port) saved in either SPIFFS or EEPROM.
See more info at [Blynk_WM](https://github.com/khoih-prog/Blynk_WM)

### Releases v1.0.1

***Why this version***

This new version enables user to include both Blynk BT/BLE and WiFi libraries in one sketch, run both ***`WiFi and BT/BLE simultaneously`***, or select one to use at runtime after reboot by pressing a switch.

### Releases v1.0.0

***Why this version***

The Blynk ESP32 libraries for BlueTooth, BLE and WiFi, by design, can't coexist. So that when we'd like to use either WiFi or BlueTooth / BLE, it's not possible within the same sketch.
With this libraries modifications, we now can compile with both options, then select one (WiFi or BT/BLE) to run at run-time by pressing a switch.

## TO DO

1. Same features for other boards with WiFi / BT
2. Optimize library so that smaller code size. Currently 2 instances of Blynk coexist and don't share code.

### Contributions and thanks
1. Thanks to [Crosswalkersam](https://community.blynk.cc/u/Crosswalkersam) for the original code and request to inspire the work.

## Contributing

If you want to contribute to this project:
- Report bugs and errors
- Ask for enhancements
- Create issues and pull requests
- Tell other people about this library

## Copyright

Copyright 2020- Khoi Hoang
