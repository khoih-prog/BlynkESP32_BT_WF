## BlynkESP32_BT_WF

[![arduino-library-badge](https://www.ardu-badge.com/badge/BlynkESP32_BT_WF.svg?)](https://www.ardu-badge.com/BlynkESP32_BT_WF)
[![GitHub release](https://img.shields.io/github/release/khoih-prog/BlynkESP32_BT_WF.svg)](https://github.com/khoih-prog/BlynkESP32_BT_WF/releases)
[![GitHub](https://img.shields.io/github/license/mashape/apistatus.svg)](https://github.com/khoih-prog/BlynkESP32_BT_WF/blob/master/LICENSE)
[![contributions welcome](https://img.shields.io/badge/contributions-welcome-brightgreen.svg?style=flat)](#Contributing)
[![GitHub issues](https://img.shields.io/github/issues/khoih-prog/BlynkESP32_BT_WF.svg)](http://github.com/khoih-prog/BlynkESP32_BT_WF/issues)

### Major Releases v1.0.5

1. ***Multiple WiFi Credentials (SSID, Password)*** and system will autoconnect to the best and available WiFi SSID.
2. ***Multiple Blynk Credentials (Server, Token)*** and system will autoconnect to the available Blynk Servers.
3. New ***powerful-yet-simple-to-use feature to enable adding dynamic custom parameters*** from sketch and input using the same Config Portal. Config Portal will be auto-adjusted to match the number of dynamic parameters.
4. Dynamic custom parameters to be saved ***automatically in EEPROM, or SPIFFS***.
5. WiFi Password max length increased to 63 from 31, according to WPA2 standard.
6. Permit to input special chars such as ***%*** and ***#*** into data fields.
7. Config Portal AP Channel is configurable (either static or random channel) to avoid channel conflict to other APs.

### Releases v1.0.4

1. Enhance Config Portal GUI.
2. Reduce code size.

By design, Blynk user can run ESP32 boards with ***either WiFi or BT/BLE*** by using different sketches, and have to upload / update firmware to change. This library enables user to include both Blynk BT / BLE and WiFi libraries in one sketch, ***run both WiFi and BT/BLE simultaneously, or select one to use at runtime after reboot.***

This library also supports (auto)connection to ***MultiWiFi and MultiBlynk, dynamic custom as well as static parameters in Config Portal***. Eliminate hardcoding your Wifi and Blynk credentials and configuration data saved in either SPIFFS or EEPROM.

Now from Version 1.0.2, you can eliminate `hardcoding` your Wifi and Blynk credentials, thanks to the `Smart Config Portal`, and have Credentials (WiFi SID/PW, Blynk WiFi/BT/BLE Tokens/ Hardware Port) saved in either SPIFFS or EEPROM.

## Prerequisite
1. [`Arduino IDE 1.8.12 or later` for Arduino](https://www.arduino.cc/en/Main/Software)
2. [`Blynk library 0.6.1 or later`](https://github.com/blynkkk/blynk-library/releases)
3. [`ESP32 core 1.0.4 or later`](https://github.com/espressif/arduino-esp32/releases) for ESP32 boards

### Installation

#### Use Arduino Library Manager
The suggested and easiest way is to use `Arduino Library Manager`. Search for `BlynkESP32_BT_WF`, then select / install the latest version.
You can also use this link [![arduino-library-badge](https://www.ardu-badge.com/badge/BlynkESP32_BT_WF.svg?)](https://www.ardu-badge.com/BlynkESP32_BT_WF) for more detailed instructions.

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

### How to add dynamic parameters from sketch

- To add custom parameters, just modify from the example below

```cpp
#define USE_DYNAMIC_PARAMETERS     true

/////////////// Start dynamic Credentials ///////////////

//Defined in <BlynkSimpleEsp32_WFM.h>
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
char MQTT_Server  [MAX_MQTT_SERVER_LEN + 1]   = "";

#define MAX_MQTT_PORT_LEN        6
char MQTT_Port   [MAX_MQTT_PORT_LEN + 1]  = "";

#define MAX_MQTT_USERNAME_LEN      34
char MQTT_UserName  [MAX_MQTT_USERNAME_LEN + 1]   = "";

#define MAX_MQTT_PW_LEN        34
char MQTT_PW   [MAX_MQTT_PW_LEN + 1]  = "";

#define MAX_MQTT_SUBS_TOPIC_LEN      34
char MQTT_SubsTopic  [MAX_MQTT_SUBS_TOPIC_LEN + 1]   = "";

#define MAX_MQTT_PUB_TOPIC_LEN       34
char MQTT_PubTopic   [MAX_MQTT_PUB_TOPIC_LEN + 1]  = "";

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
- If you don't need to add dynamic parameters, just use the following in sketch

```cpp
#define USE_DYNAMIC_PARAMETERS     false
```


That's it.

Also see examples: 
1. [ESP32_BLE_WF](examples/ESP32_BLE_WF)
2. [ESP32_BT_WF](examples/ESP32_BT_WF)
3. [Geiger_Counter_BLE](examples/Geiger_Counter_BLE)
4. [Geiger_Counter_BT](examples/Geiger_Counter_BT)
5. [Geiger_Counter_OLED](examples/Geiger_Counter_OLED)
6. [Geiger_Counter_OLED_BT_WF](examples/Geiger_Counter_OLED_BT_WF)
7. [Geiger_Counter_OLED_BT_BLE_WF](examples/Geiger_Counter_OLED_BT_BLE_WF)

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


## So, how it works?
If the necessary credentials are not valid or it cannot connect to the Blynk server in 30 seconds, it will switch to `Configuration Mode`. You will see your built-in LED turned ON. In `Configuration Mode`, it starts an access point called `ESP_xxxxxx`. Connect to it using password `MyESP_xxxxxx` .

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


## Example [ESP32_BLE_WF](examples/ESP32_BLE_WF)

Please take a look at examples, as well.

```cpp
#ifndef ESP32
#error This code is intended to run on the ESP32 platform! Please check your Tools->Board setting.
#endif

#define BLYNK_PRINT Serial

#define ESP32_BLE_WF_DEBUG       true

#define USE_BLYNK_WM      true
//#define USE_BLYNK_WM      false

//#define USE_SPIFFS                  true
#define USE_SPIFFS                  false

#if (!USE_SPIFFS)
// EEPROM_SIZE must be <= 2048 and >= CONFIG_DATA_SIZE
#define EEPROM_SIZE    (2 * 1024)
// EEPROM_START + CONFIG_DATA_SIZE must be <= EEPROM_SIZE
#define EEPROM_START   0
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

#define USE_DYNAMIC_PARAMETERS      true

/////////////// Start dynamic Credentials ///////////////

//Defined in <BlynkSimpleEsp32_WFM.h>
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
char MQTT_Server  [MAX_MQTT_SERVER_LEN + 1]   = "";

#define MAX_MQTT_PORT_LEN        6
char MQTT_Port   [MAX_MQTT_PORT_LEN + 1]  = "";

#define MAX_MQTT_USERNAME_LEN      34
char MQTT_UserName  [MAX_MQTT_USERNAME_LEN + 1]   = "";

#define MAX_MQTT_PW_LEN        34
char MQTT_PW   [MAX_MQTT_PW_LEN + 1]  = "";

#define MAX_MQTT_SUBS_TOPIC_LEN      34
char MQTT_SubsTopic  [MAX_MQTT_SUBS_TOPIC_LEN + 1]   = "";

#define MAX_MQTT_PUB_TOPIC_LEN       34
char MQTT_PubTopic   [MAX_MQTT_PUB_TOPIC_LEN + 1]  = "";

MenuItem myMenuItems [] =
{
  { "mqtt", "MQTT Server",      MQTT_Server,      MAX_MQTT_SERVER_LEN },
  { "mqpt", "Port",             MQTT_Port,        MAX_MQTT_PORT_LEN   },
  { "user", "MQTT UserName",    MQTT_UserName,    MAX_MQTT_USERNAME_LEN },
  { "mqpw", "MQTT PWD",         MQTT_PW,          MAX_MQTT_PW_LEN },
  { "subs", "Subs Topics",      MQTT_SubsTopic,   MAX_MQTT_SUBS_TOPIC_LEN },
  { "pubs", "Pubs Topics",      MQTT_PubTopic,    MAX_MQTT_PUB_TOPIC_LEN },
};

#else

MenuItem myMenuItems [] = {};

#endif

uint16_t NUM_MENU_ITEMS = sizeof(myMenuItems) / sizeof(MenuItem);  //MenuItemSize;
/////// // End dynamic Credentials ///////////

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
    Serial.print("B");
  }
  else
  {
    Serial.print("F");
  }

  if (num == 80)
  {
    Serial.println();
    num = 1;
  }
  else if (num++ % 10 == 0)
  {
    Serial.print(" ");
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
  Serial.println(F("\nStarting ESP32_BLE_WF"));

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
    // Set config portal channel, defalut = 1. Use 0 => random channel from 1-13 to avoid conflict
    Blynk_WF.setConfigPortalChannel(0);
    
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
  Serial.println("\nYour stored Credentials :");

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

The following is the sample terminal output when running example [Geiger_Counter_OLED_BT_BLE_WF](examples/Geiger_Counter_OLED_BT_BLE_WF)

1. No Config Data => Config Portal

```

Starting Geiger-Counter-OLED-BT-BLE-WF
Use WiFi to connect Blynk
[346] Hostname=GeigerCounter-WiFi
[352] CCSum=0xbedc,RCSum=0xffffffff
[352] CrCCSum=0xaf50,CrRCSum=0xffffffff
[352] InitEEPROM,sz=2048,Datasz=628
[352] pdata=blank,len=34
[353] pdata=blank,len=6
[355] pdata=blank,len=34
[357] pdata=blank,len=34
[360] pdata=blank,len=34
[362] pdata=blank,len=34
[364] CrCCSum=0xc30
[439] b:Nodat.Stay
[1285] stConf:SSID=ESP_1CA4AE30,PW=MyESP_1CA4AE30
[1285] IP=192.168.4.1,ch=7
Use BLE to connect Blynk
[1392] CCSum=0x199d,RCSum=0x0
[1392] CrCCSum=0xc30,CrRCSum=0xc30
[1392] InitEEPROM,sz=2048,Datasz=628
[1392] pdata=blank,len=34
[1392] pdata=blank,len=6
[1395] pdata=blank,len=34
[1397] pdata=blank,len=34
[1399] pdata=blank,len=34
[1402] pdata=blank,len=34
[1404] CrCCSum=0xc30
BLE_auth = blank
No valid stored BLE auth. Have to run WiFi then enter config portal
Your stored Credentials :
MQTT Server = blank
Port = blank
MQTT UserName = blank
MQTT PWD = blank
Subs Topics = blank
Pubs Topics = blank
FFFFF
```

2. Input valid credentials => reboot

```
Starting Geiger-Counter-OLED-BT-BLE-WF
Use WiFi to connect Blynk
[347] Hostname=GeigerCounter-WiFi
[353] CCSum=0x4c8e,RCSum=0x4c8e
[353] CrCCSum=0x1ef9,CrRCSum=0x1ef9
[353] Hdr=ESP32_WFM,BrdName=ESP32_BLE_BT_WM-TTGO
[353] SSID=HueNet1,PW=****
[355] SSID1=HueNet,PW1=****
[358] Server=account.ddns.net,Token=****
[364] Server1=account.duckdns.org,Token1=****
[370] BT-Token=****,BLE-Token=****
[378] Port=8080
[380] Connecting MultiWifi...
[4994] WiFi connected after time: 1
[4994] SSID:HueNet,RSSI=-38
[4994] Channel:10,IP=192.168.2.69
[4994] b:WOK.TryB
[4994] 
    ___  __          __
   / _ )/ /_ _____  / /__
  / _  / / // / _ \/  '_/
 /____/_/\_, /_//_/_/\_\
        /___/ v0.6.1 on ESP32

[5006] BlynkArduinoClient.connect: Connecting to account.ddns.net:8080
[5040] Ready (ping: 12ms).
[5111] Conn2BlynkServer=account.ddns.net,Token=****
[5111] b:WBOK
Use BLE to connect Blynk
BLE_auth = ****
[5114] 
    ___  __          __
   / _ )/ /_ _____  / /__
  / _  / / // / _ \/  '_/
 /____/_/\_, /_//_/_/\_\
        /___/ v0.6.1 on ESP32


Your stored Credentials :
MQTT Server = mqtt.ddns.net
Port = 1883
MQTT UserName = mqtt-user
MQTT PWD = mqtt-password
Subs Topics = SubTopic_ESP32_BLE_BT_WM
Pubs Topics = PubTopic_ESP32_BLE_BT_WM
cpm =    0 - RadiationValue = 0.000 uSv/h - Equivalent RadiationDose = 0.0000 uSv
B[27863] BLECon
[29155] Ready
cpm =   30 - RadiationValue = 0.197 uSv/h - Equivalent RadiationDose = 0.0008 uSv
cpm =   60 - RadiationValue = 0.395 uSv/h - Equivalent RadiationDose = 0.0025 uSv
cpm =   90 - RadiationValue = 0.592 uSv/h - Equivalent RadiationDose = 0.0049 uSv
cpm =  120 - RadiationValue = 0.790 uSv/h - Equivalent RadiationDose = 0.0082 uSv
cpm =  150 - RadiationValue = 0.987 uSv/h - Equivalent RadiationDose = 0.0123 uSv
cpm =  180 - RadiationValue = 1.184 uSv/h - Equivalent RadiationDose = 0.0173 uSv
cpm =  210 - RadiationValue = 1.382 uSv/h - Equivalent RadiationDose = 0.0230 uSv
cpm =  240 - RadiationValue = 1.579 uSv/h - Equivalent RadiationDose = 0.0296 uSv
cpm =  270 - RadiationValue = 1.777 uSv/h - Equivalent RadiationDose = 0.0370 uSv
 cpm =  300 - RadiationValue = 1.974 uSv/h - Equivalent RadiationDose = 0.0452 uSv
cpm =  330 - RadiationValue = 2.171 uSv/h - Equivalent RadiationDose = 0.0543 uSv
cpm =  360 - RadiationValue = 2.369 uSv/h - Equivalent RadiationDose = 0.0642 uSv
cpm =  390 - RadiationValue = 2.566 uSv/h - Equivalent RadiationDose = 0.0748 uSv
cpm =  420 - RadiationValue = 2.764 uSv/h - Equivalent RadiationDose = 0.0864 uSv
cpm =  450 - RadiationValue = 2.961 uSv/h - Equivalent RadiationDose = 0.0987 uSv
cpm =  480 - RadiationValue = 3.158 uSv/h - Equivalent RadiationDose = 0.1119 uSv
cpm =  510 - RadiationValue = 3.356 uSv/h - Equivalent RadiationDose = 0.1258 uSv
cpm =  540 - RadiationValue = 3.553 uSv/h - Equivalent RadiationDose = 0.1406 uSv
cpm =  570 - RadiationValue = 3.751 uSv/h - Equivalent RadiationDose = 0.1563 uSv
cpm =  600 - RadiationValue = 3.948 uSv/h - Equivalent RadiationDose = 0.1727 uSv

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
 12. Add checksum for config data integrity
 13. Add clearConfigData() to enable forcing into ConfigPortal Mode when necessary
 14. Add MultiWiFi feature to enable reconnect to the best / available WiFi AP.
 15. Add MultiBlynk feature to enable reconnect to the best / available Blynk Server.
 16. WiFi Password max length is 63, as in WPA2 standards
 17. Permit to input special chars such as ***%*** and ***#*** into data fields.
 18. Add Dynamic Custom Parameters with checksum
 19. Add function to configure AP Channel to avoid channel conflict.

### Major Releases v1.0.5

***Why this version***

1. ***Multiple WiFi Credentials (SSID, Password)*** and system will autoconnect to the best and available WiFi SSID.
2. ***Multiple Blynk Credentials (Server, Token)*** and system will autoconnect to the available Blynk Servers.
3. New ***powerful-yet-simple-to-use feature to enable adding dynamic custom parameters*** from sketch and input using the same Config Portal. Config Portal will be auto-adjusted to match the number of dynamic parameters.
4. Dynamic custom parameters to be saved ***automatically in EEPROM, or SPIFFS***.
5. WiFi Password max length increased to 63 from 31, according to WPA2 standard.
6. Permit to input special chars such as ***%*** and ***#*** into data fields.
7. Config Portal AP Channel is configurable (either static or random channel) to avoid channel conflict to other APs.

### Releases v1.0.4

***Why this version***

1. Enhance Config Portal GUI.
2. Reduce code size.

### Releases v1.0.3

***Why this version***

1. Add checksum for config data integrity.
2. Add clearConfigData() to enable forcing into ConfigPortal Mode when necessary
 
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
