/****************************************************************************************************************************
   Geiger_Counter_BLE.ino
   For ESP32 using WiFi along with BlueTooth BLE

   BlynkESP32_BT_WF is a library for inclusion of both ESP32 Blynk BT/BLE and WiFi libraries. Then select either one or both at runtime.
   Forked from Blynk library v0.6.1 https://github.com/blynkkk/blynk-library/releases
   Built by Khoi Hoang https://github.com/khoih-prog/BlynkGSM_ESPManager
   Licensed under MIT license
   Version: 1.0.5

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
    1.0.5   K Hoang      18/04/2020 MultiWiFi/Blynk. Dynamic custom parameters. SSID password maxlen is 63 now. 
                                    Permit special chars # and % in input data.
 *****************************************************************************************************************************/
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

#define WIFI_BLE_SELECTION_PIN     14   //Pin D14 mapped to pin GPIO14/HSPI_SCK/ADC16/TOUCH6/TMS of ESP32
#define GEIGER_INPUT_PIN           18   // Pin D18 mapped to pin GPIO18/VSPI_SCK of ESP32
#define VOLTAGER_INPUT_PIN         36   // Pin D36 mapped to pin GPIO36/ADC0/SVP of ESP32   

#define CONV_FACTOR                   0.00658
#define SCREEN_WIDTH                  128
#define SCREEN_HEIGHT                 32
#define OLED_RESET                    4
#define DEBOUNCE_TIME_MICRO_SEC       4200L
#define MEASURE_INTERVAL_MS           20000L
#define COUNT_PER_MIN_CONVERSION      (60000 / MEASURE_INTERVAL_MS)
#define VOLTAGE_FACTOR                ( ( 4.2 * (3667 / 3300) ) / 4096 )

float voltage               = 0;
long  countPerMinute        = 0;
long  timePrevious          = 0;
long  timePreviousMeassure  = 0;
long  _time                 = 0;
long  countPrevious         = 0;
float radiationValue        = 0.0;
float radiationDose         = 0;

void IRAM_ATTR countPulse();
volatile unsigned long last_micros;
volatile long          count = 0;

BlynkTimer timer;

#include <Ticker.h>
Ticker     led_ticker;

void IRAM_ATTR countPulse()
{
  if ((long)(micros() - last_micros) >= DEBOUNCE_TIME_MICRO_SEC)
  {
    count++;
    last_micros = micros();
  }
}

void sendDatatoBlynk()
{
#if BLYNK_USE_BLE_ONLY
  Blynk_BLE.virtualWrite(V1, countPerMinute);
  Blynk_BLE.virtualWrite(V3, radiationValue);
  Blynk_BLE.virtualWrite(V5, radiationDose);
  Blynk_BLE.virtualWrite(V7, voltage);
#else
  if (USE_BLE)
  {
    Blynk_BLE.virtualWrite(V1, countPerMinute);
    Blynk_BLE.virtualWrite(V3, radiationValue);
    Blynk_BLE.virtualWrite(V5, radiationDose);
    Blynk_BLE.virtualWrite(V7, voltage);
  }
  else
  {
    Blynk_WF.virtualWrite(V1, countPerMinute);
    Blynk_WF.virtualWrite(V3, radiationValue);
    Blynk_WF.virtualWrite(V5, radiationDose);
    Blynk_WF.virtualWrite(V7, voltage);
  }
#endif
}

void Serial_Display()
{
  Serial.print(F("cpm = "));
  Serial.printf("%4d", countPerMinute);
  Serial.print(F(" - "));
  Serial.print(F("RadiationValue = "));
  Serial.printf("%5.3f", radiationValue);
  Serial.print(F(" uSv/h"));
  Serial.print(F(" - "));
  Serial.print(F("Equivalent RadiationDose = "));
  Serial.printf("%6.4f", radiationDose);
  Serial.println(F(" uSv"));
}

void set_led(byte status)
{
  digitalWrite(LED_BUILTIN, status);
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

#define USE_SIMULATION    true
//#define USE_SIMULATION    false

void checkStatus()
{
  static float voltage;

  if (millis() - timePreviousMeassure > MEASURE_INTERVAL_MS)
  {
    if (!USE_BLE)
    {
      if (Blynk.connected())
        Serial.println(F("B"));
      else
        Serial.println(F("F"));
    }

    timePreviousMeassure = millis();

    noInterrupts();
    countPerMinute = COUNT_PER_MIN_CONVERSION * count;
    interrupts();

    radiationValue = countPerMinute * CONV_FACTOR;
    radiationDose = radiationDose + (radiationValue / float(240.0));

    // can optimize this calculation
    voltage = (float) analogRead(VOLTAGER_INPUT_PIN) * VOLTAGE_FACTOR;

    if (radiationDose > 99.999)
    {
      radiationDose = 0;
    }

    Serial_Display();

#if USE_SIMULATION
    count += 10;
    if (count >= 1000)
      count = 0;
#else
    count = 0;
#endif

    // report Blynk connection
    heartBeatPrint();
  }
}

char BLE_Device_Name[] = "GeigerCounter-BLE";

void setup()
{
  Serial.begin(115200);
  Serial.println(F("\nStarting Geiger-Counter"));

  pinMode(GEIGER_INPUT_PIN, INPUT);
  attachInterrupt(GEIGER_INPUT_PIN, countPulse, HIGH);

#if BLYNK_USE_BLE_ONLY
  Blynk_BLE.setDeviceName(BLE_Device_Name);
  Blynk_BLE.begin(auth);
#else
  if (digitalRead(WIFI_BLE_SELECTION_PIN) == HIGH)
  {
    USE_BLE = false;
    Serial.println(F("GPIO14 HIGH, Use WiFi"));
#if USE_BLYNK_WM
    // Set config portal channel, defalut = 1. Use 0 => random channel from 1-13 to avoid conflict
    Blynk_WF.setConfigPortalChannel(0);
  
    Blynk_WF.begin(BLE_Device_Name);
#else
    //Blynk_WF.begin(auth, ssid, pass);
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

  timer.setInterval(5000L, sendDatatoBlynk);
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
