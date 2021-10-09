## BlynkESP32_BT_WF

[![arduino-library-badge](https://www.ardu-badge.com/badge/BlynkESP32_BT_WF.svg?)](https://www.ardu-badge.com/BlynkESP32_BT_WF)
[![GitHub release](https://img.shields.io/github/release/khoih-prog/BlynkESP32_BT_WF.svg)](https://github.com/khoih-prog/BlynkESP32_BT_WF/releases)
[![GitHub](https://img.shields.io/github/license/mashape/apistatus.svg)](https://github.com/khoih-prog/BlynkESP32_BT_WF/blob/master/LICENSE)
[![contributions welcome](https://img.shields.io/badge/contributions-welcome-brightgreen.svg?style=flat)](#Contributing)
[![GitHub issues](https://img.shields.io/github/issues/khoih-prog/BlynkESP32_BT_WF.svg)](http://github.com/khoih-prog/BlynkESP32_BT_WF/issues)

---
---

## Table of Contents

* [Changelog](#changelog)
  * [Releases v1.2.2](#releases-v122)
  * [Releases v1.2.1](#releases-v121)
  * [Major Releases v1.2.0](#major-releases-v120)
  * [Releases v1.1.1](#releases-v111)
  * [Major Releases v1.1.0](#major-releases-v110)
  * [Major Releases v1.0.6](#major-releases-v106)
  * [Major Releases v1.0.5](#major-releases-v105)
  * [Releases v1.0.4](#releases-v104)
  * [Releases v1.0.3](#releases-v103)
  * [Releases v1.0.2](#releases-v102)
  * [Releases v1.0.1](#releases-v101)
  * [Releases v1.0.0](#releases-v100)

---
---

## Changelog

### Releases v1.2.2

1. Update `platform.ini` and `library.json` to use original `khoih-prog` instead of `khoih.prog` after PIO fix


### Releases v1.2.1

1. Add auto-reconnect feature for BLE. Check [Handle BLE disconnects #2](https://github.com/khoih-prog/Blynk_Async_ESP32_BT_WF/issues/2)

### Major Releases v1.2.0

 1. Enable scan of WiFi networks for selection in Configuration Portal. Check [PR for v1.3.0 - Enable scan of WiFi networks #10](https://github.com/khoih-prog/WiFiManager_NINA_Lite/pull/10). Now you can select optional **SCAN_WIFI_NETWORKS**, **MANUAL_SSID_INPUT_ALLOWED** to be able to manually input SSID, not only from a scanned SSID lists and **MAX_SSID_IN_LIST** (from 2-15)
 2. Fix invalid "blank" Config Data treated as Valid.
 3. Permit optionally inputting one set of WiFi SSID/PWD by using `REQUIRE_ONE_SET_SSID_PW == true`
 4. Enforce WiFi PWD minimum length of 8 chars
 5. Minor enhancement to not display garbage when data is invalid
 6. Fix issue of custom Blynk port (different from 8080 or 9443) not working on ESP32. Check [Custom Blynk port not working for BlynkSimpleEsp32_Async_WM.h #4](https://github.com/khoih-prog/Blynk_Async_WM/issues/4)
 7. To permit auto-reset after configurable timeout if DRD/MRD or non-persistent forced-CP. Check [**Good new feature: Blynk.resetAndEnterConfigPortal() Thanks & question #27**](https://github.com/khoih-prog/Blynk_WM/issues/27)
 8. Fix rare Config Portal bug not updating Config and dynamic Params data successfully in very noisy or weak WiFi situation
 9. Tested with [**Latest ESP32 Core 1.0.6**](https://github.com/espressif/arduino-esp32) for ESP32-based boards.
10. Update examples

### Releases v1.1.1

1. Add functions to control Config Portal from software or Virtual Switches. Check [How to trigger a Config Portal from code #25](https://github.com/khoih-prog/Blynk_WM/issues/25)
2. Fix rare Config Portal bug not updating Config and dynamic Params data successfully in very noisy or weak WiFi situation
3. To permit autoreset after configurable timeout if DRD/MRD or non-persistent forced-CP. Check [**Good new feature: Blynk.resetAndEnterConfigPortal() Thanks & question #27**](https://github.com/khoih-prog/Blynk_WM/issues/27)

### Major Releases v1.1.0

1. Add support to LittleFS for ESP32 using [LITTLEFS](https://github.com/lorol/LITTLEFS) Library
2. Clean-up all compiler warnings possible.
3. Add Table of Contents
4. Add Version String

### Major Releases v1.0.6

1. Add Configurable **Config Portal Title** to be either HostName, BoardName or default undistinguishable names.
2. Add optional default **Credentials as well as Dynamic parameters to be optionally autoloaded into Config Portal** to use or change instead of manually input using USE_DEFAULT_CONFIG_DATA.
3. Add **DoubleDetectDetector** feature to force Config Portal when double reset is detected within predetermined time, default 10s.
4. Auto format SPIFFS for first time usage.
5. Examples are redesigned to separate Credentials / Defines / Dynamic Params / Code so that you can change Credentials / Dynamic Params quickly for each device.


#### Major Releases v1.0.5

1. **Multiple WiFi Credentials (SSID, Password)** and system will autoconnect to the best and available WiFi SSID.
2. **Multiple Blynk Credentials (Server, Token)** and system will autoconnect to the available Blynk Servers.
3. New **powerful-yet-simple-to-use feature to enable adding dynamic custom parameters** from sketch and input using the same Config Portal. Config Portal will be auto-adjusted to match the number of dynamic parameters.
4. Dynamic custom parameters to be saved **automatically in EEPROM, or SPIFFS**.
5. WiFi Password max length increased to 63 from 31, according to WPA2 standard.
6. Permit to input special chars such as **%** and **#** into data fields.
7. Config Portal AP Channel is configurable (either static or random channel) to avoid channel conflict to other APs.

#### Releases v1.0.4

1. Enhance Config Portal GUI.
2. Reduce code size.

#### Releases v1.0.3

1. Add checksum for config data integrity.
2. Add clearConfigData() to enable forcing into ConfigPortal Mode when necessary
 
#### Releases v1.0.2

This new version enables user to eliminate `hardcoding` your Wifi and Blynk credentials, thanks to the `Smart Config Portal`, and have Credentials (WiFi SID/PW, Blynk WiFi/BT/BLE Tokens/ Hardware Port) saved in either SPIFFS or EEPROM.
See more info at [Blynk_WM](https://github.com/khoih-prog/Blynk_WM)

#### Releases v1.0.1

This new version enables user to include both Blynk BT/BLE and WiFi libraries in one sketch, run both **`WiFi and BT/BLE simultaneously`**, or select one to use at runtime after reboot by pressing a switch.

#### Releases v1.0.0

The Blynk ESP32 libraries for BlueTooth, BLE and WiFi, by design, can't coexist. So that when we'd like to use either WiFi or BlueTooth / BLE, it's not possible within the same sketch.
With this libraries modifications, we now can compile with both options, then select one (WiFi or BT/BLE) to run at run-time by pressing a switch.


