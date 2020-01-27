/****************************************************************************************************************************
 *  Geiger_Counter_OLED.ino
 *  For ESP32 using WiFi and BlueTooth simultaneously
 *
 *  Library for inclusion of both ESP32 Blynk BT or BLE and WiFi libraries and run WiFi and BT/BLE simultaneously
 *  Forked from Blynk library v0.6.1 https://github.com/blynkkk/blynk-library/releases
 *  Built by Khoi Hoang https://github.com/khoih-prog/BlynkGSM_ESPManager
 *  Licensed under MIT license
 *  Version: 1.0.1
 *
 *  Based on orignal code by Crosswalkersam (https://community.blynk.cc/u/Crosswalkersam)
 *  posted in https://community.blynk.cc/t/select-connection-type-via-switch/43176
 *  Purpose: Use WiFi when posible by GPIO14 => HIGH or floating when reset.
 *           Use Bluetooth when WiFi not available (such as in the field) by by GPIO14 => LOW when reset.
 *
 *  Version Modified By   Date      Comments
 *  ------- -----------  ---------- -----------
 *  1.0.0   K Hoang      25/01/2020 Initial coding
 *  1.0.1   K Hoang      27/01/2020 Enable simultaneously running BT/BLE and WiFi
 *****************************************************************************************************************************/


#define BLYNK_PRINT Serial

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define BLYNK_USE_BT_ONLY      false    //true

#if BLYNK_USE_BT_ONLY
#include <BlynkSimpleEsp32_BT_WF.h>
#else
#include <BlynkSimpleEsp32_BT_WF.h>
#include <BlynkSimpleEsp32_WF.h>

char ssid[] = "SSID";
char pass[] = "PASS";
#endif

String cloudBlynkServer = "account.duckdns.org";
//String cloudBlynkServer = "192.168.2.110";
#define BLYNK_SERVER_HARDWARE_PORT    8080

// Blynk token shared between BT and WiFi
char auth[] = "****";

bool USE_BT = true;

#define WIFI_BT_SELECTION_PIN     14   //Pin D14 mapped to pin GPIO14/HSPI_SCK/ADC16/TOUCH6/TMS of ESP32
#define GEIGER_INPUT_PIN          18   // Pin D18 mapped to pin GPIO18/VSPI_SCK of ESP32
#define VOLTAGER_INPUT_PIN        36   // Pin D36 mapped to pin GPIO36/ADC0/SVP of ESP32  

// OLED SSD1306 128x32
#define OLED_RESET_PIN            4   // Pin D4 mapped to pin GPIO4/ADC10/TOUCH0 of ESP32
#define SCREEN_WIDTH              128
#define SCREEN_HEIGHT             32

#define CONV_FACTOR                   0.00658

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

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET_PIN);
BlynkTimer timer;

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
  if (USE_BT)
  {
    Blynk_BT.virtualWrite(V1, countPerMinute);
    Blynk_BT.virtualWrite(V3, radiationValue);
    Blynk_BT.virtualWrite(V5, radiationDose);
    Blynk_BT.virtualWrite(V7, voltage);
  }
  else
  {
    Blynk_WF.virtualWrite(V1, countPerMinute);
    Blynk_WF.virtualWrite(V3, radiationValue);
    Blynk_WF.virtualWrite(V5, radiationDose);
    Blynk_WF.virtualWrite(V7, voltage);
  }
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

void OLED_Display()
{
  display.setCursor(0, 0);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.print(countPerMinute, DEC);
  display.setCursor(40, 0);
  display.print("CPM");
  display.setCursor(0, 10);
  display.print(radiationDose, 3);
  display.setCursor(40, 10);
  display.print("uSv");
  display.setCursor(0, 20);
  display.println(voltage, 2);
  display.setCursor(40, 20);
  display.println("V");

  if ((radiationValue, 2) < 9.99)
  {
    display.setTextSize(2);
  }
  else
  {
    display.setTextSize(1);
  }

  display.setCursor(65, 10);
  display.print(radiationValue, 2);
  display.setTextSize(1);
  display.setCursor(90, 25);
  display.print("uSv/h");
  display.display();
}

#define USE_SIMULATION    false

void checkStatus()
{
  static float voltage;

  if (millis() - timePreviousMeassure > MEASURE_INTERVAL_MS)
  {
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
    OLED_Display();
    
    #if USE_SIMULATION
      count += 10;
      if (count >= 1000)
        count = 0;
    #else  
      count = 0;
    #endif
  }
}

void setup()
{
  Serial.begin(115200);
  Serial.println(F("\nStarting Geiger-Counter-OLED"));

  pinMode(GEIGER_INPUT_PIN, INPUT);
  attachInterrupt(GEIGER_INPUT_PIN, countPulse, HIGH);

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }
  display.display();
  delay(200);
  display.clearDisplay();

#if BLYNK_USE_BT_ONLY
  Blynk_BT.setDeviceName("GeigerCounter");
  Blynk_BT.begin(auth);
#else
  if (digitalRead(WIFI_BT_SELECTION_PIN) == HIGH)
  {
    Serial.println(F("GPIO14 HIGH, Use WiFi"));
    //Blynk_WF.begin(auth, ssid, pass);
    Blynk_WF.begin(auth, ssid, pass, cloudBlynkServer.c_str(), BLYNK_SERVER_HARDWARE_PORT);
    USE_BT = false;
  }
  else
  {
    Serial.println(F("GPIO14 LOW, Use BT"));
    Blynk_BT.setDeviceName("Geigercounter");
    Blynk_BT.begin(auth);
  }
#endif

  timer.setInterval(5000L, sendDatatoBlynk);
}

void loop()
{
  if (USE_BT)
    Blynk_BT.run();
  else
    Blynk_WF.run();

  timer.run();
  checkStatus();
}
