## BlynkESP32_BT_WF

[![arduino-library-badge](https://www.ardu-badge.com/badge/BlynkESP32_BT_WF.svg?)](https://www.ardu-badge.com/BlynkESP32_BT_WF)
[![GitHub release](https://img.shields.io/github/release/khoih-prog/BlynkESP32_BT_WF.svg)](https://github.com/khoih-prog/BlynkESP32_BT_WF/releases)
[![GitHub](https://img.shields.io/github/license/mashape/apistatus.svg)](https://github.com/khoih-prog/BlynkESP32_BT_WF/blob/master/LICENSE)
[![contributions welcome](https://img.shields.io/badge/contributions-welcome-brightgreen.svg?style=flat)](#Contributing)
[![GitHub issues](https://img.shields.io/github/issues/khoih-prog/BlynkESP32_BT_WF.svg)](http://github.com/khoih-prog/BlynkESP32_BT_WF/issues)

---
---

## Table of Contents

* [Important Note](#important-note)
* [Why do we need the new Async Blynk_Async_ESP32_BT_WF library](#why-do-we-need-the-new-async-blynk_async_esp32_bt_wf-library)
* [Why do we need this BlynkESP32_BT_WF library](#why-do-we-need-this-blynkesp32_bt_wf-library)
  * [Features](#features)
  * [Currently supported Boards](#currently-supported-boards)
  * [Not yet supported Boards](#not-yet-supported-boards)
* [Changelog](changelog.md)
* [Prerequisites](#prerequisites)
* [Installation](#installation)
  * [Use Arduino Library Manager](#use-arduino-library-manager)
  * [Manual Install](#manual-install)
  * [VS Code & PlatformIO](#vs-code--platformio)
* [Note for Platform IO using ESP32 LittleFS](#note-for-platform-io-using-esp32-littlefs)
* [HOWTO Use analogRead() with ESP32 running WiFi and/or BlueTooth (BT/BLE)](#howto-use-analogread-with-esp32-running-wifi-andor-bluetooth-btble)
  * [1. ESP32 has 2 ADCs, named ADC1 and ADC2](#1--esp32-has-2-adcs-named-adc1-and-adc2)
  * [2. ESP32 ADCs functions](#2-esp32-adcs-functions)
  * [3. ESP32 WiFi uses ADC2 for WiFi functions](#3-esp32-wifi-uses-adc2-for-wifi-functions)
* [How to use](#how-to-use)
* [HOWTO use default Credentials and have them pre-loaded onto Config Portal](#howto-use-default-credentials-and-have-them-pre-loaded-onto-config-portal)
  * [ 1. To load Default Credentials](#1-to-load-default-credentials)
  * [ 2. To use system default to load "blank" when there is no valid Credentials](#2-to-use-system-default-to-load-blank-when-there-is-no-valid-credentials)
  * [ 3. Example of Default Credentials](#3-example-of-default-credentials)
  * [ 4. How to add dynamic parameters from sketch](#4-how-to-add-dynamic-parameters-from-sketch)
  * [ 5. If you don't need to add dynamic parameters](#5-if-you-dont-need-to-add-dynamic-parameters)
  * [ 6. To use custom HTML Style](#6-to-use-custom-html-style)
  * [ 7. To use custom Head Elements](#7-to-use-custom-head-elements)
  * [ 8. To use CORS Header](#8-to-use-cors-header)
  * [ 9. To use and input only one set of WiFi SSID and PWD](#9-to-use-and-input-only-one-set-of-wifi-ssid-and-pwd)
    * [ 9.1 If you need to use and input only one set of WiFi SSID/PWD](#91-if-you-need-to-use-and-input-only-one-set-of-wifi-ssidpwd)
    * [ 9.2 If you need to use both sets of WiFi SSID/PWD](#92-if-you-need-to-use-both-sets-of-wifi-ssidpwd)
  * [10. To enable auto-scan of WiFi networks for selection in Configuration Portal](#10-to-enable-auto-scan-of-wifi-networks-for-selection-in-configuration-portal)
    * [10.1 Enable auto-scan of WiFi networks for selection in Configuration Portal](#101-enable-auto-scan-of-wifi-networks-for-selection-in-configuration-portal)
    * [10.2 Disable manually input SSIDs](#102-disable-manually-input-ssids)
    * [10.3 Select maximum number of SSIDs in the list](#103-select-maximum-number-of-ssids-in-the-list)
* [Why using this BlynkESP32_BT_WF with MultiWiFi-MultiBlynk features](#why-using-this-blynkesp32_bt_wf-with-multiwifi-multiblynk-features)
* [Important Notes for using Dynamic Parameters' ids](#important-notes-for-using-dynamic-parameters-ids)
* [Examples](#examples)
  * [ 1. ESP32_BLE_WF](examples/ESP32_BLE_WF)
  * [ 2. ESP32_BT_WF](examples/ESP32_BT_WF)
  * [ 3. Geiger_Counter_BLE](examples/Geiger_Counter_BLE)
  * [ 4. Geiger_Counter_BT](examples/Geiger_Counter_BT)
  * [ 5. Geiger_Counter_OLED](examples/Geiger_Counter_OLED)
  * [ 6. Geiger_Counter_OLED_BT_WF](examples/Geiger_Counter_OLED_BT_WF)
  * [ 7. Geiger_Counter_OLED_BT_BLE_WF](examples/Geiger_Counter_OLED_BT_BLE_WF)
  * [ 8. PET_Check](examples/PET_Check)
* [So, how it works?](#so-how-it-works)
  * [ 1. Without SCAN_WIFI_NETWORKS](#1-without-scan_wifi_networks)
  * [ 2. With SCAN_WIFI_NETWORKS](#2-with-scan_wifi_networks)
* [Example ESP32_BLE_WF](#example-esp32_ble_wf)
  * [1. File ESP32_BLE_WF.ino](#1-file-esp32_ble_wfino)
  * [2. File defines.h](#2-file-definesh) 
  * [3. File Credentials.h](#3-file-credentialsh) 
  * [4. File dynamicParams.h](#4-file-dynamicparamsh) 
* [Debug Terminal Output Samples](#debug-terminal-output-samples)
  * [1. ESP32_BLE_WF on ESP32_DEV](#1-esp32_ble_wf-on-esp32_dev)
    * [1.1. No Config Data => Config Portal. Input valid credentials => reboot](#11-no-config-data--config-portal-input-valid-credentials--reboot)
    * [1.2. DRD => Config Portal. Input valid credentials => reboot](#12-drd--config-portal-input-valid-credentials--reboot) 
    * [1.3. After inputting valid credentials and reboot](#13-after-inputting-valid-credentials-and-reboot) 
    * [1.4. Enter non-persistent ConfigPortal](#14-enter-non-persistent-configportal)
    * [1.5. Enter persistent ConfigPortal](#15-enter-persistent-configportal)
* [Debug](#debug)
* [Troubleshooting](#troubleshooting)
* [Issues](#issues)
* [TO DO](#to-do)
* [DONE](#done)
* [Contributions and Thanks](#contributions-and-thanks)
* [Contributing](#contributing)
* [License](#license)
* [Copyright](#copyright)

---
---

### Important Note

This [**BlynkESP32_BT_WF**](https://github.com/khoih-prog/BlynkESP32_BT_WF) has just been modified to create the new [**Blynk_Async_ESP32_BT_WF**](https://github.com/khoih-prog/Blynk_Async_ESP32_BT_WF) in order to use the better and more efficient [**ESPAsyncWebServer Library**](https://github.com/me-no-dev/ESPAsyncWebServer), instead of the (ESP8266)WebServer library.

The new [**Blynk_Async_ESP32_BT_WF**](https://github.com/khoih-prog/Blynk_Async_ESP32_BT_WF) is based on and sync'ed with [**BlynkESP32_BT_WF**](https://github.com/khoih-prog/BlynkESP32_BT_WF). Therefore, all the features currently supported by this [**BlynkESP32_BT_WF**](https://github.com/khoih-prog/BlynkESP32_BT_WF) will be available to the new library. The code change is to port to the new library is also very negligible, **mostly just changing the include file from `BlynkSimpleEsp32_xyz.h` to `BlynkSimpleEsp32_Async_xyz.h`.**

---

#### Why do we need the new Async [Blynk_Async_ESP32_BT_WF library](https://github.com/khoih-prog/Blynk_Async_ESP32_BT_WF)

- Using asynchronous network means that you can handle **more than one connection at the same time**
- **You are called once the request is ready and parsed**
- When you send the response, you are **immediately ready** to handle other connections while the server is taking care of sending the response in the background
- **Speed is OMG**
- **Easy to use API, HTTP Basic and Digest MD5 Authentication (default), ChunkedResponse**
- Easily extensible to handle **any type of content**
- Supports Continue 100
- **Async WebSocket plugin offering different locations without extra servers or ports**
- Async EventSource (Server-Sent Events) plugin to send events to the browser
- URL Rewrite plugin for conditional and permanent url rewrites
- ServeStatic plugin that supports cache, Last-Modified, default index and more
- Simple template processing engine to handle templates

---
---

### Why do we need this [BlynkESP32_BT_WF library](https://github.com/khoih-prog/BlynkESP32_BT_WF)

#### Features

By design, Blynk user can run ESP32 boards with **either WiFi or BT/BLE** by using different sketches, and have to upload / update firmware to change. This library enables user to include both Blynk BT / BLE and WiFi libraries in one sketch, **run both WiFi and BT/BLE simultaneously, or select one to use at runtime after reboot.**

This library also supports (auto)connection to **MultiWiFi and MultiBlynk, dynamic custom as well as static parameters in Config Portal**. Eliminate hardcoding your Wifi and Blynk credentials and configuration data saved in either SPIFFS or EEPROM.

Now from Version 1.0.2, you can eliminate `hardcoding` your Wifi and Blynk credentials, thanks to the `Smart Config Portal`, and have Credentials (WiFi SID/PW, Blynk WiFi/BT/BLE Tokens/ Hardware Port) saved in either **LittleFS, SPIFFS or EEPROM**.

#### Currently supported Boards

This [**BlynkESP32_BT_WF** library](https://github.com/khoih-prog/BlynkESP32_BT_WF) currently supports these following boards:

 1. **ESP32-based boards using EEPROM, SPIFFS or LittleFS**.
 
#### Not yet supported Boards
 
 
 1. **ESP32-S2 and ESP32-C3**

---
---

## Prerequisites

 1. [`Arduino IDE 1.8.16+` for Arduino](https://www.arduino.cc/en/Main/Software)
 2. [`Blynk library 1.0.1+`](https://github.com/blynkkk/blynk-library/releases). [![Latest release](https://img.shields.io/github/release/blynkkk/blynk-library.svg)](https://github.com/blynkkk/blynk-library/releases/latest/). Never use the `Blynk beta` versions.
 3. [`ESP32 Core 2.0.0+`](https://github.com/espressif/arduino-esp32) for ESP32-based boards. [![Latest release](https://img.shields.io/github/release/espressif/arduino-esp32.svg)](https://github.com/espressif/arduino-esp32/releases/latest/)
 4. [`ESP_DoubleResetDetector library 1.1.1+`](https://github.com/khoih-prog/ESP_DoubleResetDetector) to use DRD feature. To install, check [![arduino-library-badge](https://www.ardu-badge.com/badge/ESP_DoubleResetDetector.svg?)](https://www.ardu-badge.com/ESP_DoubleResetDetector).
 5. [`LittleFS_esp32 v1.0.6+`](https://github.com/lorol/LITTLEFS) for ESP32-based boards using LittleFS. To install, check [![arduino-library-badge](https://www.ardu-badge.com/badge/LittleFS_esp32.svg?)](https://www.ardu-badge.com/LittleFS_esp32). **Notice**: This [`LittleFS_esp32 library`](https://github.com/lorol/LITTLEFS) has been integrated to Arduino [esp32 core v1.0.6](https://github.com/espressif/arduino-esp32/tree/master/libraries/LITTLEFS).

---

## Installation

### Use Arduino Library Manager

The best and easiest way is to use `Arduino Library Manager`. Search for `BlynkESP32_BT_WF`, then select / install the latest version. You can also use this link [![arduino-library-badge](https://www.ardu-badge.com/badge/BlynkESP32_BT_WF.svg?)](https://www.ardu-badge.com/BlynkESP32_BT_WF) for more detailed instructions.

### Manual Install

1. Navigate to [BlynkESP32_BT_WF](https://github.com/khoih-prog/BlynkESP32_BT_WF) page.
2. Download the latest release `BlynkESP32_BT_WF-master.zip`.
3. Extract the zip file to `BlynkESP32_BT_WF-master` directory 
4. Copy the whole `BlynkESP32_BT_WF-master` folder to Arduino libraries' directory such as `~/Arduino/libraries/`.

### VS Code & PlatformIO:

1. Install [VS Code](https://code.visualstudio.com/)
2. Install [PlatformIO](https://platformio.org/platformio-ide)
3. Install [**BlynkESP32_BT_WF** library](https://platformio.org/lib/show/11285/BlynkESP32_BT_WF) by using [Library Manager](https://platformio.org/lib/show/11285/BlynkESP32_BT_WF/installation). Search for **BlynkESP32_BT_WF** in [Platform.io Author's Libraries](https://platformio.org/lib/search?query=author:%22Khoi%20Hoang%22)
4. Use included [platformio.ini](platformio/platformio.ini) file from examples to ensure that all dependent libraries will installed automatically. Please visit documentation for the other options and examples at [Project Configuration File](https://docs.platformio.org/page/projectconf.html)

---
---

### Note for Platform IO using ESP32 LittleFS

#### Necessary only for esp32 core v1.0.6-

From esp32 core v1.0.6+, [`LittleFS_esp32 v1.0.6`](https://github.com/lorol/LITTLEFS) has been included and this step is not necessary anymore.

In Platform IO, to fix the error when using [`LittleFS_esp32 v1.0`](https://github.com/lorol/LITTLEFS) for ESP32-based boards with ESP32 core v1.0.4- (ESP-IDF v3.2-), uncomment the following line

from

```
//#define CONFIG_LITTLEFS_FOR_IDF_3_2   /* For old IDF - like in release 1.0.4 */
```

to

```
#define CONFIG_LITTLEFS_FOR_IDF_3_2   /* For old IDF - like in release 1.0.4 */
```

It's advisable to use the latest [`LittleFS_esp32 v1.0.5+`](https://github.com/lorol/LITTLEFS) to avoid the issue.

Thanks to [Roshan](https://github.com/solroshan) to report the issue in [Error esp_littlefs.c 'utime_p'](https://github.com/khoih-prog/ESPAsync_WiFiManager/issues/28) 

---
---

### HOWTO Use analogRead() with ESP32 running WiFi and/or BlueTooth (BT/BLE)

Please have a look at [**ESP_WiFiManager Issue 39: Not able to read analog port when using the autoconnect example**](https://github.com/khoih-prog/ESP_WiFiManager/issues/39) to have more detailed description and solution of the issue.

#### 1.  ESP32 has 2 ADCs, named ADC1 and ADC2

#### 2. ESP32 ADCs functions

- ADC1 controls ADC function for pins **GPIO32-GPIO39**
- ADC2 controls ADC function for pins **GPIO0, 2, 4, 12-15, 25-27**

#### 3.. ESP32 WiFi uses ADC2 for WiFi functions

Look in file [**adc_common.c**](https://github.com/espressif/esp-idf/blob/master/components/driver/adc_common.c#L61)

> In ADC2, there're two locks used for different cases:
> 1. lock shared with app and Wi-Fi:
>    ESP32:
>         When Wi-Fi using the ADC2, we assume it will never stop, so app checks the lock and returns immediately if failed.
>    ESP32S2:
>         The controller's control over the ADC is determined by the arbiter. There is no need to control by lock.
> 
> 2. lock shared between tasks:
>    when several tasks sharing the ADC2, we want to guarantee
>    all the requests will be handled.
>    Since conversions are short (about 31us), app returns the lock very soon,
>    we use a spinlock to stand there waiting to do conversions one by one.
> 
> adc2_spinlock should be acquired first, then adc2_wifi_lock or rtc_spinlock.


- In order to use ADC2 for other functions, we have to **acquire complicated firmware locks and very difficult to do**
- So, it's not advisable to use ADC2 with WiFi/BlueTooth (BT/BLE).
- Use ADC1, and pins GPIO32-GPIO39
- If somehow it's a must to use those pins serviced by ADC2 (**GPIO0, 2, 4, 12, 13, 14, 15, 25, 26 and 27**), use the **fix mentioned at the end** of [**ESP_WiFiManager Issue 39: Not able to read analog port when using the autoconnect example**](https://github.com/khoih-prog/ESP_WiFiManager/issues/39) to work with ESP32 WiFi/BlueTooth (BT/BLE).


---
---

### How to use

In your code, replace:

1. `BlynkSimpleEsp32_BT.h`    with `BlynkSimpleEsp32_BT_WF.h`
2. `BlynkSimpleEsp32_BLE.h`   with `BlynkSimpleEsp32_BLE_WF.h`
3. 
  - `BlynkSimpleEsp32.h`       with `BlynkSimpleEsp32_WFM.h` if **using** WiFiManager's Config Portal features
  - `BlynkSimpleEsp32.h`       with `BlynkSimpleEsp32_WF.h`  if **not using** WiFiManager's Config Portal features
  
4. Then replace WiFi's `Blynk.begin(...)` with :

  - `Blynk_WF.begin()` to use default DHCP hostname `ESP8266-XXXXXX` or `ESP32-XXXXXX`

  - or to have a personalized hostname `(RFC952-conformed,- 24 chars max,- only a..z A..Z 0..9 '-' and no '-' as last char)`

    `Blynk_WF.begin("Personalized-HostName")`

5. `Blynk.run();`             with `Blynk_WF.run()` for WiFi related function calls
6. `Blynk.run();`             with `Blynk_BT.run()` for BlueTooth related function calls
or 
7. `Blynk.run();`             with `Blynk_BLE.run()` for BLE related function calls

---
---

### HOWTO Use default Credentials and have them pre-loaded onto Config Portal

See this example and modify as necessary

#### 1. To load [Default Credentials](examples/ESP32_BLE_WF/Credentials.h)

```cpp
bool LOAD_DEFAULT_CONFIG_DATA = true;
```

#### 2. To use system default to load "blank" when there is no valid Credentials

```cpp
bool LOAD_DEFAULT_CONFIG_DATA = false;
```

#### 3. Example of [Default Credentials](examples/ESP32_BLE_WF/Credentials.h)

```cpp
  /// Start Default Config Data //////////////////
  
  /*
    // Defined in <BlynkSimpleESP32_WFM.h>
  
    #define SSID_MAX_LEN      32
    #define PASS_MAX_LEN      64
    
    typedef struct
    {
    char wifi_ssid[SSID_MAX_LEN];
    char wifi_pw  [PASS_MAX_LEN];
    }  WiFi_Credentials;
  
    #define BLYNK_SERVER_MAX_LEN      32
    #define BLYNK_TOKEN_MAX_LEN       36
  
    typedef struct
    {
    char blynk_server[BLYNK_SERVER_MAX_LEN];
    char blynk_token [BLYNK_TOKEN_MAX_LEN];
    }  Blynk_Credentials;
  
    #define NUM_WIFI_CREDENTIALS      2
    #define NUM_BLYNK_CREDENTIALS     2
  
    typedef struct Configuration
    {
    char header         [16];
    WiFi_Credentials  WiFi_Creds  [NUM_WIFI_CREDENTIALS];
    Blynk_Credentials Blynk_Creds [NUM_BLYNK_CREDENTIALS];
    int  blynk_port;
    char board_name     [24];
    int  checkSum;
    } Blynk_WM_Configuration;
  
  */
  
  //bool LOAD_DEFAULT_CONFIG_DATA = true;
  bool LOAD_DEFAULT_CONFIG_DATA = false;
  
  Blynk_WM_Configuration defaultConfig =
  {
    //char header[16], dummy, not used
  #if USE_SSL
    "SSL",
  #else
    "NonSSL",
  #endif
    //WiFi_Credentials  WiFi_Creds  [NUM_WIFI_CREDENTIALS]
    //WiFi_Creds.wifi_ssid and WiFi_Creds.wifi_pw
    "SSID1", "password1",
    "SSID2", "password2",
    // Blynk_Credentials Blynk_Creds [NUM_BLYNK_CREDENTIALS];
    // Blynk_Creds.blynk_server and Blynk_Creds.blynk_token
    "account.ddns.net",     "token",
    "account.duckdns.org",  "token1", 
    //int  blynk_port;
  #if USE_SSL
    9443,
  #else
    8080,
  #endif
    //char board_name     [24];
    "ESP32-BLE-WF",
    //int  checkSum, dummy, not used
    0
  };
  
  /////////// End Default Config Data /////////////
```

#### 4. How to add dynamic parameters from sketch

- To add custom parameters, just modify the example below

```cpp
#define USE_DYNAMIC_PARAMETERS      true
  
  /////////////// Start dynamic Credentials ///////////////
  
  //Defined in <BlynkSimpleESP32_WFM.h>
  /**************************************
    #define MAX_ID_LEN                5
    #define MAX_DISPLAY_NAME_LEN      16
  
    typedef struct
    {
    char id             [MAX_ID_LEN + 1];
    char displayName    [MAX_DISPLAY_NAME_LEN + 1];
    char *pdata;
    uint8_t maxlen;
    } MenuItem;
  **************************************/
  
  #if USE_DYNAMIC_PARAMETERS
  
  #define MAX_MQTT_SERVER_LEN      34
  char MQTT_Server  [MAX_MQTT_SERVER_LEN + 1]   = "default-mqtt-server";
  
  #define MAX_MQTT_PORT_LEN        6
  char MQTT_Port   [MAX_MQTT_PORT_LEN + 1]  = "1883";
  
  #define MAX_MQTT_USERNAME_LEN      34
  char MQTT_UserName  [MAX_MQTT_USERNAME_LEN + 1]   = "default-mqtt-username";
  
  #define MAX_MQTT_PW_LEN        34
  char MQTT_PW   [MAX_MQTT_PW_LEN + 1]  = "default-mqtt-password";
  
  #define MAX_MQTT_SUBS_TOPIC_LEN      34
  char MQTT_SubsTopic  [MAX_MQTT_SUBS_TOPIC_LEN + 1]   = "default-mqtt-SubTopic";
  
  #define MAX_MQTT_PUB_TOPIC_LEN       34
  char MQTT_PubTopic   [MAX_MQTT_PUB_TOPIC_LEN + 1]  = "default-mqtt-PubTopic";
  
  MenuItem myMenuItems [] =
  {
    { "mqtt", "MQTT Server",      MQTT_Server,      MAX_MQTT_SERVER_LEN },
    { "mqpt", "Port",             MQTT_Port,        MAX_MQTT_PORT_LEN   },
    { "user", "MQTT UserName",    MQTT_UserName,    MAX_MQTT_USERNAME_LEN },
    { "mqpw", "MQTT PWD",         MQTT_PW,          MAX_MQTT_PW_LEN },
    { "subs", "Subs Topics",      MQTT_SubsTopic,   MAX_MQTT_SUBS_TOPIC_LEN },
    { "pubs", "Pubs Topics",      MQTT_PubTopic,    MAX_MQTT_PUB_TOPIC_LEN },
  };
  
  uint16_t NUM_MENU_ITEMS = sizeof(myMenuItems) / sizeof(MenuItem);  //MenuItemSize;
  
  #else
  
  MenuItem myMenuItems [] = {};
  
  uint16_t NUM_MENU_ITEMS = 0;
  #endif
  
  
  /////// // End dynamic Credentials ///////////

```
#### 5. If you don't need to add dynamic parameters

Use the following code snippet in sketch

```cpp
#define USE_DYNAMIC_PARAMETERS     false
```

or

```cpp
/////////////// Start dynamic Credentials ///////////////

MenuItem myMenuItems [] = {};

uint16_t NUM_MENU_ITEMS = 0;
/////// // End dynamic Credentials ///////////

```

#### 6. To use custom HTML Style

```
const char NewCustomsStyle[] /*PROGMEM*/ = "<style>div,input{padding:5px;font-size:1em;}input{width:95%;}body{text-align: center;}\
button{background-color:blue;color:white;line-height:2.4rem;font-size:1.2rem;width:100%;}fieldset{border-radius:0.3rem;margin:0px;}</style>";

...

Blynk.setCustomsStyle(NewCustomsStyle);
```

#### 7. To use custom Head Elements


```
Blynk.setCustomsHeadElement("<style>html{filter: invert(10%);}</style>");
```

#### 8. To use CORS Header

```
Blynk.setCORSHeader("Your Access-Control-Allow-Origin");
```

#### 9. To use and input only one set of WiFi SSID and PWD

#### 9.1 If you need to use and input only one set of WiFi SSID/PWD

```
// Permit input only one set of WiFi SSID/PWD. The other can be "NULL or "blank"
// Default is false (if not defined) => must input 2 sets of SSID/PWD
#define REQUIRE_ONE_SET_SSID_PW       true
```
But it's always advisable to use and input both sets for reliability.
 
#### 9.2 If you need to use both sets of WiFi SSID/PWD

```
// Permit input only one set of WiFi SSID/PWD. The other can be "NULL or "blank"
// Default is false (if not defined) => must input 2 sets of SSID/PWD
#define REQUIRE_ONE_SET_SSID_PW       false
```

#### 10. To enable auto-scan of WiFi networks for selection in Configuration Portal

#### 10.1 Enable auto-scan of WiFi networks for selection in Configuration Portal


```
#define SCAN_WIFI_NETWORKS                  true
```

The manual input of SSIDs is default enabled, so that users can input arbitrary SSID, not only from the scanned list. This is for the sample use-cases in which users can input the known SSIDs of another place, then send the boards to that place. The boards can connect to WiFi without users entering Config Portal to re-configure.

#### 10.2 Disable manually input SSIDs

```
// To disable manually input SSID, only from a scanned SSID lists
#define MANUAL_SSID_INPUT_ALLOWED           false
```

This is for normal use-cases in which users can only select an SSID from a scanned list of SSIDs to avoid typo mistakes and/or security.

#### 10.3 Select maximum number of SSIDs in the list

The maximum number of SSIDs in the list is seletable from 2 to 15. If invalid number of SSIDs is selected, the default number of 10 will be used.


```
// From 2-15
#define MAX_SSID_IN_LIST                    8
```

---
---


### Why using this [BlynkESP32_BT_WF](https://github.com/khoih-prog/BlynkESP32_BT_WF) with MultiWiFi-MultiBlynk features

You can see that the system ***automatically detects and connects to the best or avaiable WiFi APs and/or Blynk Servers***, whenever interruption happens. This feature is very useful for systems requiring high degree of reliability.

Moreover, these `Blynk_BLE.begin()`, `Blynk_BT.begin()` and `Blynk_WF.begin()` are ***not blocking calls***, so you can use it for critical functions requiring in loop().

Anyway, this is better for projects using Blynk just for GUI (graphical user interface).

In operation, if WiFi or Blynk connection is lost, `Blynk_BLE.begin()`, `Blynk_BT.begin()` and `Blynk_WF.begin()` will try reconnecting automatically. 

Therefore, `Blynk_BLE.begin()`, `Blynk_BT.begin()` and `Blynk_WF.begin()` must be called in the `loop()` function. 

For example, don't use:

```cpp
void loop()
{
  if (Blynk.connected())
     Blynk_BLE.run();
     
  ...
}
```

just

```cpp
void loop()
{
  Blynk_BLE.run();
  ...
}
```
---
---

### Important Notes for using Dynamic Parameters' ids

1. These ids (such as "mqtt" in example) must be ***unique***.

Please be noted that the following ***reserved names are already used in library***:

```
"id"    for WiFi SSID
"pw"    for WiFi PW
"id1"   for WiFi1 SSID
"pw1"   for WiFi1 PW
"sv"    for Blynk Server
"tk"    for Blynk Token
"sv1"   for Blynk Server1
"tk1"   for Blynk Token1
"pt"    for Blynk Port
"bttk"  for BT Blynk Token
"bltk"  for BLE Blynk Token
"nm"    for Board Name
```

---
---

### Examples


1. [ESP32_BLE_WF](examples/ESP32_BLE_WF)
2. [ESP32_BT_WF](examples/ESP32_BT_WF)
3. [Geiger_Counter_BLE](examples/Geiger_Counter_BLE)
4. [Geiger_Counter_BT](examples/Geiger_Counter_BT)
5. [Geiger_Counter_OLED](examples/Geiger_Counter_OLED)
6. [Geiger_Counter_OLED_BT_WF](examples/Geiger_Counter_OLED_BT_WF)
7. [Geiger_Counter_OLED_BT_BLE_WF](examples/Geiger_Counter_OLED_BT_BLE_WF)
8. [PET_Check](examples/PET_Check)

and real-life project [Hack GMC Geigercounter With Blynk](https://www.instructables.com/id/Hack-GMC-Geigercounter-With-Blynk/) of  [Crosswalkersam](https://www.instructables.com/member/Crosswalkersam/)

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

---
---

## So, how it works?

If the necessary credentials are not valid or it cannot connect to the Blynk server in 30 seconds, it will switch to `Configuration Mode`. You will see your built-in LED turned ON. In `Configuration Mode`, it starts an access point called `ESP_xxxxxx` or configurable `TestPortal-ESP32` by using:

```cpp
Blynk.setConfigPortal("TestPortal-ESP32", "TestPortalPass");
```

Connect to it using password `MyESP_xxxxxx` or configurable `TestPortalPass`.

<p align="center">
    <img src="https://github.com/khoih-prog/BlynkESP32_BT_WF/blob/master/pics/WiFi_AP.jpg">
</p>

After you connected, please, go to http://192.168.4.1 or the configured AP IP. The Config Portal screen will appear:

<p align="center">
    <img src="https://github.com/khoih-prog/BlynkESP32_BT_WF/blob/master/pics/Main.png">
</p>

Enter your WiFi and Blynk Credentials (Server, Port, WiFi/BT/BLE tokens) 


### 1. Without SCAN_WIFI_NETWORKS


<p align="center">
    <img src="https://github.com/khoih-prog/BlynkESP32_BT_WF/blob/master/pics/ConfigPortal.png">
</p>


### 2. With SCAN_WIFI_NETWORKS


<p align="center">
    <img src="https://github.com/khoih-prog/BlynkESP32_BT_WF/blob/master/pics/Input_With_Scan.png">
</p>


Then click `Save`. After you restarted, you will see your built-in LED turned OFF. That means, it connected to your Blynk server successfully.

<p align="center">
    <img src="https://github.com/khoih-prog/BlynkESP32_BT_WF/blob/master/pics/Saved.png">
</p>


---
---

## Example [ESP32_BLE_WF](examples/ESP32_BLE_WF)

#### 1. File [ESP32_BLE_WF.ino](examples/ESP32_BLE_WF/ESP32_BLE_WF.ino)

```cpp
/****************************************************************************************************************************
   Important Notes:
   1) Sketch is ~0.9MB of code because only 1 instance of Blynk if #define BLYNK_USE_BT_ONLY  =>  true
   2) Sketch is very large (~1.3MB code) because 2 instances of Blynk if #define BLYNK_USE_BT_ONLY  =>    false
   3) To conmpile, use Partition Scheem with large APP size, such as
      a) 8MB Flash (3MB APP, 1.5MB FAT) if use EEPROM
      b) No OTA (2MB APP, 2MB SPIFFS)
      c) No OTA (2MB APP, 2MB FATFS)  if use EEPROM
      d) Huge APP (3MB No OTA, 1MB SPIFFS)   <===== Preferable if use SPIFFS
      e) Minimal SPIFFS (1.9MB APP with OTA, 190KB SPIFFS)
  *****************************************************************************************************************************/

#include "defines.h"
#include "Credentials.h"
#include "dynamicParams.h"

bool USE_BLE = true;
long timePreviousMeassure  = 0;

#define WIFI_BLE_SELECTION_PIN     14   //Pin D14 mapped to pin GPIO14/HSPI_SCK/ADC16/TOUCH6/TMS of ESP32

BlynkTimer timer;

#include <Ticker.h>
Ticker     led_ticker;

#define BLYNK_PIN_FORCED_CONFIG           V10
#define BLYNK_PIN_FORCED_PERS_CONFIG      V20

// Use button V10 (BLYNK_PIN_FORCED_CONFIG) to forced Config Portal
BLYNK_WRITE(BLYNK_PIN_FORCED_CONFIG)
{ 
  if (param.asInt())
  {
    Serial.println( F("\nCP Button Hit. Rebooting") ); 

    // This will keep CP once, clear after reset, even you didn't enter CP at all.
    Blynk.resetAndEnterConfigPortal(); 
  }
}

// Use button V20 (BLYNK_PIN_FORCED_PERS_CONFIG) to forced Persistent Config Portal
BLYNK_WRITE(BLYNK_PIN_FORCED_PERS_CONFIG)
{ 
  if (param.asInt())
  {
    Serial.println( F("\nPersistent CP Button Hit. Rebooting") ); 
   
    // This will keep CP forever, until you successfully enter CP, and Save data to clear the flag.
    Blynk.resetAndEnterConfigPortalPersistent();
  }
}

void set_led(byte status)
{
  digitalWrite(LED_BUILTIN, status);
}

void noticeAlive(void)
{ 
  if (USE_BLE)
    Blynk_BLE.virtualWrite(V0, F("OK"));
  else
    Blynk_WF.virtualWrite(V0, F("OK"));
}

void heartBeatPrint(void)
{
  static int num = 1;

  if (Blynk.connected())
  {
    set_led(HIGH);
    led_ticker.once_ms(111, set_led, (byte) LOW);
    Serial.print(F("B"));    
  }
  else
  {
    Serial.print(F("F"));
  }

  if (num == 80)
  {
    Serial.println();
    num = 1;
  }
  else if (num++ % 10 == 0)
  {
    Serial.print(F(" "));
  }
}

void checkStatus()
{
  static unsigned long checkstatus_timeout = 0;

#define STATUS_CHECK_INTERVAL     60000L

  // Send status report every STATUS_REPORT_INTERVAL (60) seconds: we don't need to send updates frequently if there is no status change.
  if ((millis() > checkstatus_timeout) || (checkstatus_timeout == 0))
  {     
    if (!USE_BLE)
    {
      // report Blynk connection
      heartBeatPrint();
    }

    checkstatus_timeout = millis() + STATUS_CHECK_INTERVAL;
  }
}

char BLE_Device_Name[] = "GeigerCounter-BLE";

#if USING_CUSTOMS_STYLE
const char NewCustomsStyle[] /*PROGMEM*/ = "<style>div,input{padding:5px;font-size:1em;}input{width:95%;}body{text-align: center;}\
button{background-color:blue;color:white;line-height:2.4rem;font-size:1.2rem;width:100%;}fieldset{border-radius:0.3rem;margin:0px;}</style>";
#endif

void setup()
{
  Serial.begin(115200);
  while (!Serial);

  delay(200);

#if (USE_LITTLEFS)
  Serial.print(F("\nStarting ESP32_BLE_WF using LITTLEFS"));
#elif (USE_SPIFFS)
  Serial.print(F("\nStarting ESP32_BLE_WF using SPIFFS"));  
#else
  Serial.print(F("\nStarting ESP32_BLE_WF using EEPROM"));
#endif

#if USE_SSL
  Serial.print(F(" with SSL on "));
#else
  Serial.print(F(" without SSL on "));
#endif

  Serial.println(ARDUINO_BOARD);
  Serial.println(BLYNK_ESP32_BT_WF_VERSION);
  
#if USE_BLYNK_WM  
  Serial.println(ESP_DOUBLE_RESET_DETECTOR_VERSION);
#endif

  pinMode(WIFI_BLE_SELECTION_PIN, INPUT_PULLUP);

#if BLYNK_USE_BLE_ONLY
  Blynk_BLE.setDeviceName(BLE_Device_Name);

  #if ESP32_BLE_WF_DEBUG
  Serial.println(F("Blynk_BLE begin"));
  #endif

  Blynk_BLE.begin(auth);
#else
  if (digitalRead(WIFI_BLE_SELECTION_PIN) == HIGH)
  {
    USE_BLE = false;
    Serial.println(F("GPIO14 HIGH, Use WiFi"));
#if USE_BLYNK_WM
#if ESP32_BLE_WF_DEBUG
    Serial.println(F("USE_BLYNK_WM: Blynk_WF begin"));
#endif

    // Set config portal SSID and Password
    Blynk.setConfigPortal("TestPortal-ESP32", "TestPortalPass");
    // Set config portal IP address
    Blynk.setConfigPortalIP(IPAddress(192, 168, 232, 1));
  
    // Set config portal channel, default = 1. Use 0 => random channel from 1-13 to avoid conflict
    Blynk_WF.setConfigPortalChannel(0);

    // From v1.0.6, select either one of these to set static IP + DNS
    Blynk.setSTAStaticIPConfig(IPAddress(192, 168, 2, 232), IPAddress(192, 168, 2, 1), IPAddress(255, 255, 255, 0));
    //Blynk.setSTAStaticIPConfig(IPAddress(192, 168, 2, 232), IPAddress(192, 168, 2, 1), IPAddress(255, 255, 255, 0),
    //                           IPAddress(192, 168, 2, 1), IPAddress(8, 8, 8, 8));
    //Blynk.setSTAStaticIPConfig(IPAddress(192, 168, 2, 232), IPAddress(192, 168, 2, 1), IPAddress(255, 255, 255, 0),
    //                           IPAddress(4, 4, 4, 4), IPAddress(8, 8, 8, 8));


  //////////////////////////////////////////////
    
  #if USING_CUSTOMS_STYLE
    Blynk.setCustomsStyle(NewCustomsStyle);
  #endif
  
  #if USING_CUSTOMS_HEAD_ELEMENT
    Blynk.setCustomsHeadElement("<style>html{filter: invert(10%);}</style>");
  #endif
  
  #if USING_CORS_FEATURE  
    Blynk.setCORSHeader("Your Access-Control-Allow-Origin");
  #endif
  
    //////////////////////////////////////////////
  
    // Use this to default DHCP hostname to ESP8266-XXXXXX or ESP32-XXXXXX
    //Blynk.begin();
    // Use this to personalize DHCP hostname (RFC952 conformed)
    // 24 chars max,- only a..z A..Z 0..9 '-' and no '-' as last char
    //Blynk.begin("ESP32-BLE-WM");
  
    Blynk_WF.begin(BLE_Device_Name);
#else
    //Blynk_WF.begin(auth, ssid, pass);
#if ESP32_BLE_WF_DEBUG    
    Serial.println(F("Not USE_BLYNK_WM: Blynk_WF begin"));
#endif    
    Blynk_WF.begin(auth, ssid, pass, cloudBlynkServer.c_str(), BLYNK_SERVER_HARDWARE_PORT);
#endif
  }
  else
  {
    USE_BLE = true;
    Serial.println(F("GPIO14 LOW, Use BLE"));
    Blynk_BLE.setDeviceName(BLE_Device_Name);
#if USE_BLYNK_WM
    if (Blynk_WF.getBlynkBLEToken() == NO_CONFIG)        //String("blank"))
    {
      Serial.println(F("No valid stored BLE auth. Have to run WiFi then enter config portal"));
      USE_BLE = false;

#if ESP32_BLE_WF_DEBUG
      Serial.println(F("USE_BLYNK_WM: No BLE Token. Blynk_WF begin"));
#endif  
      
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

#if ESP32_BLE_WF_DEBUG      
      Serial.println(F("USE_BLE: Blynk_BLE begin"));
#endif   
      
      Blynk_BLE.begin(BLE_auth.c_str());
    }
  }
#endif

  // Important, need to keep constant communication to Blynk Server at least once per ~25s
  // Or Blynk will lost and have to (auto)reconnect
  timer.setInterval(10000L, noticeAlive);
}

#if (USE_BLYNK_WM && USE_DYNAMIC_PARAMETERS)
void displayCredentials()
{
  Serial.println(F("\nYour stored Credentials :"));

  for (uint16_t i = 0; i < NUM_MENU_ITEMS; i++)
  {
    Serial.print(myMenuItems[i].displayName);
    Serial.print(F(" = "));
    Serial.println(myMenuItems[i].pdata);
  }
}

void displayCredentialsInLoop()
{
  static bool displayedCredentials = false;

  if (!displayedCredentials)
  {
    for (uint16_t i = 0; i < NUM_MENU_ITEMS; i++)
    {
      if (!strlen(myMenuItems[i].pdata))
      {
        break;
      }

      if ( i == (NUM_MENU_ITEMS - 1) )
      {
        displayedCredentials = true;
        displayCredentials();
      }
    }
  }
}

#endif

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

  timer.run(); 
  checkStatus();

#if (USE_BLYNK_WM && USE_DYNAMIC_PARAMETERS)
  displayCredentialsInLoop();
#endif
}
```

#### 2. File [defines.h](examples/ESP32_BLE_WF/defines.h)

```cpp
#ifndef defines_h
#define defines_h

#ifndef ESP32
  #error This code is intended to run on the ESP32 platform! Please check your Tools->Board setting.
#endif

#define BLYNK_PRINT                   Serial

#define ESP32_BLE_WF_DEBUG            true

#define DOUBLERESETDETECTOR_DEBUG     true
#define BLYNK_WM_DEBUG                1

// Not use #define USE_LITTLEFS and #define USE_SPIFFS  => using SPIFFS for configuration data in WiFiManager
// (USE_LITTLEFS == false) and (USE_SPIFFS == false)    => using EEPROM for configuration data in WiFiManager
// (USE_LITTLEFS == true) and (USE_SPIFFS == false)     => using LITTLEFS for configuration data in WiFiManager
// (USE_LITTLEFS == true) and (USE_SPIFFS == true)      => using LITTLEFS for configuration data in WiFiManager
// (USE_LITTLEFS == false) and (USE_SPIFFS == true)     => using SPIFFS for configuration data in WiFiManager
// Those above #define's must be placed before #include <BlynkSimpleEsp32_WFM.h>

#define USE_LITTLEFS          true
#define USE_SPIFFS            false


#if !( USE_SPIFFS || USE_LITTLEFS)
  // EEPROM_SIZE must be <= 2048 and >= CONFIG_DATA_SIZE (currently 172 bytes)
  #define EEPROM_SIZE    (2 * 1024)
  // EEPROM_START + CONFIG_DATA_SIZE must be <= EEPROM_SIZE
  #define EEPROM_START   0
#endif

/////////////////////////////////////////////

// Add customs headers from v1.2.0
#define USING_CUSTOMS_STYLE                 true
#define USING_CUSTOMS_HEAD_ELEMENT          true
#define USING_CORS_FEATURE                  true

/////////////////////////////////////////////

// Force some params in Blynk, only valid for library version 1.0.1 and later
#define TIMEOUT_RECONNECT_WIFI                    10000L
#define RESET_IF_CONFIG_TIMEOUT                   true
#define CONFIG_TIMEOUT_RETRYTIMES_BEFORE_RESET    5

// Those above #define's must be placed before #include <BlynkSimpleESP32_WFM.h>

//#define BLYNK_USE_BLE_ONLY      true
#define BLYNK_USE_BLE_ONLY      false

#include <BlynkSimpleEsp32_BLE_WF.h>
#include <BLEDevice.h>
#include <BLEServer.h>

#define USE_BLYNK_WM          true
//#define USE_BLYNK_WM          false

#if !BLYNK_USE_BLE_ONLY
  #if USE_BLYNK_WM
    #define USE_DYNAMIC_PARAMETERS                    true

    /////////////////////////////////////////////

    #define REQUIRE_ONE_SET_SSID_PW             false
    
    #define SCAN_WIFI_NETWORKS                  true
    
    // To be able to manually input SSID, not from a scanned SSID lists
    #define MANUAL_SSID_INPUT_ALLOWED           true
    
    // From 2-15
    #define MAX_SSID_IN_LIST                    8
    
    /////////////////////////////////////////////
    
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

#ifndef LED_BUILTIN
  #define LED_BUILTIN       2         // Pin D2 mapped to pin GPIO2/ADC12 of ESP32, control on-board LED
#endif

#define HOST_NAME   "ESP32-BLE-WF"

#endif      //defines_h
```

---

#### 3. File [Credentials.h](examples/ESP32_BLE_WF/Credentials.h)

```cpp
#ifndef Credentials_h
#define Credentials_h

#if USE_BLYNK_WM

  /// Start Default Config Data //////////////////
  
  /*
    // Defined in <BlynkSimpleESP32_WFM.h>
  
    #define SSID_MAX_LEN      32
    #define PASS_MAX_LEN      64
    
    typedef struct
    {
    char wifi_ssid[SSID_MAX_LEN];
    char wifi_pw  [PASS_MAX_LEN];
    }  WiFi_Credentials;
  
    #define BLYNK_SERVER_MAX_LEN      32
    #define BLYNK_TOKEN_MAX_LEN       36
  
    typedef struct
    {
    char blynk_server[BLYNK_SERVER_MAX_LEN];
    char blynk_token [BLYNK_TOKEN_MAX_LEN];
    }  Blynk_Credentials;
  
    #define NUM_WIFI_CREDENTIALS      2
    #define NUM_BLYNK_CREDENTIALS     2
  
    typedef struct Configuration
    {
    char header         [16];
    WiFi_Credentials  WiFi_Creds  [NUM_WIFI_CREDENTIALS];
    Blynk_Credentials Blynk_Creds [NUM_BLYNK_CREDENTIALS];
    int  blynk_port;
    char board_name     [24];
    int  checkSum;
    } Blynk_WM_Configuration;
  
  */
  
  //bool LOAD_DEFAULT_CONFIG_DATA = true;
  bool LOAD_DEFAULT_CONFIG_DATA = false;
  
  Blynk_WM_Configuration defaultConfig =
  {
    //char header[16], dummy, not used
  #if USE_SSL
    "SSL",
  #else
    "NonSSL",
  #endif
    //WiFi_Credentials  WiFi_Creds  [NUM_WIFI_CREDENTIALS]
    //WiFi_Creds.wifi_ssid and WiFi_Creds.wifi_pw
    "SSID1", "password1",
    "SSID2", "password2",
    // Blynk_Credentials Blynk_Creds [NUM_BLYNK_CREDENTIALS];
    // Blynk_Creds.blynk_server and Blynk_Creds.blynk_token
    "account.ddns.net",     "token",
    "account.duckdns.org",  "token1", 
    //int  blynk_port;
  #if USE_SSL
    9443,
  #else
    8080,
  #endif
    //char board_name     [24];
    "ESP32-BLE-WF",
    //int  checkSum, dummy, not used
    0
  };
  
  /////////// End Default Config Data /////////////

#endif    // #if USE_BLYNK_WM

#endif    //Credentials_h
```

---

#### 4. File [dynamicParams.h](examples/ESP32_BLE_WF/dynamicParams.h)

```cpp
#ifndef dynamicParams_h
#define dynamicParams_h

#if USE_BLYNK_WM

#if (USE_DYNAMIC_PARAMETERS)
  #warning USE_DYNAMIC_PARAMETERS
#endif

// USE_DYNAMIC_PARAMETERS defined in defined.h
  
  /////////////// Start dynamic Credentials ///////////////
  
  //Defined in <BlynkSimpleESP32_WFM.h>
  /**************************************
    #define MAX_ID_LEN                5
    #define MAX_DISPLAY_NAME_LEN      16
  
    typedef struct
    {
    char id             [MAX_ID_LEN + 1];
    char displayName    [MAX_DISPLAY_NAME_LEN + 1];
    char *pdata;
    uint8_t maxlen;
    } MenuItem;
  **************************************/
  
  #if USE_DYNAMIC_PARAMETERS
  
  #define MAX_MQTT_SERVER_LEN      34
  char MQTT_Server  [MAX_MQTT_SERVER_LEN + 1]   = "default-mqtt-server";
  
  #define MAX_MQTT_PORT_LEN        6
  char MQTT_Port   [MAX_MQTT_PORT_LEN + 1]  = "1883";
  
  #define MAX_MQTT_USERNAME_LEN      34
  char MQTT_UserName  [MAX_MQTT_USERNAME_LEN + 1]   = "default-mqtt-username";
  
  #define MAX_MQTT_PW_LEN        34
  char MQTT_PW   [MAX_MQTT_PW_LEN + 1]  = "default-mqtt-password";
  
  #define MAX_MQTT_SUBS_TOPIC_LEN      34
  char MQTT_SubsTopic  [MAX_MQTT_SUBS_TOPIC_LEN + 1]   = "default-mqtt-SubTopic";
  
  #define MAX_MQTT_PUB_TOPIC_LEN       34
  char MQTT_PubTopic   [MAX_MQTT_PUB_TOPIC_LEN + 1]  = "default-mqtt-PubTopic";
  
  MenuItem myMenuItems [] =
  {
    { "mqtt", "MQTT Server",      MQTT_Server,      MAX_MQTT_SERVER_LEN },
    { "mqpt", "Port",             MQTT_Port,        MAX_MQTT_PORT_LEN   },
    { "user", "MQTT UserName",    MQTT_UserName,    MAX_MQTT_USERNAME_LEN },
    { "mqpw", "MQTT PWD",         MQTT_PW,          MAX_MQTT_PW_LEN },
    { "subs", "Subs Topics",      MQTT_SubsTopic,   MAX_MQTT_SUBS_TOPIC_LEN },
    { "pubs", "Pubs Topics",      MQTT_PubTopic,    MAX_MQTT_PUB_TOPIC_LEN },
  };
  
  uint16_t NUM_MENU_ITEMS = sizeof(myMenuItems) / sizeof(MenuItem);  //MenuItemSize;
  
  #else
  
  MenuItem myMenuItems [] = {};
  
  uint16_t NUM_MENU_ITEMS = 0;
  #endif
  
  
  /////// // End dynamic Credentials ///////////

#endif  // USE_BLYNK_WM

#endif      //dynamicParams_h

```

---
---

### Debug Terminal Output Samples

#### 1. ESP32_BLE_WF on ESP32_DEV

The following is the sample terminal output when running example [ESP32_BLE_WF](examples/ESP32_BLE_WF)

#### 1.1. No Config Data => Config Portal. Input valid credentials => reboot

```
Starting ESP32_BLE_WF using SPIFFS without SSL on ESP32_DEV
BlynkESP32_BT_WF v1.2.2
ESP_DoubleResetDetector v1.1.1
GPIO14 HIGH, Use WiFi
USE_BLYNK_WM: Blynk_WF begin
SPIFFS Flag read = 0xd0d04321
No doubleResetDetected
Saving config file...
Saving config file OK
[219] Hostname=GeigerCounter-BLE
[329] b:Nodat.Stay
[1174] stConf:SSID=TestPortal-ESP32,PW=TestPortalPass
[1174] IP=192.168.232.1,ch=1
F
Your stored Credentials :
MQTT Server = default-mqtt-server
Port = 1883
MQTT UserName = default-mqtt-username
MQTT PWD = default-mqtt-password
Subs Topics = default-mqtt-SubTopic
Pubs Topics = default-mqtt-PubTopic
Stop doubleResetDetecting
Saving config file...
Saving config file OK
FFFFFFFFFF FFFFFFFFFF FFFFFFFFFF FFFFFFFFFF FFFFFFFFFF FFFFFFFFFF FFFFFFFFFF FFFFFFFFFF
FFFFFFFFFF FFFFFFFFFF FFFFFFFFFF FFFFFFFFFF FFFFFFFFFF FFFFFFFFFF FFFFFFFFFF FFFFFFFFFF
[9678328] h:repl
[9678335] h1:myMenuItems[0]=default-mqtt-server
[9678335] h1:myMenuItems[1]=1883
[9678336] h1:myMenuItems[2]=default-mqtt-username
[9678337] h1:myMenuItems[3]=default-mqtt-password
[9678341] h1:myMenuItems[4]=default-mqtt-SubTopic
[9678345] h1:myMenuItems[5]=default-mqtt-PubTopic
FF[9799112] id: = HueNet1
[9799134] pw: = 12345678
[9799184] id1: = HueNet2
[9799205] pw1: = 12345678
[9799226] sv: = your_account.duckdns.org
[9799248] tk: = ********
[9799275] sv1: = your_account.ddns.net
[9799302] tk1: = ********
[9799318] bttk: = ********
[9799339] bltk: = ********
[9799366] pt = 8080
[9799387] nm: = ESP32
[9799491] h:UpdSPIFFS /wfm_config.dat
[9799600] SaveCfgFile 
[9799600] WCSum=0x47ec
[9799605] OK
[9799715] SaveBkUpCfgFile 
[9799719] OK
[9799719] h:Rst
```
---

#### 1.2. DRD => Config Portal. Input valid credentials => reboot

```
Starting ESP32_BLE_WF using SPIFFS without SSL on ESP32_DEV
BlynkESP32_BT_WF v1.2.2
ESP_DoubleResetDetector v1.1.1
GPIO14 HIGH, Use WiFi
USE_BLYNK_WM: Blynk_WF begin
SPIFFS Flag read = 0xd0d01234
doubleResetDetected
Saving config file...
Saving config file OK
[119] Double Reset Detected
[215] Hostname=GeigerCounter-BLE
[244] LoadCfgFile 
[245] OK
[245] ======= Start Stored Config Data =======
[245] Hdr=ESP32_WFM,BrdName=
[245] SSID=SSID1,PW=password1
[245] SSID1=SSID2,PW1=password2
[248] Server=account.ddns.net,Token=token
[252] Server1=account.duckdns.org,Token1=token1
[256] BT-Token=ESP32-BLE-WF,BLE-Token=
[260] Port=8080
[261] ======= End Config Data =======
[264] CCSum=0x2297,RCSum=0x2297
[268] LoadCredFile 
[269] CrR:pdata=default-mqtt-server,len=34
[273] CrR:pdata=1883,len=6
[275] CrR:pdata=default-mqtt-username,len=34
[279] CrR:pdata=default-mqtt-password,len=34
[283] CrR:pdata=default-mqtt-SubTopic,len=34
[287] CrR:pdata=default-mqtt-PubTopic,len=34
[291] OK
[292] CrCCsum=0x29a6,CrRCsum=0x29a6
[295] Valid Stored Dynamic Data
[298] Hdr=ESP32_WFM,BrdName=
[301] SSID=SSID1,PW=password1
[304] SSID1=SSID2,PW1=password2
[306] Server=account.ddns.net,Token=token
[310] Server1=account.duckdns.org,Token1=token1
[314] BT-Token=ESP32-BLE-WF,BLE-Token=
[318] Port=8080
[319] ======= End Config Data =======
[323] b:Nodat.Stay
[1169] stConf:SSID=TestPortal-ESP32,PW=TestPortalPass
[1169] IP=192.168.232.1,ch=8
F
Your stored Credentials :
MQTT Server = default-mqtt-server
Port = 1883
MQTT UserName = default-mqtt-username
MQTT PWD = default-mqtt-password
Subs Topics = default-mqtt-SubTopic
Pubs Topics = default-mqtt-PubTopic
FFFFF

[194511] id: = HueNet1
[194526] pw: = 12345678
[194543] id1: = HueNet2
[194558] pw1: = 12345678
[194572] sv: = your_account.duckdns.org
[194597] tk: = ********
[194619] sv1: = your_account.ddns.net
[194635] tk1: = ********
[194655] bttk: = ********
[194669] bltk: = ********
[194690] pt = 8080
[194729] nm: = ESP32
[194866] h:UpdSPIFFS /wfm_config.dat
[194897] SaveCfgFile 
[194897] WCSum=0x47ec
[194901] OK
[194904] SaveBkUpCfgFile 
[194908] OK
[194908] h:Rst
```

#### 1.3. After inputting valid credentials and reboot

```
Starting ESP32_BLE_WF using SPIFFS without SSL on ESP32_DEV
BlynkESP32_BT_WF v1.2.2
ESP_DoubleResetDetector v1.1.1
GPIO14 HIGH, Use WiFi
USE_BLYNK_WM: Blynk_WF begin
SPIFFS Flag read = 0xd0d04321
No doubleResetDetected
Saving config file...
Saving config file OK
[214] Hostname=GeigerCounter-BLE
[243] LoadCfgFile 
[243] OK
[243] ======= Start Stored Config Data =======
[243] Hdr=ESP32_WFM,BrdName=ESP32
[243] SSID=HueNet1,PW=12345678
[244] SSID1=HueNet2,PW1=12345678
[247] Server=your_account.duckdns.org,Token=********
[253] Server1=your_account.ddns.net,Token1=********
[259] BT-Token=********,BLE-Token=********
[267] Port=8080
[269] ======= End Config Data =======
[272] CCSum=0x4ace,RCSum=0x4ace
[302] LoadCredFile 
[303] CrR:pdata=default-mqtt-server,len=34
[303] CrR:pdata=1883,len=6
[303] CrR:pdata=default-mqtt-username,len=34
[303] CrR:pdata=default-mqtt-password,len=34
[307] CrR:pdata=default-mqtt-SubTopic,len=34
[311] CrR:pdata=default-mqtt-PubTopic,len=34
[315] OK
[316] CrCCsum=0x29a6,CrRCsum=0x29a6
[319] Valid Stored Dynamic Data
[322] Hdr=ESP32_WFM,BrdName=ESP32
[325] SSID=HueNet1,PW=12345678
[328] SSID1=HueNet2,PW1=12345678
[331] Server=your_account.duckdns.org,Token=********
[337] Server1=your_account.ddns.net,Token1=********
[343] BT-Token=********,BLE-Token=********
[351] Port=8080
[353] ======= End Config Data =======
[356] bg: noConfigPortal = true
[359] Connecting MultiWifi...
[5190] WiFi connected after time: 1
[5190] SSID:HueNet1,RSSI=-42
[5190] Channel:2,IP address:192.168.2.98
[5190] bg: WiFi OK. Try Blynk
[5191] 
    ___  __          __
   / _ )/ /_ _____  / /__
  / _  / / // / _ \/  '_/
 /____/_/\_, /_//_/_/\_\
        /___/ v0.6.1 on ESP32

[5204] BlynkArduinoClient.connect: Connecting to your_account.duckdns.org:8080
[5354] Ready (ping: 8ms).
[5424] Connected to Blynk Server = your_account.duckdns.org, Token = ********
[5424] bg: WiFi+Blynk OK
B
Your stored Credentials :
MQTT Server = default-mqtt-server
Port = 1883
MQTT UserName = default-mqtt-username
MQTT PWD = default-mqtt-password
Subs Topics = default-mqtt-SubTopic
Pubs Topics = default-mqtt-PubTopic
Stop doubleResetDetecting
Saving config file...
Saving config file OK
BBBB
```

---

#### 1.4 Enter non-persistent ConfigPortal

**Non-Persistent CP will be removed after first reset or time-out, even you didn't enter the CP**. You can optionally enter CP, input and `Save` config data.

```
CP Button Hit. Rebooting
[175599] setForcedCP non-Persistent
[175608] SaveCPFile 
[175611] OK
[175620] SaveBkUpCPFile 
[175624] OK
ets Jun  8 2016 00:22:57

Starting ESP32_BLE_WF using LITTLEFS without SSL on ESP32_DEV
BlynkESP32_BT_WF v1.2.2
ESP_DoubleResetDetector v1.1.1
GPIO14 HIGH, Use WiFi
USE_BLYNK_WM: Blynk_WF begin
LittleFS Flag read = 0xD0D04321
No doubleResetDetected
Saving config file...
Saving config file OK
[350] Hostname=GeigerCounter-BLE
[381] LoadCfgFile 
[386] OK
[386] ======= Start Stored Config Data =======
[386] Hdr=ESP32_WFM,BrdName=ESP32_BT_BLE
[386] SSID=HueNet1,PW=12345678
[386] SSID1=HueNet2,PW1=12345678
[389] Server=account.duckdns.org,Token=token
[395] Server1=account.duckdns.org,Token1=token1
[401] BT-Token=bt_token,BLE-Token=ble_token
[409] Port=8080
[411] ======= End Config Data =======
[414] CCSum=0x4b86,RCSum=0x4b86
[429] LoadCredFile 
[434] CrR:pdata=new-mqtt-server,len=34
[434] CrR:pdata=1883,len=6
[434] CrR:pdata=default-mqtt-username,len=34
[434] CrR:pdata=default-mqtt-password,len=34
[437] CrR:pdata=default-mqtt-SubTopic,len=34
[441] CrR:pdata=default-mqtt-PubTopic,len=34
[445] OK
[446] CrCCsum=0x280b,CrRCsum=0x280b
[449] Valid Stored Dynamic Data
[452] Hdr=ESP32_WFM,BrdName=ESP32_BT_BLE
[456] SSID=HueNet1,PW=12345678
[459] SSID1=HueNet2,PW1=12345678
[462] Server=account.duckdns.org,Token=token
[468] Server1=account.duckdns.org,Token1=token1
[474] BT-Token=bt_token,BLE-Token=ble_token
[482] Port=8080
[484] ======= End Config Data =======
[487] Check if isForcedCP
[500] LoadCPFile 
[504] OK
[504] bg: isForcedConfigPortal = true
[504] bg:Stay forever in CP:Forced-non-Persistent
[504] clearForcedCP
[514] SaveCPFile 
[518] OK
[528] SaveBkUpCPFile 
[532] OK
[1377] stConf:SSID=TestPortal-ESP32,PW=TestPortalPass
[1377] IP=192.168.232.1,ch=9
F
Your stored Credentials :
MQTT Server = new-mqtt-server
Port = 1883
MQTT UserName = default-mqtt-username
MQTT PWD = default-mqtt-password
Subs Topics = default-mqtt-SubTopic
Pubs Topics = default-mqtt-PubTopic
Stop doubleResetDetecting
Saving config file...
Saving config file OK
F
```

---

#### 1.5 Enter persistent ConfigPortal

**Persistent CP will remain even after resets or time-out**. The only way to get rid of Config Portal is to enter CP, input (even fake data or none) and `Save` config data. So be careful to use this feature.

```
Persistent CP Button Hit. Rebooting
[10487] setForcedCP Persistent
[10500] SaveCPFile 
[10505] OK
[10628] SaveBkUpCPFile 
[10676] OK
ets Jun  8 2016 00:22:57

Starting ESP32_BLE_WF using LITTLEFS without SSL on ESP32_DEV
BlynkESP32_BT_WF v1.2.2
ESP_DoubleResetDetector v1.1.1
GPIO14 HIGH, Use WiFi
USE_BLYNK_WM: Blynk_WF begin
LittleFS Flag read = 0xD0D04321
No doubleResetDetected
Saving config file...
Saving config file OK
[399] Hostname=GeigerCounter-BLE
[421] LoadCfgFile 
[425] OK
[425] ======= Start Stored Config Data =======
[425] Hdr=ESP32_WFM,BrdName=ESP32_BT_BLE
[425] SSID=HueNet1,PW=12345678
[426] SSID1=HueNet2,PW1=12345678
[429] Server=account.duckdns.org,Token=token
[435] Server1=account.duckdns.org,Token1=token1
[441] BT-Token=bt_token,BLE-Token=ble_token
[449] Port=8080
[450] ======= End Config Data =======
[454] CCSum=0x4b86,RCSum=0x4b86
[465] LoadCredFile 
[468] CrR:pdata=new-mqtt-server,len=34
[468] CrR:pdata=1883,len=6
[468] CrR:pdata=default-mqtt-username,len=34
[468] CrR:pdata=default-mqtt-password,len=34
[472] CrR:pdata=default-mqtt-SubTopic,len=34
[476] CrR:pdata=default-mqtt-PubTopic,len=34
[480] OK
[481] CrCCsum=0x280b,CrRCsum=0x280b
[485] Valid Stored Dynamic Data
[487] Hdr=ESP32_WFM,BrdName=ESP32_BT_BLE
[491] SSID=HueNet1,PW=12345678
[494] SSID1=HueNet2,PW1=12345678
[497] Server=account.duckdns.org,Token=token
[503] Server1=account.duckdns.org,Token1=token1
[509] BT-Token=bt_token,BLE-Token=ble_token
[517] Port=8080
[519] ======= End Config Data =======
[522] Check if isForcedCP
[532] LoadCPFile 
[535] OK
[535] bg: isForcedConfigPortal = true
[535] bg:Stay forever in CP:Forced-Persistent
[1380] stConf:SSID=TestPortal-ESP32,PW=TestPortalPass
[1380] IP=192.168.232.1,ch=1
F
Your stored Credentials :
MQTT Server = new-mqtt-server
Port = 1883
MQTT UserName = default-mqtt-username
MQTT PWD = default-mqtt-password
Subs Topics = default-mqtt-SubTopic
Pubs Topics = default-mqtt-PubTopic
Stop doubleResetDetecting
Saving config file...
Saving config file OK
FFFF
```

---
---

### Debug

Debug is enabled by default on Serial.

You can also change the debugging level from 0 to 4

```cpp
#define BLYNK_PRINT                   Serial

#define ESP32_BLE_WF_DEBUG            true

#define DOUBLERESETDETECTOR_DEBUG     true
#define BLYNK_WM_DEBUG                3
```

---

### Troubleshooting

If you get compilation errors, more often than not, you may need to install a newer version of the core for Arduino boards.

Sometimes, the library will only work if you update the board core to the latest version because I am using newly added functions.

---
---


### Issues ###

Submit issues to: [BlynkESP32_BT_WF issues](https://github.com/khoih-prog/BlynkESP32_BT_WF/issues)

---
---

## TO DO

1. Same features for other boards with WiFi / BT
2. Optimize library so that smaller code size. Currently 2 instances of Blynk coexist and don't share code.
3. Add support to ESP32_S2 and ESP32_C3
4. Add support to ESP32 core 2.0.0+

---

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
12. Add checksum for config data integrity
13. Add clearConfigData() to enable forcing into ConfigPortal Mode when necessary
14. Add MultiWiFi feature to enable reconnect to the best / available WiFi AP.
15. Add MultiBlynk feature to enable reconnect to the best / available Blynk Server.
16. WiFi Password max length is 63, as in WPA2 standards
17. Permit to input special chars such as **%** and **#** into data fields.
18. Add Dynamic Custom Parameters with checksum
19. Add function to configure AP Channel (fixed or random) to avoid channel conflict.
20. Default Credentials and dynamic parameters
21. **DoubleDetectDetector** to force Config Portal when double reset is detected within predetermined time, default 10s.
22. Configurable Config Portal Title
23. Re-structure all examples to separate Credentials / Defines / Dynamic Params / Code so that you can change Credentials / Dynamic Params quickly for each device.
24. Add functions to control Config Portal from software or **Virtual Switches**.
25. Configurable **Customs HTML Headers**, including Customs Style, Customs Head Elements, CORS Header
26. Permit optionally inputting one set of WiFi SSID/PWD by using `REQUIRE_ONE_SET_SSID_PW == true`
27. Enforce WiFi PWD minimum length of 8 chars
28. Enable **scan of WiFi networks** for selection in Configuration Portal
29. Add auto-reconnect feature for BLE.

---
---

### Contributions and thanks

1. Thanks to [Crosswalkersam](https://community.blynk.cc/u/Crosswalkersam) for the original code and request to inspire the work. See [Select connection Type via Switch](https://community.blynk.cc/t/select-connection-type-via-switch/43176)
2. Thanks to [Miguel Alexandre Wisintainer](https://github.com/tcpipchip) for working with, developing, debugging, testing and contributing example [PET_Check](examples/PET_Check). See also [nina-w102-ble-detector-presenca-de-pet](https://nina-b302-scanner-presenca.blogspot.com/2020/06/nina-w102-ble-detector-presenca-de-pet.html)
3. Thanks to [Thor Johnson](https://github.com/thorathome) and [Thor Johnson in Blynk](https://community.blynk.cc/u/thorathome) to test, find bug, suggest and encourage to add those new features in [Blynk_WiFiManager library](https://github.com/khoih-prog/Blynk_WM) v1.0.13, such as Default Credentials/Dynamic Parms, Configurable Config Portal Title, DRD.
Check these new features thanks to his direct contribution and/or enhancement requests :
  * [How to trigger a Config Portal from code #25](https://github.com/khoih-prog/Blynk_WM/issues/25)
  * [Good new feature: Blynk.resetAndEnterConfigPortal() Thanks & question #27](https://github.com/khoih-prog/Blynk_WM/issues/27)
4. Thanks to [Michael H. "bizprof"](https://github.com/bizprof). With the impressive new feature :
  - `Enable scan of WiFi networks for selection in Configuration Portal`. Check [PR for v1.3.0 - Enable scan of WiFi networks #10](https://github.com/khoih-prog/WiFiManager_NINA_Lite/pull/10) leading to v1.2.0
5. Thanks to [Valeria](https://github.com/Valeria) to provide the amazing fix to permit BLE auto-reconnect. Check [Handle BLE disconnects #2](https://github.com/khoih-prog/Blynk_Async_ESP32_BT_WF/issues/2)

<table>
  <tr>
    <td align="center"><a href="https://github.com/Crosswalkersam"><img src="https://github.com/Crosswalkersam.png" width="100px;" alt="Crosswalkersam"/><br /><sub><b>Crosswalkersam</b></sub></a><br /></td>
    <td align="center"><a href="https://github.com/tcpipchip"><img src="https://github.com/tcpipchip.png" width="100px;" alt="tcpipchip"/><br /><sub><b>⭐️ tcpipchip</b></sub></a><br /></td>
    <td align="center"><a href="https://github.com/thorathome"><img src="https://github.com/thorathome.png" width="100px;" alt="thorathome"/><br /><sub><b>⭐️⭐️ Thor Johnson</b></sub></a><br /></td>
    <td align="center"><a href="https://github.com/bizprof"><img src="https://github.com/bizprof.png" width="100px;" alt="bizprof"/><br /><sub><b>⭐️⭐️ Michael H. "bizprof"</b></sub></a><br /></td>
    <td align="center"><a href="https://github.com/Valeria"><img src="https://github.com/Valeria.png" width="100px;" alt="Valeria"/><br /><sub><b>Valeria</b></sub></a><br /></td>
  </tr> 
</table>

---

### Contributing

If you want to contribute to this project:

- Report bugs and errors
- Ask for enhancements
- Create issues and pull requests
- Tell other people about this library

---

### License

- The library is licensed under [MIT](https://github.com/khoih-prog/BlynkESP32_BT_WF/blob/master/LICENSE)

---

### Copyright

Copyright 2020- Khoi Hoang
