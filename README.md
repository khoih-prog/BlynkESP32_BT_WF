## BlynkESP32_BT_WF

[![arduino-library-badge](https://www.ardu-badge.com/badge/BlynkESP32_BT_WF.svg?)](https://www.ardu-badge.com/BlynkESP32_BT_WF)
[![GitHub release](https://img.shields.io/github/release/khoih-prog/BlynkESP32_BT_WF.svg)](https://github.com/khoih-prog/BlynkESP32_BT_WF/releases)
[![GitHub](https://img.shields.io/github/license/mashape/apistatus.svg)](https://github.com/khoih-prog/BlynkESP32_BT_WF/blob/master/LICENSE)
[![contributions welcome](https://img.shields.io/badge/contributions-welcome-brightgreen.svg?style=flat)](#Contributing)
[![GitHub issues](https://img.shields.io/github/issues/khoih-prog/BlynkESP32_BT_WF.svg)](http://github.com/khoih-prog/BlynkESP32_BT_WF/issues)

---

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

By design, Blynk user can run ESP32 boards with **either WiFi or BT/BLE** by using different sketches, and have to upload / update firmware to change. This library enables user to include both Blynk BT / BLE and WiFi libraries in one sketch, **run both WiFi and BT/BLE simultaneously, or select one to use at runtime after reboot.**

This library also supports (auto)connection to **MultiWiFi and MultiBlynk, dynamic custom as well as static parameters in Config Portal**. Eliminate hardcoding your Wifi and Blynk credentials and configuration data saved in either SPIFFS or EEPROM.

Now from Version 1.0.2, you can eliminate `hardcoding` your Wifi and Blynk credentials, thanks to the `Smart Config Portal`, and have Credentials (WiFi SID/PW, Blynk WiFi/BT/BLE Tokens/ Hardware Port) saved in either SPIFFS or EEPROM.

---

## Prerequisite
1. [`Arduino IDE 1.8.12+` for Arduino](https://www.arduino.cc/en/Main/Software)
2. [`Blynk library 0.6.1+`](https://github.com/blynkkk/blynk-library/releases)
3. [`ESP32 core 1.0.4+`](https://github.com/espressif/arduino-esp32/releases) for ESP32 boards
4. [`ESP_DoubleResetDetector library 1.0.3+`](https://github.com/khoih-prog/ESP_DoubleResetDetector) to use DRD feature. To install, check [![arduino-library-badge](https://www.ardu-badge.com/badge/ESP_DoubleResetDetector.svg?)](https://www.ardu-badge.com/ESP_DoubleResetDetector).

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
3. Install **BlynkESP32_BT_WF** library by using [Library Manager](https://docs.platformio.org/en/latest/librarymanager/). Search for **BlynkESP32_BT_WF** in [Platform.io Author's Libraries](https://platformio.org/lib/search?query=author:%22Khoi%20Hoang%22)
4. Use included [platformio.ini](examples/platformio/platformio.ini) file from examples to ensure that all dependent libraries will installed automatically.

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

That's it.

Also see examples: 
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

<p align="center">
    <img src="https://github.com/khoih-prog/BlynkESP32_BT_WF/blob/master/pics/ConfigPortal.png">
</p>

Then click `Save`. After you restarted, you will see your built-in LED turned OFF. That means, it connected to your Blynk server successfully.

---
---

## Example [ESP32_BLE_WF](examples/ESP32_BLE_WF)

#### 1. File [ESP32_BLE_WF.ino](examples/ESP32_BLE_WF/ESP32_BLE_WF.ino)

```cpp
#include "defines.h"
#include "Credentials.h"
#include "dynamicParams.h"

bool USE_BLE = true;
long timePreviousMeassure  = 0;

#define WIFI_BLE_SELECTION_PIN     14   //Pin D14 mapped to pin GPIO14/HSPI_SCK/ADC16/TOUCH6/TMS of ESP32

BlynkTimer timer;

#include <Ticker.h>
Ticker     led_ticker;

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

void setup()
{
  Serial.begin(115200);
  while (!Serial);

#if ( USE_SPIFFS)
  Serial.print(F("\nStarting ESP32_BLE_WF using SPIFFS"));
#else
  Serial.print(F("\nStarting ESP32_BLE_WF using EEPROM"));
#endif

#if USE_SSL
  Serial.println(" with SSL on " + String(ARDUINO_BOARD));
#else
  Serial.println(" without SSL on " + String(ARDUINO_BOARD));
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
void displayCredentials(void)
{
  Serial.println(F("\nYour stored Credentials :"));

  for (int i = 0; i < NUM_MENU_ITEMS; i++)
  {
    Serial.println(String(myMenuItems[i].displayName) + " = " + myMenuItems[i].pdata);
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
  static bool displayedCredentials = false;

  if (!displayedCredentials)
  {
    for (int i = 0; i < NUM_MENU_ITEMS; i++)
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

#define BLYNK_PRINT               Serial

#define ESP32_BLE_WF_DEBUG        true

#define DOUBLERESETDETECTOR_DEBUG     true
#define BLYNK_WM_DEBUG                3

// Not use #define USE_SPIFFS  => using EEPROM for configuration data in WiFiManager
// #define USE_SPIFFS    false => using EEPROM for configuration data in WiFiManager
// #define USE_SPIFFS    true  => using SPIFFS for configuration data in WiFiManager
// Those above #define's must be placed before #include <BlynkSimpleEsp32_WFM.h>

#define USE_SPIFFS                  true
//#define USE_SPIFFS                  false

#if (!USE_SPIFFS)
  // EEPROM_SIZE must be <= 2048 and >= CONFIG_DATA_SIZE (currently 172 bytes)
  #define EEPROM_SIZE    (2 * 1024)
  // EEPROM_START + CONFIG_DATA_SIZE must be <= EEPROM_SIZE
  #define EEPROM_START   0
#endif

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

#endif  // USE_BLYNK_WM

#endif      //dynamicParams_h

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

### Debug Termimal Output Samples

The following is the sample terminal output when running example [ESP32_BLE_WF](examples/ESP32_BLE_WF)

#### 1. No Config Data => Config Portal. Input valid credentials => reboot

```
Starting ESP32_BLE_WF using SPIFFS without SSL on ESP32_DEV
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

#### 2. DRD => Config Portal. Input valid credentials => reboot

```
Starting ESP32_BLE_WF using SPIFFS without SSL on ESP32_DEV
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

#### 3. After inputting valid credentials and reboot

```
Starting ESP32_BLE_WF using SPIFFS without SSL on ESP32_DEV
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
---

## TO DO

1. Same features for other boards with WiFi / BT
2. Optimize library so that smaller code size. Currently 2 instances of Blynk coexist and don't share code.

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

---
---

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

---
---

### Contributions and thanks

1. Thanks to [Crosswalkersam](https://community.blynk.cc/u/Crosswalkersam) for the original code and request to inspire the work. See [Select connection Type via Switch](https://community.blynk.cc/t/select-connection-type-via-switch/43176)
2. Thanks to [Miguel Alexandre Wisintainer](https://github.com/tcpipchip) for working with, developing, debugging, testing and contributing example [PET_Check](examples/PET_Check). See also [nina-w102-ble-detector-presenca-de-pet](https://nina-b302-scanner-presenca.blogspot.com/2020/06/nina-w102-ble-detector-presenca-de-pet.html)

<table>
  <tr>
    <td align="center"><a href="https://github.com/Crosswalkersam"><img src="https://github.com/Crosswalkersam.png" width="100px;" alt="Crosswalkersam"/><br /><sub><b>Crosswalkersam</b></sub></a><br /></td>
    <td align="center"><a href="https://github.com/tcpipchip"><img src="https://github.com/tcpipchip.png" width="100px;" alt="tcpipchip"/><br /><sub><b>tcpipchip</b></sub></a><br /></td>
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

- The library is licensed under [MIT](https://github.com/khoih-prog/WebSockets2_Generic/blob/master/LICENSE)

---

### Copyright

Copyright 2020- Khoi Hoang
